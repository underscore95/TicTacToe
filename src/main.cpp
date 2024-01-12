// main.cpp
// Entry point

#include <string>
#include <iostream>
#include "tictactoe.h"

void playGame();

int main() {

	std::string playAgain;
	do {
		for (int i = 0; i < 10; ++i) {
			std::cout << "\n";
		}
		playGame();
		std::cout << "Play Again? (y/n): ";
		std::getline(std::cin, playAgain);
	} while (playAgain != "n");
	return 0;
}

void playGame() {
	TicTacToe game;
	Player winner = Player::NONE;
	Player turn = Player::X;
	GameState gameState;

	do {
		game.printBoard(std::cout);
		std::cout << "\nPlayer " << (turn == Player::X ? "X" : "O") << "'s Turn\n";

		int row;
		int column;
		int square;

		// Get the square
		do {
			column = 0;
			row = 0;

			// Get row
			do {
				std::cout << "Enter a row (1-3): ";
				std::cin >> row;
				std::cout << "\n";
			} while (row < 1 || row > 3);

			// Get column
			do {
				std::cout << "Enter a column (1-3): ";
				std::cin >> column;
				std::cout << "\n";
			} while (column < 1 || column > 3);

			square = (row - 1) * 3 + (column - 1);
			if (!game.isSquareEmpty(square)) {
				std::cout << "That square is taken!\n\n";
				continue;
			}
			break;
		} while (true);

		game.playAt(square, turn);
		gameState = game.getGameState(winner);

		turn = turn == Player::X ? Player::O : Player::X;
	} while (gameState == GameState::IN_PROGRESS);

	// Game over
	for (int i = 0; i < 10; ++i) {
		std::cout << "\n";
	}

	game.printBoard(std::cout);
	std::cout << "\nGame Over! ";
	if (gameState == GameState::DRAW) {
		std::cout << "DRAW\n";
	}
	else {
		std::cout << "Player " << (winner == Player::X ? "X" : "O") << " Wins\n";
	}
}