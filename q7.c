#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "q7.h"

BOOL isStartPosSet(chessPos pos)
{
	if (pos[0] == '\0' && pos[1] == '\0')
		return FALSE;
	else
		return TRUE;
}

void main()
{
	int choose;
	chessPos Pos = { '\0','\0' };

	/*this char is not on the board key so if it stay in this mode we know that the user not enter any position*/
	pathTree tr;
	tr.root = NULL;
	chessPosList* lst = NULL;

	printf("Choose one of the options\n\n:"); /*asking from the user to enter a position*/
	printMenu(); /*print the menu*/
	scanf("%d", &choose); /*get the choose from user*/
	while (choose != 6) /*while the user not exit from the game*/
	{
		if (choose == 1)
			OptionOne(&Pos); /*make option one*/
		else if (choose == 2)
		{
			if (isStartPosSet(Pos) == FALSE)
			{
				printf("Run option 1 first\n");
			}
			else
			{
				tr = OptionTwo(&Pos); /*make option two*/
			}
		}
		else if (choose == 3) /*make option three*/
		{
			if (isStartPosSet(Pos) == FALSE)
			{
				printf("Run option 1 first\n");
			}
			else
			{
				lst = OptionThree(&tr,&Pos);
			}
		}
		else if (choose == 4) /*make option four*/
		{
			if (isStartPosSet(Pos) == FALSE)
			{
				printf("Run option 1 first\n");
			}
			else
			{
				OptionFour(&tr, lst,&Pos);
			}
		}
		else if (choose == 5) /*make option five*/
			OptionFive();

		printf("Choose one of the options\n\n:"); /*asking from the user to enter a position*/
		printMenu(); /*print the menu*/
		scanf("%d", &choose); /*get the choose from user*/
	}
	if (choose == 6)
	{
		freeTree(&tr); /*free the tree before the program end*/
		freeList(lst); /*free the list before the program end*/
		printf("\nHope YOU enojy :) goodbuy!");
		exit(1); /*exit the game*/
	}
	else /*illigal input*/
	{
		while (choose > 6 || choose < 1)
		{
			printf("Wrong Move!\nChoose one of the options:");
			printMenu();
			scanf("%d", &choose);
		}
	}
}

void printMenu()
{
	printf("1. Enter a knight's starting position.\n");
	printf("2. Create all possible knight paths.\n");
	printf("3. Find a knight path covring all board.\n");
	printf("4. Save knight path covering all board to file.\n");
	printf("5. Load and display path from file.\n");
	printf("6. Exit.");
	printf("\n");
}

void GetPositionFromUser() /*got the position from user*/
{
	printf("enter start position\n");
	printf("Enter a letter from A to E.\nAnd a number between 1 - 5.\n");
}

BOOL IsValidInput(char let, char dig) /*cheak if it is ligal input*/
{
	BOOL res = TRUE;
	if (let < 'A' || let >= 'A'+ SIZE)
		res = FALSE;
	if (dig < '1' || dig >= '1' + SIZE)
		res = FALSE;

	return res;
}

void OptionOne(chessPos* position)
{
	char str[3];
	GetPositionFromUser();
	scanf("%s", str);

	while (IsValidInput(str[0],str[1])==FALSE)
	{
		printf("\n\n");
		printf("NOT Valid Input! please enter a valid input!\n");
		scanf("%s", str);
	}

	(*position)[0] = str[0];
	(*position)[1] = str[1];
}

pathTree OptionTwo(chessPos* positon)
{
	pathTree tr;


	tr = findAllPossibleKnightPaths(positon);
	printf("Created all paths\n");


	return tr;
}

chessPosList* OptionThree(pathTree* tr,chessPos* pos)
{
	if (tr->root == NULL)
	{
		*tr = OptionTwo(pos);
	}

	chessPosList* res = findKnightPathCoveringAllBoard(tr);
	if (res == NULL)
	{
		printf("Could NOT find path covering all board!\n");
	}
	else
	{
		printf("Found path covering all board\n");
	}
	return res;
}

void OptionFour(pathTree* tr, chessPosList* lst,chessPos* pos)
{
	char* name;
	name = getFileName();

	if (lst == NULL)
	{
		lst = OptionThree(tr, pos);
	}

	saveListToBinFile(name, lst);
	printf("Created the file\n:"); /*asking from the user to enter a position*/

}

void OptionFive()
{
	char* name;
	int res;
	name = getFileName();

	res = checkAndDispalyPathFromFile(name);
	if (res == -1)
		printf("File does not exits.\n");
	else if (res == 1)
		printf("The file contains an invalid path.\n");
	else if (res == 2)
		printf("The path in the file covers the entire board.\n");
	else 
		printf("The path in the file does not cover the entire board.\nAnother situation.\n");
}

char* getFileName() /*get the name of file*/
{
	char Letter;
	printf("please enter a file name\n");
	int PySize = 2, LogSize = 0;
	char* file_name = (char*)malloc(sizeof(char) * PySize);
	checkMemory(file_name);
	Letter = getchar();
	if(Letter == SPACE || Letter == '\n')
		Letter = getchar();

	while (Letter != SPACE && Letter != '\n')
	{
		if (PySize == LogSize)
		{
			PySize *= 2;
			file_name = (char*)realloc(file_name, PySize * sizeof(char));
			checkMemory(file_name);
		}
		file_name[LogSize] = Letter;
		LogSize++;
		Letter = getchar();
	}

	if (PySize == LogSize)
	{
		PySize *= 2;
		file_name = (char*)realloc(file_name, PySize * sizeof(char));
		checkMemory(file_name);
	}

	file_name[LogSize] = '\0'; /*make it string*/
	LogSize++;
	file_name = (char*)realloc(file_name, LogSize * sizeof(char)); /*make it to the real size*/
	checkMemory(file_name);

	return file_name; /*return the name*/
}

void freeTree(pathTree* tr) /*free the tree*/
{
	if (tr->root != NULL)
		freeTreeHelper(tr->root);
}

void freeTreeHelper(treeNode* root)
{
	if (root != NULL)
	{
		freeTreeNodeListCell(root->next_possible_positions);
		free(root);
	}
}

void freeTreeNodeListCell(treeNodeListCell* head) /*free list node*/
{
	treeNodeListCell* cur = head;
	treeNodeListCell* next;
	if (cur != NULL)
	{
		next = cur->next;
		freeTreeHelper(cur->node);
		free(cur);
		cur = next;
	}

}
