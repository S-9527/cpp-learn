#include <array>
#include <format>
#include <iostream>

int main() {
  constexpr size_t arraySize{5};
  std::array<int, arraySize> values{};

  for (int i{0}; i < values.size(); i++) {
    values.at(i) = 2 + 2 * i;
  }

  for (const int& value : values) {
    std::cout << std::format("{} ", value);
  }

  return 0;
}
