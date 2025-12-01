#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "pilka.h"

// Updated Game class:
// - No longer owns or manages an sf::RenderWindow.
// - Exposes update(sf::Time) and render(sf::RenderTarget&) so main can manage the window and the main loop.
// - Removed run() and processEvents() from the public interface.
// - Added setWindowSize(...) so main can inform Game about the current window size
//   before block layout is computed.

class Game
{
public:
    Game();
    ~Game() = default;

    // Inform Game about the window size so it can compute layout (blocks, paddle positions, ...)
    // Call this after creating the main window and whenever the window is resized.
    void setWindowSize(float width, float height);

    // Advance game logic by dt. Called from main only when in Playing state.
    void update(sf::Time dt);

    // Draw game contents to the provided render target (usually the main window).
    // Must not call clear() or display() here.
    void render(sf::RenderTarget& target);

    // Optional helper to (re)start or reset the game state/level
    void reset();

    // Query whether the game has reached a terminal state
    bool isGameOver() const { return m_gameOver; }

private:
    void debug();
    void sterowanie();
    void blockRender();

    // World / layout parameters
    // These represent the logical playfield size used for layout calculations.
    float m_WIDTH;
    float m_HEIGHT;
    float m_FrameLimit;
    int   m_ILOSC_KOLUMN;
    int   m_ILOSC_WIERSZY;
    float m_ROZMIAR_BLOKU_X;
    float m_ROZMIAR_BLOKU_Y;

    // Game objects
    Paletka m_paletka;
    Pilka   m_pilka;
    std::vector<Stone> m_bloki;

    // Internal counters / debug
    int m_dtCounter = 0;
    bool m_gameOver = false;
};

#endif // GAME_H