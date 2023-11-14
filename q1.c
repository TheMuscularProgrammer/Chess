#define _CRT_SECURE_NO_WARNINGS
#include "q1.h"
#include <stdio.h>
#include <stdlib.h>

chessPosArray ***validKnightMoves()
{
	chessPosArray ***res; /*declare on the tabels of chess pos arrays*/
	unsigned int CurrentRow, CurrentCol; /*make the index to run over the board*/

	res = (chessPosArray***)malloc(SIZE * sizeof(chessPosArray**)); /*inital*/
	checkMemory(res);
	for (CurrentRow = 0; CurrentRow < SIZE; CurrentRow++) /*run over the row and initial them*/
	{
		res[CurrentRow] = (chessPosArray**)malloc(SIZE * sizeof(chessPosArray*));
		checkMemory(res[CurrentRow]);
		for (CurrentCol = 0; CurrentCol < SIZE; CurrentCol++)
		{
			res[CurrentRow][CurrentCol] = BuildTheBoard(CurrentRow, CurrentCol); /*build the arrays of chess pos*/
		}
	}
	
	return res; /*return the board of moves*/
}


chessPosArray *BuildTheBoard(int row, int col)
{
	chessPosArray *Array; /*we delacare on the array*/
	unsigned int LogSize = 0; /* we want to put the logsize at the end when we know what the size of array*/

	Array = (chessPosArray*)malloc(sizeof(chessPosArray)); /*we initial the array*/
	checkMemory(Array);
	Array->positions = (chessPos*)malloc(sizeof(chessPos)* MAX_MOVES); /*we initial the positions*/
	checkMemory(Array->positions);

	/*now we cheak where can i move due to the game rules and puts there in the chesspos list all the cells we can to
	go from and we skip where i cant go, also we update the log size of each array and update the field of the struct*/
	if (row - 2 >= 0)
	{
		if (col - 1 >= 0)
		{
			((Array->positions)[LogSize])[0] = (row - 2) + 'A';
			((Array->positions)[LogSize])[1] = (col - 1) + '1';
			LogSize++;
		}
		if (col + 1 < SIZE)
		{
			((Array->positions)[LogSize])[0] = (row - 2) + 'A';
			((Array->positions)[LogSize])[1] = (col + 1) + '1';
			LogSize++;
		}
	}
	if (row + 2 < SIZE)
	{
		if (col - 1 >= 0)
		{
			((Array->positions)[LogSize])[0] = (row + 2) + 'A';
			((Array->positions)[LogSize])[1] = (col - 1) + '1';
			LogSize++;
		}
		if (col + 1 < SIZE)
		{
			((Array->positions)[LogSize])[0] = (row + 2) + 'A';
			((Array->positions)[LogSize])[1] = (col + 1) + '1';
			LogSize++;
		}
	}
	if (col - 2 >= 0)
	{
		if (row - 1 >= 0)
		{
			((Array->positions)[LogSize])[0] = (row - 1) + 'A';
			((Array->positions)[LogSize])[1] = (col - 2) + '1';
			LogSize++;
		}
		if (row + 1 < SIZE)
		{
			((Array->positions)[LogSize])[0] = (row + 1) + 'A';
			((Array->positions)[LogSize])[1] = (col - 2) + '1';
			LogSize++;
		}
	}
	if (col + 2 < SIZE)
	{
		if (row - 1 >= 0)
		{
			((Array->positions)[LogSize])[0] = (row - 1) + 'A';
			((Array->positions)[LogSize])[1] = (col + 2) + '1';
			LogSize++;
		}
		if (row + 1 < SIZE)
		{
			((Array->positions)[LogSize])[0] = (row + 1) + 'A';
			((Array->positions)[LogSize])[1] = (col + 2) + '1';
			LogSize++;
		}
	}

	Array->positions = (chessPos*)realloc(Array->positions, sizeof(chessPos)*LogSize);
	checkMemory(Array->positions);
	Array->size = LogSize;
	return Array;
}

void checkMemory(void* ptr)
{
	if (ptr == NULL)
	{
		printf("Memory allocation failed!\n");
		exit(1);
	}
}

void freeArrayBoard(chessPosArray*** Board)
{
	int i, j;
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			free(Board[i][j]->positions);
			free(Board[i][j]);
		}
		free(Board[i]);
	}
	free(Board);

}