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
     *    Removes and returns a random line stored in the LineShuffler.
     *
     * \pre Object should be non-empty (isEmpty() == false)
     * \returns A random string from the object.
     * \post Removes the selected string from the object.
     */
    std::string removeLine();

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

    int    count_;                      ///< Number of lines stored.
    Random rnd_;                        ///< State of random number generator.
    std::vector<std::string> lines_;    ///< Collection (vector) of lines.
};

#endif // LINESHUFFLER_HPP_INCLUDED


/* (Junk to make emacs use a specific indentation style)
 * Local Variables:
 * c-file-style: "stroustrup"
 * End:
 */
