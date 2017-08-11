/* sprite.hpp
   =========

   interface definition for the Sprite class. Defines the behavior
   of a single asciimation 'character'

 */

#ifndef SPRITE_HPP_INCLUDED
#define SPRITE_HPP_INCLUDED 1;

#include <iostream>
#include <fstream>

/**
 * \class Sprite
 * \brief Holds the contents of a single ASCIImation sprite
 *
 * \details
 * Stores an array of characters that will be displayed to the screen, along
 * with the sprite's current location.
 *
 * \remarks
 *    The implemented code only works for a fixed size sprite.
 *
 */
class Sprite {
public:
  

  /**
   * \brief Reads a text file containing the characters for a sprite.
   * \post Should populate the sprite's character array, but doesn't yet.
   */
  Sprite(const std::string& fname, int yLoc, int xLoc);

  ~Sprite();

  Sprite() = delete;
  Sprite(Sprite&) = delete;

  char getCharAt(size_t row, size_t col);
  void setLocation(int row, int col);

  int getTopLeftRow();
  int getTopLeftColumn();

  size_t getHeight();
  size_t getWidth();

  void setScrolling(bool scrolling);
  bool getScrolling();

  void moveRight(int maxWidth);

private:
  // Current location of the sprite on the screen.
  int topLeftRow_;
  int topLeftColumn_;

  bool scrolling_;

  size_t height_;
  size_t width_;

  // Characters to display on the screen for this sprite
  char* contents_;

};

#endif // ifndef SPRITE_HPP_INCLUDED
