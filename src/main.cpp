#include "myproject/myproject.h"
#include <fmt/format.h>
#include <iostream>

int main() {
  fmt::print("{}\n", myproject::greet("World"));
  fmt::print("Formatted: {:>10}\n", 42);
  fmt::print("Hex: {:#x}\n", 255);
  return 0;
}
