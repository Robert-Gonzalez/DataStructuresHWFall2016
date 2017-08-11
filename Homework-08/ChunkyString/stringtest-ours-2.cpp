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
#include <iostream>
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


// Testing functions


/**
 * \brief Checks the constructor by making a new ChunkyString and
 *         making sure the size is zero
 */
bool constructorTest()
{
    // Set up the TestingLogger object
    TestingLogger log{"constructor test"};

    TestingString c;
    affirm(c.size() == 0);
    
    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

// Testing functions

/**
 * \brief Checks the size function by making a new ChunkyString adding three
 *         characters and making sure the size is three
 */
bool sizeTest()
{
    // Set up the TestingLogger object
    TestingLogger log{"size test"};

    TestingString c;

    c.push_back('a');
    c.push_back('b');
    c.push_back('c');
    affirm(c.size() == 3);
    
    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/**
 * \brief Checks the equality operator for ChunkyString by making two 
 *        ChunkyStrings with identical characters and checking if 
 *        they are equal
 */
bool comparisonOpTest()
{
    // Set up the TestingLogger object
    TestingLogger log{"comparison operator test"};


    TestingString c;
    TestingString d;

    c.push_back('a');
    d.push_back('a');

    

    affirm(c == d);
    TestingString s;
    
    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/**
 * \brief Checks the inequality operator for ChunkyString by making two 
 *        ChunkyStrings with different characters and checking if they
 *        are not equal
 */
bool notEqualsTest()
{
    // Set up the TestingLogger object
    TestingLogger log{"not equals operator test"};


    TestingString c;
    TestingString d;

    c.push_back('a');
    d.push_back('b');

    

    affirm(c != d);
    
    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/**
 * \brief Checks the less than operator for ChunkyString by making two 
 *        ChunkyStrings with different characters and checking the appropriate
 *        one is less than
 */
bool lessThanTest()
{
    // Set up the TestingLogger object
    TestingLogger log{"less than operator test"};


    TestingString c;
    TestingString d;

    c.push_back('a');
    c.push_back('z');
    d.push_back('b');
    d.push_back('c');

    

    affirm(c < d);
    TestingString s;
    
    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/**
 * \brief Checks the utilization method for ChunkyString by making a
 *        ChunkyString with and checking if the utilization is above
 *        the required threshold
 */
bool utiTest()
{
    // Set up the TestingLogger object
    TestingLogger log{"uti test"};

    TestingString c;
    c.push_back('a');
    c.push_back('b');
    c.push_back('c');
    c.push_back('d');
    c.push_back('e');
    c.push_back('f');
    c.push_back('g');
    c.push_back('h');


    affirm(c.utilization() > .5);
    
    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/**
 * \brief Checks the push back method for ChunkyString by making a ChunkyString
 *        and calling the method to add character and then checking if
 *        the size changed
 */
bool pushBackTest()
{
    // Set up the TestingLogger object
    TestingLogger log{"push_back test"};

    TestingString c;

    c.push_back('a');
    c.push_back('b');

    affirm(c.size() == 2);
    
    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/**
 * \brief Checks the insert method for ChunkyString by making a ChunkyString,
 *        calling insert and cheking if the size changed and the
 *        iterator now points to the inserted character.
 */
bool insertTest()
{
    // Set up the TestingLogger object
    TestingLogger log{"insert test"};

    TestingString c;

    c.push_back('a');
    c.push_back('b');
    c.push_back('c');
    c.push_back('d');
    c.push_back('e');
    c.push_back('f');
    c.push_back('g');
    c.push_back('h');

    TestingString::iterator start = c.begin();

    TestingString::iterator newIterator = c.insert(start, 'z');

    affirm(c.size() == 9);
    affirm(*newIterator == 'z');
    checkUtilization(c, 2);
    
    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/**
 * \brief Checks the erase method for ChunkyString by making a ChunkyStrings, 
 *        calling the method and checking if the size changed and
 *        the iterator now points to the character after the erased one.
 */
bool eraseTest()
{
    // Set up the TestingLogger object
    TestingLogger log{"erase test"};

    TestingString c;

    c.push_back('a');
    c.push_back('b');
    c.push_back('c');
    c.push_back('d');
    c.push_back('e');
    c.push_back('f');
    c.push_back('g');
    c.push_back('h');

    TestingString::iterator start = c.begin();

    TestingString::iterator newIterator = c.erase(start);

    affirm(c.size() == 7);
    affirm(*newIterator == 'b');
    checkUtilization(c, 4);

    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/**
 * \brief Checks the plus equals operator for ChunkyString by making a 
 *        ChunkyStrings calling the operator and making sure the 
 *        size changed
 */
bool plusEqualsTest()
{
    // Set up the TestingLogger object
    TestingLogger log{"plus equals test"};

    TestingString c;
    TestingString d;

    c.push_back('a');
    c.push_back('b');
    c.push_back('c');
    c.push_back('d');
    d.push_back('e');
    d.push_back('f');
    d.push_back('g');
    d.push_back('h');

    c += d;

    affirm(c.size() == 8);
    checkUtilization(c, 2);

    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/**
 * \brief Checks the display operator for ChunkyString by making a ChunkyStrings
 *        calling the operator to a ostringstream and making sure the
 *        right thing is printed
 */
bool displayTest()
{
    // Set up the TestingLogger object
    TestingLogger log{"display test"};

    TestingString c;

    c.push_back('a');
    c.push_back('b');
    c.push_back('c');
    c.push_back('d');
    c.push_back('e');
    c.push_back('f');
    c.push_back('g');
    c.push_back('h');

    std::ostringstream foo;
    foo << c;

    std::cout << foo.str() << '\n';


    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/**
 * \brief Checks the begin method for ChunkyString by making a ChunkyStrings
 *        calling the method and making sure iterator points to the
 *        beginning of the ChunkyString
 */
bool beginTest()
{
    // Set up the TestingLogger object
    TestingLogger log{"begin test"};

    TestingString c;

    c.push_back('a');
    c.push_back('b');
    c.push_back('c');
    c.push_back('d');
    c.push_back('e');
    c.push_back('f');
    c.push_back('g');
    c.push_back('h');

    TestingString::iterator start = c.begin();

    affirm(*start == 'a');

    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}



/**
 * \brief Checks the inegualtiy operator for iterator by making two iterators
 *        for two ChunkyStrings and making sure they are not equal.
 */
bool itInequality()
{
    // Set up the TestingLogger object
    TestingLogger log{"iterator inequality test"};

    TestingString c;
    TestingString d;

    c.push_back('a');
    c.push_back('b');
    c.push_back('c');
    c.push_back('d');
   

    d.push_back('a');
    d.push_back('b');
    d.push_back('c');
    d.push_back('d');

    TestingString::iterator startc = c.begin();
    TestingString::iterator startc2 = c.begin();
    TestingString::iterator startd = d.begin();

    affirm(startc == startc2);
    affirm(startc != startd);

    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/**
 * \brief Checks the increment operator for iterators by making an iterator
 *        calling the operator and making sure the iterator now points to the
 *        correct character
 */
bool iteratorIncTest()
{
    // Set up the TestingLogger object
    TestingLogger log{"iterator increment and decrement test"};

    TestingString c;

    c.push_back('a');
    c.push_back('b');
    c.push_back('c');
    c.push_back('d');
   

    TestingString::iterator start = c.begin();
    ++start;
    ++start;

    affirm(*start == 'c');

    --start;

    affirm(*start == 'b');

    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/**
 * \brief Checks dereference operator for iterator by making an iterator,
 *        calling the operator and making sure the it returns the character
          the iterator is pointing to
 */
bool iteratorDrefTest()
{
    // Set up the TestingLogger object
    TestingLogger log{"iterator dereference test"};

    TestingString c;

    c.push_back('a');

    TestingString::iterator start = c.begin();

    affirm(*start == 'a');


    // Print a summary of the all the affirmations and return true
    // if they were all successful.
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
    affirm(exampleTest());
    affirm(constructorTest());
    affirm(sizeTest());
    affirm(comparisonOpTest());
    affirm(notEqualsTest());
    affirm(lessThanTest());
    affirm(utiTest());
    affirm(pushBackTest());
    affirm(insertTest());
    affirm(eraseTest());
    affirm(plusEqualsTest());
    affirm(displayTest());
    affirm(itInequality());
    affirm(iteratorIncTest());
    affirm(iteratorDrefTest());

    if (alltests.summarize(true)) {
        return 0;       // Error code of 0 == Success!
    } else {
        return 2;       // Arbitrarily chosen exit code of 2 means tests failed.
    }
}

/* (Junk to make emacs use Stroustrup-style indentation)
 * Local Variables:
 * c-file-style: "stroustrup"
 * End:
 */
