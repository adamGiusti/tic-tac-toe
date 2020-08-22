/*
    Author: Adam Giusti
    Purpose: Declare the various variables and functions necessary to play the game.

    Date Created: August 20, 2020
    Last Updated: August 20, 2020
*/

#include <stdbool.h>

extern char board[3][3];

// Print the board's template to display how input should be formatted or the actual board to show the game's state
void printBoard(void);

// Execute an individual player's turn
void playTurn(bool player1sTurn);

// Mark an individual cell on the board using the given player's input
void markBoard(int rowNumber, int columnNumber, char playerLetter);
