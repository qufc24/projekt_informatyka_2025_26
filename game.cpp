
#pragma once

#include "game.h"
#include "save.h"
#include <SFML/System/Vector2.hpp>
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

      m_paletka(m_WIDTH / 2.f, m_HEIGHT - 40.f, 100.f, 20.f, 8.f),
      m_pilka(m_WIDTH / 2.f, m_HEIGHT / 2.f - 40.f, 4, 3, 8),
      m_dtCounter(0),
      m_gameOver(false)
{

    setWindowSize(m_WIDTH, m_HEIGHT);
}

void Game::setWindowSize(float width, float height)
{

    m_WIDTH = width;
    m_HEIGHT = height;


    m_paletka = Paletka(m_WIDTH / 2.f, m_HEIGHT - 40.f, 100.f, 20.f, 8.f);
    m_pilka = Pilka(m_WIDTH / 2.f, m_HEIGHT / 2.f - 40.f, 4, 3, 8);

    blockRender();
}

void Game::reset()
{

    m_gameOver = false;
    m_dtCounter = 0;


    m_paletka = Paletka(m_WIDTH / 2.f, m_HEIGHT - 40.f, 100.f, 20.f, 8.f);
    m_pilka = Pilka(m_WIDTH / 2.f, m_HEIGHT / 2.f - 40.f, 4, 3, 8);

    blockRender();
}

void Game::update(sf::Time dt)
{
    if (m_gameOver)
        return;


    m_pilka.move();


    if (m_pilka.getY() - m_pilka.getRadius() > m_HEIGHT)
    {
        std::cout << "MISS! KONIEC GRY\n";
        m_gameOver = true;
        return;
    }

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


    m_bloki.erase(
        std::remove_if(m_bloki.begin(), m_bloki.end(), [](const Stone &s) { return s.isDestroyed(); }),
        m_bloki.end());


    sterowanie();


    debug();
}

void Game::render(sf::RenderTarget& target)
{
    m_paletka.draw(target);
    m_pilka.draw(target);
    for (const auto &blk : m_bloki)
    {
        blk.draw(target);
    }
}

void Game::blockRender()
{
    m_bloki.clear();


    const float spacing = 2.f;


    float upperHeight = m_HEIGHT * 0.40f;

    float blockW = (m_WIDTH - (m_ILOSC_KOLUMN - 1) * spacing) / static_cast<float>(m_ILOSC_KOLUMN);
    float blockH = (upperHeight - (m_ILOSC_WIERSZY - 1) * spacing) / static_cast<float>(m_ILOSC_WIERSZY);


    if (blockW < 4.f) blockW = 4.f;
    if (blockH < 4.f) blockH = 4.f;

    for (int y = 0; y < m_ILOSC_WIERSZY; ++y)
    {
        for (int x = 0; x < m_ILOSC_KOLUMN; ++x)
        {
            float posX = x * (blockW + spacing);
            float posY = y * (blockH + spacing);
            int L = (y < 1) ? 3 : (y < 3) ? 2 : 1;
            m_bloki.emplace_back(sf::Vector2f(posX, posY), sf::Vector2f(blockW, blockH), L);
        }
    }
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        Save s;
        s.capture(m_paletka, m_pilka, m_bloki);
        s.saveToFile("save.txt");
        std::cout << "Zapisano stan gry do pliku save.txt" << std::endl;
    }
}


void Game::applySave(const Save& state)
{
    m_paletka.setPosition(state.getPaddlePosition());
    m_pilka.setPosition(state.getBallPosition());
    m_pilka.setVelocity(state.getBallVelocity());
    m_bloki.clear();

    sf::Vector2f size(m_WIDTH, m_HEIGHT);
    const float spacing = 2.f;
    float upperHeight = m_HEIGHT * 0.40f;
    float blockW = (m_WIDTH - (m_ILOSC_KOLUMN - 1) * spacing) / static_cast<float>(m_ILOSC_KOLUMN);
    float blockH = (upperHeight - (m_ILOSC_WIERSZY - 1) * spacing) / static_cast<float>(m_ILOSC_WIERSZY);

    for (const auto& data : state.getBlocks())
    {
        // Use the saved block position and size directly when recreating blocks
        m_bloki.emplace_back(sf::Vector2f(data.x, data.y), sf::Vector2f(data.w, data.h), data.hp);
    }
}
