/**
 * \file exchange.hpp
 * \author Robert Gonzalez and Finn Southerland
 *
 * \brief Implements exchange
 */

#include "exchange.hpp"
#include <string>
using namespace std;

void exchange(string &s1, string &s2) {
    string temp = s1;
    s1 = s2;
    s2 = temp;
}

