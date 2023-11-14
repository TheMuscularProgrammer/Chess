
#include "q2.h"



void display(chessPosList* lst)
{
	Cell Table[SIZE][SIZE];
	int i, j, location = 1;
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			Table[i][j].Appeared = FALSE;
			Table[i][j].tableValue = 0;
		}
	}

	if (isOneListNode(lst) == TRUE)
	{
		Table[(int)(lst->head->position[0] - 'A')][(int)(lst->head->position[1] - '1')].Appeared = TRUE;
		Table[(int)(lst->head->position[0] - 'A')][(int)(lst->head->position[1] - '1')].tableValue = 1;
	}
	if (isEmptyList(lst) == FALSE && isOneListNode(lst) == FALSE)/*so we know that the list have at least 2 nodes because we cheak the option of empty list*/ {
		chessPosCell* pre, *curr, *saver;
		pre = lst->head;
		curr = lst->head->next;
		/*take care the first node*/

		Table[(int)(lst->head->position[0] - 'A')][(int)(lst->head->position[1] - '1')].Appeared = TRUE;
		Table[(int)(lst->head->position[0] - 'A')][(int)(lst->head->position[1] - '1')].tableValue = location;
		location++;

		while (curr) {
			if (Table[(int)(curr->position[0] - 'A')][(int)(curr->position[1] - '1')].Appeared == FALSE)  /*means that the cell doesnt appere yet*/
			{
				Table[(int)(curr->position[0] - 'A')][(int)(curr->position[1] - '1')].Appeared = TRUE; /*we sign that he apperaed*/
				Table[(int)(curr->position[0] - 'A')][(int)(curr->position[1] - '1')].tableValue = location; /*we give him his location*/
				location++; /*we precced the location*/
				curr = curr->next; /*get the next node*/
				pre = pre->next; /*get the next node*/
			}
			else /*means that the cell is already exsist so we want to delete him!*/
			{
				if (curr->next == NULL) /*we delete the last node in list*/
				{
					lst->tail = pre;
					pre->next = NULL;
					free(curr);
				}
				else /*we delete from the middle of the list*/
				{
					saver = curr;
					curr = curr->next;
					pre->next = curr;
					free(saver);
				}
			}
		}
	}
	PrintTable(Table);
}

void PrintTable(Cell Table[][SIZE]) /*print the table*/
{
	int row, coulm, i, k;
	printf("    ");
	PrintTabs();
	for (i = 0; i < SIZE; i++)
	{
		printf("%2d   ", i+1);
	}
	printf("\n");
	PrintTabs();
	for (k = 0; k < 3 + SIZE * PRINT_COL_WIDTH; k++)
	{
		printf("_");
	}
	printf("\n");
	PrintTabs();
	for (coulm = 0; coulm < SIZE; coulm++)
	{
		printf("%c |", coulm + 'A');
		for (row = 0; row < SIZE; row++)
		{
			if (Table[row][coulm].Appeared = TRUE)
			{
				printf(" %2d |", Table[row][coulm].tableValue);
			}
			else
			{
				printf(" %c |", ' ');
			}
		}
		printf("\n");
		PrintTabs();
	}
	for (k = 0; k < 3 + SIZE * PRINT_COL_WIDTH; k++)
	{
		printf("_");
	}
	printf("\n");
	PrintTabs();
}
void PrintTabs()
{
	printf("     ");
}
BOOL isOneListNode(chessPosList* lst)
{
	if (lst->head == lst->tail && lst->head != NULL)
		return TRUE;
	else
		return FALSE;
}

BOOL isEmptyList(chessPosList* lst)
{
	if (lst->head == NULL)
		return TRUE;
	else
		return FALSE;
}
