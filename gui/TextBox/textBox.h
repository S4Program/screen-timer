#pragma once

#include <sstream>
#include <windows.h>
#include <optional>

#include "../UIElement/uiElement.h"
#include "../LabelElement/labelElement.h"
#include "../MouseHandle/mouseHandle.h"

namespace gui
{

class TextBox : public gui::UIElement
{
public:
    bool getSet() { return isSet; };
    virtual int getType() { return gui::TEXTBOX; };

    virtual void draw(sf::RenderTarget &window, sf::RenderStates state) const;
    virtual void update();
    void getEvent(std::optional<sf::Event> event);

    virtual void setSize(sf::Vector2f size);
    virtual void setPosition(sf::Vector2f position);

    TextBox(sf::RenderWindow* window, sf::Vector2f size, sf::Color boxColor, sf::Color foreColor, sf::Font* font, float characterSize, std::string message = "", sf::Vector2f position = {0,0});
private:
#define _DELETE 8
#define ENTER 13
#define ESCAPE 27

    sf::Clock timer;

    std::string textValue = "";
    std::string defaultMessage; // message that appears when there're no text

    sf::RectangleShape box;

    gui::Label text;
    gui::MouseHandle boxFrame;

    sf::RenderWindow* window;

    bool isFocused = false;
    bool isSet = false;
    bool isFlick = false;

    int setTime = 0;

    void inputLogic(int charTyped);
    void fill();
};

}