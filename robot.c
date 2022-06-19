						int card_num;
						int card_id = 0;
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
							else if(FindCard(HandCard[i],"BANG") != -1){
								card_id = FindCard(HandCard[i],"BANG");
							}
						}
						if(card_id != 0){
							card_id = rand()%(countCard(HandCard[i]))+1; 
						}
					
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
									card_id = rand()%(countCard(HandCard[i]))+1; 
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
								// Slab the Killer
								if (strncmp(character[i].name, "Slab the Killer", 15) == 0)
								{
									// _SlabTheKiller_(player[i], deadwood);
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
										BANG(board, HandCard, i, bang_object, deck, deadwood, card_id);
									}
								}
								isBang = 1;
							}
							// MISSED
							else if (strncmp(pointer->name, "MISSED", 6) == 0)
							{
					/*
								// Calamity Janet
								if (strncmp(character[i].name, "Calamity Janet", 14) == 0)
								{
									if (strncmp(_CalamityJanet_(player[i], "MISSED", deadwood), "MISSED", 6)
									{
										printf("You cannot play [Missed!] card.\n");
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
											BANG(board, HandCard, i, bang_object, deck, deadwood, card_id);
										}
										isBang = 1;
									}
								}
								else
								{
									printf("You cannot play [Missed!] card.\n");
									continue;
								}
					*/
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
								int panic_object = i;
								while (1)
								{
									if (panic_object == 3)
									{
										panic_object = 0;
									}
									else
									{
										panic_object++;
									}
					
									if (isDead[panic_object] == 0)
									{
										break;
									}
								}
								PANIC(board, HandCard, i, panic_object, deck, deadwood, card_id);
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
