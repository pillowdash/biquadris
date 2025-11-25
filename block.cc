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

        void getInput() {

        }
    public:
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
        void rotate(Rotation dir, int pivotX, int pivotY) {
            if (dir == Rotation::Left) {
                for (auto &pos : positions) {
                    int dx = pos.getX() - pivotX;
                    int dy = pos.getY() - pivotY;

                    // 90 degree rotation matrix
                    int oldDx = dx;
                    dx = -dy;
                    dy = oldDx;

                    pos.x = pivotX + dx;
                    pos.y = pivotY + dy;
                }
            } else if (dir == Rotation::Right) {
                for (auto &pos : positions) {
                    int dx = pos.getX() - pivotX;
                    int dy = pos.getY() - pivotY;

                    // -90 degree rotation matrix
                    int oldDx = dx;
                    dx = dy;
                    dy = -oldDx;

                    pos.x = pivotX + dy;
                    pos.y = pivotY + dx;
                }
            }
        }

        /**
         * Wrapper for rotate function to adjust positions after rotation
         */
        void rotateWrapper(Rotation dir) {

            // FIXME: this rotation adjustment system still has issues: could move in unexpected ways
            
            // find where the bottom right is before rotation
            Pos oldBottomRight = {getExtreme("right"), getExtreme("bottom")};
            Pos *newBottomRight = nullptr;
            // make a pointer to that bottom-right position so that we can find it after rotation
            for (auto &pos : positions) {
                if (pos == oldBottomRight) {
                    newBottomRight = &pos;
                    break;
                }
            }

            int pivotY = getExtreme("bottom");
            int pivotX = getExtreme("left");
            rotate(dir, pivotX, pivotY);
            // use the old bottom-right to adjust positions
            
            int xOffset = newBottomRight->getX() - pivotX;
            int yOffset = newBottomRight->getY() - pivotY;

            for (auto &pos : positions) {
                pos.x += xOffset;
                pos.y += yOffset;
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

        virtual void MoveLeft() = 0;
        virtual void MoveRight() = 0;
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

        virtual ~Block() = default;
};

export class I : public Block {

    public:
        I(Observer *b) : Block{b, {{0, 0}, {0, 1}, {0, 2}, {0, 3}}, 'I'} {}

        void MoveLeft() override {
            checkHeaviness();
            if (getExtreme("left") <= 0) return;
            for (auto &pos : positions) {
                pos.x -= 1;
            }
            notifyBoard();
        }
        void MoveRight() override {
            checkHeaviness();
            if (getExtreme("right") >= BOARD_WIDTH - 1) return;
            for (auto &pos : positions) {
                pos.x += 1;
            }
            notifyBoard();
        }

        // TODO: fix rotation going out of bounds
        void RotateCounterClockWise() override {
            checkHeaviness();
            rotateWrapper(Rotation::Left);
            notifyBoard();
        }
        void RotateClockWise() override {
            checkHeaviness();
            rotateWrapper(Rotation::Right);
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
