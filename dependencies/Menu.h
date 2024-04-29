#include <vector>
#include <iostream>
using namespace std;

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;
#include "Visualizer.h"
#ifndef MENU
#define MENU

struct Menu
{
    RectangleShape menu;
    RenderWindow *window;

    Texture image;
    Music music;
    
   Font font;
    Sprite background;
    
    Text selectedOption;
    bool multiThreadedSelected = false;

    Menu()
    {   
        image.loadFromFile("assets/images/back.jpg");
        background.setTexture(image);
        font.loadFromFile("assets/fonts/font2.ttf");
        window=new  RenderWindow(sf::VideoMode(1600, 900), "Menu");
        music.openFromFile("assets/sounds/gottrim.wav");
    
    
 }

    void draw()
    {
        music.setLoop(true);
        music.play();
        music.setPitch(1.3);

        sf::Text multiThreadedText("Multi Threaded", font, 60);
        multiThreadedText.setPosition(350, 200);
        multiThreadedText.setFillColor(sf::Color::White);

        Text singleThreadedText("Single Threaded", font,60);
        singleThreadedText.setPosition(350, 350);
        singleThreadedText.setFillColor(sf::Color::White);

        Text selectedOption;
        bool multiThreadedSelected = false;
        while (window->isOpen())
        {
           
            sf::Event event;
            while (window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window->close();
                else if (event.type == sf::Event::MouseButtonPressed)
                {
                    sf::FloatRect multiThreadedBounds = multiThreadedText.getGlobalBounds();
                    FloatRect singleThreadedBounds = singleThreadedText.getGlobalBounds();

                    if (multiThreadedBounds.contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        multiThreadedSelected = true;
                        selectedOption = multiThreadedText;
                        Visualizer viz;
                        viz.setup();//mutithreaded
                        viz.run();
                    }
                    else if (singleThreadedBounds.contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        multiThreadedSelected = false;
                        selectedOption = singleThreadedText;
                        Visualizer viz;
                        viz.run();//single threaded
                    }
                }
               else if (event.type == sf::Event::MouseMoved)
                {
                    sf::FloatRect multiThreadedBounds = multiThreadedText.getGlobalBounds();
                    sf::FloatRect singleThreadedBounds = singleThreadedText.getGlobalBounds();

                    if (multiThreadedBounds.contains(event.mouseMove.x, event.mouseMove.y))
                    {
                        multiThreadedText.setFillColor(sf::Color::Yellow);
                        window->draw(multiThreadedText);
                    }
                    else if (singleThreadedBounds.contains(event.mouseMove.x, event.mouseMove.y))
                    {
                        singleThreadedText.setFillColor(sf::Color::Yellow);
                        window->draw(singleThreadedText);
                    }
                    else
                    {
                        multiThreadedText.setFillColor(sf::Color::White);
                        singleThreadedText.setFillColor(sf::Color::White);
                        window->draw(multiThreadedText);
                        window->draw(singleThreadedText);
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
