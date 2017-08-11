/* movie.hpp
   =========

   Interface definition for the Movie class, which handles the main screen
   and coordination of an asciimation movie.

 */
#ifndef ASCIIMATION_HPP_INCLUDED
#define ASCIIMATION_HPP_INCLUDED = 1;

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
    static const size_t MOVIE_WIDTH = 80;
    static const size_t MOVIE_HEIGHT = 40;

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

private:
    // The sprite to display in this movie.

    // The characters to display on the screen.
};

#endif // ifndef ASCIIMATION_HPP_INCLUDED
