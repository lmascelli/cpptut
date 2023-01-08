#include <iostream>
#include "include/rational.hpp"
#include "include/polynomial.hpp"
using namespace std;

int main(int argc, char *argv[])
{
  polynomial p {1, 3, 5, 9};
  cout << p << endl;
  p = {3, 4, 1, 4, 5};
  cout << p << endl;
  return 0;
}
