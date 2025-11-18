# 
<p align="center">

```
██████╗ ██╗   ██╗███╗   ██╗ ██████╗ ███████╗ ██████╗ ███╗   ██╗
██╔══██╗██║   ██║████╗  ██║██╔════╝ ██╔════╝██╔═══██╗████╗  ██║
██║  ██║██║   ██║██╔██╗ ██║██║  ███╗█████╗  ██║   ██║██╔██╗ ██║
██║  ██╗██║   ██║██║╚██╗██║██║   ██║██╔══╝  ██║   ██║██║╚██╗██║
██████╔╝╚██████╔╝██║ ╚████║╚██████╔╝███████╗╚██████╔╝██║ ╚████║
╚═════╝  ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝  ╚═══╝

██████╗ ███████╗███████╗ ██████╗███████╗███╗   ██╗████████╗
██╔══██╗██╔════╝██╔════╝██╔════╝██╔════╝████╗  ██║╚══██╔══╝
██║  ██║█████╗  ███████╗██║     █████╗  ██╔██╗ ██║   ██║   
██╔══██╗██╔══╝  ╚════██║██║     ██╔══╝  ██║╚██╗██║   ██║   
██████╔╝███████╗███████║╚██████╗███████╗██║ ╚████║   ██║   
╚═════╝ ╚══════╝╚══════╝ ╚═════╝╚══════╝╚═╝  ╚═══╝   ╚═╝    

A  T E R M I N A L -  B A S E D  D U N G E O N   C R A W L E R

```

A terminal-based RPG dungeon crawler game with turn-based combat, ASCII art, and progressive difficulty.
```
╔══════════════════════════════════════════════════════════════════════════╗
║                     DUNGEON DESCENT GAMEPLAY                             ║
╚══════════════════════════════════════════════════════════════════════════╝

┌─────────────────────┐  ┌─────────────────────┐  ┌─────────────────────┐
│   STAGE 1/3         │  │   STAGE 2/3         │  │   STAGE 3/3         │
│   ═════════         │  │   ═════════         │  │   ═════════         │
│                     │  │                     │  │                     │
│      SKELETON       │  │       WITCH         │  │     MINOTAUR        │
│         .-.         │  │         /\          │  │      (__)(__)       │
│        (o.o)        │  │        /**\         │  │      /      \       │
│         |=|         │  │       /****\        │  │     | ^    ^ |      │
│        __|__        │  │      /  ^  ^\       │  │     |   ()   |      │
│      //.=|=.\\      │  │     |  (o)(o) |     │  │    /|        |\     │
│                     │  │                     │  │   / |  ____  | \    │
│   HP: ████░░ 8      │  │   HP: ██████░ 12    │  │  HP: ████████ 20    │
│   ATK: 2  DEF: 1    │  │   ATK: 3  DEF: 2    │  │  ATK: 5  DEF: 4     │
│                     │  │                     │  │                     │
│   DIFFICULTY: ★     │  │   DIFFICULTY: ★★    │  │  DIFFICULTY: ★★★    │
└─────────────────────┘  └─────────────────────┘  └─────────────────────┘
            │                       │                       │
            ▼                       ▼                       ▼
        [FIGHT]                  [FIGHT]               [FINAL BOSS]
```       
## What It Does

Fight through a dungeon with three enemies (Skeleton, Witch, Minotaur) using:
- **Attack** - Deal damage
- **Heal** - Use potions to restore HP
- **Special Skill** - 1.5x damage attack (limited uses)

Level up, gain stats, and choose from 3 difficulty modes (Easy, Normal, Hard).
```   
    ╔═════════════════════════════════════════════════════════════╗
    ║                    ENEMY #1: SKELETON                       ║
    ╠═════════════════════════════════════════════════════════════╣
    ║         .-.                                                 ║
    ║        (o.o)              HP: [########........] 8/8        ║
    ║         |=|                                                 ║
    ║        __|__                                                ║
    ║      //.=|=.\\             ATK: 2  |  DEF: 1                ║
    ║     // .=|=. \\                                             ║
    ║        || ||                                                ║
    ╚═════════════════════════════════════════════════════════════╝
                                  │
                   ┌──────────────┼──────────────┐
                   │              │              │
              ┌────▼────┐    ┌────▼────┐   ┌────▼────┐
              │ ATTACK  │    │  HEAL   │   │ SPECIAL │
              │  Deal   │    │ Restore │   │  1.5x   │
              │ Damage  │    │  +5 HP  │   │ Damage  │
              └────┬────┘    └────┬────┘   └────┬────┘
                   │              │              │
                   └──────────────┼──────────────┘
                                  │
                                  ▼
    ╔═════════════════════════════════════════════════════════════╗
    ║                    ⚔️ COMBAT PHASE ⚔️                        ║
    ╠═════════════════════════════════════════════════════════════╣
    ║  HERO (YOU)                     VS            SKELETON      ║
    ║   _O_                                           .-.         ║
    ║    H                                           (o.o)        ║
    ║   /|\          ────────────────>                |=|         ║
    ║  [___]         ◄────────────────              __|__         ║
    ║   / \                                       //.=|=.\\       ║
    ║                                                             ║
    ║  HP: [##############....] 30/30   HP: [####........] 4/8    ║
    ║  ATK: 3  |  DEF: 3                ATK: 2  |  DEF: 1         ║
    ║  Potions: 2  |  Skills: 3                                   ║
    ╚═════════════════════════════════════════════════════════════╝
```   
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
