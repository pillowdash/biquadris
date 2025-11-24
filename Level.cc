export module Level;
inport <memory>;
import <vector>;
import <string>;
import Block;


export class Level {
    protected:
        int levelNum;
        bool isheavy = false;
        std::shared_ptr<Block> createBlock(char blockType) {
            if (blockType == 'I') {
                return std::make_shared<I>(nullptr);
            } else if (blockType == 'J') {
                return std::make_shared<J>(nullptr);
            } else if (blockType == 'L') {
                return std::make_shared<L>(nullptr);
            } else if (blockType == 'O') {
                return std::make_shared<O>(nullptr);
            } else if (blockType == 'S') {
                return std::make_shared<S>(nullptr);
            } else if (blockType == 'T') {
                return std::make_shared<T>(nullptr);
            } else if (blockType == 'Z') {
                return std::make_shared<Z>(nullptr);
            } else {
                return nullptr;
            }
        }

    public:
        Level();
        virtual std::shared_ptr<Block> spawnBlock() = 0;
        virtual int getLevelNum() const {
            return levelNum;
        }
};

export class Level0 : public Level {
    public:
        Level0();
        std::shared_ptr<Block> spawnBlock() override;
};

export class Level1 : public Level {
    public:
        Level1();
        std::shared_ptr<Block> spawnBlock() override;
};

export class Level2 : public Level {
    public:
        Level2();
        std::shared_ptr<Block> spawnBlock() override;
};

export class Level3 : public Level {
    public:
        Level3();
        std::shared_ptr<Block> spawnBlock() override;
};

export class Level4 : public Level {
    public:
        Level4();
        std::shared_ptr<Block> spawnBlock() override;
};



