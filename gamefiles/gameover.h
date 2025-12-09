#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#define OPCJIE 2
class Game;

class Gameover
{
private:
    sf::Font font;
    sf::Text menu[OPCJIE];
    sf::Text scoreText;
    int selectedItem = 0;
    bool fontLoaded = false;
    sf::RectangleShape entries[OPCJIE];
    sf::Texture gameOverTexture;
    sf::Sprite gameOverSprite;
    float baseY = 0.f;
    float Amplitude = 10;
    float speed= 0.3f;
    float currentHeight = 0.f;


public:
    Gameover(float width, float height, Game& game, int lastScore);
    ~Gameover() = default;

    void update();
    void przesunP();
    void przesunL();
    void setScore(int score);


    int getSelectedItem() const { return selectedItem; }
    void draw(sf::RenderWindow &window);
};

#endif
