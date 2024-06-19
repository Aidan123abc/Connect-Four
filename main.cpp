#include "c4.h"
#include "minimax.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
    Board board = createBoard();
    printBoard(board);
    bool game_over = false;
    int turn = 1;

    while (!game_over)
    {
        if (turn == PLAYER)
        {
            int col;
            cout << "Player 1, make your selection (1-7): ";
            cin >> col;
            col = col - 1;

            if (isValidLocation(board, col))
            {
                int row = getNextOpenRow(board, col);
                dropPiece(board, row, col, PLAYER_PIECE);

                if (winningMove(board, PLAYER_PIECE))
                {
                    cout << "Player 1 wins!!" << endl;
                    game_over = true;
                }

                turn = (turn + 1) % 2;
                printBoard(board);
            }
        }
        else if (turn == AI && !game_over)
        {
            int col, minimax_score;
            tie(col, minimax_score) = minimax(board, 5, numeric_limits<int>::min(), numeric_limits<int>::max(), true);

            if (isValidLocation(board, col))
            {
                int row = getNextOpenRow(board, col);
                dropPiece(board, row, col, AI_PIECE);

                if (winningMove(board, AI_PIECE))
                {
                    cout << "Player 2 wins!!" << endl;
                    game_over = true;
                }

                printBoard(board);
                turn = (turn + 1) % 2;
            }
        }

        if (game_over)
        {
            cout << "Game over!" << endl;
        }
    }

    return 0;
}
