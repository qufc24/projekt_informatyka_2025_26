
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "pilka.h"


class Game
{
public:
    Game();

    void run();

private:
    void processEvents();
    void update(sf::Time dt);
    void render();

    void debug();
    void sterowanie();
    void blockRender();

    sf::RenderWindow m_window;
    sf::Clock m_deltaClock; // used to compute real delta time passed to update()

    // Game entities
    Paletka m_paletka;
    Pilka   m_pilka;
    std::vector<Stone> m_bloki;

    float m_WIDTH;
    float m_HEIGHT;
    float m_FrameLimit;
    int   m_ILOSC_KOLUMN;
    int   m_ILOSC_WIERSZY;
    float m_ROZMIAR_BLOKU_X;
    float m_ROZMIAR_BLOKU_Y;

    int m_dtCounter = 0;
};
