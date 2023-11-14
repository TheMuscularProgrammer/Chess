#define _CRT_SECURE_NO_WARNINGS
#include "q6.h"
#include <stdio.h>
#include <stdlib.h>

long getFileSize(FILE* f);
chessPosList* buildList(BYTE* arr, int size, short int listLen);
BOOL isValidPathList(chessPosList* lst);

BYTE* getBytesFromFile(FILE* f, int* size);
chessPosList* getListFromFile(char* file_name);

int checkAndDispalyPathFromFile(char* file_name)
{
	int res;
	chessPosList* lst = getListFromFile(file_name);
	if (lst == NULL)
		return -1;
	else
	{
		if (isValidPathList(lst) == FALSE)
			res = 1;
		else
		{
			display(lst);
			if (LenList(lst) == SIZE * SIZE)
				res = 2;
			else
				res = 3;
		}
		freeList(lst);
		return res;
	}

}

long getFileSize(FILE* f)
{
	long currPos = ftell(f);
	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	fseek(f, currPos, SEEK_SET);
	return size;
}
BYTE* getBytesFromFile(FILE* f, int* size)
{
	BYTE* arr;
	*size = getFileSize(f) - sizeof(short int);
	arr = (BYTE*)malloc(*size);
	checkMemory(arr);
	fread(arr, sizeof(BYTE), *size, f);

	return arr;
}

void freeList(chessPosList* lst)
{
	if (lst == NULL)
		return;
	chessPosCell* curr = lst->head;
	chessPosCell* next;
	while (curr != NULL)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	free(lst);
}

chessPosList* buildList(BYTE* arr, int size, short int listLen)
{
	chessPosList* lst;

	BYTE buffer = 0x00;
	BYTE row, col;
	int i,j;
	int bitIndex = 7;
	int index = 0;
	chessPos currPos;
	lst = (chessPosList*)malloc(sizeof(chessPosList));
	checkMemory(lst);
	makeEmptyList(lst);
	//loop the bytes and make the list
	for(i = 0; i < listLen; i++)
	{
		row = 0x00;
		for (j = 0; j < BITS_FOR_POS; j++)
		{
			shiftAndSet(&row, arr[index], bitIndex);
			bitIndex--;
			if (bitIndex == -1) {
				bitIndex = 7;
				index++;
			}
		}
		currPos[0] = row + 'A';

		col = 0x00;
		for (j = 0; j < BITS_FOR_POS; j++)
		{
			shiftAndSet(&col, arr[index], bitIndex);
			bitIndex--;
			if (bitIndex == -1) {
				bitIndex = 7;
				index++;
			}
		}
		currPos[1] = col + '1';

		insertNodeToEndOfList(lst, CreatChessPosCell(currPos, NULL));
	}
	return lst;
}
BOOL isPosInArray(chessPosArray* posArr, chessPos* pos)
{
	unsigned int i;
	for (i = 0; i < posArr->size; i++) {
		if (posArr->positions[i][0] == (*pos)[0] && posArr->positions[i][1] == (*pos)[1])
			return TRUE;
	}
	return FALSE;
}
BOOL isValidPathList(chessPosList* lst)
{
	chessPosCell* curr;
	int i;
	int r, c;
	chessPosArray*** posArrayMatrix = validKnightMoves();
	short int listLen = LenList(lst);
	curr = lst->head;
	for (i=0; i < listLen-1; i++)
	{
		r = curr->position[0] - 'A';
		c = curr->position[1] - '1';
		if (isPosInArray(posArrayMatrix[r][c], &(curr->next->position)) == FALSE)
		{
			free(posArrayMatrix);
			return FALSE;
		}

		curr = curr->next;
	}
	freeArrayBoard(posArrayMatrix);
	return TRUE;
}

chessPosList* getListFromFile(char* file_name)
{
	chessPosList* lst;
	BYTE buffer = 0x00;
	short int listLen;
	int bitCounter = 0;
	FILE* f;
	int bytesSize;

	//open file, check alloc, calc list len, get bytes from file
	f = fopen(file_name, "rb");
	if (f == NULL)
	{
		return NULL;
	}
	fread(&listLen, sizeof(short int), 1, f);
	BYTE* bytesArr = getBytesFromFile(f, &bytesSize);
	fclose(f);
	
	//get the list
	lst = buildList(bytesArr, bytesSize, listLen);
	free(bytesArr);

	return lst;
}
