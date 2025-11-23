import Game;
import <stdexcept>;

void Game::run() {
    // Implementation of the game loop
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

