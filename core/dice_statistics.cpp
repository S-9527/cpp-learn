#include <array>
#include <format>
#include <iostream>
#include <random>

int main() {
  std::random_device rd;
  std::default_random_engine engine{rd()};
  std::uniform_int_distribution randomDie{1, 6};

  constexpr size_t arraySize{7};
  std::array<int, arraySize> frequency{};

  for (int roll{1}; roll <= 60'000'000; ++roll) {
    ++frequency.at(randomDie(engine));
  }

  std::cout << std::format("{}{:>13}\n", "Face", "Frequency");

  for (size_t face{1}; face < frequency.size(); ++face) {
    std::cout << std::format("{:>4}{:>13}\n", face, frequency.at(face));
  }

  return 0;
}
