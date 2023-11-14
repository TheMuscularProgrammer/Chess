#pragma once
#include "q4.h"

typedef unsigned char BYTE;
#define BITS_FOR_POS 3

void saveListToBinFile(char* file_name, chessPosList* pos_list);

short int LenList(chessPosList* pos_list);

BOOL isBitSet(BYTE buffer, int index);
void shiftAndSet(BYTE* buffer, BYTE pos, int index);
void checkIfFileOpen(FILE* f);
