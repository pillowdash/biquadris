module Board;

using namespace std;

int Cell::getX() const { return x; }
int Cell::getY() const { return y; }
char Cell::getColor() const { return color; }
int Cell::getTick() const { return tick; }
void Cell::setColor(char c) { color = c; }
void Cell::incrementTick() { ++tick; }

Cell &Cell::operator=(const Cell &other) {
  if (this == &other) {
    return *this;
  }
  x = other.x;
  y = other.y;
  color = other.color;
  tick = other.tick;
  return *this;
}


void Board::clearLines()
{
  int linesClearedHere = 0;
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
      incScore();
      ++linesClearedHere;
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
  linesCleared = linesClearedHere;
}

Board::Board(Level *lvl) : level{lvl}, width{11}, height{18}, 
  score{0}, highScore{0}, linesCleared{0}, isBlind{false}, 
  isTerminate{false}, specialEffectHeavy{false}, timeSinceLastClear{0}
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

std::string Board::getInput()
{
  auto protection = currentBlock; // to prevent use after free error
  return currentBlock->getInput();
}

std::shared_ptr<Block> Board::getBlock()
{
  bool heavy = level->getIsHeavy();
  char blockType = level->spawnBlock();
  std::shared_ptr<Block> block;
  if (blockType == 'I')
  {
    block = std::make_shared<I>(this);
  }
  else if (blockType == 'J')
  {
    block = std::make_shared<J>(this);
  }
  else if (blockType == 'L')
  {
    block = std::make_shared<L>(this);
  }
  else if (blockType == 'O')
  {
    block = std::make_shared<O>(this);
  }
  else if (blockType == 'S')
  {
    block = std::make_shared<S>(this);
  }
  else if (blockType == 'T')
  {
    block = std::make_shared<T>(this);
  }
  else if (blockType == 'Z')
  {
    block = std::make_shared<Z>(this);
  }
  else
  {
    throw std::invalid_argument("Invalid block type");
  }
  // stacking heaviness
  if (heavy)
  {
    block->IncHeaviness();
  }
  if (specialEffectHeavy)
  {
    block->IncHeaviness();
  }
  return block;
}

void Board::createNewBlock() {
  currentBlock = getBlock();
  nextBlock = getBlock();
}

void Board::notify()
{
  timeSinceLastClear++;
  isBlind = false;
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

  if (timeSinceLastClear > 5 && level->getLevelNum() >= 4) {
    std::shared_ptr<B> specialBlock = std::make_shared<B>(this);
    placeBlock(specialBlock.get());
    timeSinceLastClear = 0;
  }

  if (getLinesCleared() > 1) {
    resetLinesCleared();
    bool specialEffected = false;
    while (!specialEffected) {
      string s = "";
      std::cout << "enter a special effect to use (blind, heavy, force): " << std::endl;
      std::cin >> s;
      if (s == "blind") {
        isBlind = true;
        specialEffected = true;
      } else if (s == "heavy") {
        currentBlock->IncHeaviness();
        specialEffectHeavy = true;
        specialEffected = true;
      } else if (s == "force") {
        char blockType;
        std::cout << "enter a block type to force (I, J, L, O, S, T, Z): ";
        std::cin >> blockType;
        if (blockType == 'I' || blockType == 'J' || blockType == 'L' ||
            blockType == 'O' || blockType == 'S' || blockType == 'T' ||
            blockType == 'Z') {
          //force the next block to be of type blockType
          specialEffected = true;
        }
      } else {
        std::cout << "invalid special effect" << std::endl;
      }
    }
  }
}

Cell *Board::getCellAt(int x, int y) const
{
  return &(*cells[y])[x];
}

void Board::incScore()
{
  for (int i = 0; i < level->getLevelNum() + 1; ++i) {
    score++;
  }
  if (score > highScore)
    highScore = score;
}

void Board::placeBlock(Block *b)
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

  for (const auto &p : basePos)
  {
    int x = p.x;
    int y = p.y + drop;

    if (x < 0 || x >= width || y < 0 || y >= height)
    {
      continue;
    }

    (*cells[y])[x].setColor(b->getType());
  }
  clearLines();
  for (int r = 0; r < 3; ++r)
  {
    for (int col = 0; col < width; ++col)
    {
      if ((*cells[r])[col].getColor() != ' ')
      {
        isTerminate = true;
        break;
      }
    }
  }
  return;
}

int Board::getScore() const
{
  return score;
}

Block *Board::getCurrentBlock() const
{
  return currentBlock.get();
}

Block *Board::getNextBlock() const
{
  return nextBlock.get();
}

void Board::getCellsCopy() {
  cellsCopy.clear();
  for (int r = 0; r < height; ++r) {
    vector<Cell> row;
    for (int c = 0; c < width; ++c) {
      row.push_back((*cells[r])[c]);
    }
    cellsCopy.push_back(row);
  }
}

void Board::initializeCellsCopy() {
  cellsCopy.resize(height);
  for (int r = 0; r < height; ++r) {
    cellsCopy[r].resize(width);
    for (int c = 0; c < width; ++c) {
      cellsCopy[r][c] = Cell(c, r, '+');
    }
  }
}

bool Board::cellHasChanged(int x, int y) const {
  return cellsCopy[y][x].getColor() != (*cells[y])[x].getColor();
}

/*
void Board::cacheCells() {
  // use copy assignment operator to copy cells to cachedCells
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      cachedCells[i][j] = (*cells[i])[j];
    }
  }
}

vector<Cell> Board::cacheDiff() {
  vector<Cell> diffs;
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      if (cachedCells[i][j].getColor() != (*cells[i])[j].getColor()) {
        diffs.push_back((*cells[i])[j]);
      }
    }
  }
  return diffs;
}
*/