#include <array>
#include <format>
#include <iostream>

int main() {
  constexpr std::array frequencies{0, 0, 0, 0, 0, 0, 1, 2, 4, 2, 1};

  for (int i{0}; const int& frequency : frequencies) {
    if (i < 10) {
      std::cout << std::format("{:02d}-{:02d}: ", i * 10, (i * 10) + 9);
    } else {
      std::cout << std::format("{:>5d}: ", 100);
    }

    ++i;

    for (int stars{0}; stars < frequency; ++stars) {
      std::cout << "*";
    }

    std::cout << "\n";
  }

  return 0;
}
