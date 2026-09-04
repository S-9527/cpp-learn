#include <array>
#include <format>
#include <iostream>
#include <numeric>
#include <ranges>

int main() {
  auto showValues{[](auto& values, const std::string& message) {
    std::cout << std::format("{}: ", message);

    for (const auto& value : values) {
      std::cout << std::format("{} ", value);
    }

    std::cout << "\n";
  }};

  auto values1{std::views::iota(1, 11)};
  showValues(values1, "Generate integers 1-10");

  auto values2{values1 | std::views::filter([](const auto& x) { return x % 2 == 0; })};
  showValues(values2, "Filtering even integers");

  auto values3{values2 | std::views::transform([](const auto& x) { return x * x; })};
  showValues(values3, "Mapping even integers to squares");

  auto values4{values1 | std::views::filter([](const auto& x) { return x % 2 == 0; }) |
               std::views::transform([](const auto& x) { return x * x; })};

  showValues(values4, "Squares of even integers");

  std::cout << std::format("Sum squares of even integers 2-10: {}\n",
                           std::accumulate(std::begin(values4), std::end(values4), 0));

  constexpr std::array numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto values5{numbers | std::views::filter([](const auto& x) { return x % 2 == 0; }) |
               std::views::transform([](const auto& x) { return x * x; })};
  showValues(values5, "Squares of even integers in array numbers");

  return 0;
}
