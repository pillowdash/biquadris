export module Level;
import <memory>;
import <vector>;
import <string>;
import <cstdlib>;
import <fstream>;
import Block;

export class Level {
    protected:
        int levelNum;
        bool isheavy = false;

    public:
        Level();
        virtual ~Level() = default;
        virtual char spawnBlock() = 0;
        virtual int getLevelNum() const {
            return levelNum;
        }
        virtual bool getIsHeavy() const {
            return isheavy;
        }
};

export class Level0 : public Level {
    std::ifstream file;
    std::string filename;
    public:
        Level0(const std::string &filename) : filename{filename} {
            levelNum = 0; 
            file.open(filename);
        }

        void resetFile() {
            if (file.is_open()) {
                file.close();
            }
            file.open(filename);
        }

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





