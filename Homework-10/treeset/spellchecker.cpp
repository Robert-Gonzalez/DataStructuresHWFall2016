/**
 * \file spellchecker.cpp
 *
 * \author hawk & reindeer, make it rein.
 *
 * \brief Implements the spellchecker class
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <list>
#include "spellchecker.hpp"

using namespace std;

void SpellChecker::populateDict(const string& dictFile, bool debug)
{

    // create a stream from a dictionary file
    ifstream dictStream(dictFile);
    string word;

    // insert each word from the stream into the dictionary
    // until the end of the file
    while (dictStream >> word) {
        dictionary.insert(word);
    }

    // output hash set statistics if in debug mode
    if (debug) {
        dictionary.showStatistics(cerr);
        cout << endl;
    }
}

// words are only considered correctly spelt if they are in the dictionary
bool SpellChecker::spelledCorrectly(const string& word)
{
    return dictionary.exists(word);
}

void SpellChecker::printSuggestions(const string& word)
{
    // create a test string that we can change to analyze for possible
    // respellings of our input word
    string testWord = word;
    cout << word << ": ";

    // loop through each letter in the word and for each
    // letter, we should replace it with every letter in the alphabet
    // and check if that new word is in the dictionary
    for (auto it = testWord.begin(); it != testWord.end(); ++it) {
        for (char c = 'a'; c <= 'z'; ++c ) {
            *it = c;
            // if the word is correct, print it as a sugegsted fix
            if (spelledCorrectly(testWord)) {
                cout << testWord << " ";
            }
        }
        // reset testword to original spelling to test another letter
        testWord = word;
    }
    cout << endl;

}

void SpellChecker::spellCheck(istream& inputStream)
{
    string currWord;

    // continue to take words from the input string until the end of the stream
    while (inputStream >> currWord)
    {

        // fix word for capitalization and exterior non-letter before
        // placing it into the list
        string formatWord =  removeOuterPunct(currWord);
        formatWord = lowercase(formatWord);

        // if our word have no letters, then removeOuterPunct will
        // leave our currWord empty, so do not add to list
        if(!formatWord.empty()) {
            if (!dictionary.exists(formatWord) &&
                !ignoredWords.exists(formatWord)) {

                // Mark the word as ignored after checking
                // it's spelling the first time
                ignoredWords.insert(formatWord);
                printSuggestions(formatWord);
            }
        }

    }

}

string SpellChecker::removeOuterPunct(const string& str) {

    // firstIndex is the index we use to note the first place in the string
    // we find a letter. It is set to the string length because this is a
    // number that the first letter index will never be. Therefore, it is an
    // indicator that we never found a letter in the string.
    size_t firstIndex = str.length();

    // if we find a letter within the string that is a letter
    // when indexing forward, keep its index and leave the loop
    for (size_t i = 0; i < str.length(); ++i) {
        if (isalpha(str[i])) {
            firstIndex = i;
            break;
        }
    }

    // if our firstIndex is still the string length, the word has no letters
    if (firstIndex == str.length()) {
        return "";
    }

    // lastIndex is the index we use to note the last place in the string
    // we find a letter. We only check for a last index if we found an initial
    // letter in our word. The last index will be at furthest the end of str.
    int lastIndex = str.length()-1;

    // loop back through string until we find a letter, and then mark its index
    for (size_t i = lastIndex; i > firstIndex; --i) {
        if (isalpha(str[i])) {
            lastIndex = i;
            break;
        }
    }

    // return the substring from the first letter through the last letter
    return str.substr(firstIndex, (lastIndex - firstIndex) +1);
}

string SpellChecker::lowercase(const string& str) {
    string result = "";

    // make each character from the str lowercase and add to result string
    for(auto it = str.begin(); it != str.end(); ++it) {
        result += tolower(*it);
    }
    return result;
}
