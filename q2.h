#pragma once
#include "q1.h"
#include <stdio.h>
#include <stdlib.h>

/*macros*/
//#define isEmptyList(lst) (lst->head==NULL && lst->tail==NULL)
//#define isOneListNode(lst) (lst->head==lst->tail && lst->head !=NULL)

typedef struct _chessPosCell {
	chessPos position;
	struct _chessPosCell* next;
}chessPosCell;

typedef struct _chessPosList {
	chessPosCell* head;
	chessPosCell* tail;
}chessPosList;

typedef struct cell {
	BOOL Appeared;
	int tableValue;
}Cell;

#define PRINT_COL_WIDTH 5

void display(chessPosList* lst);
void PrintTable(Cell Table[][SIZE]);
void PrintTabs();
BOOL isOneListNode(chessPosList* lst);
BOOL isEmptyList(chessPosList* lst);
