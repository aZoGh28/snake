# Snake (C / SDL2)

> Version française ci-dessous — English version below.

## Français

Jeu du **Snake** classique écrit en **C** avec la bibliothèque **SDL2**.

Projet personnel réalisé pour m'entraîner en C et découvrir le rendu 2D temps réel
avec SDL2 (boucle de jeu, gestion du clavier, limiteur de FPS).

### Fonctionnalités
- Serpent complet (tête + corps qui suit) contrôlé au clavier.
- Apparition de pommes et croissance du serpent quand il en mange.
- Détection de collision / mort du serpent.
- Compteur et limiteur de FPS.
- Petits détails visuels (yeux du serpent).
- Code final nettoyé (pas de fuites mémoire).

### Compilation & exécution
Nécessite **SDL2** installé, ainsi que les en-têtes de **SDL2_ttf** (incluses
dans le code mais non utilisées, elles doivent tout de même être présentes à
la compilation) :

```bash
sudo apt install libsdl2-dev libsdl2-ttf-dev   # Debian/Ubuntu
gcc snake.c -o snake -lSDL2 -lm
./snake
```

### Structure
- `snake.c` — l'intégralité du jeu.
- `README.md` — ce fichier.

---

## English

Classic **Snake** game written in **C** with the **SDL2** library.

A personal project built to practice C and to explore real-time 2D rendering with
SDL2 (game loop, keyboard handling, FPS limiter).

### Features
- Full snake (head + trailing body) controlled with the keyboard.
- Apples spawning and snake growth when eaten.
- Collision detection / snake death.
- FPS counter and limiter.
- Small visual touches (snake eyes).
- Cleaned-up final code (no memory leaks).

### Build & run
Requires **SDL2** installed, plus the **SDL2_ttf** headers (included in the
code but unused — they still need to be present at compile time):

```bash
sudo apt install libsdl2-dev libsdl2-ttf-dev   # Debian/Ubuntu
gcc snake.c -o snake -lSDL2 -lm
./snake
```

### Structure
- `snake.c` — the whole game.
- `README.md` — this file.
