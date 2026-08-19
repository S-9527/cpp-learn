#include <cmath>
#include <format>
#include <iostream>

int main() {
  double principal{1000.00};
  double rate{0.05};

  std::cout << std::format("Initial principal: {:>7.2f}\n", principal)
            << std::format("    Interest rate: {:>7.2f}\n", rate);

  std::cout << std::format("\n{}{:>20}\n", "Year", "Amount on deposit");

  for (int year{1}; year <= 10; ++year) {
    double amount{principal * std::pow(1.0 + rate, year)};
    std::cout << std::format("{:>4d}{:>20.2f}\n", year, amount);
  }
}
