#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

enum GameState
{
    STATE_MAIN_MENU     = 0,
    STATE_PAUSED        = 1,
    STATE_PAUSED_FOCUS  = 2,
    STATE_PLAYING       = 3,
    STATE_GAME_OVER     = 4,
};

#define GAME_STATE_DRAW_GAME(x) (x == STATE_PAUSED || x == STATE_PAUSED_FOCUS || x == STATE_PLAYING)
#define GAME_STATE_PAUSED(x) (x == STATE_PAUSED || x == STATE_PAUSED_FOCUS)

struct MenuButtonInfo
{
    int id;
    sf::RectangleShape rectShape;
    sf::Text textShape;
};

inline int urand(int min, int max)
{
    return (rand() % (max - min + 1) + min);
}

inline bool IsInRange(float currX, float xDest, float currY, float yDest, float distance)
{
    return ((currX < xDest - distance && currX > xDest + distance && currY < yDest - distance && currY > yDest + distance) ||
            (currX > xDest - distance && currX < xDest + distance && currY > yDest - distance && currY < yDest + distance));
}

inline bool WillCollision(float x1, float y1, float h1, float w1, float x2, float y2, float h2, float w2)
{
    return !(y1 >= y2 + h2 || x1 >= x2 + w2 || y1 + h1 <= y2 || x1 + w1 <= x2);
}
