// tictactoe.cpp
// TicTacToe implementation

#include "tictactoe.h"

TicTacToe::TicTacToe()
{
	clearBoard();
}

TicTacToe::~TicTacToe()
{
	delete board;
}

bool TicTacToe::isSquareEmpty(int index) const
{
	return board[index] == Player::NONE;
}

void TicTacToe::playAt(int index, Player player)
{
	board[index] = player;
}

GameState TicTacToe::getGameState(Player& winner) const
{
	// Is there a winner?
	if (hasWon(Player::O)) {
		winner = Player::O;
		return GameState::HAS_WINNER;
	}
	else if (hasWon(Player::X)) {
		winner = Player::X;
		return GameState::HAS_WINNER;
	}
	
	// Is game over?
	for (int i = 0; i < 9; ++i) {
		if (isSquareEmpty(i)) {
			return GameState::IN_PROGRESS;
		}
	}

	return GameState::DRAW;
}

void TicTacToe::printBoard(std::ostream& out) const
{
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			// Player symbol
			switch (board[i * 3 + j]) {
			case Player::NONE:
				out << "  ";
				break;
			case Player::X:
				out << " X";
				break;
			case Player::O:
				out << " O";
				break;
			}

			// Vertical line
			if (j < 2) {
				out << " |";
			}
		}

		// Horizontal line
		if (i < 2) {
			out << "\n-----------\n";
		}
	}

	out << std::endl;
}

bool TicTacToe::hasWon(Player player) const
{
	// Check columns
	Player** cols = getColumns();
	for (int i = 0; i < 3; ++i) {
		if (areAllEqualToThenFreeMemory(cols[i], 3, player)) {
			delete[] cols;
			return true;
		}
	}

	delete[] cols;

	// Check rows
	Player** rows = getRows();
	for (int i = 0; i < 3; ++i) {
		if (areAllEqualToThenFreeMemory(rows[i], 3, player)) {
			delete[] rows;
			return true;
		}
	}

	delete[] rows;

	// Check diagonals
	Player** diagonals = getDiagonals();
	for (int i = 0; i < 2; ++i) {
		if (areAllEqualToThenFreeMemory(diagonals[i], 3, player)) {
			delete[] diagonals;
			return true;
		}
	}

	delete[] diagonals;
	return false;
}

void TicTacToe::clearBoard()
{
	for (int i = 0; i < 9; ++i) {
		board[i] = Player::NONE;
	}
}

Player** TicTacToe::getColumns() const
{
	Player** cols = new Player*[3];
	
	for (int i = 0; i < 3; ++i) {
		Player* col = new Player[3];
		for (int j = 0; j < 3; ++j) {
			col[j] = board[i + j * 3];
		}
		cols[i] = col;
	}

	return cols;
}

Player** TicTacToe::getRows() const
{
	Player** rows = new Player*[3];

	for (int i = 0; i < 3; ++i) {
		Player* row = new Player[3];
		for (int j = 0; j < 3; ++j) {
			row[j] = board[3 * i + j];
		}
		rows[i] = row;
	}

	return rows;
}

/*
0 1 2
3 4 5
6 7 8
*/
Player** TicTacToe::getDiagonals() const
{
	Player** diagonals = new Player*[2];
	diagonals[0] = new Player[] { board[0], board[4], board[8] };
	diagonals[1] = new Player[] { board[2], board[4], board[6] };
	return diagonals;
}

bool TicTacToe::areAllEqualToThenFreeMemory(Player* squares, int numSquares, Player player) const
{
	for (int i = 0; i < numSquares; ++i) {
		if (squares[i] != player) {
			delete[] squares;
			return false;
		}
	}

	delete[] squares;
	return true;
}
