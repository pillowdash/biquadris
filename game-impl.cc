module Game;
import <stdexcept>;
import Board;
import Viewver;

void Game::run(const Viewver &viewver) {
    // Implementation of the game loop
    std::string command;
    while (true) {
        // Game logic here

        // Render the game state
        viewver.drawGrid(*this);
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