/**
 * \file treeset-string-test.cpp
 * \author hawk and reindeer
 *
 * \brief Test suite that checks basic functions on a tree set
 *        templated with a string
 */

#include <ostream> // For std::ostream
#include <cstddef>
#include <iostream>
#include "signal.h" // For signal
#include "unistd.h" // For alarm
#include <string>
#include "treeset.hpp"

template class TreeSet<string>;

#include "testing-logger.hpp"

/**
*
* \brief Checks to see if the class templates properly
* and that all the default statistics and data are correct
*
*/
bool defaultConstructionTest()
{
     // Set up the TestingLogger object
    TestingLogger log{"default construction test"};

    string testStr = "Hello World!";
    TreeSet<string> stringSet;

    affirm(stringSet.size() == 0);
    affirm(stringSet.height() == -1);
    affirm(!stringSet.exists(testStr));

    return log.summarize();
}

/**
*
* \brief This test checks to make sure the hashset resizes properly
* and keeps track of allocations properly.
*
*/

bool insertSimpleTest()
{
    // Set up the TestingLogger object
    TestingLogger log{"resize simple test"};


    string testStr1 = "aaa";
    string testStr2 = "aab";
    string testStr3 = "aba";
    string testStr4 = "baa";

    // Set up hash set for testing
    TreeSet<string> stringSet;

    stringSet.insert(testStr1);

    // Ensure that the table has the correct
    // size and number of buckets as
    // well as the correct statistics
    affirm(stringSet.size() == 1);
    affirm(stringSet.exists(testStr1));

    // We can't check for collisions after this point
    // becuase we can't be sure what our hash function
    // will hash our strings to.

    stringSet.insert(testStr2);


    affirm(stringSet.size() == 2);
    affirm(stringSet.exists(testStr2));


    stringSet.insert(testStr3);


    affirm(stringSet.size() == 3);
    affirm(stringSet.exists(testStr3));

    stringSet.insert(testStr4);


    stringSet.showStatistics(cout);

    return log.summarize();

}






// Called if the test runs too long.
static void timeout_handler(int)
{
    // We go super-low-level here, because we can't trust anything in
    // the C/C++ library to really be working right.
    write(STDERR_FILENO, "Timeout occurred!\n", 18);
    abort();
}




/****************************
 * Boilerplate main function
 * **************************/





/// Run tests
int main(int argc, char** argv)
{
    // Initalize testing environment
    TestingLogger alltests{"All tests"};

    signal(SIGALRM, timeout_handler);   // Call this when the timer expires
    alarm(10);                          // set the timer at 10 seconds


    // Add calls to your tests here...
    affirm(defaultConstructionTest());
    affirm(insertSimpleTest());


    if (alltests.summarize(true)) {
        return 0;       // Error code of 0 == Success!
    } else {
        return 2;       // Arbitrarily chosen exit code of 2 means tests failed.
    }

}
