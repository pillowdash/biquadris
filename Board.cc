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
  int x;
  int y;
  char color;
  int tick;

public:
  Cell(int x = 0, int y = 0, char c = ' ') : x{x}, y{y}, color{c}, tick{0} {}
  Cell(const Cell &other) = default;
  Cell &operator=(const Cell &other) {
    if (this == &other) {
      return *this;
    }
    x = other.x;
    y = other.y;
    color = other.color;
    tick = other.tick;
    return *this;
  }
  int getX() const;
  int getY() const;
  char getColor() const;
  int getTick() const;
  void setColor(char c);
  void incrementTick();
  //Cell &operator=(const Cell &other) = default;
};

export class Board : public Observer
{
  vector<unique_ptr<vector<Cell>>> cells;
  vector<vector<Cell>> cellsCopy;
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

  bool cellHasChanged(int x, int y) const;

  void incScore(int inc);

  void placeBlock(Block *b);

  bool getBlind() const { return isBlind; }
  void setBlind(bool b) { isBlind = b; }
  bool getTerminate() const {return isTerminate;}
  void setLevel(Level* lvl) { level = lvl; }

  void getCellsCopy();
  void initializeCellsCopy();
  int getScore() const;
  Block *getCurrentBlock() const;
  Block *getNextBlock() const;

  // only called by Viewver-impl.cc

  //void cacheCells(); // will save the current cells in [cells] to [cachedcells]
  //vector<Cell> cacheDiff(); // sends the difference between [cells] and [cachedcells]
};
