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

Player::Player(Game* _game, sf::RenderWindow* _window)
{
    game = _game;
    window = _window;
    posX = 100.0f;
    posY = 300.0f;
    image.loadFromFile("Graphics/Character/helicopter_green.png");
    smokeTrailTimer = 200;
}

Player::~Player()
{

}

void Player::Update()
{
    if (game->GetGameState() == STATE_MAIN_MENU)
        return;

    if (game->GetGameState() == STATE_PLAYING)
    {
        posX += 6.0f;
        posY += 3.0f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            posY -= 6.0f;

        if (posX < 0.0f)
            posX = 0.1f;

        if (posY < 0.0f)
            posY = 0.1f;

        if (!smokeTrailTimer)
        {
            smokeTrailTimer = 200;
            game->AddSmokeTrail();
        }
    }

    sf::Sprite sprite(image);
    sprite.setPosition(posX, posY);
    window->draw(sprite);
}

void Player::HandleTimers(sf::Int32 diff_time)
{
    if (game->GetGameState() != STATE_PLAYING)
        return;

    if (diff_time >= smokeTrailTimer)
        smokeTrailTimer = 0;
    else
        smokeTrailTimer -= diff_time;
}
