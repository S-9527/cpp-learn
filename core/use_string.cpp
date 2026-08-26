#include <iostream>
#include <string>

int main() {
  std::string s1{"happy"};
  std::string s2{" birthday"};
  std::string s3;

  std::cout << "s1 " << s1 << " length: " << s1.length();
  std::cout << "\ns2 " << s2 << " length: " << s2.length();
  std::cout << "\ns3 " << s3 << "length: " << s3.length();

  std::cout << "\nThe result of compare s2 to s1: " << std::boolalpha << "\ns2 == s1 " << (s2 == s1)
            << "\ns2 != s1 " << (s2 != s1);

  std::cout << "\nTesting s3.empty(): \n";
  if (s3.empty()) {
    std::cout << "s3 is empty; assigning to s3;\n";
    s3 = s1 + s2;
    std::cout << "s3: " << s3;
  }

  return 0;
}
