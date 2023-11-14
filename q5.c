#define _CRT_SECURE_NO_WARNINGS
#include "q5.h"
#include <stdio.h>
#include <stdlib.h>

void writeByteToFile(FILE* f, BYTE* buffer);

void saveListToBinFile(char* file_name, chessPosList* pos_list)
{
	BYTE buffer = 0x00;
	BYTE row, col;
	chessPosCell* curr = pos_list->head;
	short int listLen;
	int i;
	int bitCounter = 0;
	FILE* f;

	if (pos_list == NULL)
		return;
	//open file, check alloc, calc list len, save len to file
	f = fopen(file_name, "wb");
	checkIfFileOpen(f);
	listLen = LenList(pos_list);
	fwrite(&listLen, sizeof(short int), 1, f);

	//loop the list and save to file
	while (curr != NULL)
	{
		row = curr->position[0] - 'A';
		for (i = 0; i < BITS_FOR_POS; i++)
		{
			shiftAndSet(&buffer, row, BITS_FOR_POS - 1 - i);
			bitCounter++;
			if (bitCounter == 8) {
				bitCounter = 0;
				writeByteToFile(f, &buffer);
				buffer = 0;
			}
		}

		col = curr->position[1] - '1';
		for (i = 0; i < BITS_FOR_POS; i++)
		{
			shiftAndSet(&buffer, col, BITS_FOR_POS - 1 - i);
			bitCounter++;
			if (bitCounter == 8) {
				bitCounter = 0;
				writeByteToFile(f, &buffer);
				buffer = 0;
			}
		}
		curr = curr->next;
	}
	// add last byte if necessary
	if (bitCounter != 0)
	{
		buffer <<= 8 - bitCounter;
		writeByteToFile(f, &buffer);
	}
	fclose(f);
}

void shiftAndSet(BYTE* buffer,BYTE pos, int index)
{
	BYTE rightMask = 0x01;

	*buffer <<= 1;
	if (isBitSet(pos, index) == TRUE)
	{
		*buffer = (*buffer) | rightMask;
	}
}

short int LenList(chessPosList* pos_list)
{
	short int len = 0;
	chessPosCell* curr = pos_list->head;

	while (curr)
	{
		len++;
		curr = curr->next;
	}
	return len;
}


BOOL isBitSet(BYTE byte, int index)
{
	BYTE mask = 0x01 << index;
	if (mask & byte)
		return TRUE;
	else
		return FALSE;

}
void writeByteToFile(FILE* f, BYTE* buffer)
{
	fwrite(buffer, sizeof(BYTE), 1, f);
	*buffer = 0x00;
}

void checkIfFileOpen(FILE* f)
{
	if (f == NULL)
	{
		printf("file open NOT succseed!");
		exit(1);
	}
}
