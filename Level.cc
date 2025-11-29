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
        virtual void setFile(const std::string &filename) {}
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


        void resetFile();

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
    std::ifstream file;
    std::string filename;
    protected:
        bool israndom = true;
        char randomSpawnBlock();
        char nonRandomSpawnBlock();
    public:
        Level3();
        void setFile(const std::string &filename) override;

        void resetFile();

        void setRandom(bool val);

        char spawnBlock() override;
};

export class Level4 : public Level3 {
    public:
        Level4();
};




