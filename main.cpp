#include <SFML/Graphics.hpp>
#include "menu.h"
#include "game.h"

enum class GameState { Menu, Playing, Scores, Exiting };

int main()
{
    // Create window and resources
    sf::RenderWindow window(sf::VideoMode(640, 480), "Arkanoid");
    window.setFramerateLimit(60);

    Menu menu(window.getSize().x, window.getSize().y);
    Game game;
    GameState currentState = GameState::Menu;

    // Clocks for delta time and simple key debouncing for the menu
    sf::Clock deltaClock;
    sf::Clock keyClock;
    const sf::Int32 keyDebounceMs = 150;

    while (window.isOpen())
    {
        sf::Time dt = deltaClock.restart();

        // Event handling
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Global events
            if (event.type == sf::Event::Closed)
            {
                window.close();
                break;
            }

            // State-specific input handling
            if (currentState == GameState::Menu)
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    // Debounce navigation keys so holding doesn't skip too fast
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
                            // Start new game
                            game.reset(); // reset state if available
                            currentState = GameState::Playing;
                        }
                        else if (sel == 1)
                        {
                            // Scores - not implemented, keep in menu or switch to Scores state
                            currentState = GameState::Scores;
                        }
                        else if (sel == 2)
                        {
                            // Exit
                            currentState = GameState::Exiting;
                            window.close();
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
                // Allow returning to menu with Escape or Enter
                if (event.type == sf::Event::KeyPressed &&
                    (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Enter))
                {
                    currentState = GameState::Menu;
                }
            }
        } // end event loop

        // Update logic
        if (currentState == GameState::Playing)
        {
            game.update(dt);
            // if game finished, return to menu (or handle differently)
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
            // Simple placeholder: reuse menu drawing or render scores screen if implemented.
            // For now draw the menu so window is not empty.
            menu.draw(window);
        }

        window.display();
    }

    return 0;
}
