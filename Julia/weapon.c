#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "weapon.h"

// Structure: Weapon
void Weapon_Ctor(Weapon *this, int weaponId, int attackDistance, bool isVolcanic)
{
	this->weaponId = weaponId;
	this->attackDistance = attackDistance;
	this->isVolcanic = isVolcanic;
}

int Weapon_weaponId(Weapon *this)
{
	return this->weaponId;
}

int Weapon_attackDistance(Weapon *this)
{
	return this->attackDistance;
}

bool Weapon_isVolcanic(Weapon *this)
{
	return this->isVolcanic;
}

// [Volcanic] 72, 73
// [Schofield] 74, 75, 76
// [Remington] 77
// [Rev.Carabine] 78
// [Winchedter] 79
// [Default] 80
int weapon_id[8] = {72, 73, 74, 75, 76, 77, 78, 79};
char weapon_database[8][15] = {"Volcanic", "Volcanic", "Schofield", "Schofield", "Schofield", "Remington", "Rev.Carabine", "Winchedter"};
char weapon_function[8][100] = {"The attacking distance is 1, and you can play any number of [Bang] cards during your turn.",
				"The attacking distance is 1, and you can play any number of [Bang] cards during your turn.",
				"The attacking distance is 2.",
				"The attacking distance is 2.",
				"The attacking distance is 2.",
				"The attacking distance is 3.",
				"The attacking distance is 4.",
				"The attacking distance is 5."};
int weapon_distance[8] = {1, 1, 2, 2, 2, 3, 4, 5};
