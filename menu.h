#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#define MAX_LICZBA_POZIOMOW 4

// Menu class - header + inline implementations.
// NOTE: This header no longer contains a main() function or any top-level execution code.

class Menu
{
private:
    sf::Font font;
    sf::Text menu[MAX_LICZBA_POZIOMOW]; // maksymalna liczba poziomow
    int selectedItem = 0;
    bool fontLoaded = false;
    sf::RectangleShape entries[MAX_LICZBA_POZIOMOW];

public:
    Menu(float width, float height);
    ~Menu() = default;

    // przesun do gory
    void przesunG();

    // przesun w dol
    void przesunD();

    // zwroc poziom menu
    int getSelectedItem() { return selectedItem; }

    // rysuj menu w oknie
    void draw(sf::RenderWindow &window);
};


// Konstruktor - ustawia teksty menu i pozycje
Menu::Menu(float width, float height)
{
    // Spróbuj kilku standardowych ścieżek do czcionki
    const std::vector<std::string> candidates = {
        "arial.ttf",
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
        // Jeśli żadna ścieżka nie zadziałała, kontynuujemy bez fontu i
        // przygotowujemy graficzne zastępstwo (prostokąty) tak by aplikacja
        // nie kończyła się błędem i użytkownik dalej widział interfejs menu.
        std::cerr << "Warning: could not load font from standard locations. Menu will be rendered using simple shapes.\n";

        sf::Vector2f size(width / 3.f, 40.f);
        for (int i = 0; i < MAX_LICZBA_POZIOMOW; ++i)
        {
            entries[i].setSize(size);
            entries[i].setFillColor(sf::Color(50, 50, 50));
            entries[i].setOutlineColor(sf::Color::White);
            entries[i].setOutlineThickness(2.f);
            entries[i].setPosition(width / 3.f, height / (MAX_LICZBA_POZIOMOW + 1.f) * (i + 1) - size.y / 2.f);
        }
        // highlight currently selected entry
        entries[selectedItem].setFillColor(sf::Color::Cyan);
        return;
    }

    // rysowanie elementow menu (czcionka załadowana)
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Cyan);
    menu[0].setString("Nowa gra");
    menu[0].setPosition(sf::Vector2f(width / 3.f, height / (MAX_LICZBA_POZIOMOW + 1.f) * 1.f));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Wczytaj");
    menu[1].setPosition(sf::Vector2f(width / 3.f, height / (MAX_LICZBA_POZIOMOW + 1.f) * 2.f));

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Ostatnie wyniki");
    menu[2].setPosition(sf::Vector2f(width / 3.f, height / (MAX_LICZBA_POZIOMOW + 1.f) * 3.f));

    menu[3].setFont(font);
    menu[3].setFillColor(sf::Color::White);
    menu[3].setString("Wyjscie");
    menu[3].setPosition(sf::Vector2f(width / 3.f, height / (MAX_LICZBA_POZIOMOW + 1.f) * 4.f));

    // Ensure the initially selected item is styled
    if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW)
    {
        menu[selectedItem].setFillColor(sf::Color::Cyan);
        menu[selectedItem].setStyle(sf::Text::Bold);
    }
}

// rysowanie menu w biezacym oknie
void Menu::draw(sf::RenderWindow &window)
{
    if (fontLoaded)
    {
        for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++)
        {
            window.draw(menu[i]);
        }
    }
    else
    {
        // Rysuj zastępcze prostokąty gdy brak czcionki.
        // Dzięki temu aplikacja nie wykazuje krytycznych błędów i użytkownik
        // ma widoczną reprezentację menu nawet bez fontu.
        for (int i = 0; i < MAX_LICZBA_POZIOMOW; ++i)
        {
            window.draw(entries[i]);
        }
    }
}

void Menu::przesunG()
{
    if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW)
    {
        menu[selectedItem].setFillColor(sf::Color::White);
        menu[selectedItem].setStyle(sf::Text::Regular);
        selectedItem--;
        if (selectedItem < 0)
            selectedItem = MAX_LICZBA_POZIOMOW - 1;
        menu[selectedItem].setFillColor(sf::Color::Cyan);
        menu[selectedItem].setStyle(sf::Text::Bold);
    }
}

void Menu::przesunD()
{
    if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW)
    {
        menu[selectedItem].setFillColor(sf::Color::White);
        menu[selectedItem].setStyle(sf::Text::Regular);
        selectedItem++;
        if (selectedItem >= MAX_LICZBA_POZIOMOW)
            selectedItem = 0;
        menu[selectedItem].setFillColor(sf::Color::Cyan);
        menu[selectedItem].setStyle(sf::Text::Bold);
    }
}

#endif // MENU_H
