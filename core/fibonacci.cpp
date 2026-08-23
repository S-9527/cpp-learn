#include <format>
#include <iostream>

long fibonacci(long number);

int main() {
  for (int counter{0}; counter <= 10; ++counter) {
    std::cout << std::format("fibonacci({}) = {}\n", counter,
                             fibonacci(counter));
  }

  std::cout << std::format("\nfibonacci(20) = {}\n", fibonacci(20))
            << std::format("fibonacci(30) = {}\n", fibonacci(30))
            << std::format("fibonacci(35) = {}\n", fibonacci(35));
}

long fibonacci(long number) {
  if ((0 == number) || (1 == number)) {
    return number;
  }

  return fibonacci(number - 1) + fibonacci(number - 2);
}
