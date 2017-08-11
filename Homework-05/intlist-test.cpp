/**
 * \file intlist-test.cpp
 * \authors CS 70 Starter Code
 * \brief The program unit tests the IntList class.
 *
 * \details Part of the CS 70 IntList assignment.
 */

/* Note: In testing, it's always a good idea to #include the header you're
 *       testing without including anything else beforehand.  That way, you
 *       won't accidentally depend on something being included for your
 *       header to compile.
 */
#include "intlist.hpp"
#include "testing-logger.hpp"

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <list>

#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;


///////////////////////////////////////////////////////////
//  TESTING
///////////////////////////////////////////////////////////

// ISSUE 0 TESTS

/** \brief Test default constructor for IntLists
 */
bool defaultConstructorTest()
{
    // Set up the TestingLogger object
    TestingLogger log{"default constructor"};

    // Set up for your test
    IntList myList;

    // Add checks for things that should be true. 
    affirm(myList.size() == 0);

    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

// ISSUE 1 TESTS
// Add tests here for push_front, begin, and the dereference operator.

/** \brief Test push_front
 *  \detail Describe your test here...
 *  pushFrontTest() checks to see if pushing elements onto the front of the IntList increase
 *  the size of the list. We have to check the size rather than the front element because front_
 *  is a private member with no getter.
 */


bool pushFrontTest()
{
    // Set up the TestingLogger object
    TestingLogger log{"push_front"};

    // Set up for your test
    IntList myList;

    // Fill in the test content here...

    myList.push_front(2);

    affirm(myList.size() == 1);
    
    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}


/** \brief Test begin
 *  \detail Describe your test here...
 *  beginTest() checks to see if running begin() on an array myList
 *  does return an interator who should currently point at the front
 *  element of myArray that we just pushed to the front.
 */
bool beginTest()
{
    // Set up the TestingLogger object
    TestingLogger log{"begin"};

    // Set up for your test
    IntList myList;

    // Fill in the test content here...

    myList.push_front(2);

    IntList::iterator firstElement = myList.begin();

    affirm(*firstElement == 2);
    
    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/** \brief Test op*
 *  \detail Describe your test here...
 *  Our derefencene operator returns a reference to the int value of
 *  the current elemnt in IntList.
 */
bool dRefOpTest()
{
    // Set up the TestingLogger object
    TestingLogger log{"dereference op"};

    // Set up for your test
    IntList myList;

    // Fill in the test content here...

    myList.push_front(2);

    IntList::iterator firstElement = myList.begin();
    

    affirm(*firstElement == 2);
    
    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

// Some more tests should go here...

// ISSUE 2 TESTS
// Add tests here for pop_front, ~IntList, and empty

/** \brief Test pop_front
 *  \detail Describe your test here...
 *  pushFrontTest() checks to see if removing an element from the front of the IntList decreases
 *  the size of the list. We have to check the size rather than the front element because front_
 *  is a private member with no getter.
 */


bool popFrontTest()
{
    // Set up the TestingLogger object
    TestingLogger log{"pop_front"};

    // Set up for your test
    IntList myList;

    // Fill in the test content here...

    myList.push_front(2);

    int first = myList.pop_front();

    affirm(myList.size() == 0);
    affirm(first == 2);
    
    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

 /** \brief Test emptyTest
 *  \detail Describe your test here...
 *  emptyTest() checks to see if the list is empty after we insert an element.
 *  We do this by checking the boolean value that is returned.
 */

bool emptyTest()
{
    // Set up the TestingLogger object
    TestingLogger log{"empty"};

    // Set up for your test
    IntList myList;

    // Fill in the test content here...
    affirm(myList.empty() == true);

    myList.push_front(2);

    affirm(myList.empty() == false);
    
    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

// ISSUE 3 TESTS
// Add tests here for end and push_back...


/** \brief Test push_back
 *  \detail Describe your test here...
 *  pushBackTest() checks to see if pushing elements onto the front of the IntList increase
 *  the size of the list. We have to check the size rather than the front element because front_
 *  is a private member with no getter.
 */

bool pushBackTest()
{
    // Set up the TestingLogger object
    TestingLogger log{"push_back"};

    // Set up for your test
    IntList myList;

    // Fill in the test content here...

    myList.push_back(2);
    myList.push_back(3);

    affirm(myList.size() == 2);
    
    
    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/** \brief Test end
 *  \detail Describe your test here...
 *  endTest() checks to see if running end() on an array myList
 *  does return an interator who should have a null pointer to an
 *  element. We check this by seeing if the returned pointer dereferenced
 *  is not a known value.
 */

/*
bool endTest()
{
    // Set up the TestingLogger object
    TestingLogger log{"end"};

    // Set up for your test
    IntList myList;

    // Fill in the test content here...

    myList.push_front(2);

    IntList::iterator last = myList.end();

    *last;
    
    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}*/

// ISSUE 4 TESTS
// Add tests here for Iterator ++ and ==

/** \brief Test insert_after
 *  \detail Describe your test here...
 *  insertAfterTest() checks to see if inserting elements after a
 *  specified element inbthe IntList increases the size of the list. 
 *  We have to check the size rather than the front element because front_
 *  is a private member with no getter.
 */

bool insertAfterTest()
{
    // Set up the TestingLogger object
    TestingLogger log{"insert_after"};

    // Set up for your test
    IntList myList;

    // Fill in the test content here...

    myList.push_front(2);
    myList.push_front(3);

    IntList::iterator start = myList.begin();

    myList.insert_after(start, 4);

    affirm(myList.size() == 3);
    
    
    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/** \brief Test op++
 *  \detail Describe your test here...
 *  Our preincremnt operator returns an iterator which points to the next thing in the list
 *  We test this using the dereference operator
 */
bool preincTest()
{
    // Set up the TestingLogger object
    TestingLogger log{"preincrement operator"};

    // Set up for your test
    IntList myList;

    // Fill in the test content here...

    myList.push_front(2);
    myList.push_front(3);

    IntList::iterator start = myList.begin();

    ++start;

    affirm(*start == 2);
    
    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/** \brief Test op==
 *  \detail Describe your test here...
 *  Our equality operator returns true if the iterators point to the same element.
 *  We test this using the dereference operator
 */
bool equalityOpTest()
{
    // Set up the TestingLogger object
    TestingLogger log{"equality operator"};

    // Set up for your test
    IntList myList;

    // Fill in the test content here...

    myList.push_front(2);
    myList.push_front(3);

    IntList::iterator start = myList.begin();
    IntList::iterator start2 = myList.begin();

    affirm(*start == *start2);
    
    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

// ISSUE 5 TESTS
// Add tests here for IntList ==

/** \brief Test op==
 *  \detail Describe your test here...
 *  Our equality operator for IntLists returns true if the 
 *  lists have identical values for the same indecies of each list.
 *  We test this by creating two identical lists and one different list
 *  and comparing them to each other.
 */
bool equalityOpTestIntL()
{
    // Set up the TestingLogger object
    TestingLogger log{"equality operator for IntLists"};

    // Set up for your test
    IntList myList;
    IntList myList2;
    IntList myList3;

    // Fill in the test content here...

    myList.push_front(2);
    myList.push_front(3);

    myList2.push_front(2);
    myList2.push_front(3);

    myList3.push_front(2);

    

    affirm((myList == myList2) && (myList != myList3));
    
    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

// ISSUE 6 TESTS
// Add tests here for the IntList Copy constructor 

/** \brief Test copy constructor for IntLists
 */
bool copyConstructorTest()
{
    // Set up the TestingLogger object
    TestingLogger log{"copy constructor"};

    // Set up for your test
    IntList myList;

    myList.push_back(2);
    myList.push_back(3);

    IntList newList{myList};

    // Add checks for things that should be true. 
    affirm(myList == newList);
    affirm(newList.size() == myList.size());

    // Print a summary of the all the affirmations and return true
    // if they were all successful.
    return log.summarize();
}

/*
 * Test the IntList!
 */
int main(int, char**)
{
    TestingLogger alltests{"All tests"};
    
    affirm(defaultConstructorTest());

    // Add your new tests as new affirms here...
    
    affirm(pushFrontTest());

    affirm(beginTest());

    affirm(dRefOpTest());

    affirm(popFrontTest());

    affirm(emptyTest());

    //affirm(endTest());

    affirm(pushBackTest());

    affirm(insertAfterTest());

    affirm(preincTest());

    affirm(equalityOpTest());

    affirm(equalityOpTestIntL());

    affirm(copyConstructorTest());

    
    // Print a summary of the all the affirmations and exit the program.

    if (alltests.summarize(true)) {
        return 0;       // Error code of 0 == Success!
    } else {
        return 2;       // Arbitrarily chosen exit code of 2 means tests failed.
    }
}

/* Junk to make emacs use the right C++ style when editing this code:
 *   Local Variables:
 *   c-file-style: "stroustrup"
 *   End:
 */
