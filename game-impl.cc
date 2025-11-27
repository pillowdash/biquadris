module Game;
import <stdexcept>;
import <iostream>;
import <string>;
import Board;
import Viewver;

// g++20 observer.o block.o Level.o Level-impl.o board.o viewver.o viewver-impl.o game.o game-impl.o main.o -o test 

void Game::run(const Viewver &viewver) {
    // Implementation of the game loop
    while (player1->getTerminate() == false && player2->getTerminate() == false) {
        // Game logic here

        // Render the game state
        viewver.drawGrid(*player1, *player2, level1, level2);
        std::cout << "Player 1's turn:" << std::endl;
        std::string cmd1 = player1->getInput();
        std::cout << "Works" << std::endl;
        if (player1->getTerminate() || player2->getTerminate()) {
            break;
        }
        viewver.drawGrid(*player1, *player2, level1, level2);
        std::cout << "Player 2's turn:" << std::endl;
        std::string cmd2 = player2->getInput();

        // have trie of commands to handle all commands that are non left, right, rccw
    }
    std::cout << "Game Over!" << std::endl;
    if (player1->getTerminate()) {
        std::cout << "Player 2 Wins!" << std::endl;
    } else if (player2->getTerminate()) {
        std::cout << "Player 1 Wins!" << std::endl;
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