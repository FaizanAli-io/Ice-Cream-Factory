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

    Texture cone_t;
    Sprite cone_s[3];

    Menu()
    {
        cone_t.loadFromFile("assets/images/cone.png");

        for (int i = 0; i < 3; i++)
            cone_s[i].setTexture(cone_t);

        cone_s[0].setScale(0.2, 0.2);
        cone_s[1].setScale(0.25, 0.25);
        cone_s[2].setScale(0.3, 0.3);

        cone_s[0].setPosition(448.8, 398.8);
        cone_s[1].setPosition(736, 386);
        cone_s[2].setPosition(1023.2, 373.2);

        menu.setOutlineThickness(-4.f);
        menu.setFillColor(Color::White);
        menu.setSize(Vector2f(900, 300));
        menu.setOutlineColor(Color::Black);
        menu.setPosition(Vector2f(350, 300));
    }

    void draw(RenderWindow *window)
    {
        window->draw(menu);
        window->draw(cone_s[0]);
        window->draw(cone_s[1]);
        window->draw(cone_s[2]);
    }
};

#endif