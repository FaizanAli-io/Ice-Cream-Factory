#include "Menu.h"

#include <unistd.h>

#ifndef ASSEMBLYLINE
#define ASSEMBLYLINE

vector<string> status = {
    "Reading\norder",
    "Setting\ncup size",
    "Adding\nflavour",
    "Adding\ntopping",
};

struct AssemblyLine
{
    int index;
    int stage = 0;
    int steps = 200;
    bool free = true;

    Font font;
    Text text;
    RenderWindow *window;
    RectangleShape box, order;

    AssemblyLine(int i, RenderWindow *win) : index(i), window(win)
    {
        box.setOutlineThickness(-4.f);
        box.setSize(Vector2f(1160, 80));
        box.setFillColor(Color(0, 0, 255));
        box.setOutlineColor(Color(255, 0, 0));
        box.setPosition(Vector2f(80, 280 + (160 * index)));

        order.setOutlineThickness(-4.f);
        order.setFillColor(Color::Black);
        order.setSize(Vector2f(160, 120));
        order.setOutlineColor(Color::White);

        font.loadFromFile("assets/fonts/font3.ttf");

        text.setFont(font);
        text.setCharacterSize(25);
        text.setOutlineThickness(4);
        text.setFillColor(Color::Green);

        reset();
    }

    void reset()
    {
        stage = 0;
        text.setString("Waiting\nfor order");
        text.setPosition(Vector2f(120, 285 + (160 * index)));
        order.setPosition(Vector2f(80, 260 + (160 * index)));
    }

    void progress()
    {
        text.setString(status[stage++]);
        for (int i = 0; i < steps; i++)
        {
            order.move(Vector2f(1.25, 0));
            text.move(Vector2f(1.25, 0));
            usleep(10 * 1000);
        }
    }

    void draw()
    {
        window->draw(box);
        window->draw(order);
        window->draw(text);
    }
};

#endif