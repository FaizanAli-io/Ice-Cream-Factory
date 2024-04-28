#include <vector>
#include <iostream>
using namespace std;

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;

#ifndef MENU
#define MENU

struct Menu
{
    RectangleShape menu;
    RenderWindow *window;

    Texture cone_t;
    Sprite cone_s[3];

    Menu()
    {
        window = new RenderWindow(VideoMode(1600, 900), "Data Structure Visualizer", Style::Titlebar | Style::Close);
    
        // cone_t.loadFromFile("assets/images/cone.png");

        for (int i = 0; i < 3; i++)
            cone_s[i].setTexture(cone_t);

        cone_s[0].setScale(0.2, 0.2);
        cone_s[1].setScale(0.25, 0.25);
        cone_s[2].setScale(0.3, 0.3);

        cone_s[0].setPosition(448.8, 398.8);
        cone_s[1].setPosition(736, 386);
        cone_s[2].setPosition(1023.2, 373.2);
        cone_s[1].setColor(Color::Red);
        cone_s[2].setColor(Color::Blue);
        

        float w = window->getSize().x;
        int h = window->getSize().y;

        menu.setSize(Vector2f(w, h));
        menu.setFillColor(Color(100, 100,  100));
        

        
    }

    void draw()
    {
        window->clear();
        window->draw(menu);
        window->draw(cone_s[0]);
        window->draw(cone_s[1]);
        window->draw(cone_s[2]);
         Event event;
    while (window->pollEvent(event))
    {
        if (event.type == Event::MouseButtonPressed)
        {
            
            Vector2f mousePos = window->mapPixelToCoords(Mouse::getPosition(*window));

            
            for (int i = 0; i < 3; i++)
            {
                if (cone_s[i].getGlobalBounds().contains(mousePos))
                {
                    
                    cone_s[i].setColor(Color::Red); 
                }
            }
        }
    }

        window->display();
    }
};
#endif
