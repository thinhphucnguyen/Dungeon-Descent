# 
```
____                                         
|  _ \ _   _ _ __   __ _  ___  ___  _ __  
| | | | | | | '_ \ / _` |/ _ \/ _ \| '_ \ 
| |_| | |_| | | | | (_| |  __/ (_) | | | |
|____/ \__,_|_| |_|\__, |\___|\___/|_| |_|
                   |___/                   
____                          _   
|  _ \  ___  ___  ___ ___ _ __ | |_ 
| | | |/ _ \/ __|/ __/ _ \ '_ \| __|
| |_| |  __/\__ \ (_|  __/ | | | |_ 
|____/ \___||___/\___\___|_| |_|\__|

A Terminal RPG Dungeon Crawler
```

A terminal-based RPG dungeon crawler game with turn-based combat, ASCII art, and progressive difficulty.

## What It Does

Fight through a dungeon with three enemies (Skeleton, Witch, Minotaur) using:
- **Attack** - Deal damage
- **Heal** - Use potions to restore HP
- **Special Skill** - 1.5x damage attack (limited uses)

Level up, gain stats, and choose from 3 difficulty modes (Easy, Normal, Hard).

## Features

- Animated intro sequence with typewriter effects
- Color-coded terminal graphics (ANSI)
- Turn-based combat with enemy AI
- Experience/leveling system
- ASCII art for hero and enemies
- Interactive menus with status displays

## How to Run

**Compile:**
```bash
make
```

**Run:**
```bash
./game
```

**Clean:**
```bash
make clean
```

## Files

- `main.cpp` - Entry point, intro menu
- `Game.cpp/h` - Game logic and combat system
- `Player.cpp/h` - Character stats and actions
- `Makefile` - Build configuration

## Tech Stack

- **Language**: C++17
- **Libraries**: `<iostream>`, `<thread>`, `<chrono>`, `<random>`, `<vector>`
- **Graphics**: ANSI escape codes for colors

## Game Stats

**Player Starting Stats:**
- HP: 30, Attack: 3, Defense: 3
- 2 Healing Potions, 3 Special Charges

**Enemies (Normal Mode):**
- Skeleton: 8 HP, 2 ATK, 1 DEF
- Witch: 12 HP, 3 ATK, 2 DEF
- Minotaur: 20 HP, 5 ATK, 4 DEF
