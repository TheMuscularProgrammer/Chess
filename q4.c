#include "q4.h"
#include <stdio.h>
#include <stdlib.h>
void HelperCoverBoard(treeNode* root, chessPosList* listOfChessPos, treeNode* newArr[], int currIndex);

chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree)
{
	chessPosList* listOfChessPos = (chessPosList*)malloc(sizeof(chessPosList)); /*initial the chess pos list*/
	checkMemory(listOfChessPos);
	treeNode* nodesArr[SIZE*SIZE]; /*initial the array nodes*/
	int currIndex = 0;

	makeEmptyList(listOfChessPos);
	HelperCoverBoard(path_tree->root, listOfChessPos, nodesArr, currIndex);
	if (isEmptyList(listOfChessPos) == TRUE) /*means we not got all the cells*/
	{
		free(listOfChessPos);
		
		return NULL;
    }  
	else /*we got all the cells*/
	{
		return listOfChessPos;
	}
}

void HelperCoverBoard(treeNode* root, chessPosList* listOfChessPos,treeNode* newArr[], int currIndex)
{ 
	treeNodeListCell* curr;
	int i;

	
	if (root == NULL || isEmptyList(listOfChessPos)==FALSE) /*so we finish the job*/
		return;
	else
	{
		newArr[currIndex] = root; /*we get the root to the array*/
		if (currIndex == SIZE * SIZE - 1)
		{
			for (i = 0; i < SIZE*SIZE; i++)
			{
				insertNodeToEndOfList(listOfChessPos, CreatChessPosCell(newArr[i]->position, NULL)); /*insert the node to list*/
			}
			return;
		}
		curr = root->next_possible_positions;
		while (curr)
		{
			HelperCoverBoard(curr->node, listOfChessPos, newArr, currIndex+1); /*we keep doing it for all the array nodes*/
			curr = curr->next;
		}
	}
}
void insertNodeToEndOfList(chessPosList* lst , chessPosCell* node)
{
	node->next= NULL;
	if (lst->head == NULL)
		lst->head = lst->tail = node;
	else
	{
		lst->tail->next = node;
		lst->tail = node;
	}
}
chessPosCell* CreatChessPosCell(chessPos data,chessPosCell* next)
{
	chessPosCell* res = (chessPosCell*)malloc(sizeof(chessPosCell));
	checkMemory(res);
	res->next = next;
	res->position[0] = data[0];
	res->position[1] = data[1];
	return res;
}










void makeEmptyList(chessPosList* lst)
{
	lst->head = lst->tail = NULL;
}


