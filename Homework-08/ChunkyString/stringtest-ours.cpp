/**
 * \file stringtest.cpp
 *
 * \brief Tests a ChunkyString for correctness.
 */

#include "testing-logger.hpp"
#ifndef LOAD_GENERIC_STRING
/* This test code can be used two ways.  It can either test a local
 * ChunkyString implementation, or it can dynamically load an implementation
 * at runtime and test that.  In the first homework, you'll load an
 * implementation that someone else used, but in later assignments, you'll
 * set the value to zero to use your own.
 */
#define LOAD_GENERIC_STRING 0       // 0 = Normal, 1 = Load Code Dynamically
#endif

#if LOAD_GENERIC_STRING
#include "string-wrapper.hpp"       // Use dynamic loading magic!
using TestingString = GenericString;
#else
#include "chunkystring.hpp"         // Just include and link as normal.
using TestingString = ChunkyString;
#endif

#include <string>
#include <sstream>
#include <stdexcept>
#include <cstddef>
#include <cstdlib>
#include <cassert>

#include "signal.h"
#include "unistd.h"

using namespace std;

static const size_t TESTING_CHUNKSIZE = 12;     // Assuming a chunksize of 12

// Helper functions
/**
 * \brief Assuming chunks are supposed to be at least 1/divisor full, checks
 *        for the lowest allowable utilization for the input string
 *
 * \remarks For insertion only, we assume chunks are at least 1/2 full.
 *          For erase, chunks can go down to 1/4 full.
 *          Since checkUtilization is not a test on its own, but rather
 *          a helper function to be used in other tests, it doesn't
 *          create its own TestingLogger object. Instead, its affirms
 *          will be associated with the TestingLogger of the calling
 *          function.
 *
 * \param test          TestingString to check
 * \param divisor       Fullness of chunk = 1/divisor
 * \param origin        String to describe the caller of this function to
 *                      aid in human debugging.
 */
//bool checkUtilization(const TestingString& test, size_t divisor)
void checkUtilization(const TestingString& test, size_t divisor)
{
    double utilLimit = 0;

    if (test.size() > 0)
    {
        size_t chunks = 1;
        size_t size = test.size() - 1;
        divisor = TESTING_CHUNKSIZE / divisor;
        chunks += (size + divisor - 1) / divisor;
        utilLimit = double(size) / double(chunks * TESTING_CHUNKSIZE);
        affirm(test.utilization() > utilLimit);
    }
}



// Testing functions

bool exampleTest()
{
    // Set up the TestingLogger object
    TestingLogger log{"example test"};

    TestingString s;

    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}




/**
 * \brief Confirm that default constructing a string returns an empty string
 *
 */
 bool defaultConstructorTest() 
 {
     // Set up the TestingLogger object
    TestingLogger log{"default constructor test"};

    TestingString s;

    affirm(s.size() == 0);

    return log.summarize();
 }
 
/**
 * \brief Confirm that push_back successfully adds an element to empty 
 * ChunkyString
 *
 */
 bool pushBackOnEmptyTest() 
 {
    TestingLogger log{"push back onto empty"};

    TestingString s;

    s.push_back('c');

    affirm(s.size() == 1);
    affirm(*s.begin() == 'c');

    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
 }

 /**
 * \brief Confirm that push_back successfully adds an element to the back of
 *  a non-empty Chunkystring
 *
 */
 bool pushBackNotEmptyTest() 
 {
    TestingLogger log{"push back onto non-empty"};

    TestingString s;

    s.push_back('c');
    s.push_back('a');

    affirm(s.size() == 2);
    affirm(*s.begin() == 'c');


    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
 }

 /**
 * \brief Confirm that push_back successfully adds elements to a non-empty 
 * ChunkyString, even if number of additions exceeds chunksize
 */
 bool pushBacktoNewChunkTest() 
 {
    TestingLogger log{"push back exceeding chunksize"};

    TestingString s;

    s.push_back('c');

    size_t chunkyStringSize = s.size();

    //Populate the ChunkyString such that it MUST have more than 1 chunk
    for (size_t i = 0; i < TESTING_CHUNKSIZE; ++i) {
        s.push_back('c');
        ++chunkyStringSize;
        affirm (s.size() == chunkyStringSize);
    }

    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
 }

/**
 * \brief Confirm that dereferencing the iterator returns the character
 *  stored at the position being pointed to
 */
 bool iteratorDereferenceTest()
 {
    TestingLogger log{"iterator dereference operator"};

    TestingString s;

    s.push_back('c');
    
    affirm(*s.begin() == 'c');

    return log.summarize();
 }

/**
 * \brief Confirm that dereferencing the iterator returns the character
 * stored at the position being pointed to
 */
 bool iteratorBeginTest()
 {
     TestingLogger log{"iterator begin() test"};

     TestingString s;

     s.push_back('z');
     affirm(*s.begin() == 'z');

     //Populate the ChunkyString such that it MUST have more than 1 chunk
    for (size_t i = 0; i < TESTING_CHUNKSIZE; ++i) {
        char letter = 97 + i;
        s.push_back(letter);
    }

    affirm(*s.begin() == 'z');

    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
 }

/**
 * \brief Confirm that the equals comparison returns true for iterators
 * pointing to the same thing and false for iterators pointing to different
 * things.
 */
 bool iteratorEqualTest()
 {
     TestingLogger log{"iterator equal comparison test"};

     TestingString s;

     s.push_back('z');

     affirm(s.begin() == s.begin());
     affirm(!(s.begin() == s.end()));

     return log.summarize();
 }

/**
 * \brief Confirm that incrementing the iterator advances it by one position
 * through the ChunkyString
 */
bool iteratorIncrementTest()
{
    TestingLogger  log{"basic iterator increment test"};

    TestingString s;

    s.push_back('c');
    s.push_back('s');

    TestingString::iterator myIt = s.begin();
    ++myIt;
    affirm(*myIt == 's');
    ++myIt;
    affirm(myIt == s.end());

    return log.summarize();
}

/**
 * \brief Confirm that incrementing the iterator advances it by one position
 * through the ChunkyString in the correct order, even when the ChunkyString
 * has multiple chunks
 */
bool iteratorIncrementMultiChunkTest()
{
    TestingLogger  log{"iterator increment test, multiple chunks"};

    TestingString s;


    //Populate the ChunkyString such that it MUST have more than 1 chunk
    for (size_t i = 0; i < TESTING_CHUNKSIZE + 1; ++i) {
        char letter = 97 + i;
        s.push_back(letter);
    }

    // Loops through the ChunkyString and makes sure that the iterator
    // points to the elements in order
    size_t i = 0;
    for (TestingString::iterator myIt = s.begin(); myIt != s.end(); ++myIt) {
        char letter = 97 + i;
        affirm(*myIt == letter);
        ++i;
    }
    return log.summarize();

}

/**
 * \brief Confirm that decrementing begin() results in begin()
 */
bool iteratorDecrementBeginTest()
{
    TestingLogger  log{"decrement begin() iterator test"};

    TestingString s;

    s.push_back('c');

    TestingString::iterator myIt = s.begin();
    affirm(s.begin() == --myIt);

    //decrementing otherwise results in prev thing
    return log.summarize();
}

/**
 * \brief Confirm that decrementing end() returns an iterator pointing to the
 * last element
 */
bool iteratorDecrementEndTest()
{
    TestingLogger  log{"decrement end() iterator test"};

    TestingString s;

    s.push_back('c');

    TestingString::iterator myIt = s.end();
    --myIt;

    affirm(*myIt == 'c');

    return log.summarize();
}

/**
 * \brief Confirm that decrementing works within a small ChunkyString
 */
bool iteratorDecrementOneChunkTest()
{
    TestingLogger log{"decrement within a small ChunkyString test"};

    TestingString s;

    s.push_back('c');
    s.push_back('s');

    TestingString::iterator myIt = s.end();
    --myIt;
    --myIt;
    affirm(myIt == s.begin());

    return log.summarize();
}

/**
 * \brief Confirm that decrementing works within a ChunkyString with
 * multiple chunks
 */
bool iteratorDecrementMultiChunkTest()
{
    TestingLogger log{"decrement over multiple chunks"};

    TestingString s;

    // Populate the chunkystring with more than one chunk's worth of characters
    for (size_t i = 0; i < TESTING_CHUNKSIZE + 1; ++i) {
        char letter = 97 + i;
        s.push_back(letter);
    }

    // Decrement through the chunky string and make sure that the iterator
    //moves backwards through the characters in order
    int i = TESTING_CHUNKSIZE;
    TestingString::iterator onePast = s.end();
    for (TestingString::iterator myIt = --onePast; myIt != s.begin(); --myIt) {
        char letter = 97 + i;
        affirm(*myIt == letter);
        --i;
    }

    return log.summarize();
}

/**
* \brief make sure that when we loop through a list that end works properly on 
* an empty string
*/
bool iteratorEndEmptyTest() 
{
    TestingLogger log{"end() empty test"};

    TestingString s;

    affirm(s.begin() == s.end());

    return log.summarize(); 
}

/**
* \brief make sure that when we loop through a list that end works properly 
* on populated strings
*/
bool iteratorEndNotEmptyTest() 
{
    TestingLogger log{"end() not empty test"};

    TestingString s;

    // Fill up more than one chunk for good measure
     for (size_t i = 0; i < 10 * TESTING_CHUNKSIZE; ++i) {
        char letter = i % 26 + 97;
        s.push_back(letter);
    }

    int testCount = 0;

    // Make sure the iterator iterates to the end of the string
    for (TestingString::iterator myIt = s.begin(); myIt != s.end(); ++myIt) { 
        ++testCount;
    }

    affirm(testCount == 10 * TESTING_CHUNKSIZE);

    return log.summarize(); 
}

/**
* \brief Confirm that two empty lists are equal
*/
bool chunkyStringEqualsEmptyTest()
{
    TestingLogger log{"chunky string equals empty test"};

    TestingString s1;
    TestingString s2;

    affirm(s1 == s2);

    return log.summarize();
}

/**
* \brief Confirm strings of different sizes aren't equal
*/
bool chunkyStringEqualsDifferentSizeTest()
{
    TestingLogger log{"chunky string equals different size test"};

    TestingString s1;
    TestingString s2;

    affirm(s1 == s2);

     for (size_t i = 0; i < TESTING_CHUNKSIZE; ++i) {
        char letter = 97 + i;
        s1.push_back(letter);
        s2.push_back(letter);
    }

    s2.push_back('y');

    affirm(!(s1 == s2));

    return log.summarize();
}

/**
* \brief Confirm DIFFERENT strings of same size aren't equal and that same
* strings are equal
*/
bool chunkyStringEqualsSameSizeTest() 
{
    TestingLogger log{"chunky string equals different size test"};

    TestingString s1;
    // String that will hold diferrent characters from s1
    TestingString s2;
    // String that will hold same characters in same order as s1
    TestingString s3;

    for (size_t i = 0; i < TESTING_CHUNKSIZE; ++i) {
        char letter = 97 + i;
        s1.push_back(letter);
        s2.push_back(letter+1);
        s3.push_back(letter);
    }

    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;

    affirm(!(s1 == s2));
    affirm(s1 == s3);

    return log.summarize();
}
/**
* \brief Confirm that two strings with same chars in different orders
* aren't equal
*/

bool chunkyStringEqualsDiffOrderTest() 
{
    TestingLogger log{"chunky string equals different order test"};

    TestingString s1;
    // String that will hold same characters as s1 but in different order
    TestingString s2;

    for (size_t i = 0; i < TESTING_CHUNKSIZE; ++i) {
        char letter = 97 + i;

        // letter2 goes through characters in reverse order from letter
        char letter2 = 97 + (TESTING_CHUNKSIZE - 1) - i;
        s1.push_back(letter);
        s2.push_back(letter2);
    }

    affirm(!(s1 == s2));

    return log.summarize();

}

/**
* \brief Confirm that it is possible to insert on empty strings using begin()
*  and end()
*/
bool insertEmptyTest() 
{
    TestingLogger log{"insert empty test"};

    TestingString s1;
    TestingString s2;
    TestingString correct;

    correct.push_back('c');

    TestingString::iterator returnedIt1 =  s1.insert(s1.begin(), 'c');
    TestingString::iterator returnedIt2 = s2.insert(s2.end(), 'c');


    affirm(s1.size() == 1);
    affirm(s2.size() == 1);
    affirm(s1 == correct);
    affirm(s2 == correct);
    affirm(s1.begin() == returnedIt1);
    affirm(s2.begin() == returnedIt2);

    return log.summarize();
}

/**
* \brief Confirm that inserting at the front and back works as expected
*/
bool insertFrontBackTest() 
{
    TestingLogger log{"insert front back test"};

    TestingString s1;
    TestingString s2;
    TestingString correct;
    TestingString correct2;

    correct.push_back('y');
    correct.push_back('a');
    correct.push_back('b');
    correct.push_back('c');

    correct2.push_back('a');
    correct2.push_back('b');
    correct2.push_back('c');
    correct2.push_back('z');
    
    s1.push_back('a');
    s1.push_back('b');
    s1.push_back('c');

    s2.push_back('a');
    s2.push_back('b');
    s2.push_back('c');

    // insert to the front;
    TestingString::iterator returnedIt1 =  s1.insert(s1.begin(), 'y');

    // insert to the back
    TestingString::iterator returnedIt2 =  s2.insert(s2.end(), 'z');

    cout << "TEST STRING" << endl;
    cout << s1 << endl;
    cout << "CORRECT STRING" << endl;
    cout << correct << endl;
    affirm(s1 == correct);
    affirm(s2 == correct2);
    affirm(s1.size() == 4);
    affirm(s2.size() == 4);
    affirm(s1.begin() == returnedIt1);

    // Get the iterator that points to the last character in the string
    TestingString::iterator correctIt2 = s2.end();
    --correctIt2;

    affirm(returnedIt2 == correctIt2);

    return log.summarize();

}

/**
* \brief Confirm that inserting between elements that live in one chunk works
*  as expected
*/
bool insertBetweenOneChunkTest() 
{
    TestingLogger log{"insert between one chunk test"};

    TestingString s;
    TestingString correct;
    
    // Assume that the chunk size is larger than 4 
    correct.push_back('y');
    correct.push_back('a');
    correct.push_back('b');
    correct.push_back('c');

    s.push_back('y');
    s.push_back('b');
    s.push_back('c');

    TestingString::iterator myIt = s.begin();
    ++myIt;

    TestingString::iterator returnedIt = s.insert(myIt,'a');

    cout << "TEST STRING" << endl;
    cout << s << endl;
    cout << "CORRECT STRING" << endl;
    cout << correct << endl;
    
    affirm(s == correct);
    affirm(s.size() == 4);

    // Create new iterators since insert invalidates iterators
    TestingString::iterator correctIt = s.begin();
    ++correctIt;

     affirm(correctIt == returnedIt);

     return log.summarize();
}

/**
* \brief Make sure that inserting that causes a new chunk to be used works
*  as expected
*/
bool insertSpillOverChunkTest() 
{
    // Assume that the chunk size is larger than 4
    TestingLogger log{"insert spill over chunk test"};

    TestingString s;

    TestingString correct;

    // make the correct string "abcde#fghijkl"
    char letter = 97;
    for (size_t i = 0; i < TESTING_CHUNKSIZE+1; ++i) {
        if (i == 5) {
            correct.push_back('#');
        }
        else if (i > 5) {
            correct.push_back(letter - 1);
        }
        else {
            correct.push_back(letter);
        }
        ++letter;
    }

    
    // populate the test string with one chunk
    // "abcdefghjkl" assuming TESTING_CHUNKSIZE = 12
    for (size_t i = 0; i < TESTING_CHUNKSIZE; ++i) {
        char testLetter = 97 + i;
        s.push_back(testLetter);
    }

    TestingString::iterator myIt = s.begin();
    advance(myIt, 5);

    TestingString::iterator returnedIt = s.insert(myIt,'#');

    cout << "TEST STRING" << endl;
    cout << s << endl;
    cout << "CORRECT STRING" << endl;
    cout << correct << endl;
    
    // Make sure the new insert occured correctly
    affirm(correct == s);
    
    // Make sure the correct iterator is returned
    TestingString::iterator correctIt = s.begin();
    advance(correctIt, 5);

    affirm(correctIt == returnedIt);

    return log.summarize();
}


/**
* \brief Confirm that erasing so that the string becomes empty works as
* expected (notably, begin() and end() should be equal)
*/
bool eraseToEmpty()
{
    TestingLogger log{"erase to empty"};

    TestingString s;
    TestingString correct;

    s.push_back('a');
    TestingString::iterator returnedIt = s.erase(s.begin());

    affirm(returnedIt == s.begin());
    affirm(s.size() == 0);
    affirm(s == correct);

    return log.summarize();
}

/**
* \brief Confirm that erasing an element when the string has 1 chunk works
*  as expected
*/
bool eraseWithinChunk() 
{
    
    TestingLogger log{"erase to empty"};

    TestingString s;
    TestingString correct;

    correct.push_back('a');
    correct.push_back('b');
    correct.push_back('d');
    correct.push_back('e');

    s.push_back('a');
    s.push_back('b');
    s.push_back('c');
    s.push_back('d');
    s.push_back('e');

    // create an it that points to the 'c' in s
    TestingString::iterator myIt = s.begin();
    advance(myIt, 2);

    // erase 'c' from s
    TestingString::iterator returnedIt = s.erase(myIt);

    // The correct returned iterator should point to 'd'
    TestingString::iterator correctIt = s.begin();
    advance(correctIt, 2);

    affirm(correctIt == returnedIt);
    affirm(s.size() == 4);
    affirm(s == correct);

    return log.summarize();
    
}

/**
* \brief Confirm that erasing from the string works when the string has
* multiple chunks
*/
bool eraseMultipleChunks() 
{
    TestingLogger log{"erase to empty"};

    TestingString s;
    TestingString correct;

    // Make a test string that uses multiple chunks
    // Assuming TESTING_CHUNKSIZE = 12, s will be 
    // s = "abcdefghijklmnopq" 
    for (size_t i = 0; i < TESTING_CHUNKSIZE + 5; ++i) {
        char letter = 97 + i;
        s.push_back(letter);
        
        // leave 'f' out of the correct string
        if (i != 5) {
            correct.push_back(letter);
        }
    }

    // create an it that points to the 'f' in s
    TestingString::iterator myIt = s.begin();
    advance(myIt, 5);

    // erase 'f' from s
    TestingString::iterator returnedIt = s.erase(myIt);

    // The correct returned iterator should point to 'g'
    TestingString::iterator correctIt = s.begin();
    advance(correctIt, 5);

    affirm(correctIt == returnedIt);
    affirm(s.size() == TESTING_CHUNKSIZE + 4);
    affirm(s == correct);


    return log.summarize();
}

/**
* \brief Confirm that an empty string is NOT less than another empty string
*/
bool chunkyLessThanEmptyTest()
{
    TestingLogger log{"chunkystring less than empty test"};

    TestingString s1;
    TestingString s2;

    //empty strings are equal
    affirm(!(s1 < s2));

    s2.push_back('a');

    // empty string is less than non-empty
    affirm(s1 < s2);

    return log.summarize();

}

/**
* \brief Confirm that short strings with different letters are
* compared correctly
*/
bool chunkyLessThanEasyTest()
{
    TestingLogger log{"chunkystring less than easy test"};

    TestingString s1;
    TestingString s2;
    TestingString s3;

    s1.push_back('a');

    s2.push_back('b');

    s3.push_back('a');
    s3.push_back('c');

    //a before b
    affirm(s1 < s2);

    s1.push_back('b');

    //ab before ac
    affirm(s1 < s3);

    return log.summarize();
}

/**
* \brief Confirm that very similar strings are compared correctly (considers
* that capital letters should come before lowercase)
*/
bool chunkyLessThanHardTest()
{
    TestingLogger log{"chunkystring less than hard test"};

    TestingString s1;
    TestingString s2;
    TestingString s3;

    //s1 will be 'applevallies'
    s1.push_back('A');
    s1.push_back('p');
    s1.push_back('p');
    s1.push_back('l');
    s1.push_back('e');
    s1.push_back('v');
    s1.push_back('a');
    s1.push_back('l');
    s1.push_back('l');
    s1.push_back('i');
    s1.push_back('e');
    s1.push_back('s');


    //s2 will be 'applepie'
    s2.push_back('A');
    s2.push_back('p');
    s2.push_back('p');
    s2.push_back('l');
    s2.push_back('e');
    s2.push_back('p');
    s2.push_back('i');
    s2.push_back('e');

    //s3 will be apple
    s3.push_back('a');
    s3.push_back('p');
    s3.push_back('p');
    s3.push_back('l');
    s3.push_back('e');

    // applepie before applevallies
    affirm(s2 < s1);

    //apple before applepie and applevallies
    affirm(s1 < s3);
    affirm(s2 < s3);

    return log.summarize();
}

/**
* \brief Confirm that +='ing an empty string onto another works as expected
*/
bool operatorPlusEqualEmptyTest()
{
    TestingLogger log{"plus equal an empty string test"};

    TestingString s1;
    TestingString s2;
    TestingString correct;
    TestingString empty;

    s1 += s2;
    affirm(s1 == correct);
    affirm(s2 == correct);

    s1.push_back('a');
    s1.push_back('b');

    correct.push_back('a');
    correct.push_back('b');

    s1 += s2;

    affirm(s1 == correct);
    affirm(s2 == empty);

    return log.summarize();
}

/**
* \brief Confirm that +='ing onto an empty string works as expected
*/
bool operatorPlusEqualOntoEmptyTest()
{
    TestingLogger log{"plus equal onto empty string test"};

    TestingString s1;
    TestingString s2;
    TestingString correct;

    correct.push_back('a');
    correct.push_back('b');

    s2.push_back('a');
    s2.push_back('b');

    s1 += s2;

    affirm(s1 == correct);
    affirm(s2 == correct);

    return log.summarize();
}

/**
* \brief Confirm that += works in a standard case with two different strings,
* and that it does not modify the appended string
*/
bool operatorPlusEqualTest()
{
    TestingLogger log{"standard plus equal test"};

    TestingString s1;
    TestingString s2;
    TestingString correct;
    TestingString justb;

    correct.push_back('a');
    correct.push_back('b');

    justb.push_back('b');

    s1.push_back('a');
    s2.push_back('b');

    s1 += s2;

    affirm(s1 == correct);
    affirm(s2 == justb);

    return log.summarize();
}

/**
* \brief  Confirm that appending a string to itself effectively modifies
* the string
*/
bool operatorPlusEqualToItselfTest() 
{
    TestingLogger log{"plus equal to itself test"};

    TestingString s1;
    TestingString s2;

    //insert at random position within the ChunkyString
    TestingString::iterator myIt1 = s1.begin();
    TestingString::iterator myIt2 = s2.begin();

    //Populate two chunkystrings by inserting random letters at
    //random positions
    for (size_t i = 0; i < 50 * TESTING_CHUNKSIZE; ++i) {
        char letter = rand() % 26 + 97;
        s1.insert(myIt1, letter);
        s2.insert(myIt2, letter);
        myIt1 = s1.begin();
        myIt2 = s2.begin();
        int advanceNum = rand() % s1.size();
        advance(myIt1, advanceNum);
        advance(myIt2, advanceNum);
    }

    s1 += s1;

    affirm(s1 != s2);

    return log.summarize();
    
}

/**
* \brief Confirm that using the output operator works as expected
*/
bool outputOperatorTest()
{
    TestingLogger log{"output operator test"};

    TestingString s1;
    TestingString s2;

    s2.push_back('a');

    ostringstream ourStream1;
    ostringstream ourStream2;

    //load empty string to ourStream1
    ourStream1 << s1;

    //load 'a' to ourStream2
    ourStream2 << s2;

    //converting streams to strings should return original strings
    affirm(ourStream1.str() == "");
    affirm(ourStream2.str() == "a");

    return log.summarize();
}

/**
* \brief Confirm that push_back on its own maintains correct utilization
*/
bool correctUtilizationPushBackTest()
{
    TestingLogger log{"push_back utilization test"};
    
    TestingString s;

    //Populate the chunkystring with cycles of the characters from 'a' to 'z'
    for (size_t i = 0; i < 5 * TESTING_CHUNKSIZE; ++i) {
        char letter = i % 26 + 97;
        s.push_back(letter);
        checkUtilization(s, 2);
    }
   
    return log.summarize();
}

/**
* \brief Confirm that insert on its own maintains correct utilization
*/
bool correctUtilizationInsertTest()
{
    TestingLogger log{"insert utilization test"};

    TestingString s;

    s.push_back('a');
    s.push_back('b');
    s.push_back('c');

    for (size_t i = 0; i < 3 * TESTING_CHUNKSIZE; ++i) {
        TestingString::iterator myIt = s.begin();
        //place the iterator not at begin() or end() each time
        advance(myIt, i + 1);
        s.insert(myIt, 'd');
        checkUtilization(s, 2);
    }

    return log.summarize();
}
/**
* \brief Confirm that erasing maintains correct utilization
*/
bool correctUtilizationEraseTest()
{
    TestingLogger log{"erase utilization test"};
    
    // Make a test string that uses multiple chunks
    // Assuming TESTING_CHUNKSIZE = 12, s will be 
    // s = "abcdefghijklmnopq" 
    TestingString s;

    for (size_t i = 0; i < TESTING_CHUNKSIZE + 5; ++i) {
        char letter = 97 + i;
        s.push_back(letter);
    }

    TestingString::iterator myIt = s.begin();
    advance(myIt, 3);

    //erase from the middle until end() is reached
    for (size_t i = 0; i < TESTING_CHUNKSIZE + 2; ++ i) {
        TestingString::iterator returnedIt = s.erase(myIt);
        myIt = returnedIt;
        checkUtilization(s, 4);
    }
   
    return log.summarize();
}

/**
* \brief Confirm that insertions and erasings maintain good utilization
*/
bool correctUtilizationInsertEraseTest()
{
    TestingLogger log{"insert and erase utilization test"};
    
    // Make a test string that uses multiple chunks
    // Assuming TESTING_CHUNKSIZE = 12, s will be 
    // s = "abcdefghijklmnopq" 
    TestingString s;

    for (size_t i = 0; i < TESTING_CHUNKSIZE + 5; ++i) {
        char letter = 97 + i;
        s.push_back(letter);
    }

    TestingString::iterator myIt = s.begin();
    advance(myIt, 3);

    //erase from the middle and insert in the middle
    for (size_t i = 0; i < TESTING_CHUNKSIZE + 2; ++ i) {
        TestingString::iterator returnedIt = s.erase(myIt);
        myIt = returnedIt;
        s.insert(myIt, '%');
        checkUtilization(s, 4);
    }
   
    return log.summarize();
}

/**
* \brief Confirm that insertions and erasings maintain good utilization
* (harder case)
*/
bool correctUtilizationInsertEraseTest2()
{
    TestingLogger log{"insert and erase 2 utilization test"};
    
    // Make a test string that uses multiple chunks
    // Assuming TESTING_CHUNKSIZE = 12, s will be 
    // s = "abcdefghijklmnopq" 
    TestingString s;

    for (size_t i = 0; i < TESTING_CHUNKSIZE + 5; ++i) {
        char letter = 97 + i;
        s.push_back(letter);
    }

    TestingString::iterator myIt = s.begin();
    advance(myIt, 3);

    //erase from the middle and insert in the middle
    for (size_t i = 0; i < TESTING_CHUNKSIZE + 2; ++ i) {
        TestingString::iterator returnedIt = s.erase(myIt);
        myIt = returnedIt;
    }

    for (size_t i = 0; i < TESTING_CHUNKSIZE + 5; ++i) {
        char letter = 97 + i;
        s.push_back(letter);
        checkUtilization(s, 4);
    }
   
    return log.summarize();
}


/**
* \brief Confirm that insertions and erasings maintain good utilization
* for a pretty large string where we insert and erase at random positions
*/
bool correctUtilizationInsertEraseTest3()
{
    TestingLogger log{"insert and erase 3 utilization test"};
    
    TestingString s;

    //Populate a chunkystring by inserting random letters at random positions
    TestingString::iterator myIt = s.begin();
    for (size_t i = 0; i < 50 * TESTING_CHUNKSIZE; ++i) {
        char letter = rand() % 26 + 97;
        s.insert(myIt, letter);
        myIt = s.begin();
        advance(myIt, rand() % s.size());
        checkUtilization(s, 2);
    }

    //erase from random positions in the ChunkyString
    for (size_t i = 0; i < 15 * TESTING_CHUNKSIZE; ++i) {
        myIt = s.begin();
        advance(myIt, rand() % s.size());
        s.erase(myIt);
        checkUtilization(s, 4);
    }

    myIt = s.begin();
    advance(myIt, rand() % s.size());

    //Add chars to chunkystring by inserting random letters at random
    //positions
    for (size_t i = 0; i < 20 * TESTING_CHUNKSIZE; ++i) {
        char letter = rand() % 26 + 97;
        s.insert(myIt, letter);
        myIt = s.begin();
        advance(myIt, rand() % s.size());
        checkUtilization(s, 4);
    }

    return log.summarize();
}

/**
* \brief Confirm that the copy constructor executes a deep copy
*/
bool copyConstructorTest() 
{
    TestingLogger log{"copy constructor deep copy test"};

    TestingString s1;

    s1.push_back('a');
    s1.push_back('b');
    s1.push_back('c');

    TestingString s2{s1};

    affirm(s1 == s2);

    s1.push_back('d');
    affirm(s1 != s2);

    return log.summarize();    
}


//--------------------------------------------------
//           RUNNING THE TESTS
//--------------------------------------------------

// Called if the test runs too long.
static void timeout_handler(int)
{
    // We go super-low-level here, because we can't trust anything in
    // the C/C++ library to really be working right.
    write(STDERR_FILENO, "Timeout occurred!\n", 18);
    abort();
}

/// Run tests
int main(int argc, char** argv)
{
    // Initalize testing environment
    TestingLogger alltests{"All tests"};

#if LOAD_GENERIC_STRING
    // Load the desired string implementation, if that's what we're doing.

    if (argc != 2) {
        cerr << "Usage ./stringtest plugin" << endl;
        exit(0);
    }

    GenericString::loadImplementation(argv[1]);
#else
    // No setup to do if we're using ChunkyString directly
#endif

    signal(SIGALRM, timeout_handler);   // Call this when the timer expires
    alarm(10);                          // set the timer at 10 seconds

    // Add calls to your tests here...
    affirm(defaultConstructorTest());
    affirm(pushBackOnEmptyTest());
    affirm(pushBackNotEmptyTest());
    affirm(pushBacktoNewChunkTest());
    affirm(iteratorDereferenceTest());
    affirm(iteratorBeginTest());
    affirm(iteratorEqualTest());
    affirm(iteratorIncrementTest());
    affirm(iteratorIncrementMultiChunkTest());
    affirm(iteratorDecrementEndTest());
    affirm(iteratorDecrementOneChunkTest());
    affirm(iteratorDecrementMultiChunkTest());
    affirm(iteratorEndEmptyTest());
    affirm(iteratorEndNotEmptyTest());
    affirm(chunkyStringEqualsEmptyTest());
    affirm(chunkyStringEqualsDifferentSizeTest());
    affirm(chunkyStringEqualsSameSizeTest());
    affirm(chunkyStringEqualsDiffOrderTest());
    affirm(insertEmptyTest());
    affirm(insertFrontBackTest());
    affirm(insertBetweenOneChunkTest());
    affirm(insertSpillOverChunkTest());
    affirm(eraseToEmpty());
    affirm(eraseWithinChunk());
    affirm(eraseMultipleChunks());
    affirm(chunkyLessThanEmptyTest());
    affirm(chunkyLessThanEasyTest());
    affirm(chunkyLessThanHardTest());
    affirm(operatorPlusEqualEmptyTest());
    affirm(operatorPlusEqualOntoEmptyTest());
    affirm(operatorPlusEqualTest());
    affirm(outputOperatorTest());
    affirm(correctUtilizationPushBackTest());
    affirm(correctUtilizationInsertTest());
    affirm(correctUtilizationEraseTest());
    affirm(correctUtilizationInsertEraseTest());
    affirm(correctUtilizationInsertEraseTest2());
    affirm(copyConstructorTest());
    affirm(correctUtilizationInsertEraseTest3());
    affirm(operatorPlusEqualToItselfTest());



    if (alltests.summarize(true)) {
        return 0;       // Error code of 0 == Success!
    } else {
        return 2;       // Arbitrarily chosen exit code of 2 means tests
                        // failed.
    }
}

/* (Junk to make emacs use Stroustrup-style indentation)
 * Local Variables:
 * c-file-style: "stroustrup"
 * End:
 */
