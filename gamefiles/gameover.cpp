#include "gameover.h"
#include "game.h"
#include <SFML/Graphics/Text.hpp>
#include <fstream>


Gameover::Gameover(float width, float height, Game& game, int lastScore)
{

    const std::vector<std::string> candidates = {
        "./fonts/BoldPixels.ttf"
    };

    for (const auto& path : candidates)
    {
        if (font.loadFromFile(path))
        {
            fontLoaded = true;
            break;
        }
    }

    if (!fontLoaded)
    {
        std::cerr << "Warning: could not load font. Rendering with simple shapes.\n";

        sf::Vector2f size(width / 2.f, 40.f);

        for (int i = 0; i < OPCJIE; ++i)
        {
            entries[i].setSize(size);
            entries[i].setFillColor(sf::Color(50, 50, 50));
            entries[i].setOutlineColor(sf::Color::White);
            entries[i].setOutlineThickness(2.f);
            entries[i].setPosition(
                width / 2.f - entries[i].getLocalBounds().width / 2.f,
                height * 0.40f + i * 80.f
            );
        }

        entries[selectedItem].setFillColor(sf::Color(144, 238, 144));
        return;
    }

    // czcionka załadowana:

    if(fontLoaded)
    {
        scoreText.setFont(font);
        scoreText.setCharacterSize(64);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(width / 4.f - scoreText.getLocalBounds().width, (height / 2.f) + 80.f );

    }
    menu[0].setFont(font);
    menu[0].setCharacterSize(64);
    menu[0].setFillColor(sf::Color(144, 238, 144));
    menu[0].setString("MENU");
    menu[0].setPosition(width / (OPCJIE + 5.f) * 1.f, (height / 2.f) - 2.f );

    menu[1].setFont(font);
    menu[1].setCharacterSize(64);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("QUIT");
    menu[1].setPosition(width / (OPCJIE + 3.f) * 3.f, (height / 2.f) - 2.f);


    menu[selectedItem].setFillColor(sf::Color(144, 238, 144));
    menu[selectedItem].setStyle(sf::Text::Bold);

    if (!gameOverTexture.loadFromFile("./textures/GameOverSprite.png"))
        {
            std::cerr << "tekstura?";
        }
    else
    {

        gameOverSprite.setTexture(gameOverTexture);


        sf::FloatRect bounds = gameOverSprite.getLocalBounds();
        gameOverSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

        gameOverSprite.setPosition(width / 2.f, height * 0.25f);

        baseY = gameOverSprite.getPosition().y;

    }

}


void Gameover::draw(sf::RenderWindow &window)
{

    window.draw(gameOverSprite);
    window.draw(scoreText);
    update();
    if (fontLoaded)
    {

        for (int i = 0; i < OPCJIE; i++)
            window.draw(menu[i]);
    }
    else
    {
        for (int i = 0; i < OPCJIE; ++i)
            window.draw(entries[i]);
    }
}

void Gameover::przesunL()
{
    if (fontLoaded)
    {
        menu[selectedItem].setFillColor(sf::Color::White);
        menu[selectedItem].setStyle(sf::Text::Regular);
    }
    selectedItem--;
    if (selectedItem < 0)
        selectedItem = OPCJIE - 1;

    if (fontLoaded)
    {
        menu[selectedItem].setFillColor(sf::Color(144, 238, 144));
        menu[selectedItem].setStyle(sf::Text::Bold);
    }
}

void Gameover::przesunP()
{
    if (fontLoaded)
    {
        menu[selectedItem].setFillColor(sf::Color::White);
        menu[selectedItem].setStyle(sf::Text::Regular);
    }

    selectedItem++;
    if (selectedItem >= OPCJIE)
        selectedItem = 0;

    if (fontLoaded)
    {
        menu[selectedItem].setFillColor(sf::Color(144, 238, 144));
        menu[selectedItem].setStyle(sf::Text::Bold);
    }
}

void Gameover::update()
{
    if(currentHeight >= Amplitude){
        speed = -speed;
    }
    if(currentHeight <= -Amplitude){
        speed = -speed;
    }

    currentHeight += speed;
    gameOverSprite.setPosition(gameOverSprite.getPosition().x, baseY + currentHeight);
}


void Gameover::setScore(int score, bool newRecord)
{
    if (!fontLoaded)
        return;

    if (newRecord){
        scoreText.setString("New Record: " + std::to_string(score));
    }
    else{
        scoreText.setString("Score: " + std::to_string(score));

    }

}

bool Gameover::updateBestScore(const std::string& filename, int score)
{
    std::ifstream fille(filename);
    int best_score = 0;

    if (fille) {
        fille >> best_score;
    }
    fille.close();

    if (score > best_score) {
        std::ofstream out(filename, std::ios::trunc);
        if (out) {
            out << score;
        }
        return true;
    }

    return false;
}
