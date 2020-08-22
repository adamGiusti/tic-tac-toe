/*
    Author: Adam Giusti
    Purpose:
        * The entry point for the entire program
        * Handles introducing the game to the players
        * Invokes the game loop

    Date Created: August 20, 2020
    Last Updated: August 22, 2020
*/

#include <stdio.h>
#include "tictactoe.h"

void printIntroduction(void);

int main(void) {
    printIntroduction();
    playGame();

    return 0;
}

void printIntroduction(void) {
    printf("\nWelcome to Tic-Tac-Toe!\n\n");

    printf("The rules of the game are simple:\n\n");
    printf("  * Player 1 (X) and Player 2 (O) will compete against each other.\n");
    printf("  * Each player will take turns marking a space on the board by specifying a row number and column number.\n");
    printf("  * Whoever aligns three of their letters in a row, column, or diagonal wins the game.\n\n");

    printf("Have fun!\n");

    printBoard();
}
