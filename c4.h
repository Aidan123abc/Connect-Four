#ifndef C4_H
#define C4_H

#include <vector>

#define ROW_COUNT 6
#define COLUMN_COUNT 7
#define PLAYER 0
#define AI 1
#define EMPTY 0
#define PLAYER_PIECE 1
#define AI_PIECE 2

using namespace std;

typedef vector<vector<int>> Board;

Board createBoard();
void dropPiece(Board &board, int row, int col, int piece);
bool isValidLocation(Board &board, int col);
int getNextOpenRow(Board &board, int col);
void printBoard(Board &board);
bool winningMove(Board &board, int piece);
vector<int> getValidLocations(Board &board);
bool isTerminalNode(Board &board);

#endif
