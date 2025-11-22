#include "game.h"
#include <algorithm>
#include <iostream>

Game::Game()
    : m_WIDTH(640.f),
      m_HEIGHT(480.f),
      m_FrameLimit(60.f),
      m_ILOSC_KOLUMN(10),
      m_ILOSC_WIERSZY(5),
      m_ROZMIAR_BLOKU_X(60.f),
      m_ROZMIAR_BLOKU_Y(20.f),
      m_window(sf::VideoMode(static_cast<unsigned>(m_WIDTH), static_cast<unsigned>(m_HEIGHT)), "Arkanoid test"),
      m_paletka(m_WIDTH / 2.f, m_HEIGHT - 40.f, 100.f, 20.f, 8.f),
      m_pilka(m_WIDTH / 2.f, m_HEIGHT / 2.f - 40.f, 4, 3, 8)
{
    // ustaw limit klatek
    m_window.setFramerateLimit(static_cast<unsigned>(m_FrameLimit));

    // przygotuj bloki
    blockRender();

    // restart zegara na start
    m_deltaClock.restart();
}

void Game::run()
{
    // główna pętla gry
    while (m_window.isOpen())
    {
        // oblicz rzeczywisty dt
        sf::Time dt = m_deltaClock.restart();

        processEvents();
        sterowanie();
        update(dt);
        render();
        debug();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window.close();
    }
}

void Game::update(sf::Time dt)
{
    // Aktualizacja pozycji piłki (obecna implementacja Pilka::move nie używa dt,
    // więc wywołujemy istniejącą metodę; dt jest przekazane dla przyszłych rozszerzeń)
    m_pilka.move();

    // Sprawdzenie czy piłka wypadła poza ekran (przegrana)
    if (m_pilka.getY() - m_pilka.getRadius() > m_WIDTH /* mistake? original used HEIGHT */)
    {
        // Poprawka: warunek powinien porównywać do wysokości okna
        // Jednak aby nie modyfikować semantyki innych modułów, sprawdzamy względem m_HEIGHT
    }
    if (m_pilka.getY() - m_pilka.getRadius() > m_HEIGHT)
    {
        std::cout << "MISS! KONIEC GRY\n";
        m_window.close();
        return;
    }

    // Kolizje
    m_pilka.collideWalls(m_WIDTH, m_HEIGHT);

    if (m_pilka.collidePaddle(m_paletka))
    {
        std::cout << "HIT PADDLE\n";
    }

    for (auto &blk : m_bloki)
    {
        if (!blk.isDestroyed() && m_pilka.collideBlock(blk))
        {
            std::cout << "HIT BLOCK\n";
            blk.trafienie();
            m_pilka.bounceY();
        }
    }

    // Usuń zniszczone bloki
    m_bloki.erase(
        std::remove_if(m_bloki.begin(), m_bloki.end(), [](const Stone &s) { return s.isDestroyed(); }),
        m_bloki.end());
}

void Game::blockRender()
{
    m_bloki.clear();
    for (int y = 0; y < m_ILOSC_WIERSZY; ++y)
    {
        for (int x = 0; x < m_ILOSC_KOLUMN; ++x)
        {
            float posX = x * (m_ROZMIAR_BLOKU_X + 2.f);
            float posY = y * (m_ROZMIAR_BLOKU_Y + 2.f); // offset from top
            int L = (y < 1) ? 3 : (y < 3) ? 2 : 1;
            m_bloki.emplace_back(sf::Vector2f(posX, posY), sf::Vector2f(m_ROZMIAR_BLOKU_X, m_ROZMIAR_BLOKU_Y), L);
        }
    }
}

void Game::render()
{
    m_window.clear(sf::Color(20, 20, 30));
    m_paletka.draw(m_window);
    m_pilka.draw(m_window);
    for (const auto &blk : m_bloki)
    {
        blk.draw(m_window);
    }
    m_window.display();
}

void Game::debug()
{
    m_dtCounter++;
    if (m_dtCounter >= 60)
    {
        std::cout << "x=" << m_pilka.getX() << " y=" << m_pilka.getY() << " vx=" << m_pilka.getVx() << " vy=" << m_pilka.getVy() << std::endl;
        m_dtCounter = 0;
    }
}

void Game::sterowanie()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_paletka.moveLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_paletka.moveRight();
    }
    m_paletka.clampToBounds(m_WIDTH);
}
