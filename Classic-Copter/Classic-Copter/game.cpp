#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include <time.h>
#include <unordered_map>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include "game.h"
#include "player.h"
#include "menu.h"

Game::Game()
{
    player = NULL;
    isRunning = true;
    gameState = STATE_MAIN_MENU;
    showDebugInfo = true;
}

Game::~Game()
{
    delete player;
}

int Game::Update()
{
    sf::Clock clockStart, fpsClock;
    clockStart.restart();

    sf::RenderWindow window(sf::VideoMode(1000, 600), "Classic-Copter C++ SFML", sf::Style::Close);
    window.setFramerateLimit(30);

    sf::View view(window.getDefaultView());
    player = new Player(this, &window);

    LoadMap();

    sf::Font font;
    font.loadFromFile("Fonts/Market_Deco.ttf");

    Menu* menu = new Menu(this);

    std::cout << "Time in milliseconds taken to load everything before entering while-loop: " << clockStart.restart().asMilliseconds() << std::endl;

    while (window.isOpen())
    {
        sf::Event _event;
        window.clear(sf::Color::Black);
        fpsClock.restart();

        while (window.pollEvent(_event))
        {
            switch (_event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::LostFocus:
                    if (gameState == STATE_PLAYING)
                        gameState = STATE_PAUSED_FOCUS;
                    break;
                case sf::Event::GainedFocus:
                    if (gameState == STATE_PAUSED_FOCUS)
                        gameState = STATE_PLAYING;
                    break;
                case sf::Event::KeyReleased:
                {
                    switch (_event.key.code)
                    {
                        //! Turn on/off debug information
                        case sf::Keyboard::F3:
                        {
                            showDebugInfo = !showDebugInfo;
                            break;
                        }
                        //! Pause or un-pause game based on current gamestate.
                        case sf::Keyboard::Escape:
                        {
                            if (gameState != STATE_MAIN_MENU)
                                gameState = gameState == STATE_PLAYING ? STATE_PAUSED : STATE_PLAYING;
                            else
                                window.close();
                            break;
                        }
                        //! Re-start game when pressing Enter after we died
                        case sf::Keyboard::Return:
                        {
                            switch (gameState)
                            {
                                case STATE_GAME_OVER:
                                {
                                    player->SetPosition(100.0f, 300.0f);
                                    gameState = STATE_PLAYING;
                                    break;
                                }
                                case STATE_MAIN_MENU:
                                {
                                    menu->PressedEnterOrMouse(window);
                                    break;
                                }
                                default:
                                    break;
                            }
                            break;
                        }
                        default:
                            break;
                    }
                    break;
                }
                case sf::Event::MouseButtonPressed:
                {
                    switch (_event.mouseButton.button)
                    {
                        //! Select menu option
                        case sf::Mouse::Left:
                            if (gameState == STATE_MAIN_MENU)
                                menu->PressedEnterOrMouse(window);
                            break;
                    }
                    break;
                }
            }
        }

        if (gameState != STATE_MAIN_MENU)
        {
            for (std::vector<sf::RectangleShape>::iterator itr = gameObjects.begin(); itr != gameObjects.end(); ++itr)
                if (IsInRange(player->GetPositionX(), (*itr).getPosition().x, player->GetPositionY(), (*itr).getPosition().y, 1000.0f))
                    window.draw(*itr);
        }

        switch (gameState)
        {
            case STATE_MAIN_MENU:
            {
                menu->Update(window);
                break;
            }
            case STATE_PLAYING:
            {
                player->Update();

                if (player->GetPositionX() > window.getSize().x / 2.f)
                    view.setCenter(player->GetPositionX(), view.getCenter().y);
                else
                    view.setCenter(window.getSize().x / 2.f, view.getCenter().y);

                if (player->GetPositionY() > window.getSize().y / 2.f)
                    view.setCenter(view.getCenter().x, player->GetPositionY());
                else
                    view.setCenter(view.getCenter().x, window.getSize().y / 2.f);

                window.setView(view);

                for (std::vector<sf::RectangleShape>::iterator itr = gameObjects.begin(); itr != gameObjects.end(); ++itr)
                {
                    if (IsInRange(player->GetPositionX(), (*itr).getPosition().x, player->GetPositionY(), (*itr).getPosition().y, 100.0f))
                    {
                        if (WillCollision(player->GetPositionX(), player->GetPositionY(), 50.0f, 100.0f, (*itr).getPosition().x, (*itr).getPosition().y, (*itr).getGlobalBounds().height, (*itr).getGlobalBounds().width))
                        {
                            gameState = STATE_GAME_OVER;
                            break;
                        }
                    }
                }
                break;
            }
            case STATE_PAUSED:
            case STATE_PAUSED_FOCUS:
            {
                player->Update();

                sf::Text textPaused("Paused", font, 60);
                textPaused.setColor(sf::Color::White);
                textPaused.setPosition(view.getCenter().x - (textPaused.getLocalBounds().width / 2.0f), view.getCenter().y - (textPaused.getLocalBounds().height / 2.0f));
                window.draw(textPaused);

                sf::Text textPaused1(gameState == STATE_PAUSED_FOCUS ? "Focus on this screen again in order to continue" : "Press Escape in order to continue", font, 20);
                textPaused1.setColor(sf::Color::White);
                textPaused1.setPosition(view.getCenter().x - (textPaused1.getLocalBounds().width / 2.0f), view.getCenter().y - (textPaused1.getLocalBounds().height / 2.0f) + 60.0f);
                window.draw(textPaused1);
                break;
            }
            case STATE_GAME_OVER:
            {
                player->Update();

                sf::Text textGameOver("Game Over!", font, 60);
                textGameOver.setColor(sf::Color::White);
                textGameOver.setPosition(view.getCenter().x - (textGameOver.getLocalBounds().width / 2.0f), view.getCenter().y - (textGameOver.getLocalBounds().height / 2.0f));
                window.draw(textGameOver);

                sf::Text textGameOver1("Press Enter to start over", font, 20);
                textGameOver1.setColor(sf::Color::White);
                textGameOver1.setPosition(view.getCenter().x - (textGameOver1.getLocalBounds().width / 2.0f), view.getCenter().y - (textGameOver1.getLocalBounds().height / 2.0f) + 60.0f);
                window.draw(textGameOver1);
                break;
            }
            default:
                std::cout << "Unknown gamestate " << gameState << std::endl;
                break;
        }

        if (showDebugInfo)
        {
            sf::Text text("Position X: " + std::to_string(static_cast<long long>(player->GetPositionX())) + "\nPosition Y: " + std::to_string(static_cast<long long>(player->GetPositionY())), font, 15);
            text.setColor(sf::Color::White);
            text.setPosition(view.getCenter().x + 375.0f, view.getCenter().y - 300.0f);
            window.draw(text);

            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            sf::Text text3("Mouse X: " + std::to_string(static_cast<long long>(mousePos.x)) + "\nMouse Y: " + std::to_string(static_cast<long long>(mousePos.y)), font, 15);
            text3.setColor(sf::Color::White);
            text3.setPosition(view.getCenter().x + 375.0f, view.getCenter().y - 265.0f);
            window.draw(text3);

            float fps = 1 / fpsClock.getElapsedTime().asSeconds();
            sf::Text text2("FPS: " + std::to_string(static_cast<long long>(fps)), font, 15);
            text2.setColor(sf::Color::White);
            text2.setPosition(view.getCenter().x + 375.0f, view.getCenter().y - 230.0f);
            window.draw(text2);
        }

        window.display();
    }

    return 0;
}

void Game::LoadMap()
{
    sf::Clock _clock;
    _clock.restart();
    std::vector<std::vector<std::string>> tilesInfoLayers;
    std::vector<std::string> tilesInfoBlocks;
    std::ifstream openfile("level.txt");
    std::stringstream lineStream;
    std::string line;

    while (std::getline(openfile, line))
    {
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] != ' ')
            {
                lineStream << line[i];
                tilesInfoBlocks.push_back(lineStream.str());
                lineStream.str(std::string());
            }
        }

        tilesInfoLayers.push_back(tilesInfoBlocks);
        tilesInfoBlocks.clear();
    }

    gameObjects.clear();

    for (int i = 0; i < tilesInfoLayers.size(); i++)
    {
        for (int j = 0; j < tilesInfoLayers[i].size(); j++)
        {
            if (tilesInfoLayers[i][j] == "_")
                continue;

            sf::RectangleShape gameobjectRect;

            if (tilesInfoLayers[i][j] == "!")
            {
                gameobjectRect.setSize(sf::Vector2f(25.0f, 25.0f));
                gameobjectRect.setFillColor(sf::Color::Green);
            }
            else
            {
                std::cout << "Unkown type ID found in level.txt, letter '" + tilesInfoLayers[i][j] + "'." << std::endl;
                continue;
            }

            gameobjectRect.setPosition(sf::Vector2f(j * 25.0f, i * 25.0f));
            gameObjects.push_back(gameobjectRect);
        }
    }

    std::cout << "Time in milliseconds taken to load level.txt: " << _clock.restart().asMilliseconds() << std::endl;
}
