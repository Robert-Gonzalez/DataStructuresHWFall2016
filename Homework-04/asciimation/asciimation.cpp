/**
 * \file movie.cpp
 * \author CS 70 Provided Code
 *
 * \brief Implements the Movie class
 *
 * \details
 *
 * \remarks
 *
 */

#include <iostream>
#include <ncurses.h>
#include <unistd.h>

#include "ncurses-helper.hpp"
#include "asciimation.hpp"
#include "sprite.hpp"

using namespace std;

Asciimation::Asciimation(size_t width, size_t height){
  height_ = height;
  width_ = width;
  contents_ = new char[width_*height_];
  size_ = 0;
  sprites_ = new Sprite*[DEFAULT_SPRITE_NUM];
  capacity_ = DEFAULT_SPRITE_NUM;
}


Asciimation::~Asciimation(){
  delete[] contents_;
  for (size_t i = 0; i < size_; ++i){
    delete sprites_[i];
  }
  delete[] sprites_;
}

void Asciimation::addSprite(const string&filename, int xPos, int yPos, bool scrolling){
  //make sure we have room for the new sprite
  checkResize();
  //make the new Sprite in the heap
  Sprite* newSprite = new Sprite(filename, yPos, xPos);
  newSprite->setScrolling(scrolling);
  //put the reference into the array
  sprites_[size_] = newSprite;
  size_++;
}


void Asciimation::clearContents()
{
  // Clear the character array by writing a space to each element
  for (size_t i=0; i < width_*height_; ++i) {
    contents_[i] = ' ';
  }
}

void Asciimation::checkResize(){
  //checks if the number of sprites equals the capacity
  if (size_ == capacity_){
    //create a new array of Sprite*'s and copies the old references to it
    Sprite** newSprites = new Sprite*[capacity_*2];
    for(size_t i = 0; i < capacity_; ++i){
      newSprites[i] = sprites_[i];
    }
    //remove the old references
    delete[] sprites_;
    //update data members
    sprites_ = newSprites;
    capacity_ = capacity_*2;
  }
}

void Asciimation::updateSpritePosition()
{
  for(size_t i = 0; i< size_; ++i){
    if (sprites_[i]->getScrolling() == true) {
    sprites_[i]->moveRight(width_);
  }
  }
}

void Asciimation::updateContents()
{ 
  clearContents();
  updateSpritePosition();

  // Loop through all of the characters in the sprite and copy them to 
  // the right spot in the movie's character array.
  size_t movieRow=0;
  size_t movieCol=0;

  for(size_t i = 0; i < size_; ++i){
    for (size_t spriteRow=0; spriteRow < sprites_[i]->getHeight(); ++spriteRow) {
     for(size_t spriteCol=0; spriteCol < sprites_[i]->getWidth(); ++spriteCol) {
      movieRow = spriteRow + sprites_[i]->getTopLeftRow();
      movieCol = spriteCol + sprites_[i]->getTopLeftColumn();
      if ((0 < movieCol) && (movieCol < width_)) {
        contents_[movieRow*width_+movieCol] =
          sprites_[i]->getCharAt(spriteRow, spriteCol);
      }
    }
   }
  }
}

/**
 * Initializes the screen for ncurses, then repeatedly updates the screen until
 * the user exits by pressing 'q'.
 */
void Asciimation::play() 
{

  // Time to sleep between screen refreshes
  const int PAUSE_TIME_IN_MICROSECONDS = 40000;

  init_ncurses();


  // Play the movie by refreshing the screen with new data, every so often
  int ch;
  bool finished = false;

  while (not(finished)) {
    // Copy contents to the screen
    updateContents(); // Get updated character values from the sprite object

    copyToScreen();        // Copy the movie's characters to the screen's buffer
    refresh();        // Refresh the screen

    // Sleep between updates
    usleep(PAUSE_TIME_IN_MICROSECONDS);

    // Check to see if the user has entered 'q' to quit yet
    ch = getch();
    if (ch == 'q') {
        finished = true;
    }
  }

  cleanup();
}

void Asciimation::copyToScreen() 
{
  // Loop through all of the characters in the movie's character array and
  // copy  them to the right place on the screen, using the ncurses function
  // mvaddch: mvaddch(r, c, char) puts the character char at row r, column c
  // of the screen.

  for (size_t row = 0; row < height_; ++row) {
    for (size_t col = 0; col < width_; ++col) {
      char ch = contents_[row*width_+col];
      mvaddch(row, col, ch);
    }
  }
}
