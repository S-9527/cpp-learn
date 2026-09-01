#include <array>
#include <format>
#include <iostream>

int main() {
  std::array items{1, 2, 3, 4, 5};

  std::cout << "items before modification: ";
  for (const int& item : items) {
    std::cout << std::format("{} ", item);
  }

  for (int& item : items) {
    item *= 2;
  }

  std::cout << "\nitems after modification: ";
  for (int& item : items) {
    std::cout << std::format("{} ", item);
  }

  std::cout << "\ncalculating a running total of items' values: \n";
  for (int runningTotal{0}; const int& item : items) {
    runningTotal += item;
    std::cout << std::format("item: {}; runningTotal: {}\n", item, runningTotal);
  }

  return 0;
}
