# projekt_informatyka_2025_26

Prosty projekt w języku C++ z wykorzystaniem biblioteki **SFML 2.6.x**, przygotowany na zajęcia z informatyki II.

## Opis projektu

"Arkanoid" to klasyczna gra wideo, w której gracz steruje paletką przy użyciu klawiszy strzałek, odbija piłkę i zdobywa punkty poprzez niszczenie bloczków.  
Projekt zawiera następujące elementy:

- Sterowanie paletką (lewo/prawo)
- Odbijanie piłki
- System punktów
- Zapisywanie najlepszego wyniku
- Niszczenie bloczków o różnej wytrzymałości
- Zapis stanu gry pod klawiszem **P** (obsługuje maksymalnie jeden slot)
- Wczytywanie zapisu
- Pętlę gry — po zniszczeniu wszystkich bloczków blokowisko generowane jest ponownie bez resetowania punktów
- Proste grafiki i animacje 
- Trzy różne stany gry
- Efekty dźwiękowe  
  (źródło audio: https://pixabay.com/sound-effects/game-bonus-02-294436/ )

## Instalacja i uruchomienie

1. **Zainstaluj zależności:**
   - Kompilator C++ (np. GCC/g++)
   - CMake (3.10+)
   - Biblioteka SFML w wersji 2.6.x

2. **Sklonuj repozytorium:**
   ```bash
   git clone https://github.com/qufc24/projekt_informatyka_2025_26.git
```

3. **Utwórz katalog build i przejdź do niego:**
   ```bash
   mkdir build
   cd build
```

4. **Wygeneruj pliki projektu:**
   ```bash
   cmake ..
```
5. **Skompiluj projekt:**
   ```bash
   cmake --build .
```

6. **Uruchom grę:**
   ```bash
   ./arkanoid



Zgodnie z wytycznymi wykorzystania narzędzi GenAI w procesie kształcenia na Politechnice
Gdańskiej, dla narzędzi GenAI potencjalnie NISKIEGO stopnia ingerencji w prace studenta: oświadczam, że treści wygenerowane przy pomocy GenAI poddałem krytycznej analizie i zweryfikowałem. 

Użycie narzędzi GenAI w tym projekcie sprowadziło się głównie do: 
- lokalizacji i zrozumienia błędów w kodzie
- utworzenia README.md oraz CMakeLists.txt
