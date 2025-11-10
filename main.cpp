#include <iostream>
#include <SFML/Graphics.hpp>
#include "pilka.h"


int main()
{
    const float WIDTH = 640.f;
    const float HEIGHT = 480.f;
    sf::RenderWindow window({(unsigned)WIDTH, (unsigned)HEIGHT}, "Arkanoid test");
    window.setFramerateLimit(60);

    Paletka pal(320.f, 440.f, 100.f, 20.f, 8.f); // x,y,szer,wys, predkosc
    Pilka pilka(320.f, 200.f, 4.f, 3.f, 8.f);     // x,y,vx,vy,radius

    int dt = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //Sterowanie
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            pal.moveLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            pal.moveRight();
        }
        pal.clampToBounds(WIDTH);

        // Aktualizacja piłki
        pilka.move();
        pilka.collideWalls(WIDTH, HEIGHT);
        if (pilka.collidePaddle(pal))
        {
            std::cout << "HIT PADDLE\n";
        }

        // Sprawdzenie przegranej (piłka całkowicie poniżej ekranu)
        if (pilka.getY() - pilka.getRadius() > HEIGHT)
        {
            std::cout << "MISS! KONIEC GRY\n";
            window.close();
            break;
        }

        // Rysowanie
        window.clear(sf::Color(20, 20, 30));
        pal.draw(window);
        pilka.draw(window);
        window.display();

        // Zliczanie klatek
        dt++;
        if (dt == 60)
        {
            std::cout << "x=" << pilka.getX() << " y=" << pilka.getY() << " vx=" << pilka.getVx() << " vy=" << pilka.getVy() << std::endl;

            dt = 0;
        }
    }

    return 0;
}
