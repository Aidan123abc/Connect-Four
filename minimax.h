#ifndef MINIMAX_H
#define MINIMAX_H

#include <vector>
#include "c4.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <ctime>
#include <algorithm>

#define ROW_COUNT 6
#define COLUMN_COUNT 7
#define PLAYER 0
#define AI 1
#define EMPTY 0
#define PLAYER_PIECE 1
#define AI_PIECE 2
#define WINDOW_LENGTH 4

using namespace std;

typedef vector<vector<int>> Board;

using namespace std;

pair<int, int> minimax(Board &board, int depth, int alpha, int beta, bool maximizingPlayer);
int evaluateWindow(vector<int> &window, int piece);
int scorePosition(Board &board, int piece);

#endif
