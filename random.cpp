#include <iostream>
#include <random>

int main()
{
  std::default_random_engine engine{};

  std::uniform_int_distribution randomDie{1, 6};

  for (int counter{1}; counter <= 10; ++counter)
  {
    std::cout << randomDie(engine) << " ";
  }

  std::cout << '\n';
}
