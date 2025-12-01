#include "pilka.h"
#include <cmath>

Pilka::Pilka(float x_in, float y_in, float vx_in, float vy_in, float r_in)
    : x(x_in),
      y(y_in),
      vx(vx_in),
      vy(vy_in),
      radius(r_in),
      shape(radius)
{
    shape.setOrigin(radius, radius);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(x, y);
}

void Pilka::move(){
    x += vx;
    y += vy;
    shape.setPosition(x, y);
}

void Pilka::bounceX(){
    vx = -vx;
}

void Pilka::bounceY(){
    vy = -vy;
}

void Pilka::collideWalls(float width, float height){
    if (x - radius <= 0.f) {
        x = radius;
        bounceX();
    }

    if (x + radius >= width){
        x = width - radius;
        bounceX();
    }

    if (y - radius <= 0.f) {
        y = radius;
        bounceY();
    }
    shape.setPosition(x, y);
}

bool Pilka::collidePaddle(const Paletka& p){
    if ( x < p.getX() - p.getSzerokosc() / 2.f || x > p.getX() + p.getSzerokosc() / 2.f){
        return false;
    }
    //Dla czytelności nowa zmienna lokalna
    const float palTop = p.getY() - p.getWysokosc() / 2.f;

    if ((y + radius) >= palTop && (y - radius) < palTop){
        vy = -std::abs(vy);
        y = palTop - radius;
        shape.setPosition(x, y);
        return true;
    }
    return false;
}

void Pilka::draw(sf::RenderTarget& target){
    target.draw(shape);
}

bool Pilka::collideBlock(Stone& blk){
    if (x - radius <= blk.getX() + blk.getSzerokosc() / 2.f && x + radius >= blk.getX() - blk.getSzerokosc() / 2.f){
        if (y + radius >= blk.getY() - blk.getWysokosc() / 2.f && y - radius <= blk.getY() + blk.getWysokosc() / 2.f){
            return true;
        }
    }
    return false;
}

float Pilka::getX() const { return x; }
float Pilka::getY() const { return y; }
sf::Vector2f Pilka::getPosition() const { return sf::Vector2f(x, y); }
float Pilka::getVx() const { return vx; }
float Pilka::getVy() const { return vy; }
sf::Vector2f Pilka::getVelocity() const { return sf::Vector2f(vx, vy); }
float Pilka::getRadius() const { return radius; }

void Pilka::setPosition(const sf::Vector2f& pos)
{
    x = pos.x;
    y = pos.y;
    shape.setPosition(x, y);
}

void Pilka::setVelocity(const sf::Vector2f& vel)
{
    vx = vel.x;
    vy = vel.y;
}
