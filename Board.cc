#include <memory>
#include <vector>
using namespace std;
// class Level
// {
// };
// class Block
// {
// };
class Cell
{
  const int x;
  const int y;
  char color;
  int tick;

public:
  Cell(int x = 0, int y = 0, char c = ' ') : x{x}, y{y}, color{c}, tick{0} {}
  int getX() const { return x; }
  int getY() const { return y; }
  char getColor() const { return color; }
  int getTick() const { return tick; }
  void setColor(char c) { color = c; }
  void incrementTick() { ++tick; }
};

class Board : public Observer
{
  vector<unique_ptr<vector<Cell>>> cells;
  Level *level;
  int width;
  int height;
  int score;
  int highScore;
  unique_ptr<Block> currentBlock;
  unique_ptr<Block> nextBlock;
  bool isBlind;
  
  unique_ptr<Block> getBlock() {
    return unique_ptr<Block>( level->spawnBlock() );
  }

  void clearLines()
  {
    for (int row = 0; row < height; ++row)
    {

      bool full = true;
      for (int col = 0; col < width; ++col)
      {
        if ((*cells[row])[col].getColor() == ' ')
        {
          full = false;
          break;
        }
      }

      if (full)
      {
        for (int rowred = row; rowred > 0; --rowred)
        {
          cells[rowred] = move(cells[rowred - 1]);
        }

        auto newRow = make_unique<vector<Cell>>();
        for (int col = 0; col < width; ++col)
        {
          newRow->emplace_back(col, 0, ' ');
        }
        cells[0] = move(newRow);
        --row;
      }
    }
  }


public:


  explicit Board(Level *lvl) : level{lvl}, width{11}, height{18},
                      score{0}, highScore{0}, isBlind{false}
  {
    for (int r = 0; r < height; ++r)
    {
      auto row = make_unique<std::vector<Cell>>();
      row->reserve(width);

      for (int c = 0; c < width; ++c)
      {
        row->emplace_back(c, r, ' ');
      }
      cells.push_back(move(row));
    }
    currentBlock = getBlock();
    nextBlock = getBlock();
  }


  void notify() override {
  }

  Cell *getCellAt(int x, int y)
  {
    return &(*cells[y])[x];
  }

  void incScore(int inc) {
    score += inc;
    if (score > highScore)
      highScore = score;
  }

  bool getBlind() const { return isBlind; }
  void setBlind(bool b) { isBlind = b; }

  bool placeBlock(Block *b)
  {
    vector<Pos> basePos = b->getPositions();
    int drop = 0;
    while (true)
    {
      bool canDrop = true;
      for (const auto &p : basePos)
      {
        int x = p.x;
        int y = p.y + drop + 1;

        if (y >= height)
        {
          canDrop = false;
          break;
        }
        if ((*cells[y])[x].getColor() != ' ')
        {
          canDrop = false;
          break;
        }
      }
      if (!canDrop)
        break;
      ++drop;
    }

    bool illegalPlacement = false;
    for (const auto &p : basePos) {
        int x = p.x;
        int y = p.y + drop;

        if (x < 0 || x >= width || y < 0 || y >= height) {
            continue;
        }

        if (y < 3) {
            illegalPlacement = true;
        }

        (*cells[y])[x].setColor(b->getType());
    }
    clearLines();
    notify();
    return !illegalPlacement;
  }



  Block* getCurrentBlock() {
    return currentBlock.get();
  }

  Block* getNextBlock() {
    return nextBlock.get();
  }

}