#include <algorithm>
#include <array>
#include <format>
#include <iostream>
#include <string>

int main() {
  using namespace std::string_literals;

  std::array colors{"red"s, "orange"s, "yellow"s, "green"s, "blue"s, "indigo"s, "violet"s};

  std::cout << "Unsorted colors array:\n  ";
  for (const std::string& color : colors) {
    std::cout << std::format("{} ", color);
  }

  std::sort(std::begin(colors), std::end(colors));

  std::cout << "\nSorted colors array:\n  ";
  for (const std::string& color : colors) {
    std::cout << std::format("{} ", color);
  }

  bool found{std::binary_search(std::begin(colors), std::end(colors), "indigo")};
  std::cout << std::format("\n\n\"indigo\" {} found in colors array\n", found ? "was" : "was not");

  found = std::binary_search(std::begin(colors), std::end(colors), "cyan");
  std::cout << std::format("\"cyan\" {} found in colors array\n", found ? "was" : "was not");
  return 0;
}
