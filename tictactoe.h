/*
    Author: Adam Giusti
    Purpose: Declare the various variables and functions necessary to play the game.

    Date Created: August 20, 2020
    Last Updated: August 22, 2020
*/

#include <stdbool.h>

extern char board[3][3];
extern bool gameOver;

// Start the game loop
void playGame(void);

// Execute an individual player's turn
void playTurn(bool player1sTurn);

// Determine whether or not the given player's mark is valid
bool markIsValid(int rowNumber, int columnNumber);

// Mark an individual cell on the board using the given player's mark
void markBoard(int rowNumber, int columnNumber, char playerLetter);

// Print the board's template to display how input should be formatted or the actual board to show the game's state
void printBoard(void);
