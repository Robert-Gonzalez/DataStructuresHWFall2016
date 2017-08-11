/**
 * \file spellchecker.hpp
 *
 * \author hawk & reindeer, make it rein.
 *
 * \brief Interface for the spellchecker class
 *
 */
#include <string>
#include <iostream>
#include <list>



#include "treeset.hpp"


#ifndef SPELLCHECKER_HPP_INCLUDED
#define SPELLCHECKER_HPP_INCLUDED 1



/**
* \class SpellChecker
* \brief allows us to  check if words are correctly spelt by formatting them
*    to a dictionary and comparing to that dictionary
*
*/


class SpellChecker {
public:

    /**
    * \brief Populate our spell checker's dictionary with words
    *
    *
    * \param dictFile     filename for the dictionary
    * \param debug        Boolean to know if we want to be in debug mode
    *
    *
    * \note if debug is true, the function prints stats about the dictionary
    *
    */
    void populateDict(const std::string& dictFile, bool debug);


    /**
    * \brief determine if a word is in dict, if not then it is not spelled correctly
    *
    * \param word     word to analyze spelling of
    *
    * \return true if the word is spelled correctly
    *
    */
    bool spelledCorrectly(const std::string& word);

    /**
    * \brief print suggestions for an incorrectly spelled word
    *
    * \param word     word to check suggested variations
    *
    */
    void printSuggestions(const std::string& word);



    /**
    * \brief get words from an instream, and print suggestions if they
    *   are mispelled
    *
    * \param inputStream     the stream to get words from
    *
    *
    */
    void spellCheck(istream& inputStream);



private:

    /**
    * \brief remove exterior symbols from a word
    *
    * \param str     string to remove symbols from
    *
    * \return a string with the outer non-letters removed
    *
    */
    std::string removeOuterPunct(const std::string& str);

    /**
    * \brief take string and make it all lowercase
    *
    * \param str     string to make lowercase
    *
    * \return a string with all letters now lowercase
    *
    */
    std::string lowercase(const std::string& str);

    TreeSet<std::string> dictionary;
    TreeSet<std::string> ignoredWords;

};

#endif //* SPELLCHECKER_HPP_INCLUDED
