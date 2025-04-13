#include "GameLoop.h"
#include "../libioutils/io_utils/io_utils.h"
#include "../libknight/Battle/Battle.h"
#include <iostream>

void runGameLoop(std::vector<Knight>& knights) {
    int choice;

    while (true) {
        printKnights(knights);
        std::cout << "\nМеню:\n"
            << "1. Добавить рыцаря\n"
            << "2. Редактировать рыцаря\n"
            << "3. Убрать рыцаря\n"
            << "4. Бой: Игрок vs ИИ\n"
            << "5. Бой: ИИ vs ИИ\n"
            << "6. Бой: Игрок vs Игрок\n"
            << "7. Выход\n> ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Ошибка ввода. Пожалуйста, введите число.\n";
            clear_buf();
            continue;
        }
        clear_buf();

        switch (choice) {
        case 1: {
            int hp, armor, dmg, skillUses;
            double chance;
            std::cout << "Введите ОЗ, Броню, Урон, Шанс блокировать урон (0.0–1.0), Количество использования спецспособности: ";
            std::cin >> hp >> armor >> dmg >> chance >> skillUses;
            if (std::cin.fail()) {
                std::cout << "Ошибка ввода. Рыцарь не добавлен.\n";
                clear_buf();
                break;
            }
            clear_buf();
            knights.emplace_back(hp, armor, dmg, chance, skillUses);
            break;
        }
        case 2: { 
            int idx;
            std::cout << "Введите индекс рыцаря для редактирования: ";
            std::cin >> idx;
            if (std::cin.fail()) {
                std::cout << "Ошибка ввода. Пожалуйста, введите число.\n";
                clear_buf();
                break;
            }
            clear_buf();
            if (idx >= 0 && idx < knights.size()) {
                int hp, armor, dmg, skillUses;
                double chance;
                std::cout << "Введите новые значения ОЗ, Брони, Урона, Шанса блокировать урон (0.0–1.0), Количества использования спецспособности: ";
                std::cin >> hp >> armor >> dmg >> chance >> skillUses;
                if (std::cin.fail()) {
                    std::cout << "Ошибка ввода. Рыцарь не обновлён.\n";
                    clear_buf();
                    break;
                }
                clear_buf();
                knights[idx] = Knight(hp, armor, dmg, chance, skillUses);
                std::cout << "Рыцарь " << (idx + 1) << " обновлён.\n";
            }
            else {
                std::cout << "Неверный индекс.\n";
            }
            break;
        }
        case 3: {
            int idx;
            std::cout << "Введите индекс для удаления: ";
            std::cin >> idx;
            if (std::cin.fail()) {
                std::cout << "Ошибка ввода. Пожалуйста, введите число.\n";
                clear_buf();
                break;
            }
            clear_buf();
            if (idx >= 0 && idx < knights.size()) {
                knights.erase(knights.begin() + idx);
            }
            else {
                std::cout << "Неверный индекс.\n";
            }
            break;
        }
        case 4:
        case 5:
        case 6:
            if (knights.size() < 2) {
                std::cout << "Недостаточно рыцарей!\n";
            }
            else {
                duel(knights, 0, 1, choice - 3);
            }
            break;
        case 7:
            return;
        default:
            std::cout << "Неверный выбор.\n";
            break;
        }
    }
}
