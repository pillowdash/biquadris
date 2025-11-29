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

// Level0::Level0(const std::string &filename) : filename{filename} {
//     levelNum = 0; 
//     file.open(filename);
// }


void Level0::resetFile() {
    if (file.is_open()) {
        file.close();
    }
    file.open(filename);
}

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

void Level3::setFile(const std::string &filename) {
    this->filename = filename;
    if (file.is_open()) {
        file.close();
    }
    file.open(filename);
    israndom = false;
}

void Level3::resetFile() {
    if (file.is_open()) {
        file.close();
    }
    file.open(filename);
}

void Level3::setRandom(bool val) {
    israndom = val;
}

char Level3::spawnBlock() {
    if (israndom) {
        return randomSpawnBlock();
    } else {
        return nonRandomSpawnBlock();
    }
}

char Level3::randomSpawnBlock() {
    std::vector<char> blockTypes = {'I', 'J', 'L', 'O', 'S', 'T', 'Z'};
    int randIndex = rand() % blockTypes.size();
    char blockType = blockTypes[randIndex];
    return blockType;
}

char Level3::nonRandomSpawnBlock() {
    char blockType;
    if (file.is_open()) {
        file >> blockType;
        if (file.eof()) {
            resetFile();
            file >> blockType;
        }
    } else {
        throw std::runtime_error("Level3: Unable to open block sequence file.");
    }
    return blockType;
}

Level4::Level4() {
    levelNum = 4;
}
