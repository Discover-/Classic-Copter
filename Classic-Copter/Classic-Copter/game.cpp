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

Game::Game()
{
    player = NULL;
    isRunning = true;
    gameState = STATE_PLAYING;
}

Game::~Game()
{
    delete player;
}

int Game::Update()
{
    sf::Clock clockStart;
    clockStart.restart();

    sf::RenderWindow window(sf::VideoMode(1000, 600), "Classic-Copter C++ SFML", sf::Style::Close);
    window.setFramerateLimit(30);

    sf::View view(window.getDefaultView());
    player = new Player(this, &window);

    LoadMap();

    std::cout << "Time in milliseconds taken to load everything before entering while-loop: " << clockStart.restart().asMilliseconds() << std::endl;

    while (window.isOpen())
    {
        sf::Event _event;
        window.clear(sf::Color::Black);

        while (window.pollEvent(_event))
        {
            switch (_event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        switch (gameState)
        {
            case STATE_MAIN_MENU:
            {
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
                    if (IsInRange(player->GetPositionX(), (*itr).getPosition().x, player->GetPositionY(), (*itr).getPosition().y, 1000.0f))
                        window.draw(*itr);
                break;
            }
            case STATE_PAUSED:
            case STATE_PAUSED_FOCUS:
            {
                break;
            }
            default:
                std::cout << "Unknown gamestate " << gameState << std::endl;
                break;
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
