#include <SFML/Graphics.hpp>
#include "menu.h"
#include "game.h"
#include "save.h"

enum class GameState { Menu, Playing, Scores, Exiting };

int main()
{

    sf::RenderWindow window(sf::VideoMode(640, 480), "Arkanoid");
    window.setFramerateLimit(60);

    Menu menu(window.getSize().x, window.getSize().y);
    Game game;
    GameState currentState = GameState::Menu;
    Save save;

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

                            currentState = GameState::Scores;
                        }
                        else if (sel == 3)
                        {
                            currentState = GameState::Playing;
                            window.close();
                        }
                        else if (sel == 1)
                        {
                            if (save.loadFromFile("save.txt")) {
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
                // example: pressing Escape returns to menu
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
        }

        if (currentState == GameState::Playing)
        {
            game.update(dt);
            if (game.isGameOver())
            {
                currentState = GameState::Menu;
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

        window.display();
    }

    return 0;
}
