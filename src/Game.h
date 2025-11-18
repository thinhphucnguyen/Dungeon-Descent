#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include <vector>
#include <random>

class Game {
private:
    Player player;
    std::vector<Player> npcList;
    size_t currentEnemyIndex;
    int turnCounter;
    int difficultyLvl;
    unsigned int rngSeed;
    std::mt19937 rng;

    // Helper functions
    void displayBanner();
    void displayStatus();
    void displayPlayerHUD();
    void displayEnemyHUD();
    int getPlayerChoice();
    void handlePlayerTurn();
    void handleEnemyTurn();

public:
    Game(int difficulty);
    void run();
};

#endif