export module Block;

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

// TODO: use map for command parsing
export class Controller : public Subject {
    protected: 
        Observer *board;
        bool isDropped;

    public:
        bool getIsDropped() const;
        string getInput();
        string setInput(string cmd);

        virtual void MoveLeft() = 0;
        virtual void MoveRight() = 0;
        virtual void RotateCounterClockWise() = 0;  
        virtual void RotateClockWise() = 0;
        Controller(Observer *b) : Subject{b}, board{b}, isDropped{false} {}
};

enum class Rotation {
    Left,
    Right,
    Up,
    Down
};

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

export class B : public Block {

    public:
        B(Observer *b) : Block{b, {{5, 0}}, 'B'} {}
};