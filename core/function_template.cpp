#include <iostream>

#include "maximum.h"

int main() {
  std::cout << "Input three integer values: ";
  int int1, int2, int3;
  std::cin >> int1 >> int2 >> int3;

  std::cout << "The maximum integer value is: " << maximum(int1, int2, int3);

  std::cout << "\n\nInput three double values: ";
  double double1, double2, double3;
  std::cin >> double1 >> double2 >> double3;

  std::cout << "The maximum double value is: " << maximum(double1, double2, double3);

  std::cout << "\n\nInput three characters: ";
  char char1, char2, char3;
  std::cin >> char1 >> char2 >> char3;

  std::cout << "The maximum character value is: " << maximum(char1, char2, char3) << '\n';
}
