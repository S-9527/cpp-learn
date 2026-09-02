#include <array>
#include <format>
#include <iostream>

int main() {
  constexpr std::array responses{1, 2, 5, 4, 3, 5, 2, 1, 3, 1, 4, 3, 3, 3, 2, 3, 3, 2, 2, 5};

  constexpr size_t frequencySize{6};
  std::array<int, frequencySize> frequency{};

  for (const int& response : responses) {
    ++frequency.at(response);
  }

  std::cout << std::format("{},{:>12}\n", "Rating", "Frequency");

  for (size_t rating{1}; rating < frequency.size(); ++rating) {
    std::cout << std::format("{:>6}{:>12}\n", rating, frequency.at(rating));
  }

  return 0;
}
