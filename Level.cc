export module Level;
import <memory>;
import <vector>;
import <string>;
import <cstdlib>;
import Block;

export class Level {
    protected:
        int levelNum;
        bool isheavy = false;

    public:
        Level();
        virtual char spawnBlock() = 0;
        virtual int getLevelNum() const {
            return levelNum;
        }
};

export class Level0 : public Level {
    public:
        Level0();
        char spawnBlock() override;
};

export class Level1 : public Level {
    public:
        Level1();
        char spawnBlock() override;
};

export class Level2 : public Level {
    public:
        Level2();
        char spawnBlock() override;
};

export class Level3 : public Level {
    public:
        Level3();
        char spawnBlock() override;
};

export class Level4 : public Level {
    public:
        Level4();
        char spawnBlock() override;
};





