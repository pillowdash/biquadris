//export module Block;

#include <iostream>
#include <memory>
#include <vector>
#include <string>

using namespace std;

const int BOARD_WIDTH = 11;
const int BOARD_HEIGHT = 18;
const int BLOCK_SIZE = 4;

class Game {
    private:
        Board *player1;
        Board *player2;
        Level levelPlayer1;
        Level levelPlayer2;

    public:
        void run();
        void reset();
        Level& getLevel(int player);
};

class Level {

};


class Observer {
    public:
    virtual void notify() = 0;
};

class Subject {
    protected:
    Observer *subscriber;

    void notifyBoard() {
        subscriber->notify();
    }
};

class Subject {
    protected:
        Observer *subscriber;

        // Notify the subscribed observer
        void notifyBoard() {
            subscriber->notify();
        }
    public:
        Subject(Observer *obs) : subscriber{obs} {}
        virtual ~Subject() = default;
};

struct Pos {
    int x;
    int y;

    int getX() const { return x; }
    int getY() const { return y; }
};

class Board : public Observer {
    
};

class Controller : public Subject {
    protected: 
        Board *board;

        void getInput();
    public:
        Controller(Board *b) : Subject{b}, board{b} {}
};

enum class Rotation {
    Left,
    Right,
    Up,
    Down
};

class Block : public Controller {
    protected:
        std::vector<Pos> positions;
        Rotation rotation;
        char type;

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
            
            Pos oldBottomRight = {getExtreme("right"), getExtreme("bottom")};

            int pivotY = getExtreme("bottom");
            int pivotX = getExtreme("left");
            rotate(dir, pivotX, pivotY);
            // use the old bottom-right to adjust positions
            
            int xOffset = oldBottomRight.getX() - pivotX;
            int yOffset = oldBottomRight.getY() - pivotY;

            for (auto &pos : positions) {
                pos.x += xOffset;
                pos.y += yOffset;
            }

            notifyBoard();
        }

    public:
        Block(Board *b, int t, vector<Pos> p, Rotation r = Rotation::Up) :
            Controller{b}, type{t}, rotation{r}, positions{p} {}

        virtual void MoveLeft() = 0;
        virtual void MoveRight() = 0;
        virtual std::vector<Pos> getPositions() const = 0;
        virtual void RotateCounterClockWise() = 0;
        virtual void RotateClockWise() = 0;

        virtual Rotation getRotation() const {
            return rotation;
        }
        virtual char getType() const {
            return type;
        }

        virtual ~Block() = default;
};

class I : public Block {

    public:
        I(Board *b) : Block{b, 'I', {{0, 0}, {0, 1}, {0, 2}, {0, 3}}} {}

        void MoveLeft() override {
            if (getExtreme("left") <= 0) return;
            for (auto &pos : positions) {
                pos.x -= 1;
            }
            notifyBoard();
        }
        void MoveRight() override {
            if (getExtreme("right") >= BOARD_WIDTH - 1) return;
            for (auto &pos : positions) {
                pos.x += 1;
            }
            notifyBoard();
        }
        std::vector<Pos> getPositions() const override {
            return positions;
        }

        // does not check if out of bounds
        void RotateCounterClockWise() override {
            rotateWrapper(Rotation::Left);
            notifyBoard();
        }
        void RotateClockWise() override {
            rotateWrapper(Rotation::Right);
            notifyBoard();
        }
};


class Decorator : public Block {
    protected:
        std::unique_ptr<Block> next;

    public:
        virtual ~Decorator() {}
};

// it could be that two lines would clear at different spots

// ostream operator<<(ostream &sink, const Game game) {
//     return sink;
// }
