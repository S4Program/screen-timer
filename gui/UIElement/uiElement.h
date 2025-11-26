#pragma once
#include "SFML/Graphics.hpp"
#include "elementList.h"

namespace gui
{

class UIElement : public sf::Drawable
{   
public:
    virtual sf::Vector2f getSize() { return size; };
    virtual sf::Vector2f getPadding() { return padding; };
    virtual int getType() = 0;

    virtual void draw(sf::RenderTarget &window, sf::RenderStates state) const = 0;
    virtual void update() = 0;

    virtual void setSize(sf::Vector2f size) = 0;
    virtual void setPosition(sf::Vector2f position) = 0;
    void setPadding(sf::Vector2f padding);
    virtual void pack(sf::Vector2f padding);

    UIElement(sf::Vector2f padding, sf::Vector2f size);
    UIElement(sf::Vector2f size = {0,0});
protected:
    sf::Vector2f padding = {0, 0};
    sf::Vector2f size;
};

}