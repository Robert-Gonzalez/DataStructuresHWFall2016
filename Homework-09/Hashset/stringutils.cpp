/**
 * \file stringutil.cpp
 * \author CS 70 Provided Code.
 *
 * \brief Miscellaneous utility code for strings
 */
#include "stringutils.hpp"

#include <iostream>
#include <cctype>

using namespace std;

string getWord(istream& in)
{
    string accumulator;   // The word we are building
    char c;               // The most recently-read character

    // Loop until end of input (or we break out of the loop,
    // whichever comes first).

    while (in.get(c)) {

        // Abort the loop after reading one non-letter
        if (! isalpha(c)) break;

        // It's alphabetic; append to our accumulated string
        accumulator += c;
    }

    return accumulator;
}


