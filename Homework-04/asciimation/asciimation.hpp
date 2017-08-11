/* movie.hpp
   =========

   Interface definition for the Movie class, which handles the main screen
   and coordination of an asciimation movie.

 */
#ifndef ASCIIMATION_HPP_INCLUDED
#define ASCIIMATION_HPP_INCLUDED = 1;

#include <string>
#include "sprite.hpp"


/**
 * \class Asciimation
 * \brief Holds the contents of an ASCIImation movie
 *
 * \details
 * Stores an array of characters that will be displayed to the screen, and
 * a Sprite that will be added to the screen.
 *
 */
class Asciimation {
public:

  Asciimation(size_t width, size_t height);
  
   /**
     * \brief Adds a new Sprite to the Asciimation
     * \post There is a new Sprite's location in sprites_
     */
  void addSprite(const std::string&filename, int xPos, int yPos, bool scroling);

    /**
     * \brief Creates the current display showing the sprite
     * \post The current display contents are up to date and
     * ready to display to the screen.
     */
  void updateContents();

  /**
     * \brief Displays an asciimation on the screen until the user enters "q"
     * \post The screen is destroyed.
     */
  void play();

  /**
   * \brief Displays the current display on the screen
   * \post No change to the asciimation object
   */
  void copyToScreen();

  void updateSpritePosition();

  ~Asciimation();

private:
  const size_t DEFAULT_SPRITE_NUM = 5;
  
  // The sprite to display in this movie.
  Sprite** sprites_;
  
  //the number of Sprites that belong to the Asciimation
  size_t size_;
  //the amount of space in sprites_
  size_t capacity_;

  size_t height_;
  size_t width_;

  // The characters to display on the screen.
  char* contents_;

  void clearContents();

  //Checks whether sprites_ is full.
  //If so, copies into a new array twice the size
  void checkResize();

  
};

#endif // ifndef ASCIIMATION_HPP_INCLUDED
