/**
 * \file our-movie.cpp
 * \author CS 70 Provided Code
 *
 * \brief Provides the main() function for creating and running
 * a specific asciimation movie. 
 *
 * \details
 *
 * \remarks
 *
 */

#include <iostream>
#include <string>
#include "asciimation.hpp"
#include "sprite.hpp"


using namespace std;

void makeOurMovie() 
{

  string text{"spriteImages/text.txt"};
  string top{"spriteImages/top.txt"};
  string bottom{"spriteImages/bottom.txt"};
  string left{"spriteImages/left.txt"};
  string right{"spriteImages/right.txt"};
  
  size_t width = 80;
  size_t height = 28;

  Asciimation ourMovie{width, height};
  
  ourMovie.addSprite(text, 0, 7, true);
  ourMovie.addSprite(top, 0, 0, false);
  ourMovie.addSprite(left, 0, 3, false);
  ourMovie.addSprite(right, 61, 3, false);
  ourMovie.addSprite(bottom, 0, 15, false);
  ourMovie.play();
}


int main()
{
    makeOurMovie();
    return 0;
}
