import Game;
import Board;
import Level;
import Viewver;
import <iostream>;
import <vector>;
import <string>;

const int BOARD_WIDTH = 11;
const int BOARD_HEIGHT = 18;
const std::string BLOCK_SEQUENCE_FILE_P1 = "biquadris_sequence1.txt";
const std::string BLOCK_SEQUENCE_FILE_P2 = "biquadris_sequence2.txt";

int main(int argc, char **argv) {
    bool textOnlyMode = false;
    if (argc > 1) {
        std::string arg1 = argv[1];
        if (arg1 == "-text") {
            textOnlyMode = true;
        }
    }
    Game game = Game(1, 1);
    Viewver viewver = Viewver(BOARD_WIDTH, BOARD_HEIGHT, textOnlyMode);
    try {
        game.run(viewver);
    } catch (const std::exception &e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    return 0;
}