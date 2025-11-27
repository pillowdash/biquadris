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
    char selectedBlock = 0;
    if (argc == 2) {
        selectedBlock = *argv[1];
    }
    Level0 level0_p1 = Level0(BLOCK_SEQUENCE_FILE_P1);
    Level0 level0_p2 = Level0(BLOCK_SEQUENCE_FILE_P2);
    Board board1 = Board(&level0_p1);
    Board board2 = Board(&level0_p2);
    Game game = Game(&board1, &board2, &level0_p1, &level0_p2);
    Viewver viewver = Viewver(BOARD_WIDTH, BOARD_HEIGHT);

    try {
        game.run(viewver);
    } catch (const std::exception &e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    return 0;
}