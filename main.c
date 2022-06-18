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

Player player[PLAYER_NUM];
card *deck;
card *deadwood;
card *HandCard[PLAYER_NUM];
card *EquipmentCard[PLAYER_NUM];
Role role[PLAYER_NUM];
Character character[PLAYER_NUM];
Board board[PLAYER_NUM];
Weapon weapon[PLAYER_NUM];
Mustang mustang[PLAYER_NUM];

int isDead[PLAYER_NUM];
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

void print_board()
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
		printf(" - Equipment Card: ");
		print(EquipmentCard[i]);

		// Hand Card: Player1
		if (i == 0)
		{
			printf(" - Hand Card: ");
			Player_GetCards(&player[i]);
		}

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

int print_HandCard(int player)
{
	int k = 0;
	card *pointer = HandCard[player];
	printf("This is your hand card:\n");
	while (pointer->next != NULL)
	{
		pointer = pointer->next;
		printf("\"%d\" %s\n", k+1, pointer->name);
		k++;
	}

	return k;
}

int round_check(int round)
{
	if (round == PLAYER_NUM-1)
	{
		return -1;
	}
}

int discard_check(int card_num, int player)
{
	// Don't need to discard.
	if (card_num <= Board_hp(&board[player]))
	{
		return 0;
	}
	// Need to discard.
	else
	{
		return 1;
	}
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
	////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////  INTRO  ////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////

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

	////////////////////////////////////////////////////////////////////////////////
	///////////////////////////  GAME SETTING  /////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////

	///////* Game start or exit. *///////
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

	memset(isDead, 0, sizeof(isDead));

	///////* Role *///////
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

	///////* Character *///////
	int sheriff = 0;
	int character_count[16];
	memset(character_count, 1, sizeof(character_count));
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

	///////* Card *///////
	deck = malloc(sizeof(card));
	CreateCard(deck);
	for (int i=0; i<PLAYER_NUM; i++)
	{
		HandCard[i] = malloc(sizeof(card));
		EquipmentCard[i] = malloc(sizeof(card));
		draw(HandCard[i], deck, character[i].hp);
		Player_Ctor(&player[i], i, i, HandCard[i]);
	}

	press_to_continue();

	///////* Board *///////
	for (int i=0; i<PLAYER_NUM; i++)
	{
		// Initilaize the board of every player.
		Weapon_Ctor(&weapon[i], 80, 1, 0);
		Mustang_Ctor(&mustang[i], 80);
		Board_Ctor(&board[i], i+1, character[i].hp, role[i], weapon[i], mustang[i], 0, 0, 0, 0);
	}

	////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////  GAME  ////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////

	while (1)
	{
		///////* Player Round: start with the Sheriff *///////
		//for (int i=sheriff; i<PLAYER_NUM; i++)
		for (int i=0; i<PLAYER_NUM; i++)
		{
			///////* Dead Check *///////
			if (isDead[i] == 1)
			{
				i = round_check(i);
				continue;
			}			

			print_board(i);
			printf("\n[Player%d Round]\n", i+1);

			///////* Bomb Check *///////
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

				print_board();
				printf("\n[Player%d Round]\n", i+1);
				press_to_continue();
			}

			///////* Jail Check *///////
			if (Board_isJail(&board[i]) == 1)
			{
				printf("You have a [Jail].\n");
				///// Jail Function /////
				// success ---> put the [Jail] in the deadwood, Board_isJail(&board[i]) = 0
				// fail ---> continue, put the [Jail] in the deadwood, Board_isJail(&board[i]) = 0

				// Lucky Duke
				if (strncmp(character[i].name, "Lucky Duke", 10) == 0)
				{
					
				}

				//continue: i = round_check(i);

				print_board();
				printf("\n[Player%d Round]\n", i+1);
				press_to_continue();
			}

			///////* Drawing 2 Cards *///////
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
				print_board();
				printf("\n[Player%d Round]\n", i+1);

				///////* Player1 *///////
				if (i == 0)
				{
					int card_num;
					int card_id;
					card_num = print_HandCard(i);
					printf("Input the \"ID\" of card which you want to play or input \"0\" to skip: ");
					scanf("%d", &card_id);

					// Skip
					if (card_id == 0)
					{
						///////* Discard Check *///////
						while (discard_check(card_num, i) != 0)
						{
							int discard_id;
							print_HandCard(i);
							printf("Input the \"ID\" of card which you want to discard: ");
							scanf("%d", &discard_id);

							if (discard_id < 0 || discard_id > card_num)
							{
								printf("Invalid \"ID\"!\n");
							}
							else
							{
								Move1Card(deadwood, HandCard[i], discard_id);
								card_num--;
								printf("Successfully discard!\n");
							}
						}
						
						break;
					}
					///////* Play Card *///////
					else
					{
						
					}

					///////* Dead Check *///////
					for ()

					///////* Win Check *///////
					
				}
				///////* AI Player: Player2, Player3, Player4 *///////
				else
				{
					
				}
				
				break;
			}
			break;

			i = round_check(i);
		}

		break;
	}

	return 0;
}
