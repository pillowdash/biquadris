//export module Block;

#include <memory>

using namespace std;

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
        Observer* subscriber;

        void notifyBoard() {
            subscriber->notify();
        }
    public:
        virtual ~Subject() = default;
};

struct Pos {
    int x;
    int y;
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
    
};

class Decorator : public Block {
protected:
    std::unique_ptr<Block> next;

public:
    virtual ~Decorator() = default;
};

// it could be that two 