#include "q3.h"
#include <stdio.h>
#include <stdlib.h>

pathTree findAllPossibleKnightPaths(chessPos* startingPosition)
{
	pathTree tr;

	chessPosArray*** WhereCanIgo = validKnightMoves(); /*get the function from seif 1*/
	BOOL WhereIwas[SIZE][SIZE] = { FALSE };
	
	tr.root = findAllPossibleKnightPathsHelper(startingPosition, WhereCanIgo, WhereIwas);
	freeArrayBoard(WhereCanIgo);
	return tr;
}


treeNode* findAllPossibleKnightPathsHelper(chessPos* startingPosition, chessPosArray*** mat, BOOL path[SIZE][SIZE])
{
	if (alreadyAppeared(startingPosition, path) == TRUE)
		return NULL;
	else
	{
		treeNode* root, *kid;
		int row = (*startingPosition)[0] - 'A'; /*make index*/
		int col = (*startingPosition)[1] - '1'; /*make index*/
		int size;
		chessPosArray* curr;

		root = creatTreeNode(startingPosition); /*make the tree root*/
		path[row][col] = TRUE; /*make the root location in math to know that i was there already*/
		size = mat[row][col]->size; /*get the size of the children of the root*/

		for (int i = 0; i < size; i++) /*i run all over the childrens*/
		{
			curr = (chessPosArray*)malloc((mat[row][col]->size) * sizeof(chessPosArray)); /*initial the array of children*/
			checkMemory(curr);
			curr = mat[row][col];
			if (alreadyAppeared(&(curr->positions[i]), path) == FALSE) /*if doesnt apprare*/
			{
				kid = findAllPossibleKnightPathsHelper(&(curr->positions[i]), mat, path); /*we assume that the function work of smaller input so that the kid became a tree with his own kids*/
				insertTreeNodeToList(root, kid); /*we insert it to the list of the father*/
			}
		}
		path[row][col] = FALSE; /*to not destroy the array*/
		return root;
	}
}

BOOL alreadyAppeared(chessPos* currPos, BOOL path[SIZE][SIZE]) /*cheak if i was in that cell before or doesnt*/
{
	int row = (*currPos)[0] - 'A';
	int col = (*currPos)[1] - '1';
	if (path[row][col] == TRUE)
		return TRUE;
	else
		return FALSE;
}

treeNode* creatTreeNode(chessPos* position)
{
	treeNode* res;
	res = (treeNode*)malloc(sizeof(treeNode));
	checkMemory(res);
	res->position[0] = (*position)[0];
	res->position[1] = (*position)[1];
	res->next_possible_positions = NULL;

	return res;
}

void insertTreeNodeToList(treeNode* lst, treeNode* kid)
{
	treeNodeListCell* newNode;
	newNode = createNewListNode(kid, NULL);
	insertNodeToStartList(lst, newNode);
}

treeNodeListCell* createNewListNode(treeNode* kid, treeNodeListCell* next)
{
	treeNodeListCell* res;
	res = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	checkMemory(res);
	res->node = kid;
	res->next = next;

	return res;
}

void insertNodeToStartList(treeNode* lst, treeNodeListCell* newNode)
{
	if (isEmptyListTree(lst) == TRUE)
	{
		newNode->next = NULL;
		lst->next_possible_positions = newNode;
	}
	else
	{
		newNode->next = lst->next_possible_positions;
		lst->next_possible_positions = newNode;
	}
}

BOOL isEmptyListTree(treeNode* lst)
{
	if (lst->next_possible_positions == NULL)
		return TRUE;
	else
		return FALSE;
}