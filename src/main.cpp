#include "Game.h"
#include <iostream>
#include <thread>
#include <chrono>

using std::cout;
using std::cin;

// ANSI color codes
const char* RED     = "\033[31m";
const char* GREEN   = "\033[32m";
const char* YELLOW  = "\033[33m";
const char* CYAN    = "\033[36m";
const char* MAGENTA = "\033[35m";
const char* RESET   = "\033[0m";
const char* BOLD    = "\033[1m";

void clearScreen()
{
    // Use ANSI escape codes - works on Mac, Linux, and modern Windows terminals
    cout << "\033[2J\033[H" << std::flush;
}

void printSlow(const std::string& text, int delayMs = 30)
{
    for (char c : text)
    {
        cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
}

void animatedTitle()
{
    cout << CYAN << BOLD;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    cout << "\n";
    cout << "  ═════════════════════════════════════════════════════════\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    cout << "  ║                                                       ║\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    cout << "  ║         ";
    printSlow("D U N G E O N   D E S C E N T", 40);
    cout << "           ║\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    cout << "  ║                                                       ║\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    cout << "  ═════════════════════════════════════════════════════════\n";
    cout << RESET;
    cout << "\n";
}

void printHeroAscii()
{
    cout << CYAN;
    cout << "                    _O_\n";
    cout << "                     H\n";
    cout << "                    /|\\\n";
    cout << "                   [___]\n";
    cout << "                    / \\\n";
    cout << "                   /   \\\n";
    cout << RESET;
}

void printDungeonEntrance()
{
    cout << YELLOW;
    cout << "              _______________\n";
    cout << "             |   DUNGEON    |\n";
    cout << "             |    ENTRANCE  |\n";
    cout << "             |_____________|\n";
    cout << "             |  ___   ___  |\n";
    cout << "             | |   | |   | |\n";
    cout << "             | |___| |___| |\n";
    cout << "             |_____________|\n";
    cout << RESET;
}

void displayIntro()
{
    clearScreen();
    animatedTitle();
    
    cout << "\n";
    printHeroAscii();
    cout << "\n";
    
    cout << YELLOW << "              ";
    printSlow("A brave hero stands before", 20);
    cout << "\n              ";
    printSlow("the ancient dungeon doors...", 20);
    cout << RESET << "\n\n";
    
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
    printDungeonEntrance();
    cout << "\n";
}

void displayDifficultyMenu()
{
    cout << "\n";
    cout << BOLD << CYAN << "  ╔═══════════════════════════════════════════════╗\n";
    cout << "  ║        SELECT YOUR CHALLENGE                 ║\n";
    cout << "  ╚═══════════════════════════════════════════════╝\n" << RESET;
    cout << "\n";
    
    // Easy
    cout << GREEN << "  [1] " << RESET << "EASY MODE" << RESET << "\n";
    cout << "      " << YELLOW << "- Enemies have 80% health\n";
    cout << "      - Enemies deal 80% damage\n";
    cout << "      - Perfect for beginners\n" << RESET;
    cout << "\n";
    
    // Normal
    cout << CYAN << "  [2] " << RESET << "NORMAL MODE" << RESET << "\n";
    cout << "      " << YELLOW << "- Balanced challenge\n";
    cout << "      - Standard enemy stats\n";
    cout << "      - Recommended for most players\n" << RESET;
    cout << "\n";
    
    // Hard
    cout << RED << "  [3] " << RESET << "HARD MODE" << RESET << "\n";
    cout << "      " << YELLOW << "- Enemies have 130% health\n";
    cout << "      - Enemies deal 120% damage\n";
    cout << "      - Only for the bravest warriors\n" << RESET;
    cout << "\n";
    
    cout << CYAN << "  ════════════════════════════════════════════════\n" << RESET;
    cout << "\n";
}

int main()
{
    displayIntro();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    
    displayDifficultyMenu();
    
    cout << CYAN << "  Enter your choice (1-3): " << RESET;
    
    int difficulty = 2;
    cin >> difficulty;

    if (difficulty < 1 || difficulty > 3)
    {
        cout << RED << "\n  Invalid choice! " << RESET;
        printSlow("Defaulting to NORMAL MODE...", 30);
        cout << "\n";
        difficulty = 2;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    else
    {
        cout << "\n" << GREEN << "  Challenge accepted! " << RESET;
        
        if (difficulty == 1)
            printSlow("Entering EASY MODE...", 30);
        else if (difficulty == 2)
            printSlow("Entering NORMAL MODE...", 30);
        else
            printSlow("Entering HARD MODE... May the gods be with you!", 30);
        
        cout << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    clearScreen();
    
    Game game(difficulty);
    game.run();

    return 0;
}