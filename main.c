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
#include "ability.h"


#define YELLOW  "\x1b[33m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
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
char card_name[20];

int draw_card_check(int case_num, int player_id);

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

void distance_compute(int case_num, int player_id)
{
	switch (case_num)
	{
		// All other players add 1 to the distance.
		case 0:
		{
			for (int i=0; i<PLAYER_NUM; i++)
			{
				if (player_id == i)
				{
					continue;
				}
				else
				{
					distance[i][player_id]++;
				}
			}
			break;
		}
	
		// See other players at a distance decreased by 1.
		case 1: 
		{
			for (int i=0; i<PLAYER_NUM; i++)
			{
				if (player_id == i)
				{
					continue;
				}
				else
				{
					distance[player_id][i]--;
					if (distance[player_id][i] == 0)
					{
						distance[player_id][i] = 1;
					}
				}
			}
			break;
		}

		// There's a player died, recompute the distance between players.
		case 2:
		{
			for (int i=0; i<PLAYER_NUM; i++)
			{
				distance[i][player_id] = 0;
				distance[player_id][i] = 0;
			}

			// Player1 Died
			if (player_id == 0)
			{
				distance[player_id+1][PLAYER_NUM-1]--;
				if (distance[player_id+1][PLAYER_NUM-1] == 0)
				{
					distance[player_id+1][PLAYER_NUM-1] = 1;
				}
				distance[PLAYER_NUM-1][player_id+1]--;
				if (distance[PLAYER_NUM-1][player_id+1] == 0)
				{
					distance[PLAYER_NUM-1][player_id+1] = 1;
				}
			}
			// Player4 Died
			else if (player_id == 3)
			{
				distance[player_id-1][0]--;
				if (distance[player_id-1][0] == 0)
				{
					distance[player_id-1][0] = 1;
				}
				distance[0][player_id-1]--;
				if (distance[0][player_id-1] == 0)
				{
					distance[0][player_id-1] = 1;
				}
			}
			// Player2 or Player3 Died
			else
			{
				distance[player_id-1][player_id+1]--;
				if (distance[player_id-1][player_id+1] == 0)
				{
					distance[player_id-1][player_id+1] = 1;
				}
				distance[player_id+1][player_id-1]--;
				if (distance[player_id+1][player_id-1] == 0)
				{
					distance[player_id+1][player_id-1] = 1;
				}
			}
		}

		default:
			break;
	}

	return;
}

int distance_attack(int player_id)
{
	int bang_num = 0;
	int bang_player;
	int bang_available[PLAYER_NUM+1];
	memset(bang_available, 0, sizeof(bang_available));
	printf("Input the \"ID\" of player which you want to " YELLOW "[Bang!]" RESET  "\n");
	for (int i=0; i<PLAYER_NUM; i++)
	{
		if (i == player_id)
		{
			continue;
		}

		if (isDead[i] == 0 && Weapon_attackDistance(&weapon[player_id]) >= distance[player_id][i])
		{
			printf("\"%d\" Player%d\n", i+1, i+1);
			bang_available[i+1] = 1;
			bang_num++;
		}
	}

	if (bang_num == 0)
	{
		printf("You cannot" YELLOW "[Bang!]" RESET "anyone.\n");
		return 0;
	}

	while (1)
	{
		scanf("%d", &bang_player);
		// Jourdonnais
		if (strncmp(Character_name(&character[bang_player-1]), "Jourdonnais", 11) == 0)
		{
			if (draw_card_check(1, player_id) == 1)
			{
				return PLAYER_NUM+1;
			}
			else
			{
				return bang_player;
			}
		}

		if (bang_player >= 1 && bang_player <= PLAYER_NUM && bang_available[bang_player] == 1)
		{
			return bang_player;
		}
		printf("Invalid input!\n");
		printf("Input the \"ID\" of player which you want to " YELLOW "[Bang!]" RESET "\n");
	}
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
		printf(" - Hp: \033[1;31m%d\033[0m\n", Board_hp(&board[i]));

		// Character
		printf(" - Character:" CYAN " %s\n" RESET, character[i].name);
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

int print_HandCard(int player_id)
{
	int k = 0;
	card *pointer = HandCard[player_id];
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

	return round;
}

int draw_card_check(int case_num, int player_id)
{
	card *chosen_card;
	chosen_card = malloc(sizeof(card));
	// Lucky Duke
	if (strncmp(character[player_id].name, "Lucky Duke", 10) == 0)
	{
		*chosen_card = _LuckyDuke_(player[player_id], deck, deadwood);
	}
	else
	{
		card *temp;
		temp = malloc(sizeof(card));
		draw(temp, deck, 1);
		chosen_card = temp;
		Move1Card(deadwood, temp, 1);
	}

	chosen_card = chosen_card->next;

	switch (case_num)
	{
		// Dynamite
		case 0:
		{
			// Fail
			if (strncmp(chosen_card->suit, "SPADE", 5) == 0 && (chosen_card->number >= 2 && chosen_card->number <= 9))
			{
				return 0;
			}
			// Success
			else
			{
				return 1;
			}

			break;
		}
		// Jail, Jourdonnais
		case 1:
		{
			// Success
			if (strncmp(chosen_card->suit, "HEART", 5) == 0)
			{
				return 1;
			}
			// Fail
			else
			{
				return 0;
			}

			break;
		}
		default:
			break;
	}
}

int discard_check(int card_num, int player_id)
{
	// Don't need to discard.
	if (card_num <= Board_hp(&board[player_id]))
	{
		return 0;
	}
	// Need to discard.
	else
	{
		return 1;
	}
}

int beer_check(int player_id)
{
	int k = 1;
	card *pointer = HandCard[player_id];
	while (pointer->next != NULL)
	{
		pointer = pointer->next;
		if (strncmp(pointer->name, "BEER", 4) == 0)
		{
			return k;
		}
		k++;
	}

	return 0;
}

void player_win_check(char win_group[10])
{
	if (strncmp(Role_roleName(&role[0]), win_group, strlen(win_group)) == 0)
	{
		printf("You win!\n");
	}
	else
	{
		printf("You lose!\n");
	}

	return;
}

int win_check()
{
	int sheriff_dead = 0;
	int outlaw_dead = 0;
	int renegade_dead = 0;

	for (int i=0; i<PLAYER_NUM; i++)
	{
		if (isDead[i] == 1 && strncmp(Role_roleName(&role[i]), "Sheriff", 7) == 0)
		{
			sheriff_dead++;
		}
		else if (isDead[i] == 1 && strncmp(Role_roleName(&role[i]), "Outlaw", 6) == 0)
		{
			outlaw_dead++;
		}
		else if (isDead[i] == 1 && strncmp(Role_roleName(&role[i]), "Renegade", 8) == 0)
		{
			renegade_dead++;
		}
	}

	// Sheriff Win
	if (sheriff_dead == 0 && outlaw_dead == 2 && renegade_dead == 1)
	{
		printf("The [Sheriff] wins!\n");
		player_win_check("Sheriff");
		return 1;
	}
	// Renegade Win
	else if (sheriff_dead == 1 && outlaw_dead == 2 && renegade_dead == 0)
	{
		printf("The [Renegade] wins!\n");
		player_win_check("Renegade");
		return 1;
	}
	// Outlaw Win
	else if (sheriff_dead == 1)
	{
		printf("The [Outlaw] wins!\n");
		player_win_check("Outlaw");
		return 1;
	}

	return 0;
}

void reward(int killer_id, int dead_id)
{
	// Bomb causes the dead.
	if (killer_id == 0)
	{
		return;
	}
	// Player causes the Outlaw dead. ---> Draw 3 cards from the deck.
	else if (strncmp(Character_name(&character[dead_id]), "Outlaw", 6) == 0)
	{
		draw(HandCard[killer_id], deck, 3);
		return;
	}

	return;
}

int dead_check(int player_id, int killer_id)
{
	for (int j=0; j<PLAYER_NUM; j++)
	{
		while (isDead[j] == 0 && Board_hp(&board[j]) <= 0)
		{
			///////* Beer Check *///////
			int beer_id = beer_check(j);
			if (beer_id == 0)
			{	
				// Dead ---> Expose Role
				isDead[j] = 1;
				printf("Player%d is dead! The role is %s\n", j+1, Role_roleName(&role[j]));

				///////* Win Check *///////
				if (win_check()	== 1)
				{
					// A group wins. ---> End the game.
					return 1;
				}			

				// Reward
				reward(killer_id, j);

				// Distance Recompute
				distance_compute(2, j);

				// Vulture Sam
				if (strncmp(character[player_id].name, "Vulture Sam", 11) == 0)
				{
					int card_num = countCard(HandCard[j]);
					draw(HandCard[player_id], HandCard[j], card_num);
					card_num = countCard(EquipmentCard[j]);
					draw(HandCard[player_id], EquipmentCard[j], card_num);
				}
			}
			else
			{
				board[j].hp++;
				Move1Card(deadwood, HandCard[j], beer_id);
			}
		}
	}

	return 0;
}

int main()
{
	////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////  INTRO  ////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////

	system("clear");                            
	printf(YELLOW "                                                                      ====================================================                                                                      \n");
	printf("                                                                      ‖    /$$$$$$$   /$$$$$$  /$$   /$$  /$$$$$$  /$$  ‖\n");
	printf("                                                                      ‖   | $$__  $$ /$$__  $$| $$$ | $$ /$$__  $$| $$  ‖\n");
	printf("                                                                      ‖   | $$  %c $$| $$  %c $$| $$$$| $$| $$  %c__/| $$  ‖\n", 92, 92, 92);
	printf("                                                                      ‖   | $$$$$$$ | $$$$$$$$| $$ $$ $$| $$ /$$$$| $$  ‖\n");
	printf("                                                                      ‖   | $$__  $$| $$__  $$| $$  $$$$| $$|_  $$|__/  ‖\n");
	printf("                                                                      ‖   | $$  %c $$| $$  | $$| $$%c  $$$| $$  %c $$      ‖\n", 92, 92, 92);
	printf("                                                                      ‖   | $$$$$$$/| $$  | $$| $$ %c  $$|  $$$$$$/ /$$  ‖\n", 92);
	printf("                                                                      ‖   |_______/ |__/  |__/|__/  %c__/ %c______/ |__/  ‖\n", 92, 92);
	printf("                                                                      ====================================================\n" RESET);
	printf("\n                                                                                     - Welcome to Bang! -\n\n");
	printf("                                                                                    ‖ Press "YELLOW "[S]" RESET" to Start‖\n");
	printf("                                                                                    ‖ Press " YELLOW "[E]" RESET " to Exit ‖\n");

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
	deadwood = malloc(sizeof(card));
	deadwood->next = NULL;
	CreateCard(deck);
	shuffle(deck);
	for (int i=0; i<PLAYER_NUM; i++)
	{
		HandCard[i] = malloc(sizeof(card));
		HandCard[i]->next = NULL;
		EquipmentCard[i] = malloc(sizeof(card));
		EquipmentCard[i]->next = NULL;
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
			///////* Player1 *///////
			if (i == 0)
			{
				///////* Dead Check ---> Next Player *///////
				if (isDead[i] == 1)
				{
					i = round_check(i);
					continue;
				}			

				print_board();
				printf("\n[Player%d Round]\n", i+1);

				///////* Bomb Check *///////
				if (Board_isBomb(&board[i]) == 1)
				{
					printf("You have a [Dynamite].\n");
					// Fail
					if (draw_card_check(0, i) == 0)
					{
						printf("The [Dynamite] is exploded!\n");
						board[i].hp -= 3;

						// End the game.
						if (dead_check(i, 0) == 1)
						{
							return 0;
						}
					
						press_to_continue();
						board[i].isBomb = 0;
						Move1Card(deadwood, EquipmentCard[i], FindCard(EquipmentCard[i], "DYNAMITE"));
					}
					// Success
					else
					{
						printf("The [Dynamite] isn't exploded!\n");

						int next_player_id = i;
						while (1)
						{
							if (next_player_id == 3)
							{
								next_player_id = 0;
							}
							else
							{
								next_player_id++;
							}

							if (isDead[next_player_id] == 0)
							{
								break;
							}
						}

						Move1Card(EquipmentCard[next_player_id], EquipmentCard[i], FindCard(EquipmentCard[i], "DYNAMITE"));
						board[i].isBomb = 0;
						board[next_player_id].isBomb = 1;
					}

					print_board();
					printf("\n[Player%d Round]\n", i+1);
					press_to_continue();
				}

				///////* Jail Check *///////
				if (Board_isJail(&board[i]) == 1)
				{
					printf("You are in a [Jail].\n");
					// Fail
					if (draw_card_check(1, i) == 0)
					{
						printf("You didn't escape from the [Jail], you have to skip this round.\n");
						board[i].isJail = 0;
						Move1Card(deadwood, EquipmentCard[i], FindCard(EquipmentCard[i], "JAIL"));
						i = round_check(i);
						continue;
					}
					// Success
					else
					{
						printf("You successfully escape from the [Jail]!\n");
						board[i].isJail = 0;
						Move1Card(deadwood, EquipmentCard[i], FindCard(EquipmentCard[i], "JAIL"));
					}

					print_board();
					printf("\n[Player%d Round]\n", i+1);
					press_to_continue();
				}

				///////* Drawing 2 Cards *///////
				// Black Jack
				if (strncmp(character[i].name, "Black Jack", 10) == 0)
				{
					draw(HandCard[i], deck, 2);
					_Blackjack_(player[i], deck);
				}
				// Jesse Jones
				else if (strncmp(character[i].name, "Jesse Jones", 11) == 0)
				{
					_JesseJones_(player[i], deck, player, character, isDead);
					draw(HandCard[i], deck, 1);
				}
				// Kit Carlson
				else if (strncmp(character[i].name, "Kit Carlson", 11) == 0)
				{
					_KitCarlson_(player[i], deck);
				}
				// Pedro Ramirez
				else if (strncmp(character[i].name, "Pedro Ramirez", 13) == 0)
				{
					_PedroRamirez_(player[i], deck, deadwood);
					draw(HandCard[i], deck, 1);
				}
				else
				{
					draw(HandCard[i], deck, 2);
				}

				press_to_continue();
			
				///////* Play Cards *///////
				int isBang = 0;
				while (1)
				{
					print_board();
					printf("\n[Player%d Round]\n", i+1);
				
					int card_num;
					int card_id;
					card_num = print_HandCard(i);
					printf("Input the \"ID\" of card which you want to play or input \"0\" to skip: ");
					scanf("%d", &card_id);

					print_board();
					printf("\n[Player%d Round]\n", i+1);

					// Skip
					if (card_id == 0)
					{
						///////* Discard Check *///////
						while (discard_check(card_num, i) == 1)
						{
							print_board();
							printf("\n[Player%d Round]\n", i+1);

							int discard_id;
							print_HandCard(i);
							printf("There are too many cards! Input the \"ID\" of card which you want to discard: ");
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
							press_to_continue();
						}
					
						break;
					}
					// Play Card
					else
					{
						if (card_id < 0 || card_id > card_num)
						{
							printf("Invalid \"ID\"!\n");
							press_to_continue();
							continue;
						}						

						///// Card Function /////
						card *pointer = HandCard[i];
						for (int j=0; j<card_id; j++)
						{
							pointer = pointer->next;
						}

						// BANG
						if (strncmp(pointer->name, "BANG", 4) == 0)
						{
							if (isBang == 1)
							{
								printf("You have already used the " YELLOW "[Bang!]" RESET "\n");
								press_to_continue();
								continue;
							}							

							int bang_object = distance_attack(i);
							if (bang_object == 0 || bang_object == PLAYER_NUM+1)
							{
								continue;
							}

							// Slab the Killer
							if (strncmp(character[i].name, "Slab the Killer", 15) == 0)
							{
								//_SlabTheKiller_(HandCard, i, bang_object-1);
							}
							else
							{
								BANG(board, HandCard, i, bang_object-1, deck, deadwood, card_id);
							}
							isBang = 1;
						}
						// MISSED
						else if (strncmp(pointer->name, "MISSED", 6) == 0)
						{
							// Calamity Janet
							if (strncmp(character[i].name, "Calamity Janet", 14) == 0)
							{
								if (_CalamityJanet_() == 2)
								{
									printf("You cannot play [Missed!] card.\n");
									press_to_continue();
									continue;
								}
								else
								{
									int bang_object = distance_attack(i);
									if (bang_object == 0 || bang_object == PLAYER_NUM+1)
									{
										continue;
									}
									else
									{
										BANG(board, HandCard, i, bang_object-1, deck, deadwood, card_id);
									}
									isBang = 1;
								}
							}
							else
							{
								printf("You cannot play [Missed!] card.\n");
								press_to_continue();
								continue;
							}
						}
						// GATLING
						else if (strncmp(pointer->name, "GATLING", 7) == 0)
						{
							GATLING(board, HandCard, i, 0, deck, deadwood, card_id);
						}
						// INDIANS
						else if (strncmp(pointer->name, "INDIANS", 7) == 0)
						{
							INDIANS(board, HandCard, i, 0, deck, deadwood, card_id);
						}
						// PANIC
						else if (strncmp(pointer->name, "PANIC", 5) == 0)
						{
							int panic_temp[PLAYER_NUM+1];
							memset(panic_temp, 0, sizeof(panic_temp));
							printf("Input the \"ID\" of player which you want to use [Panic!]\n");
							for (int j=0; j<PLAYER_NUM; j++)
							{
								if (i == j)
								{
									continue;
								}
								if (distance[i][j] == 1)
								{
									printf("\"%d\" Player%d\n", j+1, j+1);
									panic_temp[j+1] = 1;
								}
							}

							int panic_object;
							while(1)
							{
								scanf("%d", &panic_object);
								if (panic_object >= 1 && panic_object <= PLAYER_NUM && panic_temp[panic_object] == 1)
								{
									PANIC(board, HandCard, i, panic_object-1, deck, deadwood, card_id);
									break;
								}
								printf("Invalid input!\n");
								printf("Input the \"ID\" of player which you want to use [Panic!]\n");
							}
						}
						// CATBALOU
						else if (strncmp(pointer->name, "CATBALOU", 8) == 0)
						{
							int catbalou_temp[PLAYER_NUM+1];
							memset(catbalou_temp, 0, sizeof(catbalou_temp));
							printf("Input the \"ID\" of player which you want to use [Catbalou]\n");
							for (int j=0; j<PLAYER_NUM; j++)
							{
								if (i == j)
								{
									continue;
								}
								if (isDead[j] == 0)
								{
									printf("\"%d\" Player%d\n", j+1, j+1);
									catbalou_temp[j+1] = 1;
								}
							}

							int catbalou_object;
							while(1)
							{
								scanf("%d", &catbalou_object);
								if (catbalou_object >= 1 && catbalou_object <= PLAYER_NUM && catbalou_temp[catbalou_object] == 1)
								{
									CATBALOU(board, HandCard, i, catbalou_object-1, deck, deadwood, card_id);
									break;
								}
								printf("Invalid input!\n");
								printf("Input the \"ID\" of player which you want to use [Catbalou]\n");
							}
						}

						// Willy the Kid
						if (strncmp(character[i].name, "Willy the Kid", 13) == 0)
						{
							isBang = 0;
						}
					}

					///////* Dead Check *///////
					if (dead_check(i, i) == 1)
					{
						// End the game.
						return 0;
					}
					else
					{
						press_to_continue();
						continue;
					}				
					break;
				}

				break;

				i = round_check(i);
			}
			///////* AI Player: Player2, Player3, Player4 *///////
			else
			{

			}
		}

		break;
	}

	return 0;
}
