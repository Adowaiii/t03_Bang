#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "mustang.h"

// Structure: Mustang
void Mustang_Ctor(Mustang *this, int mustangId)
{
	this->mustangId = mustangId;
}

int Mustang_mustangId(Mustang *this)
{
	return this->mustangId;
}



// [Mustang] 66 67
// [Default] 80
int mustang_id[2] = {66, 67};
char mustang_function[2][100] = {"All other players must add 1 to the distance to you.", "You may subtract 1 from the distance to all other players."};
