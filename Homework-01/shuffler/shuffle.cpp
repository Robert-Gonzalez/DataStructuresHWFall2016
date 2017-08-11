/**
 * \file shuffle.cpp
 *
 * \brief Reads a sequence of lines from user, terminated by empty
 * line, then prints them out in random order.
 *
 * \note
 *  User interaction is handled by main, storing and fetching the lines
 *  is handled by the LineShuffler class.
 */

#include <iostream>
#include <string>
#include "lineshuffler.hpp"

using namespace std;

/**
 * \brief Reads lines from user until it sees a blank line, then
 *   outputs in random order.
 *
 * \remarks
 *   The inputs give the command-line arguments, but have
 *   no names because they are unused.
 */
int main (int, const char* [])
{
    // Display the prompt.
    cout << "Enter lines to shuffle, ending with a blank line" << endl;

    // Get the lines.
    LineShuffler randomLines;

    for (;;) {
        string line;
        getline(cin, line);

        if (line == "")
            break;

        randomLines.addLine(line);
    }

    // Show the shuffled lines.
    cout << "Here are the shuffled lines:" << endl;

    while (!randomLines.isEmpty())
        cout << randomLines.removeLine() << endl;

    return 0;
}


/* (Junk to make emacs use a specific indentation style)
 * Local Variables:
 * c-file-style: "stroustrup"
 * End:
 */
