#include "renderHandler.h"

RenderHandler::RenderHandler(sf::RenderWindow& window)
:
win(window)
{
}

void RenderHandler::draw(sf::Drawable* d, int priority)
{
    buffer[priority].push_back(d);
}

void RenderHandler::display()
{
    for(int i = 0; i < 9; i++)
    {
        for(const auto drawable : buffer[i])
        {
            win.draw(*drawable);
        }
        buffer[i].clear();
    }
    win.display();
    win.clear(sf::Color(200,200,200));
}