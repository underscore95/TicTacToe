// tictactoe.h
// Represents a tic tac toe game

#pragma once

#include "game_state.h"
#include "player.h"
#include <math.h>
#include <iostream>

class TicTacToe {
public:
	TicTacToe();
	~TicTacToe();

	// Returns true if no player has played at the square yet, otherwise returns false
	bool isSquareEmpty(int index) const;

	// Play at a square, this will overwrite any existing player
	void playAt(int index, Player player);

	// Get the current game state, will update winner reference if there is a winner
	GameState getGameState(Player& winner) const;

	// Print the board
	void printBoard(std::ostream& out) const;

private:
	// Check if a player has won
	bool hasWon(Player player) const;

	// Clear the board
	void clearBoard();

	// Get all columns of the board
	Player** getColumns() const;

	// Get all rows of the board
	Player** getRows() const;

	// Get all diagonals of the board
	Player** getDiagonals() const;

	// Return true if all squares in the squares array are equal to player, then frees the squares array memory
	bool areAllEqualToThenFreeMemory(Player* squares, int numSquares, Player player) const;

	Player* board = new Player[9];
};