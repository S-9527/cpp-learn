#include <iomanip>
#include <iostream>

int main() {
  double total{0.0};
  int gradeCounter{0};

  std::cout << "Enter grade or -1 to quit: ";
  int grade;
  std::cin >> grade;
  while (grade != -1) {
    total = total + grade;
    gradeCounter = gradeCounter + 1;
    std::cout << "Enter grade or -1 to quit: ";
    std::cin >> grade;
  }

  if (gradeCounter != 0) {
    double average{total / gradeCounter};
    std::cout << "\nTotal of the " << gradeCounter << " grades entered is " << total;
    std::cout << std::setprecision(2) << std::fixed;
    std::cout << "\nClass average is " << average;
  } else {
    std::cout << "No grades were entered\n";
  }

  return 0;
}
