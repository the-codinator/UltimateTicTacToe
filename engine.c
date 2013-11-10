#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For sleep function
#include <time.h>
#include "gameio.h"

#define BOT1 system("./bot1");
#define BOT2 system("./bot2");

// Prints a string letter ny letter with time gap of 1/9 secs
void styleprint(char* s) {
    struct timespec tim;
    int i;
    for (i=0; s[i] != '\0'; i++) {
        printf("%c", s[i]);
        fflush(stdout);
        tim.tv_sec  = 0;
        tim.tv_nsec = 111111111L;
        struct timespec tim2;
        nanosleep(&tim, &tim2);
    }
    printf("\n");
}

// Pauses between 2 successive prints of the game
void waiting() {
    while (getchar() != '\n');          //Waiting for enter(return) to be pressed to continue
    //sleep(2);                           //Auto-play with 2 second delay cetween steps
}

// Print a game start message
void welcome() {
    printf("================================\n");
    printf("      Ultimate Tic Tac Toe      \n");
    printf("================================\n");
    styleprint("\nGame Simulation between bot1 and bot2 .....");
    sleep(2);
}

// Checks a 3x3 board to see who won
// 1 => bot1 wins, 2 => bot2 wins, 0 => draw/tie, -1 => incomplete game
int check3x3(char board[3][3]) {
    return -1;
}

// Checks whether the board is a won game
// 1 => bot1 wins, 2 => bot2 wins, 0 => draw/tie, -1 => incomplete game
int check(char** board) {
    char bigBoard[3][3];
    int i, j, k, l;
    for (i=0; i<3; i++) {
        for (j=0; j<3; j++) {
            char smallBoard[3][3];
            for (k=0; k<3; k++) {
                for (l=0; l<3; l++) {
                    smallBoard[k][l]=board[3*i+k][3*j+l];
                }
            }
            int x = check3x3(smallBoard);
            if (x == 2) bigBoard[i][j] = 'O';
            else if (x == 1) bigBoard[i][j] = 'X';
            else bigBoard[i][j] = '.';
        }
    }
    return check3x3(bigBoard);
}

// Create a blank board to play in
void makeBlankBoard() {
    FILE* fp = fopen(SOURCE, "w");
    char* s = ".........\n";
    fprintf(fp, "%s%s%s%s%s%s%s%s%s-1 -1\n",
        s, s, s, s, s, s, s, s, s);
    fclose(fp);
}

int main() {
    welcome();
    
    makeBlankBoard();
    
    int x, y;
    char** board = input2D(&x, &y);
    int move=1, j;
    
    while (move<17 || (j=check(board)) == -1) {
        system("clear");
        output2user(board, x, y);
        
        if (move%2)
            BOT1
        else BOT2
        
        free(board);
        waiting();
        board = input2D(&x, &y);
        move++;
    }
    
    output2user(board, x, y);
    
    if (j==1) {
        styleprint("\nGame Over!\nbot1 has won the game .....");
    }
    else if (j==2) {
        styleprint("\nGame Over!\nbot2 has won the game .....");
    }
    else {
        styleprint("\nGame Over!\nbot1 and bot2 have tied .....");
    }
    
    return 0;
}
