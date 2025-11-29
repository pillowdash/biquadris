module Game;
import <stdexcept>;
import <iostream>;
import <string>;
import <memory>;
import Board;
import Viewver;

// g++20 observer.o block.o Level.o Level-impl.o board.o viewver.o viewver-impl.o game.o game-impl.o main.o -o test 

void Game::run(Viewver &viewver) {
    player1->initializeCellsCopy();
    player2->initializeCellsCopy();
    viewver.Draw(*player1, *player2, level1.get(), level2.get());
    player1->getCellsCopy();
    player2->getCellsCopy();
    while (player1->getTerminate() == false && player2->getTerminate() == false) {
        viewver.Draw(*player1, *player2, level1.get(), level2.get());
        std::cout << "Player 1's turn:" << std::endl;
        std::string cmd1 = player1->getInput();
        commandManager(cmd1, 1);
        viewver.Draw(*player1, *player2, level1.get(), level2.get());
        player1->getCellsCopy(); 
        player2->getCellsCopy();

        std::cout << "Player 2's turn:" << std::endl;
        std::string cmd2 = player2->getInput();
        commandManager(cmd2, 2);

        viewver.Draw(*player1, *player2, level1.get(), level2.get());
        player1->getCellsCopy();
        player2->getCellsCopy();

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
        return level1.get();
    } else if (player == 2) {
        return level2.get();
    } else {
        throw std::invalid_argument("Invalid player number");
    }
}

Board *Game::getBoard(int player) {
    if (player == 1) {
        return player1.get();
    } else if (player == 2) {
        return player2.get();
    } else {
        throw std::invalid_argument("Invalid player number");
    }
}

void Game::commandManager(std::string command, int player) {
    std::cout << "Command received for player " << player << ": " << command << std::endl;
    if (player == 1) {
        if (command == "levelup") {
            levelUp(1);
            player1->setLevel(level1.get());
        } else if (command == "leveldown") {
            levelDown(1);
            player1->setLevel(level1.get());
        } else if (command == "norandom") {
            if (level1->getLevelNum() == 3 || level1->getLevelNum() == 4) {
                std::string filemname;
                std::cin >> filemname;
                level1->setFile(filemname);
                std::cout << "Player 1 is not random: File set to " << filemname << std::endl;
            }
        } else if (command == "random") {

        }
    } else if (player == 2) {
        if (command == "levelup") {
            levelUp(2);
            player2->setLevel(level2.get());
        } else if (command == "leveldown") {
            levelDown(2);
            player2->setLevel(level2.get());
        }
    } else {
        throw std::invalid_argument("Invalid player number");
    }
}

void Game::levelUp(int player) {
    if (player == 1) {
        switch (level1->getLevelNum()) {
            case 0:
                level1 = std::make_unique<Level1>();
                break;
            case 1:
                level1 = std::make_unique<Level2>();
                break;
            case 2:
                level1 = std::make_unique<Level3>();
                break;
            case 3:
                level1 = std::make_unique<Level4>();
                break;
            default:
                break;
        }
    } else if (player == 2) {
        switch (level2->getLevelNum()) {
            case 0:
                level2 = std::make_unique<Level1>();
                break;
            case 1:
                level2 = std::make_unique<Level2>();
                break;
            case 2:
                level2 = std::make_unique<Level3>();
                break;
            case 3:
                level2 = std::make_unique<Level4>();
                break;
            default:
                break;
        }
    } else {
        throw std::invalid_argument("Invalid player number");
    }
}

void Game::levelDown(int player) {
    if (player == 1) {
        switch (level1->getLevelNum()) {
            case 4:
                level1 = std::make_unique<Level3>();
                break;
            case 3:
                level1 = std::make_unique<Level2>();
                break;
            case 2:
                level1 = std::make_unique<Level1>();
                break;
            case 1:
                level1 = std::make_unique<Level0>("biquadris_sequence.txt");
                break;
            default:
                break;
        }
    } else if (player == 2) {
        switch (level2->getLevelNum()) {
            case 4:
                level2 = std::make_unique<Level3>();
                break;
            case 3:
                level2 = std::make_unique<Level2>();
                break;
            case 2:
                level2 = std::make_unique<Level1>();
                break;
            case 1:
                level2 = std::make_unique<Level0>("biquadris_sequence.txt");
                break;
            default:
                break;
        }
    } else {
        throw std::invalid_argument("Invalid player number");
    }
}
