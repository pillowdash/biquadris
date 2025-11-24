module Level;
import <memory>;
import <vector>;
import <string>;
import Block;

Level::Level() : levelNum{0} {}

Level0::Level0() {
    levelNum = 0;
}

std::shared_ptr<Block> Level0::spawnBlock() {
    std::vector<char> blockTypes = {'I'};
    int randIndex = rand() % blockTypes.size();
    char blockType = blockTypes[randIndex];
    return std::make_shared<Block>(blockType);
}


Level1::Level1() {
    levelNum = 1;
}

std::shared_ptr<Block> Level1::spawnBlock() {
    std::vector<char> blockTypes = {'I', 'J', 'L', 'O', 'S', 'T', 'Z'};
    int randIndex = rand() % blockTypes.size();
    char blockType = blockTypes[randIndex];
    return std::make_shared<Block>(blockType);
}


Level2::Level2() {
    levelNum = 2;
}


std::shared_ptr<Block> Level2::spawnBlock() {
    std::vector<char> blockTypes = {'I', 'J', 'L', 'O', 'S', 'T', 'Z'};
    int randIndex = rand() % blockTypes.size();
    char blockType = blockTypes[randIndex];
    return std::make_shared<Block>(blockType);
}

Level3::Level3() {
    levelNum = 3;
}

std::shared_ptr<Block> Level3::spawnBlock() {
    std::vector<char> blockTypes = {'I', 'J', 'L', 'O', 'S', 'T', 'Z'};
    int randIndex = rand() % blockTypes.size();
    char blockType = blockTypes[randIndex];
    return std::make_shared<Block>(blockType);
}


Level4::Level4() {
    levelNum = 4;
}


std::shared_ptr<Block> Level4::spawnBlock() {
    std::vector<char> blockTypes = {'I', 'J', 'L', 'O', 'S', 'T', 'Z'};
    int randIndex = rand() % blockTypes.size();
    char blockType = blockTypes[randIndex];
    return std::make_shared<Block>(blockType);
}


class Block {
    int velocity = 0;

    void moveLeft() {
        for (auto &pos : positions) {
            pos.y -= 1;
        }
    }
}