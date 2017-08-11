#include <iostream>
#include <vector>

using std::cout;
using std::endl;

bool checkRange(int value, int lowerBound, int upperBound) { 
  if (value >= lowerBound && value <= upperBound) {
    return true;
  }
  return false;
}


int main() {
  int smallestOk = -3;
  int biggestOk = 3;

  int currentValue = 1;

  bool valueInRange = checkRange(currentValue, smallestOk, biggestOk);

  if (valueInRange) {
    cout << "value is in acceptable range" << endl;
  }

  return 0;
}
