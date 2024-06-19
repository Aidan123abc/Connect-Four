#include "c4.h"
#include <iostream>

Board createBoard()
{
    return Board(ROW_COUNT, vector<int>(COLUMN_COUNT, EMPTY));
}

void dropPiece(Board &board, int row, int col, int piece)
{
    board[row][col] = piece;
}

bool isValidLocation(Board &board, int col)
{
    return board[ROW_COUNT - 1][col] == EMPTY;
}

int getNextOpenRow(Board &board, int col)
{
    for (int r = 0; r < ROW_COUNT; ++r)
    {
        if (board[r][col] == EMPTY)
        {
            return r;
        }
    }
    return -1; // Should never reach here if called correctly
}

void printBoard(Board &board)
{
    cout << "\n  1    2    3    4    5    6    7\n";
    cout << "___________________________________\n";
    for (int r = ROW_COUNT - 1; r >= 0; --r)
    {
        for (int c = 0; c < COLUMN_COUNT; ++c)
        {
            cout << "|_" << board[r][c] << "_|";
        }
        cout << endl;
    }
    cout << endl;
}

bool winningMove(Board &board, int piece)
{
    // Check horizontal locations for win
    for (int c = 0; c < COLUMN_COUNT - 3; ++c)
    {
        for (int r = 0; r < ROW_COUNT; ++r)
        {
            if (board[r][c] == piece && board[r][c + 1] == piece &&
                board[r][c + 2] == piece && board[r][c + 3] == piece)
            {
                return true;
            }
        }
    }

    // Check vertical locations for win
    for (int c = 0; c < COLUMN_COUNT; ++c)
    {
        for (int r = 0; r < ROW_COUNT - 3; ++r)
        {
            if (board[r][c] == piece && board[r + 1][c] == piece &&
                board[r + 2][c] == piece && board[r + 3][c] == piece)
            {
                return true;
            }
        }
    }

    // Check positively sloped diagonals
    for (int c = 0; c < COLUMN_COUNT - 3; ++c)
    {
        for (int r = 0; r < ROW_COUNT - 3; ++r)
        {
            if (board[r][c] == piece && board[r + 1][c + 1] == piece &&
                board[r + 2][c + 2] == piece && board[r + 3][c + 3] == piece)
            {
                return true;
            }
        }
    }

    // Check negatively sloped diagonals
    for (int c = 0; c < COLUMN_COUNT - 3; ++c)
    {
        for (int r = 3; r < ROW_COUNT; ++r)
        {
            if (board[r][c] == piece && board[r - 1][c + 1] == piece &&
                board[r - 2][c + 2] == piece && board[r - 3][c + 3] == piece)
            {
                return true;
            }
        }
    }

    return false;
}

vector<int> getValidLocations(Board &board)
{
    vector<int> valid_locations;
    for (int col = 0; col < COLUMN_COUNT; ++col)
    {
        if (isValidLocation(board, col))
        {
            valid_locations.push_back(col);
        }
    }
    return valid_locations;
}

bool isTerminalNode(Board &board)
{
    return winningMove(board, PLAYER_PIECE) || winningMove(board, AI_PIECE) || getValidLocations(board).empty();
}
