
#pragma once

#include "game.h"
#include "save.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>


Game::Game()
    : m_WIDTH(640.f),
      m_HEIGHT(480.f),
      m_FrameLimit(60.f),
      m_ILOSC_KOLUMN(10),
      m_ILOSC_WIERSZY(5),
      m_ROZMIAR_BLOKU_X(60.f),
      m_ROZMIAR_BLOKU_Y(20.f),

      m_paletka(m_WIDTH / 2.f, m_HEIGHT - 40.f, 100.f, 20.f, 8.f),
      m_pilka(m_WIDTH / 2.f, m_HEIGHT / 1.5f- 40.f, 4, 3, 8),
      m_dtCounter(0),
      m_gameOver(false),
      m_score(0)
{

    setWindowSize(m_WIDTH, m_HEIGHT);

    const std::vector<std::string> candidates = {
        "./fonts/BoldPixels.ttf"
    };

    for (const auto& path : candidates)
    {
        if (font.loadFromFile(path))
        {
            fontLoaded = true;
            break;
        }
    }


    if (!buffer.loadFromFile("./sounds/point.mp3"))
        std::cerr << "Błąd wczytywania dźwięku";

    sound.setBuffer(buffer);

    if(fontLoaded)
    {
        scoreText.setFont(font);
        scoreText.setCharacterSize(64);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setString("Score: 0");
        scoreText.setPosition(m_WIDTH / 5.5f - scoreText.getLocalBounds().width / 2.f, (m_HEIGHT / 90.f) - 25.f);
    }
}

void Game::setWindowSize(float width, float height)
{
    //m_score = 0;
    m_WIDTH = width;
    m_HEIGHT = height;

    blockRender();
}

void Game::reset()
{
    m_gameOver = false;
    m_dtCounter = 0;

    m_paletka = Paletka(m_WIDTH / 2.f, m_HEIGHT - 40.f, 100.f, 20.f, 8.f);
    m_pilka = Pilka(m_WIDTH / 2.f, m_HEIGHT / 1.5f - 40.f, 4, 3, 8);

    blockRender();
}

void Game::update(sf::Time dt)
{
    if (m_gameOver)
        return;


    m_pilka.move();
    scoreCounter();



    if (m_pilka.getY() - m_pilka.getRadius() > m_HEIGHT)
    {
        m_gameOver = true;
        return;
    }

    m_pilka.collideWalls(m_WIDTH, m_HEIGHT);
    m_pilka.collidePaddle(m_paletka);

    for (auto &blk : m_bloki)
    {

        if (!blk.isDestroyed() && m_pilka.collideBlockX(blk))
        {
            blk.trafienie();
            sound.play();
            m_pilka.bounceX();
        }
        //priorytowanie odbić w osi X, w celu uniknięcia wielokrotnego odbicia
        if (!blk.isDestroyed() && m_pilka.collideBlockY(blk) && !m_pilka.collideBlockX(blk))
        {
            blk.trafienie();
            sound.play();
            m_pilka.bounceY();
        }
    }


    m_bloki.erase(
        std::remove_if(m_bloki.begin(), m_bloki.end(), [](const Stone &s) { return s.isDestroyed(); }),
        m_bloki.end());

    if (m_bloki.empty())
    {
        reset();
    }

    sterowanie();
    //debug();
}

void Game::render(sf::RenderTarget& target)
{
    m_paletka.draw(target);
    m_pilka.draw(target);

    if (fontLoaded)
    {
        displayScore(target);
    }

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
    float blockW = (m_WIDTH - (m_ILOSC_KOLUMN - 1) * spacing) / m_ILOSC_KOLUMN;
    float blockH = (upperHeight - (m_ILOSC_WIERSZY - 1) * spacing) / m_ILOSC_WIERSZY;


    if (blockW < 4.f) blockW = 4.f;
    if (blockH < 4.f) blockH = 4.f;

    for (int y = 0; y < m_ILOSC_WIERSZY; ++y)
    {
        for (int x = 0; x < m_ILOSC_KOLUMN; ++x)
        {
            float posX = x * (blockW + spacing);
            float posY = y * (blockH + spacing) + (m_WIDTH / 11.f);
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
    bool saveKeyNow = sf::Keyboard::isKeyPressed(sf::Keyboard::P);
        if (saveKeyNow && !m_saveKeyPrev)
        {
            Save s;
            s.capture(m_paletka, m_pilka, m_bloki);
            if (s.saveToFile("./data/save.txt")) {
                std::cout << "Zapisano stan gry do pliku save.txt\n";
            } else {
                std::cout << "Blad zapisu do save.txt\n";
            }
        }
        m_saveKeyPrev = saveKeyNow;
}


void Game::applySave(const Save& state)
{
    m_gameOver = false;
    m_paletka.setPosition(state.getPaddlePosition());
    m_pilka.setPosition(state.getBallPosition());
    m_pilka.setVelocity(state.getBallVelocity());
    m_bloki.clear();

    sf::Vector2f size(m_WIDTH, m_HEIGHT);

    for (const auto& data : state.getBlocks())
    {
        m_bloki.emplace_back(sf::Vector2f(data.x, data.y), sf::Vector2f(data.w, data.h), data.hp);

    }


}

void Game::scoreCounter()
{
    for (auto &blk : m_bloki)
       {
           if (m_pilka.collideBlockY(blk) || m_pilka.collideBlockX(blk))
           {

               if (blk.isDestroyed())
               {
                   m_score += 10;
               }
               else
               {
                   m_score += 5;
               }
           }
       }
}

void Game::displayScore(sf::RenderTarget &target)
{
    scoreText.setString("Score: " + std::to_string(m_score));
    target.draw(scoreText);
}

void Game::resetScore()
{
    m_score = 0;
}
