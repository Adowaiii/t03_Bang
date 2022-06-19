#include <stdbool.h>

#include "role.h"
#include "weapon.h"
#include "mustang.h"

#ifndef _BOARD_H_
#define _BOARD_H_

typedef struct
{
	int id;
	int hp;
	Role role;
	Weapon weapon;
	Mustang mustang;
	bool isScope;
	bool isBarrel;
	bool isJail;
	bool isBomb;
} Board;

void Board_Ctor(Board *this, int id, int hp, Role role, Weapon weapon, Mustang mustang, bool isScope, bool isBarrel, bool isJail, bool isBomb);

int Board_id(Board *this);
int Board_hp(Board *this);
Role Board_role(Board *this);
Weapon Board_weapon(Board *this);
Mustang Board_mustang(Board *this);
bool Board_isScope(Board *this);
bool Board_isBarrel(Board *this);
bool Board_isJail(Board *this);
bool Board_isBomb(Board *this);

#endif
