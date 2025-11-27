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

export class LevelManager {
    std::unique_ptr<Level> currentLevel;
    public:
        LevelManager(int initialLevel) {
            switch (initialLevel) {
                case 0:
                    currentLevel = std::make_unique<Level0>("biquadris_sequence.txt");
                    break;
                case 1:
                    currentLevel = std::make_unique<Level1>();
                    break;
                case 2:
                    currentLevel = std::make_unique<Level2>();
                    break;
                case 3:
                    currentLevel = std::make_unique<Level3>();
                    break;
                case 4:
                    currentLevel = std::make_unique<Level4>();
                    break;
                default:
                    throw std::invalid_argument("Invalid initial level number");
            }
        }

        Level* levelUp() {
            int nextLevelNum = currentLevel->getLevelNum() + 1;
            switch (nextLevelNum) {
                case 1:
                    currentLevel = std::make_unique<Level1>();
                    break;
                case 2:
                    currentLevel = std::make_unique<Level2>();
                    break;
                case 3:
                    currentLevel = std::make_unique<Level3>();
                    break;
                case 4:
                    currentLevel = std::make_unique<Level4>();
                    break;
                default:
                    break;
            }
            return currentLevel.get();
        }
};



