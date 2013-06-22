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
    posX = 300.0f;
    posY = 300.0f;
    image.loadFromFile("Graphics/Character/helicopter_green.png");
}

Player::~Player()
{

}

void Player::Update()
{
    posX += 6.0f;
    posY += 3.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        posY -= 6.0f;

    sf::Sprite sprite(image);
    sprite.setPosition(posX, posY);
    window->draw(sprite);
}
