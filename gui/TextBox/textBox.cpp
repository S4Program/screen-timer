#include "textbox.h"

void gui::TextBox::draw(sf::RenderTarget &window, sf::RenderStates state) const
{
    window.draw(box);
    window.draw(text);
}

void gui::TextBox::setSize(sf::Vector2f size)
{
    box.setSize(size);
    text.setSize(size);
}

void gui::TextBox::setPosition(sf::Vector2f position)
{
    box.setPosition(position);
    text.setPosition
    (
        sf::Vector2f(position.x, text.getSize().y/2.f + position.y)
    );
}

void gui::TextBox::update()
{
    SetWindowPos(window->getNativeHandle(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    isFocused = (boxFrame.isClicked().first | isFocused & !(boxFrame.isPressed().first & !boxFrame.isHovered())) & !isSet;
    if(isFocused)
    {
        this->text.setMessage(textValue + (isFlick ? "|" : ""));
        this->text.getText().setStyle(sf::Text::Regular);

        if(timer.getElapsedTime().asSeconds() >= 1)
        {
            isFlick = !isFlick;
            timer.restart();
        }
    }
    else
    {
        if(isSet)
        {
            std::string newText="00:00:00";
            newText[0]=setTime/3600/10+'0';
            newText[1]=setTime/3600%10+'0';
            newText[3]=setTime%3600/60/10+'0';
            newText[4]=setTime%3600/60%10+'0';
            newText[6]=setTime%60/10+'0';
            newText[7]=setTime%60%10+'0';

            this->text.setMessage(newText);

            if(setTime == 0)
            {
                isSet = false;
                textValue = "";
                defaultMessage = "00:00:00";

                timer.restart();
                window->setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().size.x/2 - window->getSize().x/2, sf::VideoMode::getDesktopMode().size.y/2 - window->getSize().y/2));
                return;
            }

            if(timer.getElapsedTime().asSeconds() >= 1.f)
            {
                timer.restart();
                setTime--;
            }
        }
        else if(textValue.size() == 0) 
        {
            this->text.setMessage(defaultMessage);
            // this->text.getText().setStyle(sf::Text::Italic);
        }
        else
        {
            this->text.setMessage(textValue);
            this->text.getText().setStyle(sf::Text::Regular);
        }
    }
}

void gui::TextBox::getEvent(std::optional<sf::Event> event)
{
    if(isFocused && event->is<sf::Event::TextEntered>())
    {
        inputLogic(event->getIf<sf::Event::TextEntered>()->unicode);
    }
}

void gui::TextBox::inputLogic(int charTyped)
{

    if(!(charTyped >= 48 && charTyped <= 57 || charTyped == _DELETE || charTyped == ENTER || charTyped == ESCAPE))
    {
        return;
    }

    if(charTyped != _DELETE && charTyped != ENTER && charTyped != ESCAPE && textValue.size() < 8)
    {
        textValue.push_back(charTyped);
        if(textValue.size() == 2 || textValue.size() == 5)
        {
            textValue.push_back(':');
        }
    }
    else if(charTyped == _DELETE && textValue.size() > 0)
    {
        if(textValue.back() == ':')
        {
            textValue.pop_back();
        }
        textValue.pop_back();
    }
    else if(charTyped == ENTER)
    {
        fill();
        isFocused = false;
        isSet = true;

        setTime = 60*60*10 * (textValue[0]-'0') + 60*60 * (textValue[1]-'0') + 60*10 * (textValue[3]-'0') + 60 * (textValue[4]-'0') + 10 * (textValue[6]-'0') + (textValue[7]-'0');
        timer.restart();
    }

    text.setMessage(textValue);
}

void gui::TextBox::fill()
{
    while(textValue.size() < 8)
    {
        inputLogic('0');
    }
}


gui::TextBox::TextBox(sf::RenderWindow* window, sf::Vector2f size, sf::Color boxColor, sf::Color foreColor, sf::Font* font, float characterSize, std::string defaultMessage, sf::Vector2f position)
:
window(window),
box(size),
text(characterSize, foreColor, font, "..."),
boxFrame(window, &box),
defaultMessage(defaultMessage)
{
    box.setFillColor(boxColor);

    text.setPosition
    (
        sf::Vector2f(box.getPosition().x + box.getSize().x / 2 - 6*text.getText().getLocalBounds().size.x/2, box.getPosition().y + box.getSize().y / 2 - 12*text.getText().getLocalBounds().size.y / 2)
    );
}