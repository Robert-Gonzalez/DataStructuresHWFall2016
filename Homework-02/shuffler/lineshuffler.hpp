/**
 * \file lineshuffler.hpp
 * \author CS 70 Provided Code
 *
 * \brief Interface definition for LineShuffler.
 */

// C++ include guard for header file.
// Its mere presence will prevent linker errors and much sorrow later.
#ifndef LINESHUFFLER_HPP_INCLUDED
#define LINESHUFFLER_HPP_INCLUDED 1

#include <vector>
#include <string>

#include "random.hpp"
#include "exchange.hpp"



/**
 * \class LineShuffler
 * \brief Takes in lines, then outputs them in a random order.
 * \details
 *   Uses the incredibly simple algorithm of: starts empty. Then call
 *   addLine many times until all lines are added. Then until isEmpty,
 *   call removeLine.
 * \remarks
 *   Randomness depends on the Random class.
 */
class LineShuffler {
public:

    // ************
    // CONSTRUCTORS
    // ************

    /**
     * \brief Initializes the object to empty.
     *
     * \pre None.
     * \post The object will contain no lines (isEmpty() == true).
     */
    LineShuffler();

    // ****************
    // MEMBER FUNCTIONS
    // ****************

    /**
     * \brief
     *    Removes and returns the first line stored in the LineShuffler.
     *
     * \pre Object should be non-empty (isEmpty() == false)
     * \returns The first string from the object.
     * \post Removes the first string from the object.
     */
    std::string removeLine();

    /**
     * \brief
     *   Scrambles the lines stored in the lineShuffler
     *
     * \pre Object should br non-empty
     * \post the lines stored in the object are in a different order
     */
     void shuffleStoredLines();

    /**
     * \brief
     *   Adds a line to the collection stored in the LineShuffler.
     *
     * \pre `line` is an arbitrary string.
     * \post `line` has been added to the collection.
     */
    void addLine(std::string line);

    /**
     * \brief Tests whether there are strings in this collection.
     *
     * \returns true iff there are no lines in the LineShuffler.
     */
    bool isEmpty() const;

private:

    // *********************
    // PROHIBITED OPERATIONS (assignment & copy construction)
    // *********************

    LineShuffler(const LineShuffler&); ///< Disabled
    LineShuffler& operator=(const LineShuffler& rhs); ///< Disabled

    // ************
    // PRIVATE DATA
    // ************

    Random rnd_;                        ///< State of random number generator.
    std::vector<std::string> storedLines_;    ///< Collection (vector) of lines.
};

#endif // LINESHUFFLER_HPP_INCLUDED


/* (Junk to make emacs use a specific indentation style)
 * Local Variables:
 * c-file-style: "stroustrup"
 * End:
 */
