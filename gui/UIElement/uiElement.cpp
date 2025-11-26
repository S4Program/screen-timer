#include "uiElement.h"

gui::UIElement::UIElement(sf::Vector2f padding, sf::Vector2f size)
:
padding(padding),
size(size)
{}

gui::UIElement::UIElement(sf::Vector2f size)
:
size(size)
{}

void gui::UIElement::pack(sf::Vector2f padding)
{
    this->padding = padding;
    setPosition(padding);
}

void gui::UIElement::setPadding(sf::Vector2f padding)
{
    this->padding = padding;
}