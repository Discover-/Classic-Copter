#pragma once

#include <vector>
#include <array>
#include <SFML/Graphics.hpp>
#include "shareddefines.h"
#include "game.h"

class Menu
{
    public:
        Menu(Game* _game);
        ~Menu();

        void Load();
        void Update(sf::RenderWindow &window);

        int GetSelectedOption() { return selectedOption; }
        void SetSelectedOption(int val) { selectedOption = val; }

        void PressedEnterOrMouse(sf::RenderWindow &window);

    private:
        Game* game;
        sf::Font font;
        std::vector<MenuButtonInfo> menuButtons;
        int selectedOption;
        sf::Vector2i prevMousePos;
};
