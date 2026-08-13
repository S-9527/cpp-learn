# C++ 入门笔记：关系运算符与 if 语句

> 本笔记涵盖 `using` 声明、关系运算符（比较运算符）及 `if` 条件判断语句。

---

## 1. 完整代码示例

```cpp
#include <iostream>

using std::cin;
using std::cout;

int main()
{
  int number1{0};
  int number2{0};

  std::cout << "Enter two integers to compare: ";
  std::cin >> number1 >> number2;

  if (number1 == number2)
  {
    std::cout << number1 << " == " << number2 << "\n";
  }

  if (number1 != number2)
  {
    std::cout << number1 << " != " << number2 << "\n";
  }

  if (number1 >= number2)
  {
    std::cout << number1 << " >= " << number2 << "\n";
  }

  if (number1 <= number2)
  {
    std::cout << number1 << " <= " << number2 << "\n";
  }

  if (number1 < number2)
  {
    std::cout << number1 << " < " << number2 << "\n";
  }

  if (number1 > number2)
  {
    std::cout << number1 << " > " << number2 << "\n";
  }

  return 0;
}
```

---

## 2. 代码逐行解析

### 2.1 头文件与 `using` 声明
```cpp
#include <iostream>

using std::cin;
using std::cout;
```

- `#include <iostream>` 引入输入输出流库。
- `using std::cin;` 和 `using std::cout;` 是 **using 声明**，作用是将 `std::cin` 和 `std::cout` 引入当前作用域，之后可以直接写 `cin` 和 `cout`，无需 `std::` 前缀。

**对比两种写法**：
| 写法 | 示例 | 适用场景 |
|------|------|----------|
| 完全限定名 | `std::cout << "Hello";` | 明确来源，避免命名冲突 |
| using 声明 | `using std::cout;` 后直接 `cout << "Hello";` | 简化代码，适合单个命名空间中少量名称 |
| using 指令（不推荐） | `using namespace std;` | 导入整个命名空间，易引起名称冲突 |

> **注意**：本代码中 `std::cout` 和 `cout` 混用，不影响编译。建议统一风格，此处可以全部改为 `cout`（因为已经 `using std::cout;`）。

### 2.2 变量声明与链式输入
```cpp
int number1{0};
int number2{0};

std::cout << "Enter two integers to compare: ";
std::cin >> number1 >> number2;
```

- `std::cin >> number1 >> number2;` 是**链式输入**，相当于：
  ```cpp
  std::cin >> number1;
  std::cin >> number2;
  ```
- 用户输入时用空格或回车分隔两个整数，例如 `5 3` 或：
  ```
  5
  3
  ```

### 2.3 `if` 语句与关系运算符
```cpp
if (number1 == number2)
{
    std::cout << number1 << " == " << number2 << "\n";
}
```

#### C++ 关系运算符一览
| 运算符 | 含义 | 示例 |
|--------|------|------|
| `==` | 等于 | `a == b` |
| `!=` | 不等于 | `a != b` |
| `>` | 大于 | `a > b` |
| `<` | 小于 | `a < b` |
| `>=` | 大于等于 | `a >= b` |
| `<=` | 小于等于 | `a <= b` |

> **注意**：
> - `==` 是**相等比较**，`=` 是**赋值**，两者极易混淆。
> - 关系运算符的结果是布尔值（`true` / `false`）。

### 2.4 多个独立 `if` 语句的特点
本代码中使用了 **6 个独立的 `if` 语句**，彼此互不影响。

- 每个 `if` 都独立判断条件，不依赖其他条件的结果。
- 因此，当用户输入 `5` 和 `3` 时，会输出多条结果：
  ```
  Enter two integers to compare: 5 3
  5 != 3
  5 >= 3
  5 > 3
  ```
  因为 `5 != 3`、`5 >= 3`、`5 > 3` 三个条件都成立。

#### 对比：`if-else if` 链
如果想让程序只输出一种关系（如“5 > 3”），需要用 `if-else if-else` 结构：
```cpp
if (number1 > number2) {
    cout << number1 << " > " << number2 << "\n";
} else if (number1 < number2) {
    cout << number1 << " < " << number2 << "\n";
} else {
    cout << number1 << " == " << number2 << "\n";
}
```
此时只输出一条结果。

---

## 3. 核心知识点总结

### 3.1 `using` 的三种形式
| 形式 | 示例 | 说明 |
|------|------|------|
| using 声明 | `using std::cout;` | 只引入特定名称，推荐 |
| using 编译指令 | `using namespace std;` | 引入整个命名空间，不推荐（易冲突） |
| 完全限定名 | `std::cout` | 最安全，稍繁琐 |

**建议**：在小型程序或学习阶段可以使用 `using` 声明。在企业项目中，头文件内通常禁用 `using`，在 `.cpp` 文件中适度使用。

### 3.2 关系运算符的结果类型
关系运算的结果是 `bool` 类型：
- 条件成立 → `true`（整数值为 1）
- 条件不成立 → `false`（整数值为 0）

可以用于赋值：
```cpp
bool isEqual = (number1 == number2);   // 注意括号
```

### 3.3 大括号风格
本代码采用 **Stroustrup 风格**（又称“埃及括号”）：
```cpp
if (条件) {
    // 语句
}
```
大括号内的代码构成一个**复合语句**（代码块），即使只有一条语句，也建议加上大括号，便于维护和扩展。

---

## 4. 编译与运行

### 4.1 编译命令
```bash
g++ -std=c++17 compare.cpp -o compare
```

### 4.2 运行示例
```bash
$ ./compare
Enter two integers to compare: 5 3
5 != 3
5 >= 3
5 > 3
```

```bash
$ ./compare
Enter two integers to compare: 3 3
3 == 3
3 >= 3
3 <= 3
```

```bash
$ ./compare
Enter two integers to compare: 2 7
2 != 7
2 <= 7
2 < 7
```

---

## 5. 练习建议

1. **测试所有情况**：分别输入 `a > b`、`a < b`、`a == b`，观察输出差异。
2. **改用 `if-else if-else`**：改写代码，使程序只输出一条最准确的关系描述。
3. **引入 `bool` 变量**：
   ```cpp
   bool isGreater = number1 > number2;
   if (isGreater) { ... }
   ```
4. **扩展至 `double` 类型**：将 `int` 改为 `double`，注意浮点数比较的精度问题（可稍后了解）。

---

**你已经掌握了让程序根据条件做决策的能力，这是编程中最核心的逻辑之一！继续保持！** 🚀
