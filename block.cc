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

    int getX() const { return x; }
    int getY() const { return y; }
    bool operator==(const Pos &other) const {
        return x == other.x && y == other.y;
    }
};

// TODO: use map for command parsing
export class Controller : public Subject {
    protected: 
        Observer *board;
        bool isDropped = false;

    public:
        bool getIsDropped() const {
            return isDropped;
        }
        void getInput() {
            string cmd;
            cin >> cmd;
            if (cmd == "l") {
                // Move Left
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
        }
        virtual void MoveLeft() = 0;
        virtual void MoveRight() = 0;
        virtual void RotateCounterClockWise() = 0;  
        virtual void RotateClockWise() = 0;
        Controller(Observer *b) : Subject{b}, board{b} {}
};

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
        Rotation rotation;
        char type;
        Heaviness heaviness;

        /**
         * helper function to get extreme coordinate
         * @param isX: true for x-coordinate, false for y-coordinate
         * @param findMax: true to find max, false to find min
         */
        int getExtremeHelper(bool isX, bool findMax) const {
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
        
        /**
         * Get the extreme coordinate of the block
         * @param extreme: "top", "bottom", "left", "right"
         */
        int getExtreme(const string extreme) const {
            if (extreme == "top") {
               return getExtremeHelper(false, false);
            } else if (extreme == "bottom") {
               return getExtremeHelper(false, true);
            } else if (extreme == "left") {
               return getExtremeHelper(true, false);
            } else if (extreme == "right") {
               return getExtremeHelper(true, true);
            }
        }

        // Rotate block around pivot point (bottom-right corner)
        void rotate(Rotation dir) {
            Pos pivot = {getExtreme("left"), getExtreme("bottom")};

            for (auto &pos : positions) {
                int localX = pos.x - pivot.x;
                int localY = pos.y - pivot.y;

                int rx, ry;

                if (dir == Rotation::Left) {
                    // -90 degree rotation matrix
                    rx = localY;
                    ry = -localX;
                } else if (dir == Rotation::Right) {
                    // 90 degree rotation matrix
                    rx = -localY;
                    ry = localX;
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

            notifyBoard();
        }

        // apply heaviness effect after movement
        void checkHeaviness() {
            for (int i = 0; i < static_cast<int>(heaviness); ++i) {
                for (auto &pos : positions) {
                    pos.y += 1;
                }
            }
        }

    public:
        // do not use this ctor directly
        Block(Observer *b, vector<Pos> p, char t = ' ', Rotation r = Rotation::Up, Heaviness h = Heaviness::Normal) :
            Controller{b}, type{t}, rotation{r}, positions{p}, heaviness{h} {}

        // virtual void MoveLeft() = 0;
        // virtual void MoveRight() = 0;
        virtual void RotateCounterClockWise() = 0;
        virtual void RotateClockWise() = 0;

        virtual std::vector<Pos> getPositions() const {
            return positions;
        }

        virtual Rotation getRotation() const {
            return rotation;
        }
        virtual char getType() const {
            return type;
        }
        virtual void IncHeaviness() {
            if (heaviness == Heaviness::Normal) {
                heaviness = Heaviness::Heavy;
            } else if (heaviness == Heaviness::Heavy) {
                heaviness = Heaviness::VeryHeavy;
            }
        }

        virtual void MoveLeft() override {
            checkHeaviness();
            if (getExtreme("left") <= 0) return;
            for (auto &pos : positions) {
                pos.x -= 1;
            }
            notifyBoard();
        }
        virtual void MoveRight() override {
            checkHeaviness();
            if (getExtreme("right") >= BOARD_WIDTH - 1) return;
            for (auto &pos : positions) {
                pos.x += 1;
            }
            notifyBoard();
        }

        virtual ~Block() = default;
};

export class I : public Block {

    public:
        I(Observer *b) : Block{b, {{0, 0}, {0, 1}, {0, 2}, {0, 3}}, 'I'} {}

        // TODO: fix rotation going out of bounds
        void RotateCounterClockWise() override {
            checkHeaviness();
            rotate(Rotation::Right);
            notifyBoard();
        }
        void RotateClockWise() override {
            checkHeaviness();
            rotate(Rotation::Left);
            notifyBoard();
        }
};

export class L : public Block {

    public:
        L(Observer *b) : Block{b, {{0, 0}, {0, 1}, {0, 2}, {1, 2}}, 'L'} {}

        // TODO: fix rotation going out of bounds
        void RotateCounterClockWise() override {
            checkHeaviness();
            rotate(Rotation::Right);
            notifyBoard();
        }
        void RotateClockWise() override {
            checkHeaviness();
            rotate(Rotation::Left);
            notifyBoard();
        }
};

export class J : public Block {

    public:
        J(Observer *b) : Block{b, {{1, 0}, {1, 1}, {1, 2}, {0, 2}}, 'J'} {}

        // TODO: fix rotation going out of bounds
        void RotateCounterClockWise() override {
            checkHeaviness();
            rotate(Rotation::Right);
            notifyBoard();
        }
        void RotateClockWise() override {
            checkHeaviness();
            rotate(Rotation::Left);
            notifyBoard();
        }
};

export class O : public Block {

    public:
        O(Observer *b) : Block{b, {{0, 0}, {0, 1}, {1, 0}, {1, 1}}, 'O'} {}

        // TODO: fix rotation going out of bounds
        void RotateCounterClockWise() override {
            checkHeaviness();
            rotate(Rotation::Right);
            notifyBoard();
        }
        void RotateClockWise() override {
            checkHeaviness();
            rotate(Rotation::Left);
            notifyBoard();
        }
};

export class T : public Block {

    public:
        T(Observer *b) : Block{b, {{0, 0}, {0, 1}, {0, 2}, {1, 1}}, 'T'} {}

        // TODO: fix rotation going out of bounds
        void RotateCounterClockWise() override {
            checkHeaviness();
            rotate(Rotation::Right);
            notifyBoard();
        }
        void RotateClockWise() override {
            checkHeaviness();
            rotate(Rotation::Left);
            notifyBoard();
        }
};

export class S : public Block {

    public:
        S(Observer *b) : Block{b, {{0, 1}, {1, 1}, {1, 0}, {2, 0}}, 'S'} {}

        // TODO: fix rotation going out of bounds
        void RotateCounterClockWise() override {
            checkHeaviness();
            rotate(Rotation::Right);
            notifyBoard();
        }
        void RotateClockWise() override {
            checkHeaviness();
            rotate(Rotation::Left);
            notifyBoard();
        }
};

export class Z : public Block {

    public:
        Z(Observer *b) : Block{b, {{0, 0}, {0, 1}, {1, 1}, {2, 1}}, 'Z'} {}

        // TODO: fix rotation going out of bounds
        void RotateCounterClockWise() override {
            checkHeaviness();
            rotate(Rotation::Right);
            notifyBoard();
        }
        void RotateClockWise() override {
            checkHeaviness();
            rotate(Rotation::Left);
            notifyBoard();
        }
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
