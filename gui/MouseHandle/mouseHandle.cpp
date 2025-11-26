#include "mouseHandle.h"

bool gui::MouseHandle::isHovered()
{
    return hitbox->getGlobalBounds().contains(getMousePos());
}

std::pair<bool, bool> gui::MouseHandle::isPressed()
{
    return {sf::Mouse::isButtonPressed(sf::Mouse::Button::Left), sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)};
}

std::pair<bool, bool> gui::MouseHandle::isClicked()
{
    bool res1 = isHovered() && isPressed().first && flag1,
         res2 = isHovered() && isPressed().second && flag2;
    
    if(isHovered() && isPressed().first) flag1 = false;
    else flag1 = true;
    if(isHovered() && isPressed().second) flag2 = false;
    else flag2 = true;

    return {res1, res2};
}

gui::MouseHandle::MouseHandle(sf::RenderWindow* window, sf::RectangleShape* hitbox)
:
window(window),
hitbox(hitbox)
{
    
}

gui::MouseHandle::MouseHandle(sf::RenderWindow* window)
:
window(window)
{
    
}