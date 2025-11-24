export module Observer;

using namespace std;

export class Observer {
    public:
    virtual void notify() = 0;
};

export class Subject {
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
