export module Game;
import Board;
import Level;
import Viewver;
import <stdexcept>;

export class Game {
    Board *player1;
    Board *player2;
    Level *level1;
    Level *level2;
    public:
        Game(Board *p1, Board *p2, Level *l1, Level *l2) : player1{p1}, player2{p2}, level1{l1}, level2{l2} {}
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

        
};