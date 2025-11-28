module Block;

using namespace std;

int Pos::getX() const { return x; }
int Pos::getY() const { return y; }

bool Pos::operator==(const Pos &other) const {
    return x == other.x && y == other.y;
}

//-------

bool Controller::getIsDropped() const {
    return isDropped;
}

string Controller::getInput() {
    string cmd;
    cin >> cmd;
    std::cout << "Received command: " << cmd << std::endl;
    if (cmd == "left") {
        MoveLeft();
    } else if (cmd == "right") {
        // Move Right
        MoveRight();
    } else if (cmd == "clockwise") {
        // Rotate Clockwise
        RotateClockWise();
    } else if (cmd == "counterclockwise") {
        // Rotate CounterClockwise
        RotateCounterClockWise();
    } else if (cmd == "drop") {
        isDropped = true;
        notifyBoard();
    }
    return cmd;
}

//------


int Block::getExtremeHelper(bool isX, bool findMax) const {
    int extreme = isX ? positions[0].getX() : positions[0].getY();
    for (auto &pos : positions) {
        int value = isX ? pos.getX() : pos.getY();
        if (findMax) {
            if (value > extreme) {
                extreme = value;
            }
        } else {
            if (value < extreme) {
                extreme = value;
            }
        }
    }
    return extreme;
}

int Block::getExtreme(const string extreme) const {
    if (extreme == "top") {
        return getExtremeHelper(false, false);
    } else if (extreme == "bottom") {
        return getExtremeHelper(false, true);
    } else if (extreme == "left") {
        return getExtremeHelper(true, false);
    } else if (extreme == "right") {
        return getExtremeHelper(true, true);
    }
    return 0;
}

void Block::rotate(Rotation dir) {
    vector<Pos> originalPositions = positions;
    Pos pivot = {getExtreme("left"), getExtreme("bottom")};

    for (auto &pos : positions) {
        int localX = pos.x - pivot.x;
        int localY = pos.y - pivot.y;

        int rx = 0;
        int ry = 0;

        if (dir == Rotation::Left) {
            // -90 degree rotation matrix
            rx = localY;
            ry = -localX;
        } else if (dir == Rotation::Right) {
            // 90 degree rotation matrix
            rx = -localY;
            ry = localX;
        } else {
            //throw std::invalid_argument("Invalid rotation direction");
        }

        pos.x = pivot.x + rx;
        pos.y = pivot.y + ry;
    }

    Pos newPivot = {getExtreme("left"), getExtreme("bottom")};

    int dx = pivot.x - newPivot.x;
    int dy = pivot.y - newPivot.y;

    for (auto &pos : positions) {
        pos.x += dx;
        pos.y += dy; 
    }

    int newRight = getExtreme("right");
    if (newRight >= BOARD_WIDTH) { 
        // to prevent going out of right boundary
        positions = originalPositions;
    }

    notifyBoard();
}

void Block::checkHeaviness() {
    for (int i = 0; i < static_cast<int>(heaviness); ++i) {
        for (auto &pos : positions) {
            pos.y += 1;
        }
    }
    notifyBoard();
}

void Block::RotateCounterClockWise() {
    checkHeaviness();
    rotate(Rotation::Right);
    notifyBoard();
}

void Block::RotateClockWise() {
    checkHeaviness();
    rotate(Rotation::Left);
    notifyBoard();
}

std::vector<Pos> Block::getPositions() const {
    return positions;
}

void Block::MoveUpByOne() {
    for (auto &pos : positions) {
        pos.y -= 1;
    }
}

Rotation Block::getRotation() const {
    return rotation;
}
char Block::getType() const {
    return type;
}
void Block::IncHeaviness() {
    if (heaviness == Heaviness::Normal) {
        heaviness = Heaviness::Heavy;
    } else if (heaviness == Heaviness::Heavy) {
        heaviness = Heaviness::VeryHeavy;
    }
}

void Block::MoveLeft() {
    checkHeaviness();
    if (getExtreme("left") <= 0) return;
    for (auto &pos : positions) {
        pos.x -= 1;
    }
    notifyBoard();
}
void Block::MoveRight() {
    checkHeaviness();
    if (getExtreme("right") >= BOARD_WIDTH - 1) return;
    for (auto &pos : positions) {
        pos.x += 1;
    }
    notifyBoard();
}
