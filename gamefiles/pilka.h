
#pragma once

#include <SFML/Graphics.hpp>
#include "paletka.h"
#include "stone.h"

class Pilka
{
public:
    Pilka(float x_in, float y_in, float vx_in, float vy_in, float r_in);

    void move();
    void bounceX();
    void bounceY();
    void collideWalls(float width, float height);
    bool collideBlockY(Stone& blk);
    bool collideBlockX(Stone& blk);
    bool collidePaddle(const Paletka& p);
    void draw(sf::RenderTarget& target);

    float getX() const;
    float getY() const;
    float getVx() const;
    float getVy() const;
    float getRadius() const;


    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;


    void setPosition(const sf::Vector2f& pos);
    void setVelocity(const sf::Vector2f& vel);

private:
    float x, y;
    float vx, vy;
    float radius;
    sf::CircleShape shape;
};
