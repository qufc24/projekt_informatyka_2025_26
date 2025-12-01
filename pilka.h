
#pragma once

#include <SFML/Graphics.hpp>
#include "paletka.h"
#include "stone.h"

class Pilka
{
public:
    // Constructor will be implemented in pilka.cpp
    Pilka(float x_in, float y_in, float vx_in, float vy_in, float r_in);

    void move();
    void bounceX();
    void bounceY();
    void collideWalls(float width, float height);
    bool collideBlock(Stone& blk);
    bool collidePaddle(const Paletka& p);
    void draw(sf::RenderTarget& target);

    // Individual components
    float getX() const;
    float getY() const;
    float getVx() const;
    float getVy() const;
    float getRadius() const;

    // Convenient vector getters (used by GameState and elsewhere)
    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;

    // Minimal setters to support loading saved state
    void setPosition(const sf::Vector2f& pos);
    void setVelocity(const sf::Vector2f& vel);

private:
    float x, y;
    float vx, vy;
    float radius;
    sf::CircleShape shape;
};
