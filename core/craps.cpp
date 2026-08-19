#include <format>
#include <iostream>
#include <random>

int rollDice();

int main() {
  enum class Status { keppRolling, won, lost };

  int myPoint{0};
  Status gameStatus{Status::keppRolling};

  switch (const int sumOfDice{rollDice()}) {
    case 7:
    case 11:
      gameStatus = Status::won;
      break;
    case 2:
    case 3:
    case 12:
      gameStatus = Status::lost;
      break;
    default:
      myPoint = sumOfDice;
      std::cout << std::format("Point is {}\n", myPoint);
      break;
  }

  while (Status::keppRolling == gameStatus) {
    if (const int sumOfDice{rollDice()}; sumOfDice == myPoint) {
      gameStatus = Status::won;
    } else if (sumOfDice == 7) {
      gameStatus = Status::lost;
    }
  }

  if (Status::won == gameStatus) {
    std::cout << "Player win\n";
  } else {
    std::cout << "Player loses\n";
  }

  return 0;
}

int rollDice() {
  static std::random_device rd;
  static std::default_random_engine engine{rd()};
  static std::uniform_int_distribution randomDie{1, 6};

  const int die1{randomDie(engine)};
  const int die2{randomDie(engine)};
  const int sum{die1 + die2};

  std::cout << std::format("Player rolled {} + {} = {} \n", die1, die2, sum);

  return sum;
}
