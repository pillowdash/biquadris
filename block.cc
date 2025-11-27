export module Block;

// #include <iostream>
// #include <memory>
// #include <vector>
// #include <string>

import <iostream>;
import <memory>;
import <vector>;
import <string>;
import Observer;

class Board;

using namespace std;

const int BOARD_WIDTH = 11;
const int BOARD_HEIGHT = 18;
const int BLOCK_SIZE = 4;

export struct Pos {
    int x;
    int y;

    int getX() const;
    int getY() const;
    bool operator==(const Pos &other) const;
};

int Pos::getX() const { return x; }
int Pos::getY() const { return y; }

bool Pos::operator==(const Pos &other) const {
    return x == other.x && y == other.y;
}

// TODO: use map for command parsing
export class Controller : public Subject {
    protected: 
        Observer *board;
        bool isDropped;

    public:
        bool getIsDropped() const;
        string getInput();

        virtual void MoveLeft() = 0;
        virtual void MoveRight() = 0;
        virtual void RotateCounterClockWise() = 0;  
        virtual void RotateClockWise() = 0;
        Controller(Observer *b) : Subject{b}, board{b}, isDropped{false} {}
};

bool Controller::getIsDropped() const {
    return isDropped;
}

string Controller::getInput() {
    string cmd;
    cin >> cmd;
    if (cmd == "l") {
        MoveLeft();
    } else if (cmd == "r") {
        // Move Right
        MoveRight();
    } else if (cmd == "rcw") {
        // Rotate Clockwise
        RotateClockWise();
    } else if (cmd == "rccw") {
        // Rotate CounterClockwise
        RotateCounterClockWise();
    } else if (cmd == "d") {
        isDropped = true;
        notifyBoard();
    }
    return cmd;
}

enum class Rotation {
    Left,
    Right,
    Up,
    Down
};

// TODO: decorator heaviness is too complicated, so use enum / map instead?
enum class Heaviness {
    VeryHeavy = 2,
    Heavy = 1,
    Normal = 0
};

export class Block : public Controller {
    protected:
        std::vector<Pos> positions;
        char type;
        Rotation rotation;
        Heaviness heaviness;

        /**
         * helper function to get extreme coordinate
         * @param isX: true for x-coordinate, false for y-coordinate
         * @param findMax: true to find max, false to find min
         */
        int getExtremeHelper(bool isX, bool findMax) const;
        
        /**
         * Get the extreme coordinate of the block
         * @param extreme: "top", "bottom", "left", "right"
         */
        int getExtreme(const string extreme) const;

        // Rotate block around pivot point (bottom-right corner)
        void rotate(Rotation dir);

        // apply heaviness effect after movement
        void checkHeaviness();

    public:
        // do not use this ctor directly
        Block(Observer *b, vector<Pos> p, char t = ' ', Rotation r = Rotation::Up, Heaviness h = Heaviness::Normal) :
            Controller{b}, positions{p}, type{t}, rotation{r}, heaviness{h} {}

        void RotateCounterClockWise();

        void RotateClockWise();

        void MoveUpByOne();

        virtual std::vector<Pos> getPositions() const;

        virtual Rotation getRotation() const;
        virtual char getType() const;
        virtual void IncHeaviness();

        virtual void MoveLeft() override;
        virtual void MoveRight() override;

        virtual ~Block() = default;
};

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

export class I : public Block {

    public:
        I(Observer *b) : Block{b, {{0, 0}, {0, 1}, {0, 2}, {0, 3}}, 'I'} {}
};

export class L : public Block {

    public:
        L(Observer *b) : Block{b, {{0, 1}, {0, 2}, {0, 3}, {1, 3}}, 'L'} {}
};

export class J : public Block {

    public:
        J(Observer *b) : Block{b, {{1, 1}, {1, 2}, {1, 3}, {0, 3}}, 'J'} {}
};

export class O : public Block {

    public:
        O(Observer *b) : Block{b, {{0, 2}, {0, 3}, {1, 2}, {1, 3}}, 'O'} {}
};

export class T : public Block {

    public:
        T(Observer *b) : Block{b, {{0, 1}, {0, 2}, {0, 3}, {1, 2}}, 'T'} {}
};

export class S : public Block {

    public:
        S(Observer *b) : Block{b, {{0, 3}, {1, 3}, {1, 2}, {2, 2}}, 'S'} {}
};

export class Z : public Block {

    public:
        Z(Observer *b) : Block{b, {{0, 2}, {1, 2}, {1, 3}, {2, 3}}, 'Z'} {}
};


// might be too complicated to use decorator pattern here
// class Decorator : public Block {
//     protected:
//         std::unique_ptr<Block> next;

//     public:
//         Decorator(Board *b, std::unique_ptr<Block> n)
//             : Block{b, n->getPositions(), n->getType(), n->getRotation()}, next{std::move(n)} {}

//         virtual ~Decorator() {}
// };

// class Heavy : public Decorator {
//     void MoveDown() {
//         for (auto &pos : positions) {
//             pos.y += 1;
//         }
//     }

//     public:
//         Heavy(Board *b, std::unique_ptr<Block> n)
//             : Decorator{b, std::move(n)} {}

//         void MoveLeft() override {
//             MoveDown();
//             next->MoveLeft();
//         }
//         void MoveRight() override {
//             MoveDown();
//             next->MoveRight();
//         }
//         std::vector<Pos> getPositions() const override {
//             return next->getPositions();
//         }
//         void RotateCounterClockWise() override {
//             MoveDown();
//             next->RotateCounterClockWise();
//         }
//         void RotateClockWise() override {
//             MoveDown();
//             next->RotateClockWise();
//         }
//         Rotation getRotation() {
//             return next->getRotation();
//         }
//         char getType() {
//             return next->getType();
//         }
// };

// it could be that two lines would clear at different spots

// ostream operator<<(ostream &sink, const Game game) {
//     return sink;
// }
