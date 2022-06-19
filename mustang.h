// Structure: Mustang
#ifndef _MUSTANG_H_
#define _MUSTANG_H_

typedef struct
{
	int mustangId;
} Mustang;

void Mustang_Ctor(Mustang *this, int mustangId);

int Mustang_mustangId(Mustang *this);

#endif
