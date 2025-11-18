#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>

class Player{
private:
    std::string name;
    double Hp;
    double MaxHp;
    double attackPower;
    double defense;
    bool isAlive = true; //default value - true 
    int HealPotions = 2; //default value

    // Leveling system
    int level = 1;
    int exp = 0;
    int expToNext = 10;

    // Skill system: limited charges for special attack
    int specialCharges = 3;

public:
    Player(std::string name, double Hp, double attackPower, double defense)
        : name(name), Hp(Hp), MaxHp(Hp), attackPower(attackPower), defense(defense) {}

    // Getters
    double getHp()
    {
        return this->Hp;
    }

    double getMaxHp()
    {
        return this->MaxHp;
    }

    double getAttack()
    {
        return this->attackPower;
    }

    std::string getName()
    {
        return this->name;
    }

    double getDefense()
    {
        return this->defense;
    }

    bool getisAlive()
    {
        return this->isAlive;
    }

    int getHealPotions()
    {
        return this->HealPotions;
    }

    int getLevel()
    {
        return this->level;
    }

    int getExp()
    {
        return this->exp;
    }

    int getExpToNext()
    {
        return this->expToNext;
    }

    int getSpecialCharges()
    {
        return this->specialCharges;
    }

    //Setters / state changes
    void Kill()
    {
        this->isAlive = false;
    }

    void changeHp(double amount)
    {
        // For healing potions 
        this->Hp = this->getHp() + amount;
        if(this->Hp > MaxHp)
            this->Hp = MaxHp;
        else if(this->Hp <= 0)
        {
            this->Hp = 0;
            this->Kill();
        }
    }

    void setHealingPotions()
    {
        if (this->getHealPotions() > 0)
            this->HealPotions = this->getHealPotions() - 1;
        else
            std::cout<<"Healing Potion Inventory depleted!\n";
    }

    // Methods
    void DmgHp(double dmgInflicted)
    {
        this->Hp = this->getHp() - dmgInflicted;
        if (this->getHp() <= 0)
        {
            this->Hp = 0;
            this->Kill();
        }
    }

    // Basic attack with minimum damage rule
    void attack(Player &target)
    {
        double atk = getAttack();
        double def = target.getDefense();

        double rawDamage = atk - def;
        if (rawDamage < 1) rawDamage = 1; // minimum damage rule

        target.DmgHp(rawDamage);

        std::cout << rawDamage << " Damage Inflicted on " 
                  << target.getName() << "\n";
    }

    // Special skill attack: stronger but limited uses
    void specialAttack(Player &target)
    {
        if (this->specialCharges <= 0)
        {
            std::cout << "No skill charges left!\n";
            return;
        }

        this->specialCharges--;

        double atk = getAttack();
        double def = target.getDefense();

        double rawDamage = atk - def;
        if (rawDamage < 1) rawDamage = 1;

        double finalDamage = rawDamage * 1.5; // stronger skill

        target.DmgHp(finalDamage);

        std::cout << ">>> SPECIAL ATTACK! " << finalDamage 
                  << " damage dealt to " << target.getName() << "!\n";
    }

    void heal()
    {
        if(this->getHealPotions() > 0)
        {
            // Potions heal 5 Hp points
            this->changeHp(5);
            this->setHealingPotions();
        }
        else
        {
            std::cout << "No potions left!\n";
        }
    }

    // Leveling / EXP
    void addExp(int amount)
    {
        if (!this->getisAlive()) return;

        this->exp += amount;
        while (this->exp >= this->expToNext)
        {
            levelUp();
        }
    }

    void levelUp()
    {
        this->exp -= this->expToNext;
        this->level++;
        this->expToNext = static_cast<int>(this->expToNext * 1.5);

        // Stat growth on level up
        this->MaxHp += 5;
        this->attackPower += 1;
        this->defense += 1;
        this->Hp = this->MaxHp;

        std::cout << "\n*** " << this->name 
                  << " leveled up to Level " << this->level << "! ***\n";
        std::cout << "Max HP: " << this->MaxHp 
                  << " | Attack: " << this->attackPower 
                  << " | Defense: " << this->defense << "\n\n";
    }
    
};

#endif
