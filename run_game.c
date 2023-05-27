#include <stdio.h>
#include <stdlib.h>

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

void insertPiece(char** board, int col, char color) {
        int i = 0;
        while (board[i][col] != 'O') {
                i++;
        }
        board[i][col] = color;
}

int main(int argc, char *argv[]) {
        char** board = initBoard();
        printBoard(board);
        freeBoard(board);
}
