#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


class Paletka;
class Pilka;
class Stone;

struct BlockData {
    float x, y;
    float w, h;
    int hp;
};

class Save {
public:

    void capture(const Paletka& paddle, const Pilka& ball, const std::vector<Stone>& stones);
    void saveToFile(const std::string& filename);
    bool loadFromFile(const std::string& filename);

    // Match implementation in save.cpp
    void apply(Paletka& paddle, Pilka& ball, std::vector<Stone>& stones) const;

    const sf::Vector2f& getPaddlePosition() const { return paddlePosition; }
    const sf::Vector2f& getBallPosition() const { return ballPosition; }
    const sf::Vector2f& getBallVelocity() const { return ballVelocity; }
    const std::vector<BlockData>& getBlocks() const { return blocks; }

private:
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    std::vector<BlockData> blocks;

};
