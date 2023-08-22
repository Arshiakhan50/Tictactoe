#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
// Name: Arshia Sharifi, Student Number: 501158323
void printBoard(char board[]) {
    printf(" %c | %c | %c \n", board[0], board[1], board[2]);
    printf("-----------\n");
    printf(" %c | %c | %c \n", board[3], board[4], board[5]);
    printf("-----------\n");
    printf(" %c | %c | %c \n", board[6], board[7], board[8]);
}

bool checkWin(char board[], char player) {
    for (int i = 0; i < 9; i += 3) {
        if (board[i] == player && board[i+1] == player && board[i+2] == player)
            return true;
    }
    for (int i = 0; i < 3; i++) {
        if (board[i] == player && board[i+3] == player && board[i+6] == player)
            return true;
    }
    if ((board[0] == player && board[4] == player && board[8] == player) ||
        (board[2] == player && board[4] == player && board[6] == player))
        return true;

    return false;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <X or O> <input_file>\n", argv[0]);
        return 1;
    }

    char player = argv[1][0]; 
    if (player != 'X' && player != 'O') {
        fprintf(stderr, "Arg 1: must be X or O\n");
        return 1;
    }

    FILE *file = fopen(argv[2], "r");
    if (file == NULL) {
        fprintf(stderr, "Arg 2: Must be a readable file\n");
        return 2;
    }
    char player2;
    if (player == 'X'){
        player2 = 'O';
    }
    else 
        player2 = 'X';

    int moves[9] = {0};
    int count = 0;
    int num;

    int locator = 0;
    while (1){
        int status = fscanf(file, "%d", &num);
        if (status == EOF){
            break;
        }
        else if (status == 0){
            fprintf(stderr, "Arg 2: File must contain integers 1-9\n");
            return 3;
        }
        else{
            if (num < 1 || num > 9) {
                fprintf(stderr, "Arg 2: File must contain integers 1-9\n");
                return 3;
            }
            moves[count++] = num;
            locator++;
            }
    }
    if (locator < 9){
        fprintf(stderr, "Arg 2: File must contain integers 1-9\n");
        return 3;
    }

    char board[9] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};

    for (int i = 0; i < count; i++) {
        int move = moves[i] - 1;
        if (board[move] != '-') {
            fprintf(stderr, "Arg 2: File contains duplicate number\n");
            return 3;
        }
        board[move] = (i % 2 == 0) ? player : player2;

        if (checkWin(board, board[move])) {
            printBoard(board);
            printf("%c is the winner!\n", board[move]);
            if (board[move] == 'X')
                return 4;
            else
                return 5;
        }
    }

    printBoard(board);
    printf("The game ends in a tie.\n");
    return 6;
}
