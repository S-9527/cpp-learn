#include <iostream>

int squareByValue(int number);
void squareByReference(int& numberRef);

int main() {
  int x{2};
  int z{2};

  std::cout << "x = " << x << " before squareByValue\n";
  std::cout << "Value returned by squareByValue: " << squareByValue(x) << '\n';
  std::cout << "x = " << x << " after squareByValue\n\n";

  // demonstrate squareByReference
  std::cout << "z = " << z << " before squareByReference\n";
  squareByReference(z);
  std::cout << "z = " << z << " after squareByReference\n";
}

int squareByValue(int number) {
  return number *= number;
}

void squareByReference(int& numberRef) {
  numberRef *= numberRef;
}
