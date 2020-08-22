/*
    Author: Adam Giusti
    Purpose: Implement the various functions necessary to play the game.

    Date Created: August 20, 2020
    Last Updated: August 22, 2020
*/

#include <stdio.h>
#include <stdbool.h>
#include "tictactoe.h"

#define ROW_COUNT 3
#define COLUMN_COUNT 3

char board[ROW_COUNT][COLUMN_COUNT] = {
    {'_', '_', '_'},
    {'_', '_', '_'},
    {'_', '_', '_'}
};
bool gameOver = false;

// Start the game loop
void playGame(void) {
    bool player1sTurn = true;

    printBoard();

    while (!gameOver) {
        playTurn(player1sTurn);

        // Switch to the other player's turn
        player1sTurn = !player1sTurn;
    }
}

// Execute an individual player's turn
void playTurn(const bool player1sTurn) {
    bool replayTurn;

    // Ask the player for their mark until it's valid
    do {
        const int playerNumber = player1sTurn ? 1 : 2;
        const char playerLetter = player1sTurn ? 'X' : 'O';
        int rowNumber;
        int columnNumber;
        
        // Get the player's mark
        printf("Player %d, mark a space on the board (row column): ", playerNumber);
        scanf("%d %d", &rowNumber, &columnNumber);

        // Only mark the board if the player's mark is valid
        if (markIsValid(rowNumber, columnNumber)) {
            markBoard(rowNumber, columnNumber, playerLetter);
            printBoard();
            // Check win...
            replayTurn = false;
        }
        else {
            replayTurn = true;
        }
    } while (replayTurn);
}

// Determine whether or not the given player's mark is valid
bool markIsValid(const int rowNumber, const int columnNumber) {
    const bool rowOutOfBounds = rowNumber > ROW_COUNT;
    const bool columnOutOfBounds = columnNumber > COLUMN_COUNT;
    // Only evaluate the expression if the row and column indices are in the bounds of the board
    const bool cellAlreadyMarked = (rowOutOfBounds || columnOutOfBounds) ? false : (board[rowNumber - 1][columnNumber - 1] != '_');
    const bool result = !rowOutOfBounds && !columnOutOfBounds && !cellAlreadyMarked;

    // Print an out-of-bounds message based on the values of rowOutOfBounds and columnOutOfBounds
    if (rowOutOfBounds && columnOutOfBounds) {
        printInvalidMarkMessage("Your row and column numbers must be from 1-3!");
    }
    else if (rowOutOfBounds || columnOutOfBounds) {
        if (rowOutOfBounds) {
            printInvalidMarkMessage("You must specify a row number from 1-3!");
        }
        else if (columnOutOfBounds) {
            printInvalidMarkMessage("You must specify a column number from 1-3!");
        }
    }
    // Only check if the cell is already marked if both the row and column numbers are in bounds
    else if (cellAlreadyMarked) {
        printInvalidMarkMessage("That space is already taken up!");
    }

    return result;
}

// Print some messages to indicate that the current player's mark is invalid
void printInvalidMarkMessage(const char message[]) {
    printf("\n%s\n", message);
    printf("Please try again.\n\n");
}

// Mark an individual cell on the board using the given player's mark
void markBoard(const int rowNumber, const int columnNumber, const char playerLetter) {
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

// Determine whether or not the game is unfinished (i.e. the board is not filled up)
bool notFinished(void) {
    bool result = false;

    for (int rowIndex = 0; rowIndex < ROW_COUNT; rowIndex++) {
        for (int columnIndex = 0; columnIndex < COLUMN_COUNT; columnIndex++) {
            const char cell = board[rowIndex][columnIndex];

            // If there's an empty cell, don't bother checking the rest of them
            if (cell == '_') {
                result = true;
                break;
            }
        }
    }

    return result;
}

// Determine whether or not the current player's move has caused a row win
bool rowWin(void) {
    bool result = false;

    for (int rowIndex = 0; rowIndex < ROW_COUNT; rowIndex++) {
        char row[ROW_COUNT];
        bool rowIsEqual;

        for (int columnIndex = 0; columnIndex < COLUMN_COUNT; columnIndex++) {
            const char cell = board[rowIndex][columnIndex];
            row[columnIndex] = cell;
        }

        rowIsEqual = (row[0] == row[1]) && (row[0] == row[2]);
        if (rowIsEqual) {
            result = true;
            break;
        }
    }

    return result;
}
