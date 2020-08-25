/*
    Author: Adam Giusti
    Purpose: Declare the various variables and functions necessary to play the game.

    Date Created: August 20, 2020
    Last Updated: August 24, 2020
*/

#include <stdbool.h>

extern char board[3][3];
extern bool gameOver;

// Start the game loop
void playGame(void);

// Execute an individual player's turn
void playTurn(const bool player1sTurn);

// Return whether or not the given player's mark is valid
bool markIsValid(const int rowNumber, const int columnNumber);

// Print some messages to indicate that the current player's mark is invalid
void printInvalidMarkMessage(const char message[]);

// Mark an individual cell on the board using the given player's mark
void markBoard(const int rowNumber, const int columnNumber, const char playerLetter);

// Print the board's template to display how input should be formatted or the actual board to show the game's state
void printBoard(void);

// Check if the given player has won in any way
void checkWin(const int playerNumber, const char playerLetter);

// Return whether or not the current player's move has caused a row win
bool rowWin(void);

// Return whether or not the current player's move has caused a column win
bool columnWin(void);

// Return whether or not the current player's move has caused a diagonal win
bool diagonalWin(void);

// Return whether or not the board is filled up
bool boardIsFilled(void);

// Print the result of the game and invoke promptRematch()
void endGame(const int playerNumber, const char playerLetter, const char winType[]);

// Ask the player who lost if they want a rematch
void promptRematch(const int playerNumber);

// Reset the game's elements, such as the board, when the game is replayed
void resetGame(void);
