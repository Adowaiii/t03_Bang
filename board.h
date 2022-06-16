#include "role.h"

#ifndef _BOARD_H_
#define _BOARD_H_

typedef struct
{
	int id;
	int hp;
	Role role;
	//Weapon player_weapon;
	//Horse player_horse;
	bool isScope;
	bool isBarrel;
	bool isJail;
	bool isBomb;
} Board;

void Board_Ctor(Board *this, int id, int hp, Role role, bool isScope, bool isBarrel, bool isJail, bool isBomb);

int Board_id(Board *this);
int Board_hp(Board *this);
Role Board_role(Board *this);
bool Board_isScope(Board *this);
bool Board_isBarrel(Board *this);
bool Board_isJail(Board *this);
bool Board_isBomb(Board *this);

#endif
