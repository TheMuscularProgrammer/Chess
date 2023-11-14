#pragma once
#include "q2.h"
#include "q3.h"

chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree);
void makeEmptyList(chessPosList* list);

void insertNodeToEndOfList(chessPosList* lst, chessPosCell* node);
chessPosCell* CreatChessPosCell(chessPos data, chessPosCell* next);

