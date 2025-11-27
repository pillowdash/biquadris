export module Viewver;
import xwindow;
import <iostream>;
import <string>;
import <vector>;
import Board;
import Level;
import Block;

export class Viewver {
  // Graphics will be implemented using X11 in the future
  int width;
  int height;
  Xwindow window;
public:
  Viewver(int w = 11, int h = 18);
  /**
   * Draws the current state of the game.
   * @param game The game instance to draw.
  */
  void drawGrid(const Board &p1, const Board &p2, const Level* level_p1, const Level* level_p2) const;
  void drawGraphics(const Board&, const Board&, const Level* level_p1, const Level* level_p2);
};
