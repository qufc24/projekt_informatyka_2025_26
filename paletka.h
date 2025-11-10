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
    float getSzerokosc() const;
    float getWysokosc() const;

private:
    float x;
    float y;
    float szerokosc;
    float wysokosc;
    float predkosc;
    sf::RectangleShape shape;
};



void Paletka::moveLeft()
{
    x -= predkosc;
    shape.setPosition(x, y);
}

void Paletka::moveRight()
{
    x += predkosc;
    shape.setPosition(x, y);
}

void Paletka::clampToBounds(float width)
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

void Paletka::draw(sf::RenderTarget& target)
{
    target.draw(shape);
}

float Paletka::getX() const { return x; }
float Paletka::getY() const { return y; }
float Paletka::getSzerokosc() const { return szerokosc; }
float Paletka::getWysokosc() const { return wysokosc; }
