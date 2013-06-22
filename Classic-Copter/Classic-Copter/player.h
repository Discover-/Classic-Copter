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
        void HandleTimers(sf::Int32 diff_time);

        float GetPositionX() { return posX; }
        float GetPositionY() { return posY; }
        void SetPositionX(float val) { posX = val; }
        void SetPositionY(float val) { posY = val; }
        void SetPosition(float valX, float valY) { posX = valX; posY = valY; }

    private:
        Game* game;
        sf::RenderWindow* window;
        float posX, posY;
        sf::Texture image;
        sf::Int32 smokeTrailTimer;
};
