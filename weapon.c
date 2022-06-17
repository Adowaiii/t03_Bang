#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "weapon.h"

// Structure: Weapon
void Weapon_Ctor(Character *this, char *weaponName, int attackDistance)
{
	this->weaponName = weaponName;
	this->attackDistance = attackDistance;
}

char *Weapon_weaponName(Weapon *this)
{
	return this->weaponName;
}

int Weapon_attackDistance(Character *this)
{
	return this->attackDistance;
}


// Function: 

/*
// Function: character_choose
char name_database[16][20] = {"Bart Cassidy", "Black Jack", "Calamity Janet", "El Gringo",
                              "Jesse Jones", "Jourdonnais", "Kit Carlson", "Lucky Duke",
                              "Paul Regret", "Pedro Ramirez", "Rose Doolan", "Sid Ketchum",
                              "Slab the Killer", "Suzy Lafayette", "Vulture Sam", "Willy the Kid"};

int hp_database[16] = {4, 4, 4, 3,
                       4, 4, 4, 4,
                       3, 4, 4, 4,
                       4, 4, 4, 4};

char ability_database[16][300] =
{
	"Each time he loses a life point, he immediately draws a card from the deck.",
	"During drawing phase of his turn, he must show the second card he draws. If it's Heart or Diamond, he draws one additional card without revealing it.",
	"She can use [BANG] cards as [Missed] cards and vice versa. If she plays a [Missed] as a [BANG], she cannot play another [BANG] card that turn unless she has a [Volcanic] in play.",
	"Each time he loses a life point due to a card played by another player, he draws a random card from the hands of that player. Note that [Dynamite] damages are not caused by any player.",
	"During drawing phase of his turn, he may choose to draw the first card from the deck, or randomly from the hand of any other player. Then he draws the second card from the deck.",
	"He is considered to have a [Barrel] in play at all times; he can draw when he is the target of a [BANG], and on a Heart he is missed. If he has another real [Barrel] card in play, he can count both of them, giving him two chances to cancel the [BANG] before playing a [Missed].",
	"During drawing phase of his turn, he looks at the top three cards of the deck. He chooses 2 to draw, and puts the other one back on the top of the deck, face down.",
	"Each time he is required to draw, he flips the top two cards from the deck and chooses the result he prefers. Discard both cards afterward.",
	"He is considered to have a [Mustang] in play at all times; all other players must add 1 to the distance to him. If he has another real [Mustang] in play, he can count both of them, increasing all distances to him by a total of 2.",
	"During drawing phase of his turn, he may choose to draw the first card from the top of the discard pile or from the deck. Then, he draws the second card from the deck.",
	"She is considered to have a [Scope] in play at all times; she sees the other players at a distance decreased by 1. If she has another real [Scope] in play, she can count both of them, reducing her distance to all other players by a total of 2.",
	"At any time, he may discard 2 cards from his hand to regain one life point. If he is willing and able, he can use this ability more than once at a time.",
	"Players trying to cancel his [BANG] cards need to play 2 [Missed]. The [Barrel] effect, if successfully used, only counts as one [Missed].",
	"As soon as she has no cards in her hand, she draws a card from the draw pile.",
	"Whenever a character is eliminated from the game, he takes all the cards that player had in his hand and in play, and adds them to his hand.",
	"He can play any number of [BANG] cards during his turn."
};

Character character_choose(Character c, int number)
{
	Character_Ctor(&c, name_database[number], hp_database[number], ability_database[number]);

	return c;
}
*/
