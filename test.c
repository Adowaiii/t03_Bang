// reference: https://iter01.com/572476.html

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "role.h"
#include "character.h"
#include "board.h"

#define PLAYER_NUM 4

int main()
{
	srand(time(NULL));
	int random_num;

	/* Role */
	int role_count[7] = {0};

	// Version: 4 players
	if (PLAYER_NUM == 4)
	{
		role_count[0] = 1;	// Sheriff
		role_count[1] = 0;	// Vice
		role_count[2] = 2;	// Outlaw
		role_count[3] = 1;	// Renegade
	}

	Role role[PLAYER_NUM];
	for (int i=0; i<PLAYER_NUM; i++)
	{
		// Random choosing roles (without repeating).
		while (1)
		{
			random_num = rand() % 4;
			if (role_count[random_num] == 0)
			{
				continue;
			}
			else
			{
				role_count[random_num]--;
				break;
			}
		}
		role[i] = role_choose(role[i], random_num);

		//printf("[player%d] %s: %s\n", i+1, Role_rolename(&role[i]), Role_object(&role[i]));
	}

	/* Character */
	int character_count[16];
	memset(character_count, 1, sizeof(character_count));
	Character character[PLAYER_NUM];
	for (int i=0; i<PLAYER_NUM; i++)
	{
		// Random choosing characters (without repeating).
		while (1)
		{
			random_num = rand() % 16;
			if (character_count[random_num] == 0)
			{
				continue;
			}
			else
			{
				character_count[random_num]--;
				break;
			}
		}
		character[i] = character_choose(character[i], random_num);

		// Sheriff: hp + 1
		if (strncmp(Role_roleName(&role[i]), "Sheriff", 7) == 0)
		{
			character[i].hp++;
		}

		//printf("[player%d] %s (hp = %d)\n%s\n\n", i+1, Character_name(&character[i]), Character_hp(&character[i]), Character_ability(&character[i]));
	}

	/* Board */
	Board player[PLAYER_NUM];
	for (int i=0; i<PLAYER_NUM; i++)
	{
		Board_Ctor(&player[i], i+1, character[i].hp, role[i], 0, 0, 0, 0);

		//printf("[player%d] hp=%d, role=%s, character=%s\n", Board_id(&player[i]), Board_hp(&player[i]), Board_role(&player[i]).roleName, character[i].name);
	}
	
	return 0;
}
