module Viewver;
import Board;
import Game;
import Block;
import <iostream>;
import <string>;
import <vector>;

Viewver::Viewver(int w, int h) : width{w}, height{h} {}

bool isBlockPosition(const std::vector<Pos> &positions, Pos position) {
    for (const auto &pos : positions) {
        if (pos == position) {
            return true;
        }
    }
    return false;
}

void Viewver::drawGrid(const Game &game) const {
    std::cout << "Leve          " << game.getLevel(1)->getLevelNum() << "        "
              << "Level          " << game.getLevel(2)->getLevelNum() << std::endl;
    std::cout << "Score         " << game.getBoard(1)->getScore() << "        "
              << "Score         " << game.getBoard(2)->getScore()
    std::cout << "---------------" << "        "
              << "---------------" << std::endl;
    

    Block *currentBlock1 = game.getBoard(1)->getCurrentBlock();
    Block *currentBlock2 = game.getBoard(2)->getCurrentBlock();

    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            Pos p{c, r};
            if (isBlockPosition(currentBlock1->getPositions(), p)) {
                std::cout << currentBlock1->getType();
            } else {
                Cell *cell = game.getBoard(1)->getCellAt(c, r);
                std::cout << cell->getColor();
            }
        }
        std::cout << "        ";
        for (int c = 0; c < width; ++c) {
            Pos p{c, r};
            if (isBlockPosition(currentBlock1->getPositions(), p)) {
                std::cout << currentBlock1->getType();
            } else {
                Cell *cell = game.getBoard(2)->getCellAt(c, r);
                std::cout << cell->getColor();
            }
        }
        std::cout << std::endl;
    }
    std::cout << "---------------" << "        "
              << "---------------" << std::endl;
    std::cout << "Next: " << "S" << "                "
              << "Next: " << "S" << std::endl;
}

