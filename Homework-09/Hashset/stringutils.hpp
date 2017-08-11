/**
 * \file stringutil.hpp
 * \author CS 70 Provided Code.
 *
 * \brief Miscellaneous utility code for strings
 */
#ifndef STRINGUTIL_CPP_INCLUDED
#define STRINGUTIL_CPP_INCLUDED 1

#include <iosfwd>
#include <string>

/**
 * \brief Reads a word from input stream in, where a word is the longest
 *        possible sequence of alphabetical characters. Reads (and ignores)
 *        one non-alphabetic character at the end of the word.
 *
 * \returns The word at the start of the input. (This will be the
 *          empty string if the input does not start with an
 *          alphabetic character.)
 *
 * \remarks  Only handles words with alphabetic characters;
 *               does not skip leading whitespace;
 *               returning the empty string is a hacky
 *               way of reporting that no word was found.
 */
std::string getWord(std::istream& in);

#endif // STRINGUTIL_CPP_INCLUDED
