#include <SFML/Graphics.hpp>
#include "paletka.h"
#include "stone.h"

class Pilka
{
public:
    Pilka(int x_in, int y_in, int vx_in, int vy_in, int r_in):
        x(x_in),
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

    void move();
    void bounceX();
    void bounceY();
    void collideWalls(float widht, float height);
    bool collideBlock(Stone& blk);
    bool collidePaddle(const Paletka& p);
    void draw(sf::RenderTarget& target);

    float getX() const;
    float getY() const;
    float getVx() const;
    float getVy() const;
    float getRadius() const;

private:
    float x, y;
    float vx, vy;
    float radius;
    sf::CircleShape shape;
};



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

void Pilka::collideWalls(float widht, float height){
    if (x - radius <= 0.f) {
        x = radius;
        bounceX();
    }

    if (x + radius >= widht){
        x = widht - radius;
        bounceX();
    }

    if (y - radius <= 0.f) {
        y = radius;
        bounceY();
    }
    shape.setPosition(x, y);
}

bool Pilka::collidePaddle(const Paletka& p){
    const float palX = p.getX();
    const float palY = p.getY();
    const float palW = p.getSzerokosc();
    const float palH = p.getWysokosc();

    if ( x < palX - palW / 2.f || x > palX + palW / 2.f){
        return false;
    }

    const float palTop = palY - palH / 2.f;

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
    const float blkX = blk.getX();
    const float blkY = blk.getY();
    const float blkW = blk.getSzerokosc();
    const float blkH = blk.getWysokosc();

    if (x - radius <= blkX + blkW / 2.f && x + radius >= blkX - blkW / 2.f){
        if (y + radius >= blkY - blkH / 2.f && y - radius <= blkY + blkH / 2.f){
            return true;
        }
    }
    return false;
}



float Pilka::getX() const { return x; }
float Pilka::getY() const { return y; }
float Pilka::getVx() const { return vx; }
float Pilka::getVy() const { return vy; }
float Pilka::getRadius() const { return radius; }
