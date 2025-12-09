#pragma once
#include <SFML/Graphics.hpp>

class Paletka
{
public:
    Paletka(float x_in, float y_in, float szerokosc_in, float wysokosc_in, float predkosc_in):
        x(x_in),
        y(y_in),
        szerokosc(szerokosc_in),
        wysokosc(wysokosc_in),
        predkosc(predkosc_in)
    {
        shape.setSize(sf::Vector2f(szerokosc, wysokosc));
        shape.setOrigin(szerokosc / 2.f, wysokosc / 2.f);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::White);
    }

    void moveLeft();
    void moveRight();
    void clampToBounds(float width);
    void draw(sf::RenderTarget& target);

    float getX() const;
    float getY() const;
    sf::Vector2f getPosition() const;
    float getSzerokosc() const;
    float getWysokosc() const;

    // New setters so saved state can be applied
    void setPosition(const sf::Vector2f& pos);
    void setX(float nx);
    void setY(float ny);

private:
    float x;
    float y;
    float szerokosc;
    float wysokosc;
    float predkosc;
    sf::RectangleShape shape;
};


inline void Paletka::moveLeft()
{
    x -= predkosc;
    shape.setPosition(x, y);
}

inline void Paletka::moveRight()
{
    x += predkosc;
    shape.setPosition(x, y);
}

inline void Paletka::clampToBounds(float width)
{
    const float half = szerokosc / 2.f;

    if (x - half < 0.f) {
        x = half;
    }
    if (x + half > width) {
        x = width - half;
    }

    shape.setPosition(x, y);
}

inline void Paletka::draw(sf::RenderTarget& target)
{
    target.draw(shape);
}

inline float Paletka::getX() const { return x; }
inline float Paletka::getY() const { return y; }
inline sf::Vector2f Paletka::getPosition() const { return sf::Vector2f(x, y); }
inline float Paletka::getSzerokosc() const { return szerokosc; }
inline float Paletka::getWysokosc() const { return wysokosc; }

inline void Paletka::setPosition(const sf::Vector2f& pos)
{
    x = pos.x;
    y = pos.y;
    shape.setPosition(x, y);
}

inline void Paletka::setX(float nx)
{
    x = nx;
    shape.setPosition(x, y);
}

inline void Paletka::setY(float ny)
{
    y = ny;
    shape.setPosition(x, y);
}
