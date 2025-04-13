#include "Knight.h"
#include <iostream>
Knight::Knight(int health, int armor, int damage, double blockChance, int specialSkillUses)
    : health(health), maxHealth(health), armor(armor), maxArmor(armor * 2), damage(damage),
    blockChance(blockChance), specialSkillUses(specialSkillUses >= 0 ? specialSkillUses : 0),
    specialSkillCooldown(0), dist(0.0, 1.0) {
    std::random_device rd;
    rng.seed(rd());
}

void Knight::takeDamage(int inputDamage, const std::string& attackerName) {
    int reduced = inputDamage;
    reduced -= armor * 0.2;
    if (reduced < 2) reduced = 2;

    if (dist(rng) < blockChance * 0.8) {
        reduced /= 2;
        std::cout << ">> " << (attackerName.empty() ? "Рыцарь" : attackerName) << " заблокировал половину урона!\n";
    }

    health -= reduced;
    if (health < 0) health = 0;

    armor -= inputDamage * 0.5;
    if (armor < 0) armor = 0;

    std::cout << ">> " << (attackerName.empty() ? "Рыцарь" : attackerName)
        << " получил " << reduced << " урона. Осталось HP: " << health
        << ", Броня: " << armor << "\n";
}

void Knight::useSpecialSkill() {
    if (specialSkillUses > 0 && specialSkillCooldown == 0) {
        armor += 15;
        if (armor > maxArmor) armor = maxArmor;
        damage -= 5;
        if (damage < 1) damage = 1;
        specialSkillUses--;
        specialSkillCooldown = 3;
        std::cout << ">> Использовал особое умение! Броня +15, Урон -5. Осталось использований: " << specialSkillUses << "\n";
    }
    else {
        std::cout << ">> Особое умение недоступно! Осталось использований: " << specialSkillUses
            << ", Перезарядка: " << specialSkillCooldown << "\n";
    }
}

void Knight::updateCooldown() {
    if (specialSkillCooldown > 0) {
        specialSkillCooldown--;
    }
}

int Knight::getHealth() const { return health; }
int Knight::getMaxHealth() const { return maxHealth; }
int Knight::getArmor() const { return armor; }
int Knight::getDamage() const { return damage; }
int Knight::getSpecialSkillUses() const { return specialSkillUses; }
int Knight::getSpecialSkillCooldown() const { return specialSkillCooldown; }
double Knight::getBlockChance() const { return blockChance; }
bool Knight::isAlive() const { return health > 0; }
