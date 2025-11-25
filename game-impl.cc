module Game;
import <stdexcept>;
import <iostream>;
import <string>;
import Board;
import Viewver;

// g++20 observer.o block.o Level.o Level-impl.o board.o viewver.o viewver-impl.o game.o game-impl.o main.o -o test 

void Game::run(const Viewver &viewver) {
    // Implementation of the game loop
    std::string command;
    while (true) {
        // Game logic here

        // Render the game state
        viewver.drawGrid(*player1, *player2, level1, level2);
        std::cin >> command;
    }
}

void Game::reset() {
    // Implementation to reset the game state
}

Level *Game::getLevel(int player) {
    if (player == 1) {
        return level1;
    } else if (player == 2) {
        return level2;
    } else {
        throw std::invalid_argument("Invalid player number");
    }
}

Board *Game::getBoard(int player) {
    if (player == 1) {
        return player1;
    } else if (player == 2) {
        return player2;
    } else {
        throw std::invalid_argument("Invalid player number");
    }
}