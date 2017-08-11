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
    : count_(0)
{
    // Nothing else to do.
}


string LineShuffler::removeLine()
{
    // Choose a random line.
    int index = rnd_.next(count_);
    string line = lines_[index];

    // Delete the string at lines_[index] and move the other strings up.
    lines_.erase(lines_.begin() + index);
    --count_;

    return line;
}


void LineShuffler::addLine(string line)
{
    lines_.push_back(line);
    ++count_;
}


bool LineShuffler::isEmpty() const
{
    return count_ == 0;
}


/* (Junk to make emacs use a specific indentation style)
 * Local Variables:
 * c-file-style: "stroustrup"
 * End:
 */
