// reference: https://iter01.com/572476.html

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "card.h"
#include "player.h"
#include "role.h"
#include "character.h"
#include "board.h"
#include "weapon.h"
#include "mustang.h"

#define PLAYER_NUM 4

int distance[PLAYER_NUM][PLAYER_NUM];

void distance_initialize(int player_num)
{
	for (int i=0; i<player_num; i++)
	{
		for (int j=i+1; j<player_num; j++)
		{
			if (j - i <= player_num / 2)
			{
				distance[i][j] = j - i;
				distance[j][i] = j - i;
			}
			else
			{
				if (j - i > player_num - j)
				{
					distance[i][j] = player_num - j;
					distance[j][i] = player_num - j;
				}
				else
				{
					distance[i][j] = j - i;
					distance[j][i] = j - i;
				}
			}
		}
	}

	return;
}

void distance_compute(int case_num, int player)
{
	switch (case_num)
	{
		// All other players add 1 to the distance.
		case 0:
		{
			for (int i=0; i<PLAYER_NUM; i++)
			{
				if (player == i)
				{
					continue;
				}
				else
				{
					distance[i][player]++;
				}
			}

			break;
		}
	
		// Sees other players at a distance decreased by 1.
		case 1: 
		{
			for (int i=0; i<PLAYER_NUM; i++)
			{
				if (player == i)
				{
					continue;
				}
				else
				{
					distance[player][i]--;
					if (distance[player][i] == 0)
					{
						distance[player][i] = 1;
					}
				}
				
			}

			break;
		}

		default:
			break;
	}

	return;
}

void print_board(int isDead[PLAYER_NUM], Role role[PLAYER_NUM], Character character[PLAYER_NUM], Board board[PLAYER_NUM])
{
	system("clear");
	printf("============================================================================================‖ Board Information‖ ===========================================================================================\n\n");
	for (int i=0; i<PLAYER_NUM; i++)
	{
		// Dead
		if (isDead[i] == 1)
		{
			printf("[Player%d] (\033[1;31mDead\033[0m)\n", i+1);
		}
		else
		{
			printf("[Player%d]\n", i+1);
		}

		// Role: Player1, dead player, Sheriff
		if (i == 0 || isDead[i] == 1 || strncmp(Role_roleName(&role[i]), "Sheriff", 7) == 0)
		{
			printf(" - Role: %s\n", Role_roleName(&role[i]));
		}
		else
		{
			printf(" - Role: X\n");
		}

		// Hp
		printf(" - Hp: %d\n", Board_hp(&board[i]));

		// Character
		printf(" - Character: %s\n", character[i].name);
		printf(" - Ability: %s\n", Character_ability(&character[i]));

		// Equipment Card

		printf("\n");
	}
	printf("============================================================================================================================================================================================================\n");

	return;
}

void press_to_continue()
{
	char c[1];
	printf("\nPress [C] to Continue...\n");
	while (1)
	{
		scanf("%s", c);
		if (c[0] == 'C' || c[0] == 'c')
		{
			break;
		}
	}

	return;
}
/*
int win_check(Board board[PLAYER_NUM], Role role[PLAYER_NUM])
{
	for (int i=0; i<PLAYER_NUM; i++)
	{
		if (isDead[i] == 0 && Board_hp(&board[i]) == 0)
		{
			isDead[i] = 1;
		}
	}



	//if (Role_roleName(&role[i]))
}
*/

int main()
{
	/* Intro */
	system("clear");                            
	printf("                                                                      ====================================================                                                                      \n");
	printf("                                                                      ‖    /$$$$$$$   /$$$$$$  /$$   /$$  /$$$$$$  /$$  ‖                                                                      \n");
	printf("                                                                      ‖   | $$__  $$ /$$__  $$| $$$ | $$ /$$__  $$| $$  ‖                                                                      \n");
	printf("                                                                      ‖   | $$  %c $$| $$  %c $$| $$$$| $$| $$  %c__/| $$  ‖                                                                      \n", 92, 92, 92);
	printf("                                                                      ‖   | $$$$$$$ | $$$$$$$$| $$ $$ $$| $$ /$$$$| $$  ‖                                                                      \n");
	printf("                                                                      ‖   | $$__  $$| $$__  $$| $$  $$$$| $$|_  $$|__/  ‖                                                                      \n");
	printf("                                                                      ‖   | $$  %c $$| $$  | $$| $$%c  $$$| $$  %c $$      ‖                                                                      \n", 92, 92, 92);
	printf("                                                                      ‖   | $$$$$$$/| $$  | $$| $$ %c  $$|  $$$$$$/ /$$  ‖                                                                      \n", 92);
	printf("                                                                      ‖   |_______/ |__/  |__/|__/  %c__/ %c______/ |__/  ‖                                                                      \n", 92, 92);
	printf("                                                                      ====================================================                                                                      \n");
	printf("\n                                                                                     - Welcome to Bang! -                                                                                     \n\n");
	printf("                                                                                    ‖ Press [S] to Start‖                                                                                    \n");
	printf("                                                                                    ‖ Press [E] to Exit ‖                                                                                    \n");

	/* Game start or exit. */
	char c[1];
	while (1)
	{
		scanf("%s", c);
		if (c[0] == 'E' || c[0] == 'e')
		{
			system("clear");
			printf("Exit\n");
			return 0;
		}
		else if (c[0] == 'S' || c[0] == 's')
		{
			break;
		}
	}

	system("clear");

	memset(distance, 0, sizeof(distance));
	distance_initialize(PLAYER_NUM);

	int isDead[PLAYER_NUM];
	memset(isDead, 0, sizeof(isDead));

	/* Role */
	srand(time(NULL));
	int random_num;

	int role_count[7];
	memset(role_count, 0, sizeof(role_count));

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
	}

	printf("[Player1]\n");
	printf(" - You are the \"\033[1;31m%s\033[0m\"!\n", Role_roleName(&role[0]));
	printf(" - Your object is to \"\033[1;31m%s\033[0m\".\n", Role_object(&role[0]));

	/* Character */
	int sheriff = 0;
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
			sheriff = i;
			character[i].hp++;
		}

		// Paul Regret
		if (strncmp(character[i].name, "Paul Regret", 11) == 0)
		{
			distance_compute(0, i);
		}
		// Rose Doolan
		else if (strncmp(character[i].name, "Rose Doolan", 11) == 0)
		{
			distance_compute(1, i);
		}
	}

	printf(" - Your character is \"\033[1;31m%s\033[0m\", and the ability is \"\033[1;31m%s\033[0m\"\n", Character_name(&character[0]), Character_ability(&character[0]));

	/* Player */
/*
	card *HandCard[PLAYER_NUM];
	for (int i=0; i<PLAYER_NUM; i++)
	{
		HandCard[i] = malloc(sizeof(card));
	}
*/

	Player player[PLAYER_NUM];

	card *deck = malloc(sizeof(card));
	CreateCard(deck);

	//card *pointer = Player_GetCards(&player[0]);
	card *pointer = malloc(sizeof(card));
	*pointer = player[0].CardinHand;
	CreateCard(pointer);

	draw(player[0].CardinHand, deck, 5);
	print(pointer);

	card *deadwood = malloc(sizeof(card));

//	card *pointer,*temp;
//	card *deck;
//	deck = malloc(sizeof(card));
//	card *deadwood = malloc(sizeof(card));
//	CreateCard(deck);
//	card *player1 = malloc(sizeof(card));
//	draw(player1,deck,5);
//	Move1Card(deadwood,player1,3);
//	printf("player1:\n");
//	print(player1); 
//	printf("deadwood:\n");
//	print(deadwood); 
//	printf("deck:\n");
//	print(deck); 

	press_to_continue();

	/* Board */
	Board board[PLAYER_NUM];
	Weapon weapon[PLAYER_NUM];
	Mustang mustang[PLAYER_NUM];
	for (int i=0; i<PLAYER_NUM; i++)
	{
		// Initilaize the board of every player.
		Weapon_Ctor(&weapon[i], 80, 1, 0);
		Mustang_Ctor(&mustang[i], 80);
		Board_Ctor(&board[i], i+1, character[i].hp, role[i], weapon[i], mustang[i], 0, 0, 0, 0);
	}

	/* Game */
	while (1)
	{
		/* Player Round: start with the Sheriff */
		for (int i=sheriff; i<PLAYER_NUM; i++)
		{
			/* Dead Check */
			if (isDead[i] == 1)
			{
				if (i == PLAYER_NUM-1)
				{
					i = -1;
				}
				continue;
			}			

			print_board(isDead, role, character, board);
			printf("[Player%d Round]\n", i+1);

			/* Bomb Check */
			if (Board_isBomb(&board[i]) == 1)
			{
				printf("You have a [Dynamite].\n");
				///// Dynamite Function /////
				// success ---> pass the [Dynamite] to the next player, Board_isBomb(&board[i]) = 0
				// fail ---> continue, put the [Dynamite] in the deadwood, Board_isBomb(&board[i]) = 0
				
				// Lucky Duke
				if (strncmp(character[i].name, "Lucky Duke", 10) == 0)
				{
					
				}
/*
				if (i == PLAYER_NUM-1)
				{
					i = -1;
				}
*/
			}
			print_board(isDead, role, character, board);
			printf("[Player%d Round]\n", i+1);
			press_to_continue();

			/* Jail Check */
			if (Board_isJail(&board[i]) == 1)
			{
				printf("You have a [Jail].\n");
				///// Jail Function /////
				// sucess ---> put the [Jail] in the deadwood, Board_isJail(&board[i]) = 0
				// fail ---> continue, put the [Jail] in the deadwood, Board_isJail(&board[i]) = 0

				// Lucky Duke
				if (strncmp(character[i].name, "Lucky Duke", 10) == 0)
				{
					
				}

/*
				if (i == PLAYER_NUM-1)
				{
					i = -1;
				}
*/
			}
			print_board(isDead, role, character, board);
			printf("[Player%d Round]\n", i+1);
			press_to_continue();

			/* Drawing 2 Cards */
			// Black Jack
			if (strncmp(character[i].name, "Black Jack", 10) == 0)
			{
				
			}
			// Jesse Jones
			else if (strncmp(character[i].name, "Jesse Jones", 11) == 0)
			{
				
			}
			// Kit Carlson
			else if (strncmp(character[i].name, "Kit Carlson", 11) == 0)
			{
				
			}
			// Pedro Ramirez
			else if (strncmp(character[i].name, "Pedro Ramirez", 13) == 0)
			{
				
			}
			else
			{
				
			}
			
			while (1)
			{
				print_board(isDead, role, character, board);
				printf("[Player%d Round]\n", i+1);

				/* Player1 */
				if (i == 0)
				{
					int card_id;
					printf("This is your card:\n");
					printf("\"0\" Skip!\n");
					///// print card /////
					printf("Press the \"id\" of card which you want to play: ");
					scanf("%d", &card_id);


					// 0: Skip
					if (card_id == 0)
					{
						

						break;
					}
					///// play card /////

					/* Win Check */
					
				}
				/* AI Player: Player2, Player3, Player4 */
				else
				{
					
				}
				
				break;
			}
			break;

			if (i == PLAYER_NUM-1)
			{
				i = -1;
			}
		}

		break;
	}

	return 0;
}
