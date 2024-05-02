#include "Factory.h"

#ifndef VISUALIZER
#define VISUALIZER

struct Visualizer
{
    Font font;
    Texture image;
    Factory *factory;
    Sprite background;
    vector<Text> texts;
    RenderWindow *window;
    vector<string> counters;
    RectangleShape newOrder;

    Visualizer(RenderWindow *window)
    {
        image.loadFromFile("assets/images/back.jpg");
        font.loadFromFile("assets/fonts/font2.ttf");
        background.setTexture(image);

        counters = {
            "Orders\nCounter",
            "Cup Size\nCounter",
            "Flavours\nCounter",
            "Toppings\nCounter",
            "Delivery\nCounter",
            "Orders in\nQueue ",
            "Orders\nFinished ",
            "Place\nOrder",
        };

        texts.resize(counters.size());
        for (int i = 0; i < counters.size(); i++)
        {
            texts[i].setFont(font);
            texts[i].setCharacterSize(50);
            texts[i].setOutlineThickness(4);
            texts[i].setString(counters[i]);
            texts[i].setFillColor(Color::Blue);
            texts[i].setOutlineColor(Color::Magenta);

            if (i == counters.size() - 3)
                texts[i].setPosition(Vector2f(1300, 330));
            else if (i == counters.size() - 2)
                texts[i].setPosition(Vector2f(1300, 500));
            else if (i == counters.size() - 1)
                texts[i].setPosition(Vector2f(1350, 670));
            else
                texts[i].setPosition(Vector2f(80 + i * 240, 40));
        }

        factory = new Factory(window);

        for (int i = 0; i < factory->lines.size(); i++)
            factory->waitingQueue.push(new IceCream());

        newOrder.setOutlineThickness(-4.f);
        newOrder.setFillColor(Color::Green);
        newOrder.setSize(Vector2f(240, 120));
        newOrder.setOutlineColor(Color::White);
        newOrder.setPosition(Vector2f(1300, 670));
    }

    void setup()
    {
        // for (int i = 0; i < 4; i++)
        //     sem_init(&semaphores[i], 0, 1);

        pthread_t threads[6];
        pthread_create(threads + 0, NULL, handler1, factory);
        pthread_create(threads + 1, NULL, handler2, factory);
        pthread_create(threads + 2, NULL, handler3, factory);
        pthread_create(threads + 3, NULL, handler4, factory);
        pthread_create(threads + 4, NULL, handler5, factory);
        pthread_create(threads + 5, NULL, assignee, factory);
    }

    void run(bool x)
    {
        srand(time(0));

        while (window->isOpen())
        {
            Event event;
            while (window->pollEvent(event))
            {
                if (event.type == Event::Closed | Keyboard::isKeyPressed(Keyboard::Escape))
                    window->close();

                if (event.type == Event::MouseButtonPressed)
                {
                    Vector2f mouse = window->mapPixelToCoords(Mouse::getPosition(*window));

                    FloatRect bounds = newOrder.getGlobalBounds();

                    if (bounds.contains(mouse))
                        factory->waitingQueue.push(new IceCream());
                }
            }

            texts[5].setString(counters[5] + to_string(factory->waitingQueue.size()));
            texts[6].setString(counters[6] + to_string(factory->finished));

            window->clear(Color::Black);
            window->draw(background);

            // Draw all window objects from here

            window->draw(newOrder);

            for (int i = 0; i < texts.size(); i++)
                window->draw(texts[i]);

            for (int i = 0; i < factory->lines.size(); i++)
                factory->lines[i]->draw();

            // To here

            window->display();
        }
    }
};

#endif