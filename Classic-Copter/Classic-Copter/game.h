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

        GameState GetGameState() { return gameState; }
        void SetGameState(GameState state) { gameState = state; }

    private:
        bool isRunning;
        GameState gameState;
        Player* player;
};
