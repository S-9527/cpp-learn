# C++ 入门笔记：函数重载（Function Overloading）

> 本笔记通过求平方的示例，展示 C++ 中函数重载的语法、匹配规则及其在简化接口设计中的作用。

---

## 1. 完整代码示例

```cpp
#include <iostream>

int square(int x) {
  std::cout << "square of integer " << x << " is ";
  return x * x;
}

double square(double y) {
  std::cout << "square of double " << y << " is ";
  return y * y;
}

int main() {
  std::cout << square(7);    // 调用 int 版本
  std::cout << '\n';
  std::cout << square(7.5);  // 调用 double 版本
  std::cout << '\n';
}
```

---

## 2. 代码逐行解析

### 2.1 头文件
```cpp
#include <iostream>
```
- 引入标准输入输出流库，用于 `std::cout`。

### 2.2 第一个 `square` 函数（`int` 版本）
```cpp
int square(int x) {
  std::cout << "square of integer " << x << " is ";
  return x * x;
}
```
- 接受一个 `int` 参数，返回 `int` 类型。
- 函数体输出一条提示信息，然后返回 `x` 的平方。

### 2.3 第二个 `square` 函数（`double` 版本）
```cpp
double square(double y) {
  std::cout << "square of double " << y << " is ";
  return y * y;
}
```
- 接受一个 `double` 参数，返回 `double` 类型。
- 函数体结构类似，但输出信息略有不同（"double"），返回 `y` 的平方。

### 2.4 `main` 函数
```cpp
std::cout << square(7);    // 调用 int 版本
```
- 实参 `7` 是 `int` 字面量，编译器选择 `int square(int)` 版本。
- 输出：`square of integer 7 is 49`（49 由返回的 `int` 值输出）。

```cpp
std::cout << square(7.5);  // 调用 double 版本
```
- 实参 `7.5` 是 `double` 字面量，编译器选择 `double square(double)` 版本。
- 输出：`square of double 7.5 is 56.25`。

---

## 3. 核心知识点：函数重载

### 3.1 什么是函数重载？
- 在**同一作用域**内，可以定义多个**同名**函数，只要它们的**形参列表**不同（参数个数、类型或顺序不同）。
- 返回类型**不是**区分重载的依据。
- 编译器根据调用时提供的实参类型、个数，选择最匹配的函数版本。

### 3.2 重载的规则
| 规则 | 示例 |
|------|------|
| **参数个数不同** | `void f(int);` 和 `void f(int, int);` |
| **参数类型不同** | `void f(int);` 和 `void f(double);` |
| **参数顺序不同** | `void f(int, double);` 和 `void f(double, int);` |
| **`const` 限定符（成员函数中）** | `void f() const;` 和 `void f();`（仅限成员函数） |
| **不可仅靠返回类型区分** | `int f();` 和 `double f();` —— 非法（重复定义） |

### 3.3 重载解析（Overload Resolution）
编译器按以下顺序尝试匹配：
1. **精确匹配**：实参类型与形参类型完全相同。
2. **提升（Promotion）**：如 `char` → `int`，`float` → `double`。
3. **标准转换**：如 `int` → `double`，`double` → `int`。
4. **用户定义转换**（如果存在）。
5. **省略号匹配**（`...`）。

- 若存在多个匹配且无法确定最佳，则产生**二义性**错误。

### 3.4 本例中的匹配
- `square(7)`：`7` 是 `int`，精确匹配 `int` 版本。
- `square(7.5)`：`7.5` 是 `double`，精确匹配 `double` 版本。

---

## 4. 代码风格与改进

### 4.1 统一输出格式
可使用 `std::format`（C++20）统一输出：
```cpp
#include <format>
int square(int x) {
    std::cout << std::format("square of integer {} is {}\n", x, x*x);
    return x*x;
}
```

### 4.2 使用模板代替重载
如果函数体相同，可使用函数模板：
```cpp
template <typename T>
T square(T x) {
    std::cout << "square of " << x << " is ";
    return x * x;
}
```
但模板无法针对不同类型输出不同的提示信息（如 "integer" vs "double"），除非使用 `if constexpr` 或特化。

### 4.3 返回类型
- 注意 `square(int)` 返回 `int`，`square(double)` 返回 `double`。若希望统一返回 `double`，可将 `int` 版本也返回 `double` 或转换后返回。

---

## 5. 编译与运行

### 5.1 编译
```bash
g++ -std=c++17 overload_square.cpp -o overload_square
```

### 5.2 运行输出
```
square of integer 7 is 49
square of double 7.5 is 56.25
```

---

## 6. 重载 vs 默认参数

| 特性 | 函数重载 | 默认参数 |
|------|----------|----------|
| **参数列表** | 必须不同 | 相同，但部分参数有默认值 |
| **函数数量** | 多个函数 | 一个函数 |
| **适用场景** | 不同类型或数量的参数，行为不同 | 相同逻辑，但可省略部分参数 |
| **可读性** | 调用时需明确选择 | 调用更简洁 |

---

## 7. 常见错误与注意事项

1. **歧义调用**：
   ```cpp
   void f(int, double);
   void f(double, int);
   f(1, 2); // 歧义：两个版本都可能匹配
   ```

2. **仅返回类型不同**：
   ```cpp
   int f();
   double f(); // 错误：重复定义
   ```

3. **重载与继承**：基类的重载函数会被派生类隐藏，除非使用 `using` 声明。

4. **`const` 形参**：`void f(int)` 和 `void f(const int)` 视为相同，因为顶层 `const` 不影响函数签名。

---

## 8. 练习建议

1. **添加 `long` 版本**：编写 `long square(long)`，测试调用 `square(100L)`。
2. **使用 `auto` 返回类型**：将两个函数改为 `auto` 返回类型推导。
3. **编写 `print` 重载**：重载 `print` 函数，分别处理 `int`、`double`、`std::string`，输出不同类型的信息。
4. **测试二义性**：编写两个重载版本，故意制造调用二义性，观察编译错误。
5. **改用模板**：将两个 `square` 替换为一个模板，并添加输出不同提示（可使用 `if constexpr` 或类型特性）。

---

## 9. 扩展：重载与 `const` 成员函数

在类中，成员函数可被 `const` 重载：
```cpp
class A {
public:
    void f() const { /* 常对象调用 */ }
    void f() { /* 非常对象调用 */ }
};
```
- 非常对象优先调用非 `const` 版本，常对象调用 `const` 版本。

---

**函数重载是 C++ 多态性的重要体现，能让接口更直观、灵活。合理使用重载，可提高代码的可读性和可维护性。继续探索，掌握更多重载技巧！** 🚀
