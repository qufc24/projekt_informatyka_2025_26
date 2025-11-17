#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "pilka.h"
#include "stone.h"


int main()
{
    const float WIDTH = 640.f;
    const float HEIGHT = 480.f;
    sf::RenderWindow window({(unsigned)WIDTH, (unsigned)HEIGHT}, "Arkanoid test");
    window.setFramerateLimit(60);

    Paletka pal(320.f, 440.f, 100.f, 20.f, 8.f); // x,y,szer,wys, predkosc
    Pilka pilka(320.f, 200.f, 4.f, 3.f, 8.f);     // x,y,vx,vy,radius
    std::vector<Stone> bloki;
    const int ILOSC_KOLUMN = 6;
    const int ILOSC_WIERSZY = 7;
    const float ROZMIAR_BLOKU_Y = 25.f;
    const float ROZMIAR_BLOKU_X = (WIDTH - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;
    int dt = 0;

    // Generate level: iterate rows (y) then columns (x)
    for (int y = 0; y < ILOSC_WIERSZY; ++y)
    {
        for (int x = 0; x < ILOSC_KOLUMN; ++x)
        {
            float posX = x * (ROZMIAR_BLOKU_X + 2.f);
            float posY = y * (ROZMIAR_BLOKU_Y + 2.f); // offset from top
            int L = (y < 1) ? 3 : (y < 3) ? 2 : 1;
            bloki.emplace_back(sf::Vector2f(posX, posY), sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y), L);
        }
    }

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
        for (auto &blk : bloki) {
            if (!blk.isDestroyed() && pilka.collideBlock(blk)) {
                std::cout << "HIT BLOCK\n";
                blk.trafienie();
                pilka.bounceY();
                }
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
        for (const auto& blk : bloki) {
            blk.draw(window);
        }
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
