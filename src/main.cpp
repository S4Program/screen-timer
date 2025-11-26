#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <filesystem>

#include "../gui/TextBox/textBox.h"
#include "../extlibs/tinyfiledialogs/tinyfiledialogs.h"

bool loadUsersChoice(const char* filepath)
{
    FILE* read = NULL;
    int state = 1;
    if(fopen(filepath,"r"))
    {
        char inp[2];
        read = fopen(filepath,"r");
        fscanf(read,"%1s",inp);
        state = inp[0]-'0';
        std::cout << std::setw(8) << std::left << "[READ]" << "Successfully read user's choice"<<std::endl;
    }
    else
    {
        std::cout<<std::setw(8)<<std::left<<"[READ]" << "Couldn't open the file!"<<std::endl;
    }
    return state;
}

void saveUsersChoice(const char* folderpath, const char* filepath, bool state)
{
    FILE* write = NULL;
    std::filesystem::create_directories(folderpath);
    if(!fopen(filepath,"w"))
    {
        std::cout << std::setw(8) << std::left << "[WRITE]" << "Couldn't open the file!" << std::endl;
    }
    else
    {
        write = fopen(filepath,"w");
        fwrite(std::to_string(state).c_str(),1,1,write);
        std::cout << std::setw(8) << std::left << "[WRITE] Successfully saved user's choice" << std::endl;
    }
    fclose(write);
}

int main()
{
    sf::Font font;
    if(!font.openFromFile("../../gui/resources/fonts/ARIAL.TTF"))
        std::cerr<<"Failed to load a font!\n";

#ifdef WIN32
    const char* appdata = std::getenv("APPDATA");

    char folderpath[256];
    char filepath[256];

    strcpy(folderpath, appdata);
    strcpy(filepath, appdata);

    strcat(filepath, "\\ScreenTimer\\userchoice.cfg");
    strcat(folderpath, "\\ScreenTimer");

    std::cout<<"Filepath for user choice file: "<<filepath<<std::endl;
    std::cout<<"Folderpath for user choice file: "<<folderpath<<std::endl;
#endif

    //---Creating window context
    auto window = sf::RenderWindow(sf::VideoMode({160u, 50u}), "Screen Timer", sf::Style::None);
    window.setFramerateLimit(60);
    
    //---Setting up variables
    sf::Color backColor = sf::Color(240,240,240);
    sf::Color foreColor = sf::Color(95, 0, 0);

    //---Hitbox of the window
    sf::RectangleShape wbox(sf::Vector2f(window.getSize()));
    
    float outlineThickness = 8.f;
    sf::RectangleShape outline(sf::Vector2f(window.getSize()) - sf::Vector2f(outlineThickness, outlineThickness));
    outline.setOrigin(sf::Vector2f(outline.getSize().x / 2, outline.getSize().y / 2));
    outline.setPosition(sf::Vector2f(wbox.getSize().x / 2, wbox.getSize().y / 2));
    outline.setFillColor(backColor);
    outline.setOutlineColor(foreColor);
    outline.setOutlineThickness(outlineThickness);
    
    //---Capturing the hitbox of the window
    gui::MouseHandle mh(&window, &wbox); 
    sf::Vector2f grabPos={-1,-1};
    bool isHeld = false;

    //---Time textbox
    gui::TextBox iTime(&window, (sf::Vector2f)window.getSize(), sf::Color::Transparent, foreColor, &font, 30, "00:00:00");

    //---Welcome message box
    if(loadUsersChoice(filepath))
    {
        int state = tinyfd_messageBox(
            "Tutorial", 
            "Do you want to open a tutorial?\n(No - do not show this again)", 
            "yesno", 
            "question", 
            1
        );

        saveUsersChoice(folderpath, filepath, state);

        if(state)
        {
            tinyfd_messageBox(
            "Tutorial", 
            "How to use a screen timer:\n1) Left click on a textbox field\n2) Enter the time amount\n3) Press enter\n4) To exit a program RIGHT CLICK on a window\n\n    The project was made by S4Program", 
            "ok", 
            "info", 
            1
        );
        }
    }
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            iTime.getEvent(event);

            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        
        iTime.update();

        //---Closing the window with a right click
        if(mh.isPressed().second)
        {
            window.close();
            break;
        }

        //---Changing the state of the window to being held
        if(mh.isPressed().first && (mh.isHovered() || isHeld))
        {
            isHeld=true;
        }
        else
        {
            isHeld = false;
        }

        //---Is time set and is window being held with a left mouse
        if(isHeld && iTime.getSet())
        {
            if(grabPos == sf::Vector2f(-1,-1))
            {
                grabPos = mh.getMousePos();
            }
            window.setPosition((sf::Vector2i)((sf::Vector2f)window.getPosition() + mh.getMousePos() - grabPos));
        }
        else
        {
            grabPos = {-1,-1};
        }

        //---Drawing
        window.draw(outline);
        window.draw(iTime);
        window.display();
        window.clear(backColor);
    }
}
