#pragma once
#include "q1.h"


typedef struct _treeNodeListCell treeNodeListCell;

typedef struct _treeNode {
	chessPos position;
	treeNodeListCell* next_possible_positions; // רשימת מיקומים
} treeNode;

typedef struct _treeNodeListCell {
	struct _treeNode* node;
	struct _treeNodeListCell* next;
} treeNodeListCell;

typedef struct _pathTree {
	treeNode* root;
} pathTree;


pathTree findAllPossibleKnightPaths(chessPos* startingPosition);
treeNode* findAllPossibleKnightPathsHelper(chessPos* startingPosition, chessPosArray*** mat, BOOL path[SIZE][SIZE]);
BOOL alreadyAppeared(chessPos* currPos, BOOL path[SIZE][SIZE]);
treeNode* creatTreeNode(chessPos* position);
void insertTreeNodeToList(treeNode* lst, treeNode* kid);
treeNodeListCell* createNewListNode(treeNode* kid, treeNodeListCell* next);
void insertNodeToStartList(treeNode* lst, treeNodeListCell* newNode);
BOOL isEmptyListTree(treeNode* lst);

