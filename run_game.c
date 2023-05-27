#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char** initBoard(){
        char** board = (char**)malloc(6 * sizeof(char*));
        for(int i = 0; i < 7; i++){
                board[i] = (char*)malloc(7 * sizeof(char));
        }

        for(int i = 0; i < 6; i++){
                for(int j = 0; j < 7; j++){
                        board[i][j] = 'O';
                }
        }
        
        return board;
}

void printBoard(char** board) {
        printf("\n  1   2   3   4   5   6   7\n");
        printf("____________________________\n");
        for(int i = 0; i < 6; i++){
                printf("|_%c_|", board[i][0]);
                for(int j = 1; j < 7; j++){
                        printf("_%c_|", board[i][j]);
                }
                printf("\n");
        }
        printf("\n");
}

void freeBoard(char** board){
        for(int i = 0; i < 7; i++){
                free(board[i]);
        }
        free(board);
}

void insertPiece(char*** board, int col, char color) {
        fprintf(stderr, "in function %d\n", col);
        int i = 5;
        while ((*board)[i][col] != 'O') {
                fprintf(stderr, "%c\n", (*board)[i][col]);
                i--;
                if (i == -1) break;
        }
        if (i >= 0) (*board)[i][col] = color;
        else printf("No space here. Try Again: \n");
}

int main(int argc, char *argv[]) {
        char** board = initBoard();

        char input;
        int player = 1; 

        printBoard(board);
        printf("Enter a column 1-7 (press 'q' to quit): \n");

        while (1) {
                scanf(" %c", &input);
                if (input == 'q') {
                printf("Exiting the program.\n");
                break;
                }
                if (input >= '1' && input <= '7') {
                        if (player == 1) {
                                insertPiece(&board, input - 1, 'R');
                                printBoard(board);
                        } else {
                                insertPiece(&board, input - 1, 'R');
                                printBoard(board);
                        }
                } else {
                        printf("Incorrect Input.\n\n");
                }
                printf("Enter a column 1-7 (press 'q' to quit): \n");
        }
        freeBoard(board);
}
