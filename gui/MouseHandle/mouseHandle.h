#pragma once
#include "SFML/Graphics.hpp"
#include <vector>

namespace gui
{
class MouseHandle
{
private:
    sf::RectangleShape* hitbox;
    sf::RenderWindow* window;
    bool flag1 = !false,
         flag2 = !false;
public:
    sf::Vector2f getMousePos() { return (sf::Vector2f)sf::Mouse::getPosition(*window); };

    std::pair<bool, bool> isPressed();
    bool isHovered();
    std::pair<bool, bool> isClicked();

    MouseHandle(sf::RenderWindow* window, sf::RectangleShape* hitbox);
    MouseHandle(sf::RenderWindow* window);
};
}