#include <SFML/Graphics.hpp>
#include "menu.h"
#include "game.h"
#include "save.h"
#include "gameover.h"

enum class GameState { Menu, Playing, Scores, Exiting, GameOver };

int main()
{

    sf::RenderWindow window(sf::VideoMode(640, 480), "Arkanoid");
    window.setFramerateLimit(60);

    Menu menu(window.getSize().x, window.getSize().y);
    Game game;
    GameState currentState = GameState::Menu;
    Save save;
    Gameover gameover(window.getSize().x, window.getSize().y, game, game.getScore());

    sf::Clock deltaClock;
    sf::Clock keyClock;
    const sf::Int32 keyDebounceMs = 150;

    while (window.isOpen())
    {
        sf::Time dt = deltaClock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
            {
                window.close();
                break;
            }


            if (currentState == GameState::Menu)
            {

                if (event.type == sf::Event::KeyPressed)
                {

                    if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down)
                    {
                        if (keyClock.getElapsedTime().asMilliseconds() > keyDebounceMs)
                        {
                            if (event.key.code == sf::Keyboard::Up)
                                menu.przesunG();
                            else
                                menu.przesunD();

                            keyClock.restart();
                        }
                    }
                    else if (event.key.code == sf::Keyboard::Enter)
                    {
                        int sel = menu.getSelectedItem();
                        if (sel == 0)
                        {

                            game.reset();
                            currentState = GameState::Playing;
                        }
                        else if (sel == 2)
                        {
                            window.close();
                        }
                        else if (sel == 1)
                        {
                            if (save.loadFromFile("./data/save.txt")) {
                                game.applySave(save);
                                currentState = GameState::Playing;
                            } else {
                                currentState = GameState::Menu;
                            }
                        }
                    }
                }
            }
            else if (currentState == GameState::Playing)
            {

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                {
                    currentState = GameState::Menu;
                }
            }
            else if (currentState == GameState::Scores)
            {
                if (event.type == sf::Event::KeyPressed &&
                    (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Enter))
                {
                    currentState = GameState::Menu;
                }
            }
            else if (currentState == GameState::GameOver)
            {

                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Right)
                        gameover.przesunP();
                    if (event.key.code == sf::Keyboard::Left)
                        gameover.przesunL();

                    if (event.key.code == sf::Keyboard::Enter)
                    {
                        int sel = gameover.getSelectedItem();
                        if (sel == 0)
                        {
                            gameover.setScore(0, false);
                            game.resetScore();
                            currentState = GameState::Menu;
                        }
                        else if (sel == 1)
                        {
                            window.close();
                        }
                    }
                }
            }
        }


        if (currentState == GameState::Playing)
        {
            game.update(dt);
            if (game.isGameOver())
            {
                bool newRecord = gameover.updateBestScore("./data/bestscore.txt", game.getScore());
                gameover.setScore(game.getScore(), newRecord);
                currentState = GameState::GameOver;
            }
        }

        // Render
        window.clear(sf::Color(20, 20, 30));

        if (currentState == GameState::Menu)
        {
            menu.draw(window);
        }
        else if (currentState == GameState::Playing)
        {
            game.render(window);
        }
        else if (currentState == GameState::Scores)
        {
            menu.draw(window);
        }
        else if (currentState == GameState::GameOver)
        {
            gameover.draw(window);
        }

        window.display();
    }

    return 0;
}
