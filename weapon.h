// Structure: Weapon
#ifndef _WEAPON_H_
#define _WEAPON_H_

typedef struct
{
	int weaponId;
	int attackDistance;
	bool isVolcanic;
} Weapon;

void Weapon_Ctor(Weapon *this, int weaponId, int attackDistance, bool isVolcanic);

int Weapon_weaponId(Weapon *this);
int Weapon_attackDistance(Weapon *this);
bool Weapon_isVolcanic(Weapon *this);

#endif
