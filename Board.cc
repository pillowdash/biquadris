#include <memory>
#include <vector>
using namespace std;
class Level {

};
class Block {

};
class Cell {
  const int x;
  const int y;
  char color;
  int tick;
public:
  Cell(int x = 0, int y = 0, char c = ' '): x{x}, y{y}, color{c}, tick{0} {}
  int getX() const { return x;}
  int getY() const { return y;}
  char getColor() const { return color; }
  int getTick() const { return tick; }
  void setColor(char c) { color = c; }
  void incrementTick() { ++tick; }


};

class Board {
  vector <unique_ptr<vector<Cell>>> cells;
  Level* level;
  int width;
  int height;
  int score;
  int highScore;
  unique_ptr<Block> currentBlock;
  unique_ptr<Block> nextBlock;
  bool isBlind;
public:
  Board(Level *lvl = nullptr) : level{lvl}, width{11}, height{18},
          score{0}, highScore{0}, isBlind{false} {
          for (int r = 0; r < height; ++r) {
            auto row = std::make_unique<std::vector<Cell>>();
            row->reserve(width);

            for (int c = 0; c < width; ++c) {
                row->emplace_back(c, r, ' ');
            }
            cells.push_back(move(row));
          }
        }

   Cell *getCellAt(int x, int y) {
        return &(*cells[y])[x];
    }
    
    void incScore(int inc) {
        score += inc;
        if (score > highScore) highScore = score;
    }

    void clearLines() {
        for (int r = 0; r < height; ++r) {

            bool full = true;
            for (int c = 0; c < width; ++c) {
                if ((*cells[r])[c].getColor() == ' ') {
                    full = false;
                    break;
                }
            }

            if (full) {
                for (int rr = r; rr > 0; --rr) {
                    cells[rr] = std::move(cells[rr - 1]);
                }

                auto newRow = std::make_unique<std::vector<Cell>>();
                for (int c = 0; c < width; ++c) {
                    newRow->emplace_back(c, 0, ' ');
                }
                cells[0] = std::move(newRow);
                --r;       // re-check this row
            }
        }
    }


}