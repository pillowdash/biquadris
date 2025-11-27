module Level;
import <memory>;
import <vector>;
import <string>;
import <memory>;
import <cstdlib>;
import <iostream>;
import <fstream>;
import Block;

Level::Level() : levelNum{0} {} 


char Level0::spawnBlock() {
    char blockType;
    if (file.is_open()) {
        file >> blockType;
        if (file.eof()) {
            resetFile();
            file >> blockType;
        }
    } else {
        throw std::runtime_error("Level0: Unable to open block sequence file.");
    }
    return blockType;
}


Level1::Level1() {
    levelNum = 1;
}

char Level1::spawnBlock() {
    std::vector<char> blockTypes = {'I', 'I', 'J', 'J', 'L', 'L', 'O', 'O', 'T', 'T', 'S', 'Z'};
    int randIndex = rand() % blockTypes.size();
    char blockType = blockTypes[randIndex];
    return blockType;
}


Level2::Level2() {
    levelNum = 2;
}


char Level2::spawnBlock() {
    std::vector<char> blockTypes = {'I', 'J', 'L', 'O', 'S', 'T', 'Z'};
    int randIndex = rand() % blockTypes.size();
    char blockType = blockTypes[randIndex];
    return blockType;
}

Level3::Level3() {
    isheavy = true;
    levelNum = 3;
}

char Level3::spawnBlock() {
    std::vector<char> blockTypes = {'I', 'J', 'L', 'O', 'S', 'S','T', 'Z', 'Z'};
    int randIndex = rand() % blockTypes.size();
    char blockType = blockTypes[randIndex];
    return blockType;
}


Level4::Level4() {
    levelNum = 4;
}


char Level4::spawnBlock() {
    std::vector<char> blockTypes = {'I', 'J', 'L', 'O', 'S', 'T', 'Z'};
    int randIndex = rand() % blockTypes.size();
    char blockType = blockTypes[randIndex];
    return blockType;
}