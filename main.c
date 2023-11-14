#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "q1.h"
#include "q3.h"
#include "q4.h"
#include "q5.h"

void main()
{
	//test q1
	//chessPosArray*** res = validKnightMoves();

	//test q2
	chessPos startPos = { 'A','1' };
	pathTree pt = findAllPossibleKnightPaths(&startPos);

	//test q4
	//chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree);
	chessPosList* theList = findKnightPathCoveringAllBoard(&pt);

	saveListToBinFile("ori.bin", theList);

}
