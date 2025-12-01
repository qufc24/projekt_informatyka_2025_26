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
      // initialize game objects with same parameters as before
      m_paletka(m_WIDTH / 2.f, m_HEIGHT - 40.f, 100.f, 20.f, 8.f),
      m_pilka(m_WIDTH / 2.f, m_HEIGHT / 2.f - 40.f, 4, 3, 8),
      m_dtCounter(0),
      m_gameOver(false)
{
    // Ensure internal layout uses the known window size; this will (re)compute block layout
    // and position paddle/ball appropriately for the current playfield size.
    setWindowSize(m_WIDTH, m_HEIGHT);
}

void Game::setWindowSize(float width, float height)
{
    // Update internal playfield size used for layout calculations.
    m_WIDTH = width;
    m_HEIGHT = height;

    // Recreate paddle and ball so their positions/sizes are consistent with the new window size.
    // (This mirrors construction used elsewhere; if Paletka/Pilka support setters, those could be used instead.)
    m_paletka = Paletka(m_WIDTH / 2.f, m_HEIGHT - 40.f, 100.f, 20.f, 8.f);
    m_pilka = Pilka(m_WIDTH / 2.f, m_HEIGHT / 2.f - 40.f, 4, 3, 8);

    // Rebuild blocks layout for the new size
    blockRender();
}

void Game::reset()
{
    // Reset positions and state to start a new game
    m_gameOver = false;
    m_dtCounter = 0;

    // Reset paddle and ball positions
    m_paletka = Paletka(m_WIDTH / 2.f, m_HEIGHT - 40.f, 100.f, 20.f, 8.f);
    m_pilka = Pilka(m_WIDTH / 2.f, m_HEIGHT / 2.f - 40.f, 4, 3, 8);

    blockRender();
}

void Game::update(sf::Time dt)
{
    if (m_gameOver)
        return;

    // Move ball according to its internal velocity
    m_pilka.move();

    // If ball goes below the bottom of the play area, mark game over.
    if (m_pilka.getY() - m_pilka.getRadius() > m_HEIGHT)
    {
        std::cout << "MISS! KONIEC GRY\n";
        m_gameOver = true;
        return;
    }

    // Keep ball within walls (left/right/top/bottom)
    m_pilka.collideWalls(m_WIDTH, m_HEIGHT);

    // Paddle collision
    if (m_pilka.collidePaddle(m_paletka))
    {
        std::cout << "HIT PADDLE\n";
    }

    // Block collisions
    for (auto &blk : m_bloki)
    {
        if (!blk.isDestroyed() && m_pilka.collideBlock(blk))
        {
            std::cout << "HIT BLOCK\n";
            blk.trafienie();
            m_pilka.bounceY();
        }
    }

    // Remove destroyed blocks
    m_bloki.erase(
        std::remove_if(m_bloki.begin(), m_bloki.end(), [](const Stone &s) { return s.isDestroyed(); }),
        m_bloki.end());

    // Player controls (kept here so update handles per-frame input-based movement)
    sterowanie();

    // Optional debug counter
    debug();
}

void Game::render(sf::RenderTarget& target)
{
    // Do not clear or display the target here; main is responsible for that.
    // Draw game objects in the expected order.
    // If you want a background color, main should clear the window with that color.
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

    // Spacing between blocks (in pixels)
    const float spacing = 2.f;

    // Decide how much vertical space the blocks should occupy.
    // Use the upper portion of the window; for example 40% of the total height.
    // You can adjust the 0.4f factor to increase/decrease the occupied height.
    float upperHeight = m_HEIGHT * 0.40f;

    // Compute block size so that columns fill the full width (taking spacing into account)
    float blockW = (m_WIDTH - (m_ILOSC_KOLUMN - 1) * spacing) / static_cast<float>(m_ILOSC_KOLUMN);
    float blockH = (upperHeight - (m_ILOSC_WIERSZY - 1) * spacing) / static_cast<float>(m_ILOSC_WIERSZY);

    // Safety clamps to avoid degenerate sizes
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
}