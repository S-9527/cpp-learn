# C++ 入门笔记：`constexpr` 与 `std::array` 的初始化

> 本笔记演示 `constexpr` 常量、`std::array` 的声明与初始化、使用 `at()` 设置元素值以及范围 `for` 循环遍历输出。

---

## 1. 完整代码示例

```cpp
#include <array>
#include <format>
#include <iostream>

int main() {
  constexpr size_t arraySize{5};
  std::array<int, arraySize> values{};

  for (int i{0}; i < values.size(); i++) {
    values.at(i) = 2 + 2 * i;
  }

  for (const int& value : values) {
    std::cout << std::format("{} ", value);
  }

  return 0;
}
```

---

## 2. 代码逐行解析

### 2.1 头文件
```cpp
#include <array>    // std::array 容器
#include <format>   // C++20 格式化输出
#include <iostream> // 标准输入输出流
```

### 2.2 `constexpr` 定义编译期常量
```cpp
constexpr size_t arraySize{5};
```
- `constexpr` 表示该变量是**编译期常量**，其值在编译时就确定。
- `size_t` 是无符号整数类型，通常用于表示大小和索引，定义在 `<cstddef>` 中（但被 `<array>` 间接包含）。
- 用 `constexpr` 确保 `arraySize` 可在**编译期**用于指定数组大小（`std::array` 的模板参数必须为编译期常量）。

### 2.3 声明并初始化 `std::array`
```cpp
std::array<int, arraySize> values{};
```
- 声明一个包含 `arraySize`（5）个 `int` 的 `std::array`。
- `values{}` 表示**值初始化**，将所有元素初始化为 0（对于 `int` 类型）。
- 若写成 `std::array<int, arraySize> values;`（无 `{}`），元素将**不被初始化**，值不确定。

### 2.4 使用 `at()` 为元素赋值
```cpp
for (int i{0}; i < values.size(); i++) {
    values.at(i) = 2 + 2 * i;
}
```
- `values.size()` 返回 `size_t` 类型的元素个数，这里为 5。
- 循环变量 `i` 从 0 到 4。
- `values.at(i)` 进行边界检查，并返回元素引用，用于赋值。
- 赋值表达式 `2 + 2 * i` 生成序列：2, 4, 6, 8, 10。

### 2.5 使用范围 `for` 循环输出
```cpp
for (const int& value : values) {
    std::cout << std::format("{} ", value);
}
```
- 遍历 `values` 每个元素，使用 `const int&`（常量引用）避免拷贝，只读访问。
- 使用 `std::format` 格式化输出，每个元素后跟一个空格。

---

## 3. 核心知识点

### 3.1 `constexpr` 与编译期常量
| 关键字 | 含义 | 适用场景 |
|--------|------|----------|
| `const` | 运行时常量（也可用于编译期，但不保证） | 运行时常量 |
| `constexpr` | 编译期常量（强制在编译期求值） | 模板参数、数组大小、`constexpr` 函数 |

- `std::array` 的模板参数（大小）必须是编译期常量，因此 `arraySize` 必须用 `constexpr` 或 `const`（但 `const` 不一定保证编译期值，故推荐 `constexpr`）。
- C++17 起，`constexpr` 可修饰函数和变量，用途更广。

### 3.2 `std::array` 的初始化
| 写法 | 结果 |
|------|------|
| `std::array<int, 5> values;` | 未初始化（垃圾值） |
| `std::array<int, 5> values{};` | 值初始化，所有元素为 0 |
| `std::array<int, 5> values{1,2,3};` | 前三个为 1,2,3，其余为 0 |

### 3.3 `at()` vs `operator[]`
- `at()` 进行边界检查，越界抛出 `std::out_of_range` 异常。
- `operator[]` 不检查边界，越界导致未定义行为。
- 本示例中 `i` 始终在合法范围（0~4），使用 `at()` 增加安全性（尤其适合索引可能来自外部输入时）。

### 3.4 范围 `for` 循环（推荐）
- 语法：`for (声明 : 容器) { ... }`
- 自动遍历所有元素，无需手动索引，更简洁、安全。
- 使用 `const` 引用避免拷贝，适合只读场景。

### 3.5 `std::format` 格式化
- `{}` 为占位符，依次替换后续参数。
- 默认按参数顺序填充，也可指定索引如 `{0}`。
- 可添加格式说明符，如 `{:>5}` 右对齐宽度 5，`{:.2f}` 保留两位小数等。

---

## 4. 编译与运行

### 4.1 编译（需 C++20 支持 `<format>`）
```bash
g++ -std=c++20 constexpr_array.cpp -o constexpr_array
```

### 4.2 运行输出
```
2 4 6 8 10 
```

---

## 5. 改进建议

### 5.1 使用 `std::iota` 生成连续值
```cpp
#include <numeric>
std::iota(values.begin(), values.end(), 2); // 生成 2,3,4,5,6
```
但本示例需要特定等差数列（2,4,6,8,10），可用 lambda 或 `std::generate`。

### 5.2 使用 `std::generate` 和 lambda
```cpp
#include <algorithm>
int n = 0;
std::generate(values.begin(), values.end(), [&n] { return 2 + 2 * n++; });
```

### 5.3 使用 `for` 循环赋值的简化
```cpp
for (int i = 0; auto& v : values) {   // C++20 初始化式
    v = 2 + 2 * i++;
}
```
（C++20 允许在范围 `for` 中使用初始化语句）

### 5.4 将 `arraySize` 改为 `constexpr` 并移动到命名空间
```cpp
inline constexpr size_t arraySize{5}; // 头文件中常用
```

---

## 6. 练习建议

1. **修改 `arraySize`** 为其他值（如 10），观察输出。
2. **去掉 `values{}` 的 `{}`**，看未初始化的输出（可能是随机值）。
3. **改用 `operator[]` 赋值**，对比与 `at()` 的区别（本例无区别）。
4. **使用 `std::generate` 重写赋值循环**。
5. **输出格式**：尝试将数字靠右对齐（`{:>3}`），使输出更整齐。

---

## 7. 注意事项

- `constexpr` 变量必须在编译期可求值，因此不能用运行时输入初始化。
- `std::array` 的大小是编译期常量，因此只能用 `constexpr` 或字面量。
- `std::format` 需要 C++20 支持，若编译器不支持，可改用 `std::cout << value << " ";`。

---

**`constexpr` 与 `std::array` 结合是编译期编程的常见模式，善用它们可提升代码的性能和可靠性。继续探索 C++ 的现代特性！** 🚀
