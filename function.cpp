#include <iostream>

int maximum(int x, int y, int z);

int main()
{
  std::cout << "Enter three integer values: ";
  int int1, int2, int3;
  std::cin >> int1 >> int2 >> int3;

  std::cout << "The maximum integer value is: "
            << maximum(int1, int2, int3) << '\n';
  return 0;
}

int maximum(int x, int y, int z)
{
  int maximumValue{x};

  if (y > maximumValue)
  {
    maximumValue = y;
  }

  if (z > maximumValue)
  {
    maximumValue = z;
  }

  return maximumValue;
}
