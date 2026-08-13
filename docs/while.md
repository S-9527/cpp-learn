# C++ 入门笔记：`while` 循环与成绩统计

> 本笔记涵盖 `while` 循环、计数器、累加变量、循环内变量声明及整数除法的注意事项。

---

## 1. 完整代码示例

```cpp
#include <iostream>

int main()
{
  int total{0};
  int gradeCounter{1};

  while (gradeCounter <= 10)
  {
    std::cout << "Enter grade: ";
    int grade;
    std::cin >> grade;
    total = total + grade;
    gradeCounter = gradeCounter + 1;
  }

  int average{total / 10};
  std::cout << "\nTotal of all 10 grades is " << total;
  std::cout << "\nClass average is " << average;

  return 0;
}
```

---

## 2. 代码逐行解析

### 2.1 头文件与入口
```cpp
#include <iostream>   // 标准输入输出流
int main()            // 程序入口
```

### 2.2 变量定义与初始化
```cpp
int total{0};          // 用于累加所有成绩
int gradeCounter{1};   // 循环计数器，从1开始
```

- `total` 通常称为“累加器”（accumulator），用于存储所有输入成绩的和。
- `gradeCounter` 称为“计数器”（counter），用于控制循环次数，这里从 1 到 10。

### 2.3 `while` 循环结构
```cpp
while (gradeCounter <= 10)
{
    // 循环体
}
```

- `while` 循环先判断条件 `gradeCounter <= 10`：
  - 若为 `true`，执行循环体；
  - 执行完毕后，返回再次判断条件，直至条件为 `false` 时退出循环。
- 循环体由一对大括号 `{}` 包围，形成复合语句（代码块）。

### 2.4 循环体内操作
```cpp
std::cout << "Enter grade: ";
int grade;
std::cin >> grade;
total = total + grade;
gradeCounter = gradeCounter + 1;
```

1. **输出提示**：提示用户输入成绩。
2. **变量 `grade` 声明**：在循环体内声明，意味着每次迭代都会创建一个新的 `grade` 变量，作用域仅限于循环体（块作用域）。
   > 这比在循环外统一声明更符合“最小作用域”原则，减少错误。
3. **读取输入**：`std::cin >> grade;` 从键盘读取一个整数存入 `grade`。
4. **累加**：`total = total + grade;` 把当前成绩加到总和中。
5. **计数器递增**：`gradeCounter = gradeCounter + 1;` 使计数器加 1，确保循环最终能终止。

### 2.5 循环结束后计算平均值
```cpp
int average{total / 10};
```
- 这里使用整数除法 `total / 10`，结果会**截断小数部分**（向下取整），只保留整数。
- 例如：`total = 425`，则 `average = 42`（实际平均值 42.5，但整数除法得到 42）。

### 2.6 输出结果
```cpp
std::cout << "\nTotal of all 10 grades is " << total;
std::cout << "\nClass average is " << average;
```
- `\n` 放在字符串开头，使得输出在上一行之后换行。

---

## 3. 核心知识点总结

### 3.1 `while` 循环的要素
| 要素 | 说明 | 本例中 |
|------|------|--------|
| **循环变量初始化** | 循环开始前初始化计数器 | `int gradeCounter{1};` |
| **循环条件** | 决定是否继续执行 | `gradeCounter <= 10` |
| **循环体** | 重复执行的代码块 | 提示、输入、累加、自增 |
| **更新计数器** | 避免死循环 | `gradeCounter = gradeCounter + 1;` |

### 3.2 累加与计数
- 累加器 `total` 通常初始化为 `0`。
- 计数器 `gradeCounter` 决定循环次数，这里从 1 到 10，共 10 次。
- 也可以从 0 开始，条件改为 `gradeCounter < 10`。

### 3.3 变量作用域
- 在循环体内部声明的变量（如 `grade`），只在循环体内有效，外部无法访问。
- 这种做法有利于封装和减少命名冲突，是推荐的良好实践。

### 3.4 整数除法的陷阱
- `int / int` 结果仍为 `int`，小数部分直接截断，**不四舍五入**。
- 要获得精确平均值，应使用浮点数类型，例如：
  ```cpp
  double average = static_cast<double>(total) / 10;
  ```

---

## 4. 改进建议

### 4.1 使用 `+=` 和 `++` 运算符简化
```cpp
total += grade;        // 等价于 total = total + grade
gradeCounter++;        // 等价于 gradeCounter = gradeCounter + 1
```

### 4.2 使用 `for` 循环更简洁
当循环次数已知时，`for` 循环通常更清晰：
```cpp
for (int i = 1; i <= 10; i++) {
    std::cout << "Enter grade: ";
    int grade;
    std::cin >> grade;
    total += grade;
}
```

### 4.3 使用浮点数计算平均值
```cpp
double average = static_cast<double>(total) / 10;
std::cout << "\nClass average is " << average << "\n";
```

### 4.4 处理无效输入（防错）
可添加检查，确保输入为有效数字：
```cpp
if (!(std::cin >> grade)) {
    std::cout << "Invalid input!\n";
    return 1;   // 退出程序
}
```

---

## 5. 运行示例

```
Enter grade: 85
Enter grade: 92
Enter grade: 78
Enter grade: 88
Enter grade: 95
Enter grade: 70
Enter grade: 65
Enter grade: 82
Enter grade: 90
Enter grade: 79

Total of all 10 grades is 824
Class average is 82
```

---

## 6. 练习建议

1. **将循环改为 `for` 循环**，比较两种写法的区别。
2. **修改程序支持任意数量成绩**（比如用户先输入个数，再循环）。
3. **改用 `double` 计算平均值**，观察输出结果。
4. **添加最大值和最小值记录**，在循环中更新 `maxGrade` 和 `minGrade`。
5. **使用 `-1` 作为哨兵值**，当用户输入 `-1` 时结束循环，统计有效成绩个数。

---

**你已经掌握了循环的核心用法，这是编程中最重要的结构之一！继续用循环解决更多问题！** 🚀
