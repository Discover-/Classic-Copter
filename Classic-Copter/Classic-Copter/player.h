#pragma once

#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include <time.h>
#include <unordered_map>
#include <set>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include "game.h"

class Player
{
    public:
        Player(Game* _game, sf::RenderWindow* _window);
        ~Player();

        void Update();

        float GetPositionX() { return posX; }
        float GetPositionY() { return posY; }
        void SetPositionX(float val) { posX = val; }
        void SetPositionY(float val) { posY = val; }

    private:
        Game* game;
        sf::RenderWindow* window;
        float posX, posY;
        sf::Texture image;
};
