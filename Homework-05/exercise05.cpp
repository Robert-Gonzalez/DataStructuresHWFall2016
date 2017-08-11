#include <random>
#include <iostream>
#include <cassert>
#include <unistd.h>
#include "intlist.hpp"

using std::endl;
using std::cout;
using std::numeric_limits;

/* An asymptotically-efficient sorting algorithm 
   for sorting numbers in the range (0, biggest possible int).
   
   Note: We *DO NOT* recommend you run this on your own computer.  If you
         want to run it on knuth, you need to type
         
                ulimit -v 8650752
                
         beforehand to increase the allowable memory use to 8.25 GB.
*/

int main(int argc, char* argv[])
{
    assert(argc == 2);              // We expect one command-line argument,  
    const int N = atoi(argv[1]);    // an integer holding the problem size.
    cout << "Problem Size: " << N << endl;

    IntList myList;

    // The biggest possible int on our system...
    size_t biggestNumberAllowed = numeric_limits<int>::max();

    // Set up some stuff for generating random numbers
    std::random_device r;
    std::default_random_engine randomMaker(r());
    std::uniform_int_distribution<int> uniformDist(0, biggestNumberAllowed);

    // Push n (pseudo-)randomly-generated ints to myList
    for (int i=0; i < N; ++i) {
        myList.push_back(uniformDist(randomMaker));
    }

    size_t ARRAY_SIZE = size_t(biggestNumberAllowed) + 1;
    // Initialize our count array to be all zeroes.
    int* count = new int[ARRAY_SIZE];
    for (int* i = count; i != count + ARRAY_SIZE; ++i) {
        *i = 0;
    }

    // Calculate counts
    for (IntList::iterator i=myList.begin(); i != myList.end(); ++i) {
        ++count[*i];
    }

    // Print the elements of myList in ascending order
    for (size_t i=0; i < biggestNumberAllowed; ++i) {
        for (int j=0; j < count[i]; ++j) {
            cout << i << endl;
        }
    }
    
    return 0;
}
