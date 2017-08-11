/**
 * \file random.hpp
 * \author CS 70 Provided Code
 * \brief Interface definition for Random Class.
 */

#ifndef RANDOM_HPP_INCLUDED             // Usual C++ include guard for header
#define RANDOM_HPP_INCLUDED 1


/**
 * \brief Random number generating class
 *
 * \details
 *   Provides basic functionality random number functionality similar
 *   to the Java's Random class.
 *
 * \note
 *   This trivial random number generator does not provide especially
 *   random "random numbers".
 */
class Random {
public:
    // *********
    // CONSTANTS
    // *********
    /**
     * \brief Upper limit for random values.
     * \details All random values will be in the range 0..(MAX-1). 
     */
    static const unsigned int MAX = 32768;
    

    // ************
    // CONSTRUCTORS
    // ************
    Random(); ///< Default constructor

    // ****************
    // MEMBER FUNCTIONS
    // ****************

    /// Returns a new random value in the range [0,MAX)
    unsigned int next();

    /// Return a new random value in the range [0,bound).
    unsigned int next(unsigned int bound /**< must be <= MAX */);

private:
    // *********************
    // PROHIBITED OPERATIONS (assignment & copy construction)
    // *********************

    Random(const Random&); ///< Disabled
    Random& operator=(const Random& rhs); ///< Disabled

    // ************
    // PRIVATE DATA
    // ************

    /// State of the random number generator.
    unsigned long state_;


    // *****************
    // PRIVATE CONSTANTS
    // *****************

    static const unsigned long MULTIPLIER = 1103515245; //< Internal constant
    static const unsigned long ADDITIVE   = 12345;      //< Internal constant
    static const unsigned long DIVISOR    = 65536;      //< Internal constant
};

#endif // RANDOM_HPP_INCLUDED


/* (Junk to make emacs use the right mode)
 * Local Variables:
 * c-file-style: "stroustrup"
 * End:
 */
