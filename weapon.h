// Structure: Weapon
#ifndef _WEAPON_H_
#define _WEAPON_H_

typedef struct
{
	char *weaponName;
	int attackDistance;
} Weapon;

void Weapon_Ctor(Character *this, char *weaponName, int attackDistance);

char *Weapon_weaponName(Weapon *this);
int Weapon_attackDistance(Character *this);

#endif



/*
// Function: character_choose
#ifndef _CHARACTER_CHOOSE_H_
#define _CHARACTER_CHOOSE_H_

Character character_choose(Character c, int number);

#endif
*/
