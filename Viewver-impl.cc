module Viewver;
import Board;
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

void Viewver::drawGrid(const Board &p1, const Board &p2, const Level* level_p1, const Level* level_p2) const {
    std::cout << "Leve          " << level_p1->getLevelNum() << "        "
              << "Level         " << level_p2->getLevelNum() << std::endl;
    std::cout << "Score         " << p1.getScore() << "        "
              << "Score         " << p2.getScore() << std::endl;
    std::cout << "---------------" << "        "
              << "---------------" << std::endl;
    

    Block *currentBlock1 = p1.getCurrentBlock();
    Block *currentBlock2 = p2.getCurrentBlock();

    Block *nextBlock1 = p1.getNextBlock();
    Block *nextBlock2 = p2.getNextBlock();

    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            Pos p{c, r};
            if (isBlockPosition(currentBlock1->getPositions(), p)) {
                std::cout << currentBlock1->getType();
            } else {
                Cell *cell = p1.getCellAt(c, r);
                std::cout << cell->getColor();
            }
        }
        std::cout << "            ";
        for (int c = 0; c < width; ++c) {
            Pos p{c, r};
            if (isBlockPosition(currentBlock2->getPositions(), p)) {
                std::cout << currentBlock2->getType();
            } else {
                Cell *cell = p2.getCellAt(c, r);
                std::cout << cell->getColor();
            }
        }
        std::cout << std::endl;
    }
    std::cout << "---------------" << "        "
              << "---------------" << std::endl;
    std::cout << "Next: " << nextBlock1->getType() << "                "
              << "Next: " << nextBlock2->getType() << std::endl;
}

