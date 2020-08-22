/*
    Author: Adam Giusti
    Purpose: Implement the various functions necessary to play the game.

    Date Created: August 20, 2020
    Last Updated: August 20, 2020
*/

#include <stdio.h>
#include <stdbool.h>
#include "tictactoe.h"

#define ROW_COUNT 3
#define COLUMN_COUNT 3

char board[3][3] = {
    {'_', '_', '_'},
    {'_', '_', '_'},
    {'_', '_', '_'}
};
bool gameOver = false;

// Start the game loop
void playGame(void) {
    bool player1sTurn = true;

    while (!gameOver) {
        playTurn(player1sTurn);
        player1sTurn = !player1sTurn;
    }
}

// Execute an individual player's turn
void playTurn(bool player1sTurn) {
    int playerNumber = player1sTurn ? 1 : 2;
    char playerLetter = player1sTurn ? 'X' : 'O';
    int rowNumber;
    int columnNumber;
    
    // Get the player's input
    printf("Player %d, mark a space on the board (row column): ", playerNumber);
    scanf("%d %d", &rowNumber, &columnNumber);

    markBoard(rowNumber, columnNumber, playerLetter);
    printBoard();
}

// Mark an individual cell on the board using the given player's input
void markBoard(int rowNumber, int columnNumber, char playerLetter) {
    board[rowNumber - 1][columnNumber - 1] = playerLetter;
}

// Print the board's template to display how input should be formatted or the actual board to show the game's state
void printBoard(void) {
    printf("\n");

    for (int rowIndex = 0; rowIndex < ROW_COUNT; rowIndex++) {
        const bool lastRow = rowIndex == (ROW_COUNT - 1);

        // Print additional line for improved style
        printf("\t\t|\t\t|\n");
        for (int columnIndex = 0; columnIndex < COLUMN_COUNT; columnIndex++) {
            const char cell = board[rowIndex][columnIndex];
            const bool lastColumn = columnIndex == (COLUMN_COUNT - 1);

            // Don't print the vertical bar character if we're on the last column
            if (lastColumn) {
                printf("\t%c\n", cell);
            }
            else {
                printf("\t%c\t|", cell);
            }
        }
        // Print additional line for improved style
        printf("\t\t|\t\t|\n");

        // Print the row separator if we're not on the last row
        if (!lastRow) {
            printf("-------------------------------------------------\n");
        }
    }

    printf("\n");
}
