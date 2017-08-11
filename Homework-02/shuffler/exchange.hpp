/**
 * \file exchange.hpp
 * \author Robert Gonzalez and Finn Southerland
 *
 * \brief Interface definition for exchange.
 */

// C++ include guard for header file.
// Its mere presence will prevent linker errors and much sorrow later.
#ifndef EXCHANGE_HPP_INCLUDED
#define EXCHANGE_HPP_INCLUDED 1

#include <string>
using namespace std;

/**
* \brief
*    Swaps the values of two strings.
*
* \pre two strings s1 and s2
* \returns nothing. This is a void function.
* \post swaps values of input strings in memory.
*/
void exchange(string &s1, string &s2);

#endif // EXCHANGE_HPP_INCLUDED


/* (Junk to make emacs use the right mode)
 * Local Variables:
 * c-file-style: "stroustrup"
 * End:
 */
