#include "minimax.h"
#include "c4.h"
#include <algorithm>
#include <limits>

int evaluateWindow(vector<int> &window, int piece)
{
    int score = 0;
    int opp_piece = (piece == PLAYER_PIECE) ? AI_PIECE : PLAYER_PIECE;
    int count_piece = 0;
    int count_empty = 0;
    int count_opp_piece = 0;

    for (int i : window)
    {
        if (i == piece)
            count_piece++;
        else if (i == EMPTY)
            count_empty++;
        else if (i == opp_piece)
            count_opp_piece++;
    }

    if (count_piece == 4)
        score += 100;
    else if (count_piece == 3 && count_empty == 1)
        score += 5;
    else if (count_piece == 2 && count_empty == 2)
        score += 2;

    if (count_opp_piece == 3 && count_empty == 1)
        score -= 4;

    return score;
}

int scorePosition(Board &board, int piece)
{
    int score = 0;

    // Score center column
    vector<int> center_array(ROW_COUNT);
    for (int i = 0; i < ROW_COUNT; ++i)
    {
        center_array[i] = board[i][COLUMN_COUNT / 2];
    }
    int center_count = count(center_array.begin(), center_array.end(), piece);
    score += center_count * 3;

    // Score Horizontal
    for (int r = 0; r < ROW_COUNT; ++r)
    {
        vector<int> row_array(board[r].begin(), board[r].end());
        for (int c = 0; c < COLUMN_COUNT - 3; ++c)
        {
            vector<int> window(row_array.begin() + c, row_array.begin() + c + WINDOW_LENGTH);
            score += evaluateWindow(window, piece);
        }
    }

    // Score Vertical
    for (int c = 0; c < COLUMN_COUNT; ++c)
    {
        vector<int> col_array(ROW_COUNT);
        for (int r = 0; r < ROW_COUNT; ++r)
        {
            col_array[r] = board[r][c];
        }
        for (int r = 0; r < ROW_COUNT - 3; ++r)
        {
            vector<int> window(col_array.begin() + r, col_array.begin() + r + WINDOW_LENGTH);
            score += evaluateWindow(window, piece);
        }
    }

    // Score positively sloped diagonal
    for (int r = 0; r < ROW_COUNT - 3; ++r)
    {
        for (int c = 0; c < COLUMN_COUNT - 3; ++c)
        {
            vector<int> window(WINDOW_LENGTH);
            for (int i = 0; i < WINDOW_LENGTH; ++i)
            {
                window[i] = board[r + i][c + i];
            }
            score += evaluateWindow(window, piece);
        }
    }

    for (int r = 0; r < ROW_COUNT - 3; ++r)
    {
        for (int c = 0; c < COLUMN_COUNT - 3; ++c)
        {
            vector<int> window(WINDOW_LENGTH);
            for (int i = 0; i < WINDOW_LENGTH; ++i)
            {
                window[i] = board[r + 3 - i][c + i];
            }
            score += evaluateWindow(window, piece);
        }
    }

    return score;
}

pair<int, int> minimax(Board &board, int depth, int alpha, int beta, bool maximizingPlayer)
{
    vector<int> valid_locations = getValidLocations(board);
    bool is_terminal = isTerminalNode(board);
    if (depth == 0 || is_terminal)
    {
        if (is_terminal)
        {
            if (winningMove(board, AI_PIECE))
            {
                return make_pair(-1, numeric_limits<int>::max());
            }
            else if (winningMove(board, PLAYER_PIECE))
            {
                return make_pair(-1, numeric_limits<int>::min());
            }
            else
            {
                return make_pair(-1, 0);
            }
        }
        else
        {
            return make_pair(-1, scorePosition(board, AI_PIECE));
        }
    }

    if (maximizingPlayer)
    {
        int value = numeric_limits<int>::min();
        int column = valid_locations[rand() % valid_locations.size()];
        for (int col : valid_locations)
        {
            int row = getNextOpenRow(board, col);
            Board b_copy = board;
            dropPiece(b_copy, row, col, AI_PIECE);
            int new_score = minimax(b_copy, depth - 1, alpha, beta, false).second;
            if (new_score > value)
            {
                value = new_score;
                column = col;
            }
            alpha = max(alpha, value);
            if (alpha >= beta)
                break;
        }
        return make_pair(column, value);
    }
    else
    {
        int value = numeric_limits<int>::max();
        int column = valid_locations[rand() % valid_locations.size()];
        for (int col : valid_locations)
        {
            int row = getNextOpenRow(board, col);
            Board b_copy = board;
            dropPiece(b_copy, row, col, PLAYER_PIECE);
            int new_score = minimax(b_copy, depth - 1, alpha, beta, true).second;
            if (new_score < value)
            {
                value = new_score;
                column = col;
            }
            beta = min(beta, value);
            if (alpha >= beta)
                break;
        }
        return make_pair(column, value);
    }
}
