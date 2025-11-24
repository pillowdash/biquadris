module Viewver;
import Board;
import <iostream>;
import <string>;
import <vector>;

Viewver::Viewver(int w, int h) : width{w}, height{h} {}

void Viewver::drawGrid(const Board &board) const {
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            Cell *cell = board.getCellAt(c, r);
            std::cout << cell->getColor();
        }
        std::cout << std::endl;
    }
}