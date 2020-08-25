/*
    Author: Adam Giusti
    Purpose: Implement the various functions necessary to play the game.

    Date Created: August 20, 2020
    Last Updated: August 24, 2020
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
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
            checkWin(playerNumber, playerLetter);

            replayTurn = false;
        }
        else {
            replayTurn = true;
        }
    } while (replayTurn);
}

// Return whether or not the given player's mark is valid
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

// Check if the given player has won in any way
void checkWin(const int playerNumber, const char playerLetter) {
    if (rowWin()) {
        endGame(playerNumber, playerLetter, "row");
    }
    else if (columnWin()) {
        endGame(playerNumber, playerLetter, "column");
    }
    else if (diagonalWin()) {
        endGame(playerNumber, playerLetter, "diagonal");
    }
    // If the board is filled up and nobody won, the result must be a draw
    else if (boardIsFilled()) {
        endGame(playerNumber, playerLetter, "draw");
    }
}

// Return whether or not the current player's move has caused a row win
bool rowWin(void) {
    bool result = false;

    for (int rowIndex = 0; rowIndex < ROW_COUNT; rowIndex++) {
        char row[ROW_COUNT];
        bool rowIsEqual;

        for (int columnIndex = 0; columnIndex < COLUMN_COUNT; columnIndex++) {
            const char cell = board[rowIndex][columnIndex];
            row[columnIndex] = cell;
        }

        // The cells shouldn't be considered equal if they are empty
        rowIsEqual = (row[0] != '_') && (row[0] == row[1]) && (row[0] == row[2]);

        if (rowIsEqual) {
            result = true;
            break;
        }
    }

    return result;
}

// Return whether or not the current player's move has caused a column win
bool columnWin(void) {
    bool result = false;

    for (int columnIndex = 0; columnIndex < COLUMN_COUNT; columnIndex++) {
        char column[COLUMN_COUNT];
        bool columnIsEqual;

        for (int rowIndex = 0; rowIndex < ROW_COUNT; rowIndex++) {
            const char cell = board[rowIndex][columnIndex];
            column[rowIndex] = cell;
        }

        // The cells shouldn't be considered equal if they are empty
        columnIsEqual = (column[0] != '_') && (column[0] == column[1]) && (column[0] == column[2]);

        if (columnIsEqual) {
            result = true;
            break;
        }
    }

    return result;
}

// Return whether or not the current player's move has caused a diagonal win
bool diagonalWin(void) {
    char mainDiagonal[ROW_COUNT];
    char crossDiagonal[ROW_COUNT];
    bool mainDiagonalIsEqual;
    bool crossDiagonalIsEqual;
    bool result;

    for (int rowIndex = 0, crossColumnIndex = COLUMN_COUNT - 1; rowIndex < ROW_COUNT; rowIndex++, crossColumnIndex--) {
        const char mainCell = board[rowIndex][rowIndex];
        const char crossCell = board[rowIndex][crossColumnIndex];

        mainDiagonal[rowIndex] = mainCell;
        crossDiagonal[rowIndex] = crossCell;
    }

    // The cells shouldn't be considered equal if they are empty
    mainDiagonalIsEqual = (mainDiagonal[0] != '_') && (mainDiagonal[0] == mainDiagonal[1]) && (mainDiagonal[0] == mainDiagonal[2]);
    crossDiagonalIsEqual = (crossDiagonal[0] != '_') && (crossDiagonal[0] == crossDiagonal[1]) && (crossDiagonal[0] == crossDiagonal[2]);

    result = mainDiagonalIsEqual || crossDiagonalIsEqual;

    return result;
}

// Return whether or not the board is filled up
bool boardIsFilled(void) {
    bool result = true;

    for (int rowIndex = 0; rowIndex < ROW_COUNT; rowIndex++) {
        for (int columnIndex = 0; columnIndex < COLUMN_COUNT; columnIndex++) {
            const char cell = board[rowIndex][columnIndex];

            // If there's an empty cell, don't bother checking the rest of them
            if (cell == '_') {
                result = false;
                break;
            }
        }
    }

    return result;
}

// Print the result of the game and invoke promptRematch()
void endGame(const int playerNumber, const char playerLetter, const char winType[]) {
    // If the result is a draw, the outputted message should be formatted differently
    if (strcmp(winType, "draw") == 0) {
        printf("Draw. Neither player wins.");
    }
    else {
        printf("Congratulations, Player %d! You won the game by placing three %c's in a %s.", playerNumber, playerLetter, winType);
    }
    printf("\n\n");

    // Determine if the program's execution should end or continue with another match
    promptRematch(playerNumber);
}

// Ask the player who lost if they want a rematch
void promptRematch(const int playerNumber) {
    const int loserPlayerNumber = playerNumber == 1 ? 2 : 1;
    char answer;
    bool answerIsValid;

    do {
        // Get the player's answer and convert it to lowercase so that mixed cases aren't compared
        printf("Player %d, would you like a rematch (y/n)?: ", loserPlayerNumber);
        scanf(" %c", &answer);
        answer = tolower(answer);

        // Test the validity of the answer
        answerIsValid = (answer == 'y') || (answer == 'n');
        if (!answerIsValid) {
            printf("\nYou must enter 'y' for yes or 'n' for no.\n");
            printf("Please try again.\n\n");
        }
        // Reset or end the game based on the answer
        else if (answer == 'y') {
            resetGame();
        }
        else if (answer == 'n') {
            gameOver = true;
            printf("\n");
        }
    } while (!answerIsValid);
}

// Reset the game's elements, such as the board, when the game is replayed
void resetGame(void) {
    // Clear the board
    for (int rowIndex = 0; rowIndex < ROW_COUNT; rowIndex++) {
        for (int columnIndex = 0; columnIndex < COLUMN_COUNT; columnIndex++) {
            board[rowIndex][columnIndex] = '_';
        }
    }

    // Restart the game loop
    playGame();
}
