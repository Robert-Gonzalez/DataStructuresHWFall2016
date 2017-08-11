#include <iostream>

using std::cout;
using std::endl;

double addTwoNumbers(double x, double y) {
  return x + y;
}

int main() {
  double x = 3.14;
  double y = 2.71;

  double z = addTwoNumbers(x, y);

  cout << "The sum is" << z << endl;

  return 0;
}
