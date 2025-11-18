#include "Game.h"
#include <iostream>
#include <iomanip>
#include <ctime>

using std::cout;
using std::cin;
using std::string;

namespace {
    // Simple ANSI color helpers (graphics in terminal)
    const char* RED     = "\033[31m";
    const char* GREEN   = "\033[32m";
    const char* YELLOW  = "\033[33m";
    const char* CYAN    = "\033[36m";
    const char* MAGENTA = "\033[35m";
    const char* RESET   = "\033[0m";

    void printHpBar(double hp, double maxHp)
    {
        int width = 20;
        double ratio = (maxHp > 0) ? hp / maxHp : 0.0;
        if (ratio < 0) ratio = 0;
        if (ratio > 1) ratio = 1;

        int filled = static_cast<int>(ratio * width + 0.5);

        cout << "[";
        for (int i = 0; i < filled; ++i) cout << "#";
        for (int i = filled; i < width; ++i) cout << ".";
        cout << "]";
    }

    void printEnemyArt(const string& enemyName)
    {
        cout << "\n";
        if (enemyName == "Skeleton")
        {
            cout << RED;
            cout << "         .-.  \n";
            cout << "        (o.o) \n";
            cout << "         |=|  \n";
            cout << "        __|__ \n";
            cout << "      //.=|=.\\\\\n";
            cout << "     // .=|=. \\\\\n";
            cout << "     \\\\ .=|=. //\n";
            cout << "      \\\\(_=_)//\n";
            cout << "       (:| |:)\n";
            cout << "        || ||  \n";
            cout << "        () ()  \n";
            cout << "        || ||  \n";
            cout << "        || ||  \n";
            cout << "       ==' '==\n";
            cout << RESET;
        }
        else if (enemyName == "Witch")
        {
            cout << "\033[35m"; // Magenta
            cout << "           /\\ \n";
            cout << "          /**\\\n";
            cout << "         /****\\   \n";
            cout << "        /      \\\n";
            cout << "       /  ^  ^  \\\n";
            cout << "      |  (o)(o)  |\n";
            cout << "      |     <    |\n";
            cout << "       \\  \\___/  /\n";
            cout << "        \\_______/\n";
            cout << "          _|_|_\n";
            cout << "         | |_| |\n";
            cout << "        /| | | |\\\n";
            cout << "       {   | |   }\n";
            cout << "        \\  | |  /\n";
            cout << "         '-'-'-'\n";
            cout << RESET;
        }
        else if (enemyName == "Minotaur")
        {
            cout << YELLOW;
            cout << "       (__)(__)\n";
            cout << "       /      \\\n";
            cout << "      | ^    ^ |\n";
            cout << "      |   ()   |\n";
            cout << "     /|        |\\\n";
            cout << "    / |  ____  | \\\n";
            cout << "   |  | |    | |  |\n";
            cout << "   |  \\_/    \\_/  |\n";
            cout << "    \\    VVVV    /\n";
            cout << "     \\__________/\n";
            cout << "        ||  ||\n";
            cout << "       /||  ||\\\n";
            cout << "      / ||  || \\\n";
            cout << "     |__||  ||__|\n";
            cout << "        /|  |\\\n";
            cout << "       /_|  |_\\\n";
            cout << RESET;
        }
        cout << "\n";
    }

    void printHeroArt()
    {
        cout << "\n" << CYAN;
        cout << "       _O_\n";
        cout << "        H\n";
        cout << "       /|\\      \n";
        cout << "      [___]\n";
        cout << "       / \\\n";
        cout << "      /   \\\n";
        cout << RESET << "\n";
    }

    void printDungeonProgress(int current, int total)
    {
        cout << "\n" << YELLOW << "╔════════════════════════════════════╗\n";
        cout << "║      DUNGEON PROGRESS              ║\n";
        cout << "╠════════════════════════════════════╣\n";
        cout << "║  ";
        
        for (int i = 0; i < total; ++i)
        {
            if (i < current)
                cout << GREEN << "[X]" << YELLOW;
            else if (i == current)
                cout << RED << "[!]" << YELLOW;
            else
                cout << "[ ]";
        }
        
        cout << "       ║\n";
        cout << "╚════════════════════════════════════╝\n" << RESET;
    }
}

// -----------------------------------
//  Game Constructor
// -----------------------------------
Game::Game(int difficulty)
    : player("Hero", 30, 3, 3),
      currentEnemyIndex(0),
      turnCounter(1),
      difficultyLvl(difficulty),
      rngSeed(static_cast<unsigned int>(std::time(nullptr))),
      rng(rngSeed)
{
    // Difficulty scaling for enemies
    // Base stats, then tweak per difficulty
    double hpMul   = 1.0;
    double atkMul  = 1.0;
    double defMul  = 1.0;

    if (difficultyLvl == 1) {         // Easy
        hpMul  = 0.8;
        atkMul = 0.8;
        defMul = 0.8;
    } else if (difficultyLvl == 2) {  // Normal
        hpMul  = 1.0;
        atkMul = 1.0;
        defMul = 1.0;
    } else {                          // Hard
        hpMul  = 1.3;
        atkMul = 1.2;
        defMul = 1.1;
    }

    auto makeEnemy = [&](const string &name, double baseHp, double baseAtk, double baseDef) {
        double hp  = baseHp  * hpMul;
        double atk = baseAtk * atkMul;
        double def = baseDef * defMul;
        return Player(name, hp, atk, def);
    };

    Player enemy1 = makeEnemy("Skeleton", 8, 2, 1);
    Player enemy2 = makeEnemy("Witch",    12, 3, 2);
    Player enemy3 = makeEnemy("Minotaur", 20, 5, 4);

    npcList.push_back(enemy1);
    npcList.push_back(enemy2);
    npcList.push_back(enemy3);
}

// -----------------------------------
//  Banner
// -----------------------------------
void Game::displayBanner()
{
    cout << CYAN;
    cout << "\n╔═══════════════════════════════════════════════╗\n";
    cout << "║                                               ║\n";
    cout << "║            DUNGEON DESCENT                    ║\n";
    cout << "║                                               ║\n";
    cout << "║         Venture into the depths...            ║\n";
    cout << "║           Defeat all enemies!                 ║\n";
    cout << "║                                               ║\n";
    cout << "╚═══════════════════════════════════════════════╝\n";
    cout << RESET;
}

// -----------------------------------
//  Main Game Loop
// -----------------------------------
void Game::run()
{
    displayBanner();
    
    cout << "\n" << YELLOW << "  The ancient dungeon doors creak open before you...\n";
    cout << "  Three deadly foes await in the darkness.\n";
    cout << "  Steel yourself, brave adventurer!\n" << RESET;
    cout << "\n" << CYAN << "  Press Enter to begin your descent..." << RESET;
    cin.ignore();
    cin.get();

    while(player.getisAlive() && (currentEnemyIndex < npcList.size()))
    {
        displayStatus();
        handlePlayerTurn();

        if (!npcList[currentEnemyIndex].getisAlive())
        {
            cout << "\n" << GREEN;
            cout << "╔═══════════════════════════════════╗\n";
            cout << "║            VICTORY!               ║\n";
            cout << "╠═══════════════════════════════════╣\n";
            cout << "║  " << npcList[currentEnemyIndex].getName() << " has been defeated!";
            // Pad to align with box
            int nameLen = npcList[currentEnemyIndex].getName().length();
            for(int i = 0; i < (17 - nameLen); i++) cout << " ";
            cout << "║\n";
            cout << "╚═══════════════════════════════════╝\n";
            cout << RESET;
            
            int expGain = 5;
            cout << YELLOW << "  [++" << expGain << " EXP]\n" << RESET;

            // Give EXP to player
            player.addExp(expGain);

            currentEnemyIndex++;
            if (currentEnemyIndex >= npcList.size())
                break; // no more enemies, stop before enemy turn
            
            // Prompt before next enemy
            cout << "\n" << YELLOW << "  The path ahead grows darker...\n";
            cout << "  Another enemy blocks your way!\n" << RESET;
            cout << "\n" << CYAN << "  Press Enter to continue..." << RESET;
            cin.get();
        }
        else
        {
            handleEnemyTurn();
            if(!player.getisAlive())
                break;
        }

        turnCounter++;
    }

    if(player.getisAlive())
    {
        cout << "\n" << GREEN;
        cout << "╔═══════════════════════════════════╗\n";
        cout << "║                                   ║\n";
        cout << "║        DUNGEON CLEARED!           ║\n";
        cout << "║                                   ║\n";
        cout << "║  You conquered all the enemies!   ║\n";
        cout << "║                                   ║\n";
        cout << "╚═══════════════════════════════════╝\n";
        cout << RESET;
        cout << "You pushed out of the dungeon victorious!\n";
    }
    else
    {
        cout << "\n" << RED;
        cout << "╔═══════════════════════════════════╗\n";
        cout << "║                                   ║\n";
        cout << "║             DEFEAT                ║\n";
        cout << "║                                   ║\n";
        cout << "║    The dungeon claims another     ║\n";
        cout << "║          fallen hero...           ║\n";
        cout << "║                                   ║\n";
        cout << "╚═══════════════════════════════════╝\n";
        cout << RESET;
    }
}

// -----------------------------------
//  Player Menu Input
// -----------------------------------
int Game::getPlayerChoice()
{
    int playerChoice = -1;

    cout << "\n";
    cout << CYAN << "╔═══════════════════════════════════╗\n";
    cout << "║           YOUR TURN               ║\n";
    cout << "╚═══════════════════════════════════╝\n" << RESET;
    cout << "\n";
    
    while(playerChoice < 1 || playerChoice > 3)
    {
        // Display menu options with icons and colors
        cout << GREEN << "  [1] " << RESET << "Attack" << RESET;
        cout << "          " << YELLOW << "(Deal " << player.getAttack() << " damage)\n" << RESET;
        
        cout << GREEN << "  [2] " << RESET << "Heal" << RESET;
        if(player.getHealPotions() > 0)
            cout << "            " << YELLOW << "(" << player.getHealPotions() << " potions, +5 HP)\n" << RESET;
        else
            cout << "            " << RED << "(No potions left!)\n" << RESET;
        
        cout << GREEN << "  [3] " << RESET << "Special Skill" << RESET;
        if(player.getSpecialCharges() > 0)
            cout << "   " << YELLOW << "(" << player.getSpecialCharges() << " charges, 1.5x damage)\n" << RESET;
        else
            cout << "   " << RED << "(No charges left!)\n" << RESET;
        
        cout << "\n" << CYAN << "  Enter your choice (1-3): " << RESET;
        cin >> playerChoice;
        
        if(playerChoice < 1 || playerChoice > 3)
        {
            cout << RED << "  Invalid choice! Please select 1, 2, or 3.\n\n" << RESET;
        }
        else if(playerChoice == 2 && player.getHealPotions() <= 0)
        {
            cout << RED << "  You have no healing potions left! Choose another action.\n\n" << RESET;
            playerChoice = -1;
        }
        else if(playerChoice == 3 && player.getSpecialCharges() <= 0)
        {
            cout << RED << "  You have no special charges left! Choose another action.\n\n" << RESET;
            playerChoice = -1;
        }
    }
    
    cin.ignore(); // Clear input buffer
    return playerChoice;
}

// -----------------------------------
//  Player Turn
// -----------------------------------
void Game::handlePlayerTurn()
{
    int playerChoice = getPlayerChoice();

    cout << "\n";
    cout << YELLOW << "════════════════════════════════════\n" << RESET;
    
    if (playerChoice == 1)
    {
        cout << RED << "\n  >> You raise your weapon and strike!\n" << RESET;
        cout << "  ";
        for(int i = 0; i < 3; i++) {
            cout << "." << std::flush;
            // Small delay for effect (optional, can remove if too slow)
        }
        cout << "\n";
        player.attack(npcList[currentEnemyIndex]);
    }
    else if(playerChoice == 2)
    {
        cout << GREEN << "\n  >> You uncork a healing potion and drink it!\n" << RESET;
        cout << "  ";
        for(int i = 0; i < 3; i++) {
            cout << "." << std::flush;
        }
        cout << "\n";
        player.heal();
    }
    else if (playerChoice == 3)
    {
        cout << MAGENTA << "\n  >> You focus your energy and unleash your power!\n" << RESET;
        cout << "  ";
        for(int i = 0; i < 3; i++) {
            cout << "." << std::flush;
        }
        cout << "\n";
        player.specialAttack(npcList[currentEnemyIndex]);
    }
    
    cout << YELLOW << "\n════════════════════════════════════\n" << RESET;
    cout << "\n" << CYAN << "Press Enter to continue..." << RESET;
    cin.get();
}

// -----------------------------------
//  Enemy Turn (RNG-based AI)
// -----------------------------------
void Game::handleEnemyTurn()
{
    Player &enemy = npcList[currentEnemyIndex];
    if (!enemy.getisAlive())
        return;

    cout << "\n";
    cout << RED << "╔═══════════════════════════════════╗\n";
    cout << "║           ENEMY TURN              ║\n";
    cout << "╚═══════════════════════════════════╝\n" << RESET;
    cout << "\n";

    cout << YELLOW << "  " << enemy.getName() << " is preparing to act...\n" << RESET;
    
    // Suspense dots
    cout << "  ";
    for(int i = 0; i < 3; i++) {
        cout << "." << std::flush;
    }
    cout << "\n\n";

    std::uniform_int_distribution<int> dist(0, 99);
    int roll = dist(rng);

    double hpRatio = enemy.getHp() / enemy.getMaxHp();

    if (hpRatio < 0.3 && enemy.getHealPotions() > 0)
    {
        // Low HP behavior: 60% chance to heal, 40% attack
        if (roll < 60)
        {
            cout << GREEN << "  >> " << enemy.getName() << " looks wounded and drinks a potion!\n" << RESET;
            enemy.heal();
        }
        else
        {
            cout << RED << "  >> " << enemy.getName() << " fights desperately through the pain!\n" << RESET;
            enemy.attack(player);
        }
    }
    else
    {
        // Normal behavior
        if (enemy.getSpecialCharges() > 0 && roll >= 80)
        {
            cout << MAGENTA << "  >> " << enemy.getName() << " channels dark energy!\n" << RESET;
            enemy.specialAttack(player);
        }
        else
        {
            cout << RED << "  >> " << enemy.getName() << " launches an attack!\n" << RESET;
            enemy.attack(player);
        }
    }
    
    cout << "\n" << CYAN << "Press Enter to continue..." << RESET;
    cin.get();
}

// -----------------------------------
//  Status + Simple Graphics
// -----------------------------------
void Game::displayStatus()
{
    Player &enemy = npcList[currentEnemyIndex];

    printDungeonProgress(currentEnemyIndex, npcList.size());
    
    cout << "\n" << CYAN << "╔═══════════════════════════════════╗\n";
    cout << "║         TURN " << turnCounter;
    // Pad for alignment
    if(turnCounter < 10) cout << "  ";
    else if(turnCounter < 100) cout << " ";
    cout << "                      ║\n";
    cout << "╚═══════════════════════════════════╝\n" << RESET;

    // Show enemy art
    printEnemyArt(enemy.getName());
    
    displayPlayerHUD();
    displayEnemyHUD();
}

void Game::displayPlayerHUD()
{
    cout << "\n" << GREEN << "╔═══════════════════════════════════╗\n";
    cout << "║          YOUR STATUS              ║\n";
    cout << "╚═══════════════════════════════════╝\n" << RESET;
    
    // Print hero art on the left side
    cout << CYAN << "       _O_" << RESET << "        Level: " << YELLOW << player.getLevel() << RESET
         << "  |  EXP: " << YELLOW << player.getExp() << "/" << player.getExpToNext() << RESET << "\n";
    
    cout << CYAN << "        H " << RESET << "        HP: ";
    printHpBar(player.getHp(), player.getMaxHp());
    cout << " " << player.getHp() << "/" << player.getMaxHp() << "\n";
    
    cout << CYAN << "       /|\\ " << RESET << "      Potions: " << YELLOW << player.getHealPotions() << RESET;
    cout << "  |  Skills: " << YELLOW << player.getSpecialCharges() << RESET << "\n";
    
    cout << CYAN << "      [___]" << RESET << "\n";
    cout << CYAN << "       / \\ " << RESET << "\n";
    cout << CYAN << "      /   \\" << RESET << "\n";
}

void Game::displayEnemyHUD()
{
    Player &enemy = npcList[currentEnemyIndex];

    cout << "\n" << RED << "╔═══════════════════════════════════╗\n";
    cout << "║          ENEMY STATUS             ║\n";
    cout << "╚═══════════════════════════════════╝\n" << RESET;
    
    cout << "  " << enemy.getName() << "\n";
    cout << "  HP: ";
    printHpBar(enemy.getHp(), enemy.getMaxHp());
    cout << " " << enemy.getHp() << "/" << enemy.getMaxHp() << "\n";
}