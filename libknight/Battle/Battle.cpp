#include "Battle.h"
#include <iostream>
#include <limits>
#include <random>

void pauseForInput() {
    std::cout << "[Нажмите Enter, чтобы продолжить...]\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void simulateTurn(Knight& attacker, Knight& defender, bool isPlayer, const std::string& attackerName, const std::string& defenderName) {
    int action = 1;
    bool validAction = false;

    while (!validAction) {
        if (isPlayer) {
            bool canUseSpecialSkill = attacker.getSpecialSkillUses() > 0 && attacker.getSpecialSkillCooldown() == 0;

            if (canUseSpecialSkill) {
                std::cout << "Выберите действие:\n1 - Атака\n2 - Использовать особое умение\n> ";
                std::cin >> action;

                while (std::cin.fail() || (action != 1 && action != 2)) {
                    std::cout << "Неверный ввод. Попробуйте снова:\n1 - Атака\n2 - Использовать особое умение\n> ";
                    std::cin >> action;
                }
            }
            else {
                std::cout << "Особое умение недоступно (Осталось использований: " << attacker.getSpecialSkillUses()
                    << ", Перезарядка: " << attacker.getSpecialSkillCooldown() << ").\n";
                std::cout << "→ Атака!\n";
                action = 1;
            }
        }
        else {
            static std::default_random_engine rng(std::random_device {}());
            static std::uniform_int_distribution<int> randPercent(0, 99);

            double healthRatio = static_cast<double>(attacker.getHealth()) / attacker.getMaxHealth();
            int selfArmor = attacker.getArmor();
            double enemyHealthRatio = static_cast<double>(defender.getHealth()) / defender.getMaxHealth();
            int enemyArmor = defender.getArmor();

            if (enemyHealthRatio < 0.2 && enemyArmor < 15) {
                action = 1;
            }
            else if (healthRatio < 0.3 && selfArmor < 10 && attacker.getDamage() > 5) {
                action = 2;
            }
            else if (randPercent(rng) < 30) {
                action = (randPercent(rng) % 2) + 1;
            }
            else {
                action = 1;
            }

            std::cout << "[ИИ выбирает] " << (action == 1 ? "Атака" : "Особое умение") << "\n";
        }

        if (action == 1) {
            std::cout << "→ Атака!\n";
            defender.takeDamage(attacker.getDamage(), defenderName);
            validAction = true;
        }
        else if (action == 2) {
            if (attacker.getSpecialSkillUses() > 0 && attacker.getSpecialSkillCooldown() == 0) {
                std::cout << "→ " << attackerName << " использует особое умение!\n";
                attacker.useSpecialSkill();
                validAction = true;
            }
            else if (!isPlayer) {
                std::cout << "[ИИ] Особое умение недоступно, переключается на атаку.\n";
                std::cout << "→ Атака!\n";
                defender.takeDamage(attacker.getDamage(), defenderName);
                validAction = true;
            }
        }
    }

    attacker.updateCooldown();
}

void duel(std::vector<Knight>& knights, size_t k1Index, size_t k2Index, int mode) {
    if (k1Index >= knights.size() || k2Index >= knights.size()) {
        std::cout << "Ошибка: некорректные индексы рыцарей.\n";
        return;
    }

    Knight& k1 = knights[k1Index];
    Knight& k2 = knights[k2Index];

    std::cout << "\n🎵 Битва начинается! 🎵\n";

    std::string k1Name, k2Name;
    if (mode == 1) {
        k1Name = "Игрок";
        k2Name = "ИИ";
    }
    else if (mode == 2) {
        k1Name = "ИИ 1";
        k2Name = "ИИ 2";
    }
    else if (mode == 3) {
        k1Name = "Рыцарь 1";
        k2Name = "Рыцарь 2";
    }

    int turn = 1;
    while (k1.isAlive() && k2.isAlive()) {
        std::cout << "\n--- Раунд " << turn << " ---\n";
        std::cout << "[" << k1Name << "] HP: " << k1.getHealth() << " | [" << k2Name << "] HP: " << k2.getHealth() << "\n";

        std::cout << ">>> " << k1Name << " атакует!\n";
        simulateTurn(k1, k2, mode == 1 || mode == 3, k1Name, k2Name);
        if (!k2.isAlive()) {
            if (mode != 3) {
                pauseForInput();
            }
            break;
        }

        std::cout << ">>> " << k2Name << " атакует!\n";
        simulateTurn(k2, k1, mode == 3, k2Name, k1Name);
        if (mode == 1) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            pauseForInput();
        }
        else if (mode != 3 || (mode == 3 && (!k1.isAlive() || !k2.isAlive()))) {
            pauseForInput();
        }

        turn++;
    }

    std::cout << "\n🏁 Битва окончена! ";
    if (k1.isAlive()) std::cout << k1Name << " победил!\n";
    else std::cout << k2Name << " победил!\n";

    bool k1Dead = !k1.isAlive();
    bool k2Dead = !k2.isAlive();

    if (k1Dead && k2Dead) {
        if (k2Index > k1Index) {
            knights.erase(knights.begin() + k2Index);
            knights.erase(knights.begin() + k1Index);
        }
        else {
            knights.erase(knights.begin() + k1Index);
            knights.erase(knights.begin() + k2Index);
        }
        std::cout << "Оба рыцаря пали и были удалены.\n";
    }
    else if (k1Dead) {
        knights.erase(knights.begin() + k1Index);
        std::cout << k1Name << " пал и был удалён.\n";
    }
    else if (k2Dead) {
        knights.erase(knights.begin() + k2Index);
        std::cout << k2Name << " пал и был удалён.\n";
    }
}

void printKnights(const std::vector<Knight>& knights) {
    if (knights.empty()) {
        std::cout << "Список рыцарей пуст.\n";
        return;
    }

    std::cout << "\n=== Список рыцарей ===\n";
    for (size_t i = 0; i < knights.size(); ++i) {
        const Knight& knight = knights[i];
        std::cout << "Рыцарь " << (i + 1) << ":\n";
        std::cout << "  Здоровье: " << knight.getHealth() << "/" << knight.getMaxHealth() << "\n";
        std::cout << "  Броня: " << knight.getArmor() << "\n";
        std::cout << "  Урон: " << knight.getDamage() << "\n";
        std::cout << "  Шанс блока: " << knight.getBlockChance() << "\n";
        std::cout << "  Особое умение (использований): " << knight.getSpecialSkillUses() << "\n";
        std::cout << "  Перезарядка умения: " << knight.getSpecialSkillCooldown() << "\n";
    }
    std::cout << "=====================\n";
}
