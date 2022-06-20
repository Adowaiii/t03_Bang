printf("\n[Player%d Round]\n", i+1);
				press_to_continue();
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
					if(FindCard(HandCard[i],"DYNAMITE") != -1){
							card_id = 0;
					}
					if(board[i].isBarrel == false && FindCard(HandCard[i],"BARREL") != -1){
						card_id = FindCard(HandCard[i],"BARREL");
					}
					if(board[i].isScope == false && FindCard(HandCard[i],"SCOPE ") != -1){
						card_id = FindCard(HandCard[i],"SCOPE ");
					}
					if(FindCardt(HandCard[i],"MUSTANG") != -1){
						card_id = FindCardt(HandCard[i],"MUSTANG");
					}
					if(FindCardt(HandCard[i],"weapon") != -1){
						card_id = FindCardt(HandCard[i],"weapon");
					}
					if(FindCard(HandCard[i],"JAIL") != -1){
				//		for(int temp = 0,max = 0;temp < PLAYER_NUM ;temp ++){
				//			if(temp != i){
				//				if(coundCard(HandCard[temp]) > max){
				//					max = temp;
				//					option max;
				//				}
				//			}
				//		}
						card_id = FindCard(HandCard[i],"JAIL");
					}
					if(FindCard(HandCard[i],"DUEL") != -1 && countCardName(HandCard[i],"BANG") >= 3){
						card_id = FindCard(HandCard[i],"DUEL");
					}
					if(board[i].hp < character[i].hp && card_id != 0){
						if(FindCard(HandCard[i],"BEER") != -1){
							card_id = FindCard(HandCard[i],"BEER");
						}
						else if(FindCard(HandCard[i],"SALOON") != -1){
							card_id = FindCard(HandCard[i],"SALOON");
						}
					}
					if(card_id != 0){
						if(FindCard(HandCard[i],"STAGECOACH") != -1){
							card_id = FindCard(HandCard[i],"STAGECOACH");
						}
						else if(FindCard(HandCard[i],"WELLS FARGO") != -1){
							card_id = FindCard(HandCard[i],"WELLS FARGO");
						}
						else if(FindCard(HandCard[i],"GENERAL STORE") != -1){
							card_id = FindCard(HandCard[i],"GENERAL STORE");
						}
						else if(FindCard(HandCard[i],"PANIC") != -1){
							card_id = FindCard(HandCard[i],"PANIC");
						}
						else if(FindCard(HandCard[i],"CAT BALOU") != -1){
							card_id = FindCard(HandCard[i],"CAT BALOU");
						}
					}
					if(card_id != 0){
						if(FindCard(HandCard[i],"GATLING") != -1){
							card_id = FindCard(HandCard[i],"GATLING");
						}
						else if(FindCard(HandCard[i],"INDIANS") != -1){
							card_id = FindCard(HandCard[i],"INDIANS");
						}
						else if(FindCard(HandCard[i],"BANG") != -1 && isBang == 0){
							card_id = FindCard(HandCard[i],"BANG");
						}
					}
					if(countCard(HandCard[i]) <= board[i].hp){
						card_id = 0;
					}

					print_board();
					printf("\n[Player%d Round]\n", i+1);

					// Skip
					if (card_id == 0)
					{
						///////* Discard Check *///////robot
						while (discard_check(card_num, i) == 1)
						{
							print_board();
							printf("\n[Player%d Round]\n", i+1);

							int discard_id;
							print_HandCard(i);
							printf("There are too many cards! Input the \"ID\" of card which you want to discard: ");
							if(FindCard(HandCard[i],"DYNAMITE") != -1){
								discard_id = FindCard(HandCard[i],"DYNAMITE");
							}
							else if(FindCard(HandCard[i],"JAIL") != -1){
								discard_id = FindCard(HandCard[i],"JAIL");
							}
							else if(FindCard(HandCard[i],"SCHOFIELD") != -1){
								discard_id = FindCard(HandCard[i],"SCHOFIELD");
							}
							else{
								discard_id = rand()%(countCard(HandCard[i]))+1; 
							}

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
					// Play Card 
					else
					{
						if (card_id < 0 || card_id > card_num)
						{
							printf("Invalid \"ID\"!\n");
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
								printf("You have already used the [Bang!]\n");
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
						// PANIC: ~~~coming soon~~~
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
						// CATBALOU: ~~~coming soon~~~
						else if (strncmp(pointer->name, "CAT BALOU", 8) == 0)
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
						// STAGECOACH
						else if (strncmp(pointer->name, "STAGECOACH", 10) == 0)
						{
							STAGECOACH(board, HandCard, i, 0, deck, deadwood, card_id);
						}
						// WELLSFARGO
						else if (strncmp(pointer->name, "WELLS FARGO", 10) == 0)
						{
							WELLSFARGO(board, HandCard, i, 0, deck, deadwood, card_id);
						}
						// GENERALSTORE
						else if (strncmp(pointer->name, "GENERAL STORE", 13) == 0)
						{
							int alive_count = 0;
							for (int j=0; j<PLAYER_NUM; j++)
							{
								if (isDead[j] == 0)
								{
									alive_count++;
								}

							}

							GENERALSTORE_2(board, HandCard, i, alive_count, deck, deadwood, card_id, isDead);
						}
						// BEER
						else if (strncmp(pointer->name, "BEER", 4) == 0)
						{
							if (board[i].hp == Character_hp(&character[i]))
							{
								printf("You cannot use [Beer], your hp are already full!\n");
								continue;
							}
							else
							{
								BEER(board, HandCard, i, 0, deck, deadwood, card_id);
							}
						}
						// SALOON
						else if (strncmp(pointer->name, "SALOON", 6) == 0)
						{
							for (int j=0; j<PLAYER_NUM; j++)
							{
								if (isDead[j] == 1 || board[j].hp == Character_hp(&character[j]))
								{
									continue;
								}
								else
								{
									BEER(board, HandCard, j, 0, deck, deadwood, card_id);
								}
							}
							Move1Card(deadwood, HandCard[i], card_id);
						}
						// DUEL
						else if (strncmp(pointer->name, "DUEL", 4) == 0)
						{
							int duel_temp[PLAYER_NUM+1];
							memset(duel_temp, 0, sizeof(duel_temp));
							printf("Input the \"ID\" of player which you want to use [Duel]\n");
							for (int j=0; j<PLAYER_NUM; j++)
							{
								if (i == j)
								{
									continue;
								}
								if (isDead[j] == 0)
								{
									printf("\"%d\" Player%d\n", j+1, j+1);
									duel_temp[j+1] = 1;
								}
							}

							int duel_object;
							while(1)
							{
								scanf("%d", &duel_object);
								if (duel_object >= 1 && duel_object <= PLAYER_NUM && duel_temp[duel_object] == 1)
								{
									DUEL(board, HandCard, i, duel_object-1, deck, deadwood, card_id);
									break;
								}
								printf("Invalid input!\n");
								printf("Input the \"ID\" of player which you want to use [Duel]\n");
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
						
						continue;
					}				
					break;
				}

				//break;

				i = round_check(i);
