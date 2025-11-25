import Game;
import Board;
import Level;
import Viewver;
import <iostream>;
import <vector>;
import <string>;


int main(int argc, char **argv) {
    char selectedBlock = 0;
    if (argc == 2) {
        selectedBlock = *argv[1];
    }
    Level0 level0 = Level0(selectedBlock);
    Board board1 = Board(&level0);
    Board board2 = Board(&level0);
    Game game = Game(&board1, &board2, &level0, &level0);
    Viewver viewver = Viewver(11, 18);

    try {
        game.run(viewver);
    } catch (const std::exception &e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    return 0;
}