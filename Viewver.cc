export module Viewver;
import xwindow;
import <iostream>;
import <string>;
import <memory>;
import <vector>;
import Board;
import Level;
import Block;

export class Viewver {
  // Graphics will be implemented using X11 in the future
  int width;
  int height;
  std::unique_ptr<Xwindow> window;
  std::vector<Pos> previousCBPosP1;
  std::vector<Pos> previousCBPosP2;
  bool textOnly = false;
  bool setUpFirstTime = true;

  void drawDiff(const Board &p1, const Board &p2,
           const Level* level_p1, const Level* level_p2);

  bool isBlockStillThere(int x, int y, const std::vector<Pos> &positions);
  void drawGrid(const Board &p1, const Board &p2, const Level* level_p1, const Level* level_p2) const;
  void drawGraphics(const Board&, const Board&, const Level* level_p1, const Level* level_p2);
public:
  Viewver(int w, int h, bool textOnlyMode);
  /**
   * Draws the current state of the game.
   * @param game The game instance to draw.
  */
  void Draw(const Board &p1, const Board &p2, const Level* level_p1, const Level* level_p2);
};
