#include <stdbool.h>
#include "board.h"

void Board_Ctor(Board *this, int id, int hp, Role role, Weapon weapon, Mustang mustang, bool isScope, bool isBarrel, bool isJail, bool isBomb)
{
	this->id = id;
	this->hp = hp;
	this->role = role;
	this->weapon = weapon;
	this->mustang = mustang;
	this->isScope = isScope;
	this->isBarrel = isBarrel;
	this->isJail = isJail;
	this->isBomb = isBomb;
}

int Board_id(Board *this)
{
	return this->id;
}

int Board_hp(Board *this)
{
	return this->hp;
}

Role Board_role(Board *this)
{
	return this->role;
}

Weapon Board_weapon(Board *this)
{
	return this->weapon;
}

Mustang Board_mustang(Board *this)
{
	return this->mustang;
}

bool Board_isScope(Board *this)
{
	return this->isScope;
}

bool Board_isBarrel(Board *this)
{
	return this->isBarrel;
}

bool Board_isJail(Board *this)
{
	return this->isJail;
}

bool Board_isBomb(Board *this)
{
	return this->isBomb;
}
