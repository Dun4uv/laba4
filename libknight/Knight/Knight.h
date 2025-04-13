#ifndef KNIGHT
#define KNIGHT
#include <random>

class Knight {
private:
    int health=1;
    int maxHealth=1;
    int armor=1;
    int maxArmor=1;
    int damage=1;
    double blockChance=0;
    int specialSkillUses=0;
    int specialSkillCooldown=0;

    std::default_random_engine rng;
    std::uniform_real_distribution<double> dist;

public:
    Knight(int health = 100, int armor = 50, int damage = 20, double blockChance = 0.3, int specialSkillUses = 3);
    void takeDamage(int inputDamage, const std::string& attackerName = "");
    void useSpecialSkill();
    void updateCooldown();
    int getHealth() const;
    int getMaxHealth() const;
    int getArmor() const;
    int getDamage() const;
    int getSpecialSkillUses() const;
    int getSpecialSkillCooldown() const;
    double getBlockChance() const;
    bool isAlive() const;
};
#endif
