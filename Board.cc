export module Board;
import <memory>;
import <vector>;
import Block;
import <iostream>;
import Observer;
import Level;
using namespace std;

export class Cell
{
  const int x;
  const int y;
  char color;
  int tick;

public:
  Cell(int x = 0, int y = 0, char c = ' ') : x{x}, y{y}, color{c}, tick{0} {}
  int getX() const;
  int getY() const;
  char getColor() const;
  int getTick() const;
  void setColor(char c);
  void incrementTick();
};

export class Board : public Observer
{
  vector<unique_ptr<vector<Cell>>> cells;
  Level *level;
  int width;
  int height;
  int score;
  int highScore;
  shared_ptr<Block> currentBlock;
  shared_ptr<Block> nextBlock;
  bool isBlind;
  bool isTerminate;

  void clearLines();

public:
  explicit Board(Level *lvl);

  std::string getInput();

  std::shared_ptr<Block> getBlock();
  
  void notify() override;

  Cell *getCellAt(int x, int y) const;

<<<<<<< HEAD
  void notify() override
  {
    // Hummmmmm......
    if (currentBlock->getIsDropped())
    {
      placeBlock(currentBlock.get());
      currentBlock = nextBlock;
      nextBlock = getBlock();
    }

    bool temp = true;
    vector<Pos> positions = currentBlock->getPositions();
    for (auto &p : positions) {
      if (p.y == 17 || getCellAt(p.x, p.y)->getColor() != ' ') {
        temp = false;
        break;
      }
    }
    
    if (!temp) {
      currentBlock->MoveUpByOne();
      placeBlock(currentBlock.get());
      currentBlock = nextBlock;
      nextBlock = getBlock();
    }
  }

  Cell *getCellAt(int x, int y) const
  {
    return &(*cells[y])[x];
  }

  void incScore(int inc)
  {
    score += inc;
    if (score > highScore)
      highScore = score;
  }
=======
  void incScore(int inc);

  void placeBlock(Block *b);
>>>>>>> cc85a3284f2ad18d9411b4c02cdfcf2ce1e16282

  bool getBlind() const { return isBlind; }
  void setBlind(bool b) { isBlind = b; }
  bool getTerminate() const {return isTerminate;}


  int getScore() const;
  Block *getCurrentBlock() const;
  Block *getNextBlock() const;
};
