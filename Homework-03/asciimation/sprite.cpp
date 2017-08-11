/**
 * \file sprite.cpp
 * \author CS 70 Provided Code
 *
 * \brief Implements the Sprite class
 *
 * \details
 *
 * \remarks
 *
 */

#include <cstddef>
#include <iostream>

#include "sprite.hpp"

using namespace std;

Sprite::Sprite(std::string& fname, int topLeftRow, int topLeftColumn)
{
  ifstream inputFile{fname};

  int widthFromFile=0;
  inputFile >> widthFromFile;

  int heightFromFile=0;
  inputFile >> heightFromFile;

  inputFile.get(); // Read past the newline character after the height. 

  if (widthFromFile != Sprite::SPRITE_WIDTH) {
    cerr << "Warning: Trying to read a Sprite with the wrong width." << widthFromFile << endl;
  }

  if (heightFromFile != Sprite::SPRITE_HEIGHT) {
    cerr << "Warning: Trying to read a Sprite with the wrong height." << endl;    
  }

  // Read in characters from the text file, 
  // copying them into the character array.

  // TODO: Fill in this part so that it puts values into the contents_ of
  // this Sprite object. You can  use inputFile.get() to get one character
  // at a time from the file. 

  inputFile.close();
}
