import Game;
import Board;
import Level;
import Viewver;
import <iostream>;
import <vector>;
import <string>;
import <cstdlib>;

const int BOARD_WIDTH = 11;
const int BOARD_HEIGHT = 18;
std::string BLOCK_SEQUENCE_FILE_P1 = "biquadris_sequence1.txt";
std::string BLOCK_SEQUENCE_FILE_P2 = "biquadris_sequence2.txt";

int main(int argc, char **argv) {
    bool textOnlyMode = false;
    int startLevel = 0;
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "-text") {
                textOnlyMode = true;
            } else if (arg == "-scriptfile1" && i + 1 < argc) {
                BLOCK_SEQUENCE_FILE_P1 = argv[++i];
            } else if (arg == "-scriptfile2" && i + 1 < argc) {
                BLOCK_SEQUENCE_FILE_P2 = argv[++i];
            } else if (arg == "-startlevel" && i + 1 < argc) {
                startLevel = std::stoi(argv[++i]);
            } else if (arg == "-seed" && i + 1 < argc) {
                std::srand(std::stoi(argv[++i]));
            }
        }
    }
    Game game = Game(startLevel, startLevel, BLOCK_SEQUENCE_FILE_P1, BLOCK_SEQUENCE_FILE_P2);
    Viewver viewver = Viewver(BOARD_WIDTH, BOARD_HEIGHT, textOnlyMode);
    try {
        game.run(viewver);
    } catch (const std::exception &e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    return 0;
}
