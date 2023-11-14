#pragma once
#include <stdio.h>
#include "q1.h"
#include "q2.h"
#include "q3.h"
#include "q4.h"
#include "q5.h"
#include "q6.h"
#define SPACE ' '

void printMenu();
void GetPositionFromUser();
BOOL IsValidInput(char let, char dig);
void OptionOne(chessPos* position);
pathTree OptionTwo(chessPos* positon);
chessPosList* OptionThree(pathTree* tr, chessPos* pos);

void OptionFour(pathTree* tr, chessPosList* lst, chessPos* pos);

void OptionFive();
char* getFileName();
void freeTree(pathTree* tr);
void freeTreeHelper(treeNode* root);
void freeTreeNodeListCell(treeNodeListCell* head);

