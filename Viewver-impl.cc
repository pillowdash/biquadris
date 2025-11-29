module Viewver;
import xwindow;
import Board;
import Block;
import <iostream>;
import <string>;
import <vector>;

Viewver::Viewver(int w, int h, bool textOnlyMode) : width{w}, height{h}, textOnly{textOnlyMode} {
    if (!textOnly) {
        window = std::make_unique<Xwindow>(500, 500);
    }
}

bool isBlockPosition(const std::vector<Pos> &positions, Pos position) {
    for (const auto &pos : positions) {
        if (pos == position) {
            return true;
        }
    }
    return false;
}

bool Viewver::isBlockStillThere(int x, int y, const std::vector<Pos> &positions) {
    for (const auto &pos : positions) {
        if (pos.x == x && pos.y == y) {
            return true;
        }
    }
    return false;
}



void Viewver::drawGrid(const Board &p1, const Board &p2, const Level* level_p1, const Level* level_p2) const {
    std::cout << "Level     " << level_p1->getLevelNum() << "        "
              << "Level     " << level_p2->getLevelNum() << std::endl;
    std::cout << "Score     " << p1.getScore() << "        "
              << "Score     " << p2.getScore() << std::endl;
    std::cout << "-----------" << "        "
              << "-----------" << std::endl;
    

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
        std::cout << "        ";
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

    std::cout << "-----------" << "        "
              << "-----------" << std::endl;
    std::cout << "Next: " << nextBlock1->getType() << "                "
              << "Next: " << nextBlock2->getType() << std::endl;
}

void Viewver::drawGraphics(const Board &p1, const Board &p2,
                           const Level* level_p1, const Level* level_p2) {


    // --- TEXT HEADER ---
    window->drawString(20, 20,  "Level: " + std::to_string(level_p1->getLevelNum()));
    window->drawString(220, 20, "Level: " + std::to_string(level_p2->getLevelNum()));

    window->drawString(20, 40,  "Score: " + std::to_string(p1.getScore()));
    window->drawString(220, 40, "Score: " + std::to_string(p2.getScore()));
    const int cellSize = 20;
    const int p1OffsetX = 20;
    const int p1OffsetY = 70;

    const int p2OffsetX = 220;
    const int p2OffsetY = 70;

    Block *currentBlock1 = p1.getCurrentBlock();
    Block *currentBlock2 = p2.getCurrentBlock();

    auto pos1 = currentBlock1->getPositions();
    auto pos2 = currentBlock2->getPositions();

    // --- PLAYER 1 GRAPHICS ---
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            Pos p{c, r};
            if (isBlockPosition(pos1, p)) {
                // falling block overrides board
                int drawColour = Xwindow::Cyan;  
                window->fillRectangle(
                    p1OffsetX + c * cellSize,
                    p1OffsetY + r * cellSize,
                    cellSize, cellSize,
                    drawColour
                );
            } else if (p1.cellHasChanged(c, r) || isBlockStillThere(c, r, previousCBPosP1)) {
                int drawColour = Xwindow::White;
                char colour = p1.getCellAt(c, r)->getColor();

                if (colour == 'I') drawColour = Xwindow::Cyan;
                else if (colour == 'J') drawColour = Xwindow::Blue;
                else if (colour == 'L') drawColour = Xwindow::Orange;
                else if (colour == 'S') drawColour = Xwindow::Green;
                else if (colour == 'Z') drawColour = Xwindow::Red;
                else if (colour == 'T') drawColour = Xwindow::Magenta;
                else if (colour == 'O') drawColour = Xwindow::Yellow;

                window->fillRectangle(
                    p1OffsetX + c * cellSize,
                    p1OffsetY + r * cellSize,
                    cellSize, cellSize,
                    drawColour
                );
            }
        }
    }

    // --- PLAYER 2 GRAPHICS ---
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            Pos p{c, r};
            if (isBlockPosition(pos2, p)) {
                int drawColour = Xwindow::Cyan;
                window->fillRectangle(
                    p2OffsetX + c * cellSize,
                    p2OffsetY + r * cellSize,
                    cellSize, cellSize,
                    drawColour
                );
            } else if (p2.cellHasChanged(c, r) || isBlockStillThere(c, r, previousCBPosP2)) {
                int drawColour = Xwindow::White;
                char colour = p2.getCellAt(c, r)->getColor();
                if (colour == 'I') drawColour = Xwindow::Cyan;
                else if (colour == 'J') drawColour = Xwindow::Blue;
                else if (colour == 'L') drawColour = Xwindow::Orange;
                else if (colour == 'S') drawColour = Xwindow::Green;
                else if (colour == 'Z') drawColour = Xwindow::Red;
                else if (colour == 'T') drawColour = Xwindow::Magenta;
                else if (colour == 'O') drawColour = Xwindow::Yellow;

                window->fillRectangle(
                    p2OffsetX + c * cellSize,
                    p2OffsetY + r * cellSize,
                    cellSize, cellSize,
                    drawColour
                );
            }
        }
    }

    // --- NEXT BLOCK ---
    window->drawString(p1OffsetX,  height * cellSize + 110,
                      "Next: " + std::string(1, p1.getNextBlock()->getType()));

    window->drawString(p2OffsetX, height * cellSize + 110,
                      "Next: " + std::string(1, p2.getNextBlock()->getType()));
    previousCBPosP1 = p1.getCurrentBlock()->getPositions();
    previousCBPosP2 = p2.getCurrentBlock()->getPositions();
}

void Viewver::Draw(const Board &p1, const Board &p2,
                   const Level* level_p1, const Level* level_p2) {
    if (textOnly) {
        drawGrid(p1, p2, level_p1, level_p2);
    } else {
        drawGrid(p1, p2, level_p1, level_p2);
        drawGraphics(p1, p2, level_p1, level_p2);
    }
}

/*
void Viewwer::drawDiff(const Board &p1, const Board &p2,
                           const Level* level_p1, const Level* level_p2) {

    const int cellSize = 20;
    const int p1OffsetX = 20;
    const int p1OffsetY = 70;

    const int p2OffsetX = 220;
    const int p2OffsetY = 70;

    // --- TEXT HEADER ---
    window.drawString(p1OffsetX, 20,  "Level: " + std::to_string(level_p1->getLevelNum()));
    window.drawString(p2OffsetX, 20, "Level: " + std::to_string(level_p2->getLevelNum()));

    window.drawString(p1OffsetX, 40,  "Score: " + std::to_string(p1.getScore()));
    window.drawString(p2OffsetX, 40, "Score: " + std::to_string(p2.getScore()));

    Block *currentBlock1 = p1.getCurrentBlock();
    Block *currentBlock2 = p2.getCurrentBlock();

    vector<Pos> pos1 = currentBlock1->getPositions();
    vector<Pos> pos2 = currentBlock2->getPositions();

    vector<Cell> diffs1 = p1.cacheDiff();
    vector<Cell> diffs2 = p2.cacheDiff();

    for (auto &cell : diffs1) {
        int c = cell.getX();
        int r = cell.getY();

        int drawColour = Xwindow::White;

        Pos p{c, r};

        if (isBlockPosition(pos1, p)) {
            // falling block overrides board
            drawColour = Xwindow::Cyan;  
        } else {
            char colour = p1.getCellAt(c, r)->getColor();

            if (colour == 'I') drawColour = Xwindow::Cyan;
            else if (colour == 'J') drawColour = Xwindow::Blue;
            else if (colour == 'L') drawColour = Xwindow::Orange;
            else if (colour == 'S') drawColour = Xwindow::Green;
            else if (colour == 'Z') drawColour = Xwindow::Red;
            else if (colour == 'T') drawColour = Xwindow::Magenta;
            else if (colour == 'O') drawColour = Xwindow::Yellow;
        }

        window.fillRectangle(
            p1OffsetX + c * cellSize,
            p1OffsetY + r * cellSize,
            cellSize, cellSize,
            drawColour
        );
    }

    for (auto &cell : diffs2) {
        int c = cell.getX();
        int r = cell.getY();

        int drawColour = Xwindow::White;

        Pos p{c, r};

        if (isBlockPosition(pos2, p)) {
            drawColour = Xwindow::Cyan;
        } else {
            char colour = p2.getCellAt(c, r)->getColor();

            if (colour == 'I') drawColour = Xwindow::Cyan;
            else if (colour == 'J') drawColour = Xwindow::Blue;
            else if (colour == 'L') drawColour = Xwindow::Orange;
            else if (colour == 'S') drawColour = Xwindow::Green;
            else if (colour == 'Z') drawColour = Xwindow::Red;
            else if (colour == 'T') drawColour = Xwindow::Magenta;
            else if (colour == 'O') drawColour = Xwindow::Yellow;
        }

        window.fillRectangle(
            p2OffsetX + c * cellSize,
            p2OffsetY + r * cellSize,
            cellSize, cellSize,
            drawColour
        );
    }

    for (auto &pos : pos1) {
        int c = pos.x;
        int r = pos.y;

        window.fillRectangle(
            p1OffsetX + c * cellSize,
            p1OffsetY + r * cellSize,
            cellSize, cellSize,
            Xwindow::Cyan
        );
    }

    for (auto &pos : pos2) {
        int c = pos.x;
        int r = pos.y;

        window.fillRectangle(
            p2OffsetX + c * cellSize,
            p2OffsetY + r * cellSize,
            cellSize, cellSize,
            Xwindow::Cyan
        );
    }



    // --- NEXT BLOCK ---
    window.drawString(p1OffsetX,  height * cellSize + 110,
                      "Next: " + std::string(1, p1.getNextBlock()->getType()));

    window.drawString(p2OffsetX, height * cellSize + 110,
                      "Next: " + std::string(1, p2.getNextBlock()->getType()));

    cacheCells();
}
*/
