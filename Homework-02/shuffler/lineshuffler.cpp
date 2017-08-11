/**
 * \file lineshuffler.cpp
 * \author CS 70 Provided Code
 *
 * \brief
 *   Implements LineShuffler. See lineshuffler.hpp for function
 *   descriptions.
 */

#include "lineshuffler.hpp"

using namespace std;

LineShuffler::LineShuffler()
{
    // Nothing else to do.
}


string LineShuffler::removeLine()
{
    // Choose the first line
    string line = storedLines_[0];

    // Delete the first string and move the other strings up.
    storedLines_.erase(storedLines_.begin());

    return line;
}

void LineShuffler::shuffleStoredLines()
{
    //Allows us to compare size with the iterating variable i
    int size = (int) storedLines_.size();
    for (int i = 0; i < size; i++)
    {
        // Swap the line at the current index with a random line
        exchange(storedLines_[rnd_.next(size)], storedLines_[i]);
    }
}

void LineShuffler::addLine(string line)
{
    storedLines_.push_back(line);
}


bool LineShuffler::isEmpty() const
{
    return storedLines_.size() == 0;
}


/* (Junk to make emacs use a specific indentation style)
 * Local Variables:
 * c-file-style: "stroustrup"
 * End:
 */
