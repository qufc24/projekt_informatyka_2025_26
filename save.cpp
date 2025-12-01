#include "save.h"
#include "pilka.h"
#include "stone.h"
#include "paletka.h"
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <fstream>

void Save::capture(
    const Paletka& paddle,
    const Pilka& ball,
    const std::vector<Stone>& stones
)
{
    // 1. Paletka
    paddlePosition = paddle.getPosition();

    // 2. Piłka
    ballPosition = ball.getPosition();
    ballVelocity = ball.getVelocity();

    // 3. Klocki
    blocks.clear();
    blocks.reserve(stones.size());

    for (const Stone& stone : stones)
    {
        BlockData data;
        // convert stone center coordinates to top-left so saved positions match
        // the positions used when recreating RectangleShape (which expects top-left)
        data.w  = stone.getSzerokosc();
        data.h  = stone.getWysokosc();
        data.x  = stone.getX() - data.w / 2.f;
        data.y  = stone.getY() - data.h / 2.f;
        data.hp = static_cast<int>(stone.getHP());

        blocks.push_back(data);
    }
}

void Save::saveToFile(const std::string& filename)
{
    std::ofstream file(filename);
    if (!file.is_open()) return;
    //Zapis Paletki
    file << paddlePosition.x << ' ' << paddlePosition.y << '\n';
    //Zapis Piłki
    file << ballPosition.x << ' ' << ballPosition.y << ' ' << ballVelocity.x << ' ' << ballVelocity.y << '\n';
    //Zapis liczby bloków
    file << blocks.size() << '\n';
    //Zapis bloków
    for (const auto& block : blocks)
    {
        file << block.x << ' ' << block.y << ' ' << block.hp << '\n';
    }

    file.close();
    return;
}

bool Save::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    //Wczytanie Paletki
    file >> paddlePosition.x >> paddlePosition.y;
    //Wczytanie Piłki
    file >> ballPosition.x >> ballPosition.y >> ballVelocity.x >> ballVelocity.y;
    //Wczytanie liczby bloków
    int numBlocks;
    file >> numBlocks;
    //Wczytanie bloków
    blocks.clear();
    blocks.reserve(numBlocks);
    for (int i = 0; i < numBlocks; ++i)
    {
        BlockData data;
        file >> data.x >> data.y >> data.hp;
        blocks.push_back(data);
    }

    file.close();
    return true;
}

void Save::apply(Paletka& paddle, Pilka& ball, std::vector<Stone>& stones) const
{

    paddle.setPosition(paddlePosition);
    ball.setPosition(ballPosition);
    ball.setVelocity(ballVelocity);

    stones.clear();
    stones.reserve(blocks.size());
    const sf::Vector2f blockSize(60.f, 20.f);

    for (const auto& data : blocks)
    {
        stones.emplace_back(sf::Vector2f(data.x, data.y), blockSize, data.hp);
    }
}
