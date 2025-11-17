#include "stone.h"
#include <array>


Stone::Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L){
    m_punktyZycia = L;
    m_jestZniszczony = false;
    this->setPosition(startPos);
    this->setSize(rozmiar);
    this->setOutlineThickness(2.f);
    aktualizujKolor();
}

void Stone::trafienie()
{
    if (m_jestZniszczony) {
        return;
    }

    --m_punktyZycia;
    aktualizujKolor();

    if (m_punktyZycia <= 0) {
        m_jestZniszczony = true;
    }
}

void Stone::aktualizujKolor()
{
    if (m_punktyZycia >= 0 && m_punktyZycia < static_cast<int>(m_colorLUT.size())) {
        this->setFillColor(m_colorLUT[static_cast<std::size_t>(m_punktyZycia)]);
    } else {
        this->setFillColor(sf::Color::Transparent);
    }
}

bool Stone::isDestroyed() const
{
    return m_jestZniszczony;
}

void Stone::draw(sf::RenderTarget& target) const
{
    if (!m_jestZniszczony) {
        target.draw(*this);
    }
}

const std::array<sf::Color, 4> Stone::m_colorLUT = {
    sf::Color::Transparent, // L = 0
    sf::Color::Red,         // L = 1
    sf::Color::Yellow,      // L = 2
    sf::Color::Blue         // L = 3
};

// --- getters for Pilka::collideBlock ---
float Stone::getX() const {
    // sf::RectangleShape::getPosition() returns top-left; convert to center x
    return this->getPosition().x + this->getSize().x / 2.f;
}

float Stone::getY() const {
    // convert top-left y to center y
    return this->getPosition().y + this->getSize().y / 2.f;
}

float Stone::getSzerokosc() const {
    return this->getSize().x;
}

float Stone::getWysokosc() const {
    return this->getSize().y;
}
