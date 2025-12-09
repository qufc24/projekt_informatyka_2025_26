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
        data.w  = stone.getSzerokosc();
        data.h  = stone.getWysokosc();
        data.x  = stone.getX() - data.w / 2.f;
        data.y  = stone.getY() - data.h / 2.f;
        data.hp = static_cast<int>(stone.getHP());

        blocks.push_back(data);
    }
}

bool Save::saveToFile(const std::string& filename)
{
    std::ofstream file(filename);
    if (!file.is_open()){
        return false;
    }

    file << paddlePosition.x << ' ' << paddlePosition.y << '\n';
    file << ballPosition.x << ' ' << ballPosition.y << ' ' << ballVelocity.x << ' ' << ballVelocity.y << '\n';
    file << blocks.size() << std::endl;

    for (const auto& block : blocks)
    {
        file << block.x << ' ' << block.y << ' ' << block.w << ' ' << block.h << ' ' << block.hp << '\n';;
    }

    file.close();
    return true;
}

bool Save::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    file >> paddlePosition.x >> paddlePosition.y;
    file >> ballPosition.x >> ballPosition.y >> ballVelocity.x >> ballVelocity.y;
    int numBlocks;
    file >> numBlocks;

    blocks.clear();
    blocks.reserve(numBlocks);
    for (int i = 0; i < numBlocks; ++i)
    {
        BlockData data;
        file >> data.x >> data.y >> data.w >> data.h >> data.hp;
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

    for (const auto& data : blocks)
    {
        stones.emplace_back(sf::Vector2f(data.x, data.y), sf::Vector2f(data.w, data.h), data.hp);
    }
}
