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
    Level3 level3 = Level3();
    Board board1 = Board(&level3);
    Board board2 = Board(&level3);
    Game game = Game(&board1, &board2, &level3, &level3);
    Viewver viewver = Viewver(11, 18);

    try {
        game.run(viewver);
    } catch (const std::exception &e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    return 0;
}