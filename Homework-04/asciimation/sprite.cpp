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

Sprite::Sprite(const std::string& fname, int topLeftRow, int topLeftColumn)
  :topLeftRow_(topLeftRow), topLeftColumn_(topLeftColumn), scrolling_(true)
{
  ifstream inputFile{fname};

  int widthFromFile=0;
  inputFile >> widthFromFile;

  int heightFromFile=0;
  inputFile >> heightFromFile;

  width_ = widthFromFile;
  height_ = heightFromFile;



  inputFile.get(); // Read past the newline character after the height. 

  // Read in characters from the text file, 
  // copying them into the character array.

  contents_ = new char[height_ * width_];

  for (size_t i = 0; i < width_ * height_; ++i) {
    contents_[i]=inputFile.get();
  }

  inputFile.close();
}

Sprite::~Sprite() {
  delete[] contents_;
}



void Sprite::setScrolling(bool scrolling) {
  scrolling_ = scrolling;
}



bool Sprite::getScrolling() {
  return scrolling_;
}

char Sprite::getCharAt(size_t row, size_t col) {
  return contents_[row*width_ + col];
}


void Sprite::moveRight(int maxWidth) {
  ++topLeftColumn_;
  if (topLeftColumn_ >= maxWidth) {
    topLeftColumn_ = -width_;
  }
}

void Sprite::setLocation(int row, int col) {
  topLeftRow_ = row;
  topLeftColumn_ = col;
}

size_t Sprite::getHeight() {
  return height_;
}
size_t Sprite::getWidth() {
  return width_;
}

int Sprite::getTopLeftRow() {
  return topLeftRow_;
}

int Sprite::getTopLeftColumn() {
  return topLeftColumn_;
}

