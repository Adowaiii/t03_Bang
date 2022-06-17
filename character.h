// Structure: Character
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

typedef struct
{
	char *name;
	int hp;
	char *ability;
} Character;

void Character_Ctor(Character *this, char *name, int hp, char *ability);

char *Character_name(Character *this);
int Character_hp(Character *this);
char *Character_ability(Character *this);

#endif



// Function: character_choose
#ifndef _CHARACTER_CHOOSE_H_
#define _CHARACTER_CHOOSE_H_

Character character_choose(Character c, int number);

#endif
