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
    LevelManager levelManagerP1(0);
    LevelManager levelManagerP2(0);
    Board board1 = Board(levelManagerP1->getCurrentLevel());
    Board board2 = Board(levelManagerP2->getCurrentLevel());
    Game game = Game(&board1, &board2, &levelManagerP1, &levelManagerP2);
    Viewver viewver = Viewver(BOARD_WIDTH, BOARD_HEIGHT);

    try {
        game.run(viewver);
    } catch (const std::exception &e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    return 0;
}