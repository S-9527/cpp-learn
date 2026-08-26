#include <format>
#include <iostream>

int main() {
  double total{0.0};
  int gradeCounter{0};
  int aCount{0};
  int bCount{0};
  int cCount{0};
  int dCount{0};
  int fCount{0};

  std::cout << "Enter the integer grades in the range 0-100.\n"
            << "Type the end-of-file indicator to terminate input:\n"
            << "   On UNIX/Linux/macOS type <Ctrl> d then press Enter\n"
            << "   On Windows type <Ctrl> z then press Enter\n";

  int grade;

  while (std::cin >> grade) {
    total += grade;
    ++gradeCounter;

    switch (grade / 10) {
      case 9:
      case 10:
        ++aCount;
        break;

      case 8:
        ++bCount;
        break;

      case 7:
        ++cCount;
        break;

      case 6:
        ++dCount;
        break;

      default:
        ++fCount;
        break;
    }
  }

  std::cout << "\nGrade Report:\n";

  if (gradeCounter != 0) {
    double average{total / gradeCounter};

    std::cout << std::format("Total of the {} grades entered is {}\n", gradeCounter, total)
              << std::format("Class average is {:.2f}\n\n", average)
              << "Summary of student's grades:\n"
              << std::format("A: {}\nB: {}\nC: {}\nD: {}\nF: {}\n", aCount, bCount, cCount, dCount,
                             fCount);
  } else {
    std::cout << "No grades were entered\n";
  }
}
