#include "print_header.h"

#include <iostream>
#include <format>
#include <string>

void print_header(const int& num) {
    std::cout << std::format("┌─ ЛР № {:<2} ─────────────────┐\n", num);
    std::cout << std::format("│  {:>8} {:<15} │\n", "Группа:", "6111");
    std::cout << std::format("│  {:>8} {:<15} │\n", "Автор:", "Крылов Даниил");
    std::cout << std::format("│  {:>8} {:<15} │\n", "Вариант:", "19");
    std::cout << "└───────────────────────────┘\n";
}


void print_result(const int& count, const bool& is_sequence) {
    std::cout << "┌─ Ответ ────────────────────────────────────────────────────────────────┐\n";
    std::cout << std::format("│ Количество элементов: {:<48} │\n", count);
    std::cout << std::format("│ {:<70} │\n", "Последовательность " + std::string(is_sequence ? "" : "НЕ ") + "является неубывающей.");
    std::cout << "└────────────────────────────────────────────────────────────────────────┘\n";
}
