#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For sleep function
#include <time.h>
#include "gameio.h"

#define BOT1 system("./bot1");
#define BOT2 system("./bot2");

// Prints a string letter ny letter with time gap of 1/9 secs
void styleprint(char* s) {
    struct timespec tim, tim2;
    tim.tv_sec  = 0;
    tim.tv_nsec = 111111111L;
    int i;
    for (i=0; s[i] != '\n'; i++) {
        printf("%c", s[i]);
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
    styleprint("\n Game Simulation between bot1 and bot2 .....");
}

// Checks whether the board is a won game
// 1 => bot1 wins, 2 => bot2 wins, 0 => draw/tie, -1 => incomplete game 
int check(char** board) {
    return -1;
}

int main() {
    welcome();
    
    int x, y;
    char** board = input2D(&x, &y);
    int move=1, j;
    
    while ((j=check(board)) == -1) {
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
