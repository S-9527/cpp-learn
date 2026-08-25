# C++ 入门笔记：`std::array` 初始化、访问与边界检查

> 本笔记通过演示 `std::array` 的默认初始化、元素赋值、两种访问方式（`operator[]` 和 `at()`），以及 `at()` 的边界检查与异常抛出，强调固定大小数组的使用要点。

---

## 1. 完整代码示例

```cpp
#include <format>
#include <iostream>
#include <array>

int main() {
   std::array<int, 5> values; // 声明 5 个 int 的数组，未初始化

   // 手动将每个元素初始化为 0
   for (size_t i{0}; i < values.size(); ++i) {
      values[i] = 0;
   }

   std::cout << std::format("{:>7}{:>10}\n", "Element", "Value");

   // 使用 operator[] 输出每个元素
   for (size_t i{0}; i < values.size(); ++i) {
      std::cout << std::format("{:>7}{:>10}\n", i, values[i]);
   }

   std::cout << std::format("\n{:>7}{:>10}\n", "Element", "Value");

   // 使用 at() 输出每个元素
   for (size_t i{0}; i < values.size(); ++i) {
      std::cout << std::format("{:>7}{:>10}\n", i, values.at(i));
   }

   // 越界访问：at(10) 会抛出 std::out_of_range 异常
   values.at(10); // throws an exception
}
```

---

## 2. 代码逐行解析

### 2.1 头文件与声明
```cpp
#include <format>   // C++20 格式化输出
#include <iostream> // 标准输入输出流
#include <array>    // std::array 容器
```
- `<array>` 提供固定大小数组容器 `std::array`。

### 2.2 未初始化的 `std::array`
```cpp
std::array<int, 5> values;
```
- **重要**：`values` 的元素**未被初始化**（对于基本类型 `int`，其值是不确定的，可能包含垃圾值）。
- 与 `std::array<int, 5> values{};` 不同，后者会将所有元素**值初始化为 0**。

### 2.3 手动初始化所有元素
```cpp
for (size_t i{0}; i < values.size(); ++i) {
    values[i] = 0;
}
```
- 使用 `operator[]` 逐个赋值为 0。
- `values.size()` 返回 `size_t`（无符号整数），表示元素个数。
- 如果忘记初始化，后续访问会读到垃圾值，可能导致不可预测的行为。

### 2.4 输出表头与元素（使用 `operator[]`）
```cpp
std::cout << std::format("{:>7}{:>10}\n", "Element", "Value");
for (size_t i{0}; i < values.size(); ++i) {
    std::cout << std::format("{:>7}{:>10}\n", i, values[i]);
}
```
- `{:>7}` 表示右对齐，宽度为 7。
- `operator[]` 不进行边界检查，访问效率高，但越界会导致**未定义行为**（可能崩溃或读到垃圾值）。

### 2.5 使用 `at()` 访问元素
```cpp
for (size_t i{0}; i < values.size(); ++i) {
    std::cout << std::format("{:>7}{:>10}\n", i, values.at(i));
}
```
- `values.at(i)` 进行边界检查，若 `i >= size()` 则抛出 `std::out_of_range` 异常。
- 安全性更高，适合调试阶段或用户输入作为索引的场景。

### 2.6 越界访问（演示异常）
```cpp
values.at(10); // 抛出 std::out_of_range 异常
```
- `values` 大小为 5，索引 10 超出范围。
- `at(10)` 会抛出异常，程序终止（除非被 `try-catch` 捕获）。
- 这行代码通常用于演示异常处理，在实际项目中应避免此类操作或使用 `try-catch` 捕获。

---

## 3. 核心知识点

### 3.1 默认初始化 vs 值初始化
| 写法 | 结果 |
|------|------|
| `std::array<int, 5> values;` | **未初始化**，元素值为垃圾值 |
| `std::array<int, 5> values{};` | **值初始化**，所有元素为 0 |
| `std::array<int, 5> values{1,2};` | 前两个元素为 1,2，其余为 0 |

### 3.2 `operator[]` vs `at()`
| 特性 | `operator[]` | `at()` |
|------|--------------|--------|
| 边界检查 | ❌ 无 | ✅ 有 |
| 越界行为 | **未定义行为**（可能崩溃） | 抛出 `std::out_of_range` |
| 性能 | 更快 | 稍慢（有检查开销） |
| 适用场景 | 确定索引合法时（如循环） | 索引来自外部输入或不安全时 |

### 3.3 异常处理（C++）
- `std::out_of_range` 继承自 `std::exception`，可通过 `try-catch` 捕获。
```cpp
try {
    values.at(10);
} catch (const std::out_of_range& e) {
    std::cout << "Caught: " << e.what() << '\n';
}
```

### 3.4 `size_t` 类型
- `size_t` 是无符号整数类型，用于表示大小和索引。
- 在循环中与有符号整数混用时需注意符号转换问题（如 `int i = 0; i < values.size(); ++i` 可能产生警告）。

---

## 4. 编译与运行

### 4.1 编译（需 C++20 支持 `<format>`）
```bash
g++ -std=c++20 array_uninitialized.cpp -o array_uninitialized
```

### 4.2 运行输出（正常部分）
```
Element   Value
      0        0
      1        0
      2        0
      3        0
      4        0

Element   Value
      0        0
      1        0
      2        0
      3        0
      4        0
terminate called after throwing an instance of 'std::out_of_range'
  what():  array::at: __n (which is 10) >= _Nm (which is 5)
Aborted (core dumped)
```
- 注意：最后一行 `values.at(10);` 导致程序崩溃。

---

## 5. 改进建议

### 5.1 使用 `fill` 方法初始化
```cpp
values.fill(0); // 将所有元素设为 0
```

### 5.2 使用列表初始化（避免未初始化）
```cpp
std::array<int, 5> values{0, 0, 0, 0, 0}; // 显式初始化
// 或
std::array<int, 5> values{}; // 全部初始化为 0
```

### 5.3 使用范围 for 循环简化输出
```cpp
for (const auto& v : values) {
    std::cout << std::format("{:>10}\n", v);
}
```

### 5.4 捕获异常（避免崩溃）
```cpp
try {
    std::cout << values.at(10) << '\n';
} catch (const std::out_of_range& e) {
    std::cout << "Index out of range: " << e.what() << '\n';
}
```

---

## 6. 练习建议

1. **对比输出**：将 `values` 声明改为 `std::array<int, 5> values{};`，观察是否还需手动赋零。
2. **测试越界**：用 `values[10]` 替换 `at(10)`，观察程序行为（可能输出垃圾值或崩溃）。
3. **捕获异常**：用 `try-catch` 捕获 `values.at(10)` 抛出的异常，并输出错误信息。
4. **改用 `fill`**：用 `values.fill(0);` 替代循环，简化代码。
5. **处理用户输入索引**：编写程序从用户输入读取索引，用 `at()` 安全访问。

---

## 7. 为什么不用 C 风格数组？

- `std::array` 提供了 `at()` 边界检查，C 风格数组需手动检查。
- `std::array` 可作为函数参数（按值或引用传递），不会退化为指针。
- `std::array` 支持标准容器接口（`size`, `begin`, `end`），便于泛型算法。

---

**`std::array` 的 `at()` 提供了安全访问机制，而 `operator[]` 提供最高性能。根据场景选择合适的访问方式，让你的代码既高效又健壮！继续探索 C++ 容器的世界！** 🚀
