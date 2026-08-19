#include <format>
#include <iostream>

int main() {
  int total{0};

  for (int number{2}; number <= 20; number += 2) {
    total += number;
  }

  std::cout << std::format("sum is {}", total);

  return 0;
}
