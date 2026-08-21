#include <iostream>

int boxVolume(int length = 1, int width = 1, int height = 1);

int main() {
  std::cout << "The default box volume is: " << boxVolume();

  std::cout << "\n\nThe volume of a box with length 10,\n"
            << "width 1 and height 1 is: " << boxVolume(10);

  std::cout << "\n\nThe volume of a box with length 10,\n"
            << "width 5 and height 1 is: " << boxVolume(10, 5);

  std::cout << "\n\nThe volume of a box with length 10,\n"
            << "width 5 and height 2 is: " << boxVolume(10, 5, 2) << '\n';
}

int boxVolume(int length, int width, int height) {
  return length * width * height;
}
