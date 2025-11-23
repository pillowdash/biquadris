import <iostream>;
import <string>;
import <vector>;
import Game;

class Viewver {
  // Graphics will be implemented using X11 in the future
  int width;
  int height;
public:
  Viewver(int w = 11, int h = 18);
  /**
   * Draws the current state of the game.
   * @param game The game instance to draw.
  */
  void drawGrid(const Game &game);
};