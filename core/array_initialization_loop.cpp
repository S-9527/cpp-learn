#include <array>
#include <format>
#include <iostream>

int main() {
  std::array<int, 5> values; // values is an array of 5 int values

  // initialize elements of array values to 0
  for (size_t i{0}; i < values.size(); ++i) {
    values[i] = 0; // set element at location i to 0
  }

  std::cout << std::format("{:>7}{:>10}\n", "Element", "Value");

  // output each array element's value
  for (size_t i{0}; i < values.size(); ++i) {
    std::cout << std::format("{:>7}{:>10}\n", i, values[i]);
  }

  std::cout << std::format("\n{:>7}{:>10}\n", "Element", "Value");

  // access elements via the at member function
  for (size_t i{0}; i < values.size(); ++i) {
    std::cout << std::format("{:>7}{:>10}\n", i, values.at(i));
  }

  // accessing an element outside the array's bounds with at
  values.at(10); // throws an exception
}
