export module Game;
import <memory>;
import Board;
import Level;
import Viewver;
import <stdexcept>;
import <string>;
import <iostream>;

export class Game {
    std::unique_ptr<Level> level1;
    std::unique_ptr<Level> level2;
    std::unique_ptr<Board> player1;
    std::unique_ptr<Board> player2;
    public:
        Game(int level1, int level2, std::string file1 = "biquadris_sequence1.txt",
             std::string file2 = "biquadris_sequence2.txt") {
            switch (level1) {
                case 0:
                    this->level1 = std::make_unique<Level0>(file1);
                    break;
                case 1:
                    this->level1 = std::make_unique<Level1>();
                    break;
                case 2:
                    this->level1 = std::make_unique<Level2>();
                    break;
                case 3:
                    this->level1 = std::make_unique<Level3>();
                    break;
                case 4:
                    this->level1 = std::make_unique<Level4>();
                    break;
                default:
                    throw std::invalid_argument("Invalid level number for player 1");
            }

            switch (level2) {
                case 0:
                    this->level2 = std::make_unique<Level0>(file2);
                    break;
                case 1:
                    this->level2 = std::make_unique<Level1>();
                    break;
                case 2:
                    this->level2 = std::make_unique<Level2>();
                    break;
                case 3:
                    this->level2 = std::make_unique<Level3>();
                    break;
                case 4:
                    this->level2 = std::make_unique<Level4>();
                    break;
                default:
                    throw std::invalid_argument("Invalid level number for player 2");
            }
            player1 = std::make_unique<Board>(this->level1.get());
            player2 = std::make_unique<Board>(this->level2.get());
        }
        /** 
         * Runs the game loop, might throw exceptions.
         * @param viewver The Viewver instance to render the game.
        */
        void run(Viewver &viewver);
        /** 
         * Resets the game to initial state.
        */
        void reset();
        /** 
         * Gets the level of the specified player.
         * @param player The player number (1 or 2).
         * @return The Level pointer of the specified player.
        */
        Level *getLevel(int player);
        /** 
         * Gets the board of the specified player.
         * @param player The player number (1 or 2).
         * @return The Board pointer of the specified player.
        */
        Board *getBoard(int player);

        void levelUp(int player);
        void levelDown(int player);

        bool commandManager(std::string command, int player);

        ~Game() = default;
};