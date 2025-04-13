#ifndef BATTLE
#define BATTLE
#include "../Knight/Knight.h"
#include <vector>

void simulateTurn(Knight& attacker, Knight& defender, bool isPlayer, const std::string& attackerName, const std::string& defenderName);
void duel(std::vector<Knight>& knights, size_t k1Index, size_t k2Index, int mode);
void printKnights(const std::vector<Knight>& knights);
#endif
