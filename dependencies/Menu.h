#include "Visualizer.h"

#ifndef MENU
#define MENU

struct Menu
{
    RectangleShape menu;
    RenderWindow *window;

    Font font;
    Music music;
    Texture image;
    Sprite background;

    Menu()
    {
        font.loadFromFile("assets/fonts/font2.ttf");
        image.loadFromFile("assets/images/back.jpg");
        music.openFromFile("assets/sounds/gottrim.wav");

        background.setTexture(image);

        window = new RenderWindow(
            VideoMode(1600, 900),
            "Ice Cream Factory",
            Style::Titlebar | Style::Close);
    }

    void draw()
    {
        music.setLoop(true);
        music.play();
        music.setPitch(1.3);

        Visualizer visualizer(window);

        Text multiThreadedText("Multi Threaded", font, 60);
        multiThreadedText.setPosition(350, 200);
        multiThreadedText.setFillColor(Color::White);

        Text singleThreadedText("Single Threaded", font, 60);
        singleThreadedText.setPosition(350, 350);
        singleThreadedText.setFillColor(Color::White);

        while (window->isOpen())
        {
            Event event;
            while (window->pollEvent(event))
            {
                FloatRect multiThreadedBounds = multiThreadedText.getGlobalBounds();
                FloatRect singleThreadedBounds = singleThreadedText.getGlobalBounds();

                if (event.type == Event::Closed)
                    window->close();

                else if (event.type == Event::MouseButtonPressed)
                {

                    if (multiThreadedBounds.contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        visualizer.setup(2);
                        visualizer.run();
                    }

                    else if (singleThreadedBounds.contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        visualizer.setup(1);
                        visualizer.run();
                    }
                }

                else if (event.type == Event::MouseMoved)
                {

                    if (multiThreadedBounds.contains(event.mouseMove.x, event.mouseMove.y))
                        multiThreadedText.setFillColor(Color::Yellow);

                    else if (singleThreadedBounds.contains(event.mouseMove.x, event.mouseMove.y))
                        singleThreadedText.setFillColor(Color::Yellow);

                    else
                    {
                        multiThreadedText.setFillColor(Color::White);
                        singleThreadedText.setFillColor(Color::White);
                    }
                }
            }

            window->clear();
            window->draw(background);

            window->draw(multiThreadedText);
            window->draw(singleThreadedText);

            window->display();
        }
    }
};

#endif
