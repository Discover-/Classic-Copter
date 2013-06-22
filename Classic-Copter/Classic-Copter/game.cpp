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

}

int Game::Update()
{
    sf::Clock clockStart;
    clockStart.restart();

    sf::RenderWindow window(sf::VideoMode(1000, 600), "Classic-Copter C++ SFML", sf::Style::Close);
    window.setFramerateLimit(30);

    sf::View view(window.getDefaultView());
    player = new Player(this, &window);

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

                if (player->GetPositionX() > window.getSize().x / 2.f + 400.0f)
                    view.setCenter(player->GetPositionX(), view.getCenter().y);
                else
                    view.setCenter(window.getSize().x / 2.f + 400.0f, view.getCenter().y);

                if (player->GetPositionY() > window.getSize().y / 2.f)
                    view.setCenter(view.getCenter().x + 400.0f, player->GetPositionY());
                else
                    view.setCenter(view.getCenter().x + 400.0f, window.getSize().y / 2.f);

                window.setView(view);
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
