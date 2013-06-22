#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "shareddefines.h"

class Player;

class Game
{
    public:
        Game();
        ~Game();

        int Update();
        bool IsRunning() { return isRunning; }
        void LoadMap();

        GameState GetGameState() { return gameState; }
        void SetGameState(GameState state) { gameState = state; }

        std::vector<sf::RectangleShape> &GetGameObjects() { return gameObjects; }
        void AddGameObject(sf::RectangleShape gameobject) { gameObjects.push_back(gameobject); }
        void ClearGameObjects() { gameObjects.clear(); }

    private:
        bool isRunning;
        GameState gameState;
        Player* player;
        std::vector<sf::RectangleShape> gameObjects;
};
