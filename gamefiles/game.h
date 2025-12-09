#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "pilka.h"


class Save;


class Game
{
public:
    Game();
    ~Game() = default;

    void setWindowSize(float width, float height);
    void update(sf::Time dt);
    void render(sf::RenderTarget& target);
    void reset();
    bool isGameOver() const { return m_gameOver; }
    void applySave(const Save& state);
    void scoreCounter();
    int getScore() const { return m_score; }


private:
    void debug();
    void sterowanie();
    void blockRender();

    int m_score = 0;
    float m_WIDTH;
    float m_HEIGHT;
    float m_FrameLimit;
    int   m_ILOSC_KOLUMN;
    int   m_ILOSC_WIERSZY;
    float m_ROZMIAR_BLOKU_X;
    float m_ROZMIAR_BLOKU_Y;
    Paletka m_paletka;
    Pilka   m_pilka;
    std::vector<Stone> m_bloki;


    int m_dtCounter = 0;
    bool m_gameOver = false;
    bool m_saveKeyPrev = false;
};
