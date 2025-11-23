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

        // positions are relative to a reference point
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

        void rotate(Rotation dir) {
            int pivotY = getExtreme("bottom");
            int pivotX = getExtreme("right");
            if (dir == Rotation::Left) {
                // Implement left rotation logic
                for (auto &pos : positions) {
                    int dx = pos.getX() - pivotX;
                    int dy = pos.getY() - pivotY;
                    pos.x = pivotX - dx;
                    pos.y = pivotY + dy;
                }
            } else if (dir == Rotation::Right) {
                // Implement right rotation logic
                for (auto &pos : positions) {
                    int dx = pos.getX() - pivotX;
                    int dy = pos.getY() - pivotY;
                    pos.x = pivotX + dy;
                    pos.y = pivotY - dx;
                }
            }
        }

    public:
        virtual void MoveLeft() = 0;
        virtual void MoveRight() = 0;
        virtual std::vector<Pos> getPositions() const = 0;
        virtual void RotateCounterClockWise() = 0;
        virtual void RotateClockWise() = 0;
        virtual Rotation getRotation() const = 0;

        virtual ~Block() = default;
};

class I : public Block {

    public:
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
        void RotateCounterClockWise() override {
            // Implement rotation logic
            notifyBoard();
        }
        void RotateClockWise() override {
            // Implement rotation logic
            notifyBoard();
        }
        Rotation getRotation() const override {
            return rotation;
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
