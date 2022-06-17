#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "role.h"

// Structure: Role
void Role_Ctor(Role *this, char *roleName, char *object)
{
	this->roleName = roleName;
	this->object = object;
}

char *Role_roleName(Role *this)
{
	return this->roleName;
}

char *Role_object(Role *this)
{
	return this->object;
}



// Function: role_choose
char role_database[4][10] = {"Sheriff", "Vice", "Outlaw", "Renegade"};
char goal_database[4][40] = {"Kill all the outlaws and renegades.", "Kill all the outlaws and renegades.", "Kill the sheriff.", "The only one alive."};

Role role_choose(Role r, int number)
{
	Role_Ctor(&r, role_database[number], goal_database[number]);

	return r;
}
