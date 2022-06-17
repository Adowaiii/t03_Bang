// Structure: Role
#ifndef _ROLE_H_
#define _ROLE_H_

typedef struct
{
	char *roleName;
	char *object;
} Role;

void Role_Ctor(Role *this, char *roleName, char *object);

char *Role_roleName(Role *this);
char *Role_object(Role *this);

#endif



// Function: role_choose
#ifndef _ROLE_CHOOSE_H_
#define _ROLE_CHOOSE_H_

Role role_choose(Role r, int number);

#endif
