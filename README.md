#projekt_informatyka_2025_26

Prosty projekt w języku C++ przy użyciu biblioteki SFML 2.6.x na potrzeby zajęć projekt informatyka II

Opis:
Projekt "arkanoid", to prosta w zamysle gra wideo polegająca na sterowaniu paletką przy użyciu strzałek w celu odbijania piłki i zdobywania punktów poprzez trafianie/niszczenie bloczków. Gra zawiera mechanikę: 
- Sterowanie paletką
- Odbijanie piłki
- Zdobywanie punktów
- Zapisywania najlepszego wyniku
- Niszczenie bloczków
- Zapisywania stanu gry pod przyciskiem "P" (zapisuje tylko jeden stan gry, nie wspiera wielokrotnego zapisywania stanu gry)
- Wczytywanie zapisu
- "Game loop" - po zniszczeniu wszystkich bloczków program renderuje na nowo bloczki nie resetując przytym zdobytych punktów
- Stosuje proste grafiki i animacjie
- 3 różne stany gry

## Instalacja i Uruchomienie

1.  **Zainstaluj zależności:**
    *   Kompilator C++ (np. GCC/g++).
    *   CMake (wersja 3.10 lub nowsza).
    *   Bibliotekę **SFML** w wersji **2.6.x**.

2.  **Sklonuj repozytorium**.
    ```bash
    git clone https://github.com/username/projekt_informatyka_2025_26.git
    ```

3.  **Utwórz katalog `build`** i przejdź do niego:
    ```bash
    mkdir build
    cd build
    ```

4.  **Skonfiguruj projekt** za pomocą CMake:
    ```bash
    cmake ..
    ```

5.  **Skompiluj projekt**:
    ```bash
    cmake --build .
    ```

6.  **Uruchom grę**:
    Plik wykonywalny `arkanoid` znajdzie się w katalogu `build`.
    ```bash
    ./arkanoid
    ```
