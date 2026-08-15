# C++ 入门笔记：成绩统计与等级分布（使用 `switch` 和 EOF）

> 本笔记涵盖 `while` 循环与 `std::cin` 的流状态检测、`switch` 多分支选择、累加器与计数器、等级统计以及 `std::format` 格式化输出。

---

## 1. 完整代码示例

```cpp
#include <format>
#include <iostream>

int main()
{
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

  while (std::cin >> grade)
  {
    total += grade;
    ++gradeCounter;

    switch (grade / 10)
    {
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

  if (gradeCounter != 0)
  {
    double average{total / gradeCounter};

    std::cout << std::format("Total of the {} grades entered is {}\n",
                             gradeCounter, total)
              << std::format("Class average is {:.2f}\n\n", average)
              << "Summary of student's grades:\n"
              << std::format("A: {}\nB: {}\nC: {}\nD: {}\nF: {}\n",
                             aCount, bCount, cCount, dCount, fCount);
  }
  else
  {
    std::cout << "No grades were entered\n";
  }
}
```

---

## 2. 代码逐行解析

### 2.1 头文件
```cpp
#include <format>   // C++20 格式化输出
#include <iostream> // 标准输入输出
```
- `<format>` 提供 `std::format`，用于类型安全的字符串格式化。
- `<iostream>` 提供 `std::cin` 和 `std::cout`。

### 2.2 变量声明与初始化
```cpp
double total{0.0};        // 累加器（double 保留精度）
int gradeCounter{0};      // 有效成绩个数
int aCount{0}, bCount{0}, cCount{0}, dCount{0}, fCount{0}; // 各等级计数
```
- 所有计数器初始化为 0，确保统计准确。
- `total` 用 `double` 以便计算平均分时保留小数。

### 2.3 输入提示与 EOF 说明
```cpp
std::cout << "Enter the integer grades in the range 0-100.\n"
          << "Type the end-of-file indicator to terminate input:\n"
          << "   On UNIX/Linux/macOS type <Ctrl> d then press Enter\n"
          << "   On Windows type <Ctrl> z then press Enter\n";
```
- 告知用户如何结束输入（发送 EOF）。
- **EOF（End-Of-File）** 是一个信号，表示没有更多输入。在终端中：
  - Unix/Linux/macOS：`Ctrl + D`（行首）
  - Windows：`Ctrl + Z`（行首）然后回车

### 2.4 循环输入与统计
```cpp
int grade;
while (std::cin >> grade)
{
    total += grade;
    ++gradeCounter;
    // 等级统计...
}
```
- `std::cin >> grade` 返回 `std::cin` 对象本身，在布尔上下文中转换为 `true`（如果读取成功）或 `false`（如果失败或 EOF）。
- 循环持续读取，直到遇到 EOF 或无效输入（例如非数字字符）。
- 每次读取成功后累加并增加计数器。

### 2.5 `switch` 多分支等级统计
```cpp
switch (grade / 10)
{
case 9:
case 10:    // 90-100 → A
    ++aCount;
    break;
case 8:     // 80-89 → B
    ++bCount;
    break;
case 7:     // 70-79 → C
    ++cCount;
    break;
case 6:     // 60-69 → D
    ++dCount;
    break;
default:    // 0-59 → F
    ++fCount;
    break;
}
```
- `grade / 10` 是整数除法，将分数映射到 0~10 的整数（例如 85/10=8）。
- 多个 `case` 可以堆叠（如 `case 9:` 和 `case 10:` 都执行同一语句）。
- `default` 捕获所有未匹配的情况（包括 0-5 和非法大于 100 的值？但本程序假设输入合法在 0-100 之间）。
- `break` 防止执行后续分支。

### 2.6 输出报告与格式化
```cpp
if (gradeCounter != 0)
{
    double average{total / gradeCounter};
    std::cout << std::format("Total of the {} grades entered is {}\n",
                             gradeCounter, total)
              << std::format("Class average is {:.2f}\n\n", average)
              << "Summary of student's grades:\n"
              << std::format("A: {}\nB: {}\nC: {}\nD: {}\nF: {}\n",
                             aCount, bCount, cCount, dCount, fCount);
}
else
{
    std::cout << "No grades were entered\n";
}
```
- 先检查是否有成绩，避免除以零。
- 平均分使用 `total / gradeCounter`（double 除法）。
- `std::format` 的格式说明：
  - `{}` 按顺序替换参数。
  - `{:.2f}` 表示浮点数保留两位小数。
- 输出各等级人数。

---

## 3. 核心知识点

### 3.1 检测 EOF 的惯用法
- `while (std::cin >> variable)` 是标准做法，简洁地处理输入直到结束。
- 也可显式使用 `!std::cin.eof()` 但不够简洁。

### 3.2 `switch` 语句
- 用于基于整型或枚举值的多路分支。
- 每个 `case` 必须为常量表达式。
- 必须使用 `break` 跳出，否则会“穿透”到下一个 `case`。
- `default` 可选，处理所有未匹配的值。

### 3.3 整数除法的应用
- `grade / 10` 实现向下取整的十位划分，非常适合分级。
- 注意输入值需在合法范围内，否则可能出现意外等级。

### 3.4 `std::format` 的优势
- 类型安全：参数类型与占位符不匹配会编译错误。
- 可读性强：格式说明符类似 Python 的 f-string。
- 性能良好：通常优于流式输出。

---

## 4. 编译与运行

### 4.1 编译（需 C++20）
```bash
g++ -std=c++20 grade_stat.cpp -o grade_stat
```

### 4.2 运行示例
```
Enter the integer grades in the range 0-100.
Type the end-of-file indicator to terminate input:
   On UNIX/Linux/macOS type <Ctrl> d then press Enter
   On Windows type <Ctrl> z then press Enter
85
90
75
63
88
92
45
^Z   (Windows) 或 ^D (Linux)

Grade Report:
Total of the 7 grades entered is 538
Class average is 76.86

Summary of student's grades:
A: 3
B: 1
C: 1
D: 1
F: 1
```

---

## 5. 改进建议

### 5.1 输入验证
- 检查成绩是否在 0-100 范围内，否则提示重新输入或忽略。
```cpp
if (grade < 0 || grade > 100) {
    std::cout << "Invalid grade, ignored.\n";
    continue;
}
```

### 5.2 使用 `std::vector` 存储所有成绩
- 以便后续进行更多统计（如排序、查找）。

### 5.3 改用枚举或字符串表示等级
- 增强可读性。

### 5.4 支持更多等级（如 A+，A-）需细化分段。

### 5.5 若编译器不支持 `<format>`，用流式输出替代：
```cpp
std::cout << "Total of the " << gradeCounter << " grades entered is " << total << '\n';
std::cout << "Class average is " << std::fixed << std::setprecision(2) << average << "\n\n";
```

---

## 6. 练习建议

1. **添加输入验证**：只接受 0-100 的整数，否则提示并忽略。
2. **扩展等级**：增加 A+ (≥95)、A (90-94)、B+ 等。
3. **统计最高分、最低分**：在循环中更新 `maxGrade` 和 `minGrade`。
4. **输出等级分布直方图**：用 `*` 表示人数。
5. **改用 `do-while` 或 `for` 循环**，比较不同实现。

---

**你已掌握通过 EOF 控制循环输入和使用 `switch` 进行多分支统计，这些是编写实用统计程序的必备技能！继续加油！** 🚀
