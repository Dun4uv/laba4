#include <gtest/gtest.h>
#include "../libknight/Knight/Knight.h"
#include "../libioutils/io_utils/io_utils.h"

class KnightTest : public ::testing::Test {
protected:
    Knight knight;

    KnightTest() : knight(100, 50, 20, 0.3, 4) {
        io_setup();
    }
};

TEST_F(KnightTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(knight.getHealth(), 100);
    EXPECT_EQ(knight.getMaxHealth(), 100);
    EXPECT_EQ(knight.getArmor(), 50);
    EXPECT_EQ(knight.getDamage(), 20);
    EXPECT_EQ(knight.getSpecialSkillUses(), 4);
    EXPECT_EQ(knight.getSpecialSkillCooldown(), 0);
    EXPECT_TRUE(knight.isAlive());
}

TEST_F(KnightTest, TakeDamageReducesHealthAndArmor) {
    knight.takeDamage(30, "");
    // Урон: 30 - 50*0.2 = 20 - Без блока
    // Броня: 50 - 30*0.5 = 35
    EXPECT_TRUE(knight.getHealth() == 80 || knight.getHealth() == 90);
    EXPECT_LE(knight.getArmor(), 35);
    EXPECT_TRUE(knight.isAlive());
}

TEST_F(KnightTest, TakeDamageMinimumDamage) {
    knight.takeDamage(1, ""); 
    // Урон: 1 - 50*0.2 = -9 -> минимум 2
    // Броня: 50 - 1*0.5 = 49.5 -> 49
    EXPECT_TRUE(knight.getHealth()==98||knight.getHealth()==99);
    EXPECT_EQ(knight.getArmor(), 49);
}

TEST_F(KnightTest, TakeDamageKillsKnight) {
    knight.takeDamage(1000, ""); 
    EXPECT_EQ(knight.getHealth(), 0);
    EXPECT_EQ(knight.getArmor(), 0);
    EXPECT_FALSE(knight.isAlive());
}

TEST_F(KnightTest, UseSpecialSkillIncreasesArmorDecreasesDamage) {
    knight.useSpecialSkill();
    EXPECT_EQ(knight.getArmor(), 65); // 50 + 15
    EXPECT_EQ(knight.getDamage(), 15); // 20 - 5
    EXPECT_EQ(knight.getSpecialSkillUses(), 3);
    EXPECT_EQ(knight.getSpecialSkillCooldown(), 3);
}

TEST_F(KnightTest, UseSpecialSkillRespectsMaxArmor) {
    knight.useSpecialSkill(); // Броня: 50 -> 65
    for (int i = 0; i < 3; ++i) knight.updateCooldown(); 
    knight.useSpecialSkill(); // Броня: 65 -> 80
    for (int i = 0; i < 3; ++i) knight.updateCooldown();
    knight.useSpecialSkill(); // Броня: 80 -> 95
    for (int i = 0; i < 3; ++i) knight.updateCooldown();
    knight.useSpecialSkill(); // Броня: 95 -> 100
    EXPECT_EQ(knight.getArmor(), 100);
    EXPECT_EQ(knight.getDamage(), 1); // 20 - 5*4-->1
    EXPECT_EQ(knight.getSpecialSkillUses(), 0);
}

TEST_F(KnightTest, UseSpecialSkillWhenUnavailable) {
    for (int i = 0; i < 4; ++i) {
        knight.useSpecialSkill();
        for (int j = 0; j < 3; ++j) knight.updateCooldown(); 
    }
    int oldArmor = knight.getArmor();
    int oldDamage = knight.getDamage();
    knight.useSpecialSkill(); // Недоступно
    EXPECT_EQ(knight.getArmor(), oldArmor);
    EXPECT_EQ(knight.getDamage(), oldDamage);
    EXPECT_EQ(knight.getSpecialSkillUses(), 0);
}

TEST_F(KnightTest, UpdateCooldownDecrements) {
    knight.useSpecialSkill();
    EXPECT_EQ(knight.getSpecialSkillCooldown(), 3);
    knight.updateCooldown();
    EXPECT_EQ(knight.getSpecialSkillCooldown(), 2);
    knight.updateCooldown();
    EXPECT_EQ(knight.getSpecialSkillCooldown(), 1);
    knight.updateCooldown();
    EXPECT_EQ(knight.getSpecialSkillCooldown(), 0);
}

TEST_F(KnightTest, NegativeSkillUsesInConstructor) {
    Knight negativeKnight(100, 50, 20, 0.3, -5);
    EXPECT_EQ(negativeKnight.getSpecialSkillUses(), 0);
}
