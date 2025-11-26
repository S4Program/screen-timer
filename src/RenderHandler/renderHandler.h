#pragma once
#include <SFML/Graphics.hpp>

class RenderHandler
{
public:
    RenderHandler(sf::RenderWindow& window);
    void draw(sf::Drawable* d, int priority);
    void display();

    sf::RenderWindow& getWindow() { return win; };
private:
    sf::RenderWindow& win;
    std::vector<sf::Drawable*> buffer[9];
};