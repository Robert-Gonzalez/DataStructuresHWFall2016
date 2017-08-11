/**
 * \file myspell.cpp
 *
 * \author CS 70 Provided Code with additions by ... your CS70 aliases here ...
 *
 * \brief Implements the UI for the spelling checker
 */

#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;


/**
 * \brief Process input from cin and compare against the dictionary.
 *        If the word is not found and has not been seen before, spelling
 *        corrections are output to cout.
 *
 * \param dictfile Name of dictionary file.
 *
 * \param debug    Boolean corresponding to the -d flag
 */
void spellcheck(const string& dictfile, bool debug)
{
    // TODO: implement spellcheck
}

/// Main function, processes inputs and runs spellcheck
int main(int argc, const char** argv)
{
    bool debug = false;

    // Process command-line options
    --argc; // Skip past 0th arg (program name)
    ++argv;

    if (argc == 2 && *argv == string("-d")) {
        debug = true;
        --argc;
        ++argv;
    }

    if (argc != 1) {
        cerr << "Usage: ./myspell [-d] dict" << endl;
        exit(2);
    }

    // Check that spelling!
    try {
        spellcheck(argv[0], debug);
    } catch (std::runtime_error err) {
        cerr << err.what() << endl;
        return 1;
    }

    return 0;
}
