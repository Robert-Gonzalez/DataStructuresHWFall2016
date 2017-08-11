/**
 * \file random.cpp
 * \author CS 70 Provided Code
 *
 * \brief Implements Random class.
 *
 * \remarks
 *   Based on example code provided in Section 7.20.2.1 of the ISO C
 *   specification.
 *
 * \note
 * Assumes that (MAX-1)*MAX fits into an unsigned int; otherwise, calculations
 *   may silently overflow.
 */

#include <cstdlib>
#include <ctime>
#include "random.hpp"

using namespace std;

Random::Random()
    : state_(time(NULL))
{
    // Nothing else to do.
}

unsigned int Random::next()
{
    state_ = state_ * MULTIPLIER + ADDITIVE;
    return (state_ / DIVISOR) % MAX;
}

unsigned int Random::next(unsigned int bound)
{
    unsigned int rawRandom = next();
    return (rawRandom * bound) / MAX;
}

/* (Junk to make emacs use a specific indentation style)
 * Local Variables:
 * c-file-style: "stroustrup"
 * End:
 */
