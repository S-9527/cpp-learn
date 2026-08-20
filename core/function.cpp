#include <iostream>

int maximum(int x, int y, int z);
double cube(double side);

int main() {
  std::cout << "Enter three integer values: ";
  int int1, int2, int3;
  std::cin >> int1 >> int2 >> int3;

  std::cout << "The maximum integer value is: " << maximum(int1, int2, int3)
            << '\n';

  double sideValue;
  std::cout << "Enter the side length of your cube: ";
  std::cin >> sideValue;

  std::cout << "Volum of cobe with side " << sideValue << " is "
            << cube(sideValue) << "\n";
  return 0;
}

int maximum(int x, int y, int z) {
  int maximumValue{x};

  if (y > maximumValue) {
    maximumValue = y;
  }

  if (z > maximumValue) {
    maximumValue = z;
  }

  return maximumValue;
}

inline double cube(double side) { return side * side * side; }
