#include "player.h"
#include "game.h"
#include "menu.h"

Menu::Menu(Game* _game)
{
    game = _game;
    selectedOption = 1;
    Load();
}

Menu::~Menu()
{

}

void Menu::Load()
{
    menuButtons.clear();
    MenuButtonInfo menuButtonInfo;

    font.loadFromFile("Fonts/Market_Deco.ttf");

    sf::RectangleShape rectangleBackground(sf::Vector2f(400.0f, 500.0f));
    rectangleBackground.setFillColor(sf::Color(255, 255, 255, 128));
    rectangleBackground.setPosition(rectangleBackground.getLocalBounds().width / 2.0f, rectangleBackground.getLocalBounds().height / 2.0f);
    menuButtonInfo.rectShape = rectangleBackground;
    menuButtonInfo.textShape = sf::Text("", font, 15);
    menuButtonInfo.id = 0;
    menuButtons.push_back(menuButtonInfo);

    sf::RectangleShape rectangleButtons(sf::Vector2f(300.0f, 50.0f));
    sf::Text textButtons("", font, 30);
    textButtons.setColor(sf::Color::Black);
    textButtons.setPosition(textButtons.getLocalBounds().width / 2.0f, textButtons.getLocalBounds().height / 2.0f);
                
    rectangleButtons.setFillColor(sf::Color::White);

    rectangleButtons.setPosition(rectangleButtons.getLocalBounds().width / 2.0f, rectangleButtons.getLocalBounds().height / 2.0f + 150.0f);
    textButtons.setPosition(rectangleButtons.getLocalBounds().width / 2.0f - 80.0f, rectangleButtons.getLocalBounds().height / 2.0f + 145.0f);
    textButtons.setString("Play Game");
    menuButtonInfo.rectShape = rectangleButtons;
    menuButtonInfo.textShape = textButtons;
    menuButtonInfo.id++;
    menuButtons.push_back(menuButtonInfo);

    rectangleButtons.setPosition(rectangleButtons.getLocalBounds().width / 2.0f, rectangleButtons.getLocalBounds().height / 2.0f + 50.0f);
    textButtons.setPosition(rectangleButtons.getLocalBounds().width / 2.0f - 80.0f, rectangleButtons.getLocalBounds().height / 2.0f + 45.0f);
    textButtons.setString("Exit Game");
    menuButtonInfo.rectShape = rectangleButtons;
    menuButtonInfo.textShape = textButtons;
    menuButtonInfo.id++;
    menuButtons.push_back(menuButtonInfo);
}

void Menu::Update(sf::RenderWindow &window)
{
    sf::Vector2i currMousePos = sf::Mouse::getPosition(window);
    sf::View view = window.getView();

    for (std::vector<MenuButtonInfo>::iterator itr = menuButtons.begin(); itr != menuButtons.end(); ++itr)
    {
        sf::Vector2f itrRectPos = (*itr).rectShape.getPosition();
        sf::RectangleShape itrRectCopy = (*itr).rectShape;
        itrRectCopy.setPosition(view.getCenter().x - itrRectPos.x, view.getCenter().y - itrRectPos.y);
        sf::Text itrTextCopy = (*itr).textShape;
        itrTextCopy.setPosition(view.getCenter().x - itrTextCopy.getPosition().x, view.getCenter().y - itrTextCopy.getPosition().y);

        if (selectedOption == (*itr).id)
            itrRectCopy.setFillColor(sf::Color::White);

        if ((*itr).id && WillCollision(float(currMousePos.x), float(currMousePos.y), 16.0f, 16.0f, itrRectCopy.getPosition().x, itrRectCopy.getPosition().y, itrRectCopy.getLocalBounds().height, itrRectCopy.getLocalBounds().width))
        {
            selectedOption = (*itr).id;
            itrRectCopy.setFillColor(sf::Color::Green);
        }

        window.draw(itrRectCopy);

        if ((*itr).id)
            window.draw(itrTextCopy);
    }
}

void Menu::PressedEnterOrMouse(sf::RenderWindow &window)
{
    switch (selectedOption)
    {
        case 0: //! Background
            break;
        case 1: //! Play Game
            game->SetGameState(STATE_PLAYING);
            break;
        case 2: //! Exit Game
            window.close();
            break;
    }
}

void Menu::UpdateSelection(bool moveNegative)
{
    if (moveNegative)
        selectedOption -= 1;
    else
        selectedOption += 1;
}
