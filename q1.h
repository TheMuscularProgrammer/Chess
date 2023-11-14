#pragma once


typedef unsigned char BYTE;

typedef int BOOL;
#define FALSE 0
#define TRUE 1

#define SIZE 5
#define MAX_MOVES 8

typedef char chessPos[2];

typedef struct _chessPosArray {
	unsigned int size;
	chessPos* positions;
}chessPosArray;

chessPosArray* BuildTheBoard(int row, int col);
chessPosArray ***validKnightMoves();
void checkMemory(void* ptr);
void freeArrayBoard(chessPosArray*** Board);

