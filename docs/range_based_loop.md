# C++ 入门笔记：`std::array`、范围 for 循环与引用

> 本笔记涵盖 `std::array` 的类模板参数推导（CTAD）、基于范围的 `for` 循环（含 `const` 引用与非 `const` 引用）、C++17 带初始化器的 `for` 循环，以及 `std::format` 的格式化输出。

---

## 1. 完整代码示例

```cpp
#include <array>
#include <format>
#include <iostream>

int main() {
  std::array items{1, 2, 3, 4, 5};

  std::cout << "items before modification: ";
  for (const int& item : items) {
    std::cout << std::format("{} ", item);
  }

  for (int& item : items) {
    item *= 2;
  }

  std::cout << "\nitems after modification: ";
  for (int& item : items) {
    std::cout << std::format("{} ", item);
  }

  std::cout << "\ncalculating a running total of items' values: \n";
  for (int runningTotal{0}; const int& item : items) {
    runningTotal += item;
    std::cout << std::format("item: {}; runningTotal: {}\n", item, runningTotal);
  }

  return 0;
}
```

---

## 2. 代码逐行解析

### 2.1 头文件与 CTAD
```cpp
#include <array>    // std::array 容器
#include <format>   // C++20 格式化输出
#include <iostream> // 标准输入输出流

std::array items{1, 2, 3, 4, 5};
```
- 使用**类模板参数推导（CTAD，C++17 起）**，编译器自动推导出 `std::array<int, 5>`。
- 相当于显式写法：`std::array<int, 5> items{1, 2, 3, 4, 5};`

### 2.2 基于范围的 `for` 循环（只读）
```cpp
for (const int& item : items) {
    std::cout << std::format("{} ", item);
}
```
- `for (元素 : 容器)` 语法，遍历 `items` 中的每个元素。
- `const int& item` 表示**常量引用**，只读访问元素，避免拷贝。
- 适合只需查看、不修改元素的场景。

### 2.3 基于范围的 `for` 循环（可修改）
```cpp
for (int& item : items) {
    item *= 2;
}
```
- `int& item` 是**非常量引用**，可以修改数组元素。
- `item *= 2` 将每个元素的值乘以 2。
- 注意：若此处用 `int item`（值传递），则修改的是局部副本，不影响原数组。

### 2.4 输出修改后的结果
```cpp
for (int& item : items) {
    std::cout << std::format("{} ", item);
}
```
- 再次遍历输出，展示修改后的值（2, 4, 6, 8, 10）。

### 2.5 带初始化器的范围 `for` 循环（C++17）
```cpp
for (int runningTotal{0}; const int& item : items) {
    runningTotal += item;
    std::cout << std::format("item: {}; runningTotal: {}\n", item, runningTotal);
}
```
- 这是 C++17 引入的**范围 `for` 循环初始化器（init-statement）**。
- 语法：`for (init; 声明 : 范围) { ... }`
- `int runningTotal{0}` 在循环开始前初始化，作用域覆盖整个循环。
- `const int& item` 是循环变量，遍历 `items` 中的每个元素。
- 循环体内计算累计总和并输出每次迭代的 `item` 和 `runningTotal`。

---

## 3. 核心知识点

### 3.1 类模板参数推导（CTAD）
- C++17 起，编译器可从构造函数参数推导模板参数类型。
- `std::array items{1,2,3,4,5};` → `std::array<int, 5>`
- 要求所有元素类型一致，否则推导失败（如 `{1, 2.5}` 推导为 `std::array<double, 2>`? 实际上会失败，因为 `1` 和 `2.5` 类型不同）。
- CTAD 也适用于其他标准容器（如 `std::vector`, `std::pair`）。

### 3.2 基于范围的 `for` 循环（Range-based `for` loop）
| 写法 | 含义 | 适用场景 |
|------|------|----------|
| `for (auto x : range)` | 按值拷贝元素 | 小对象或需要修改副本时 |
| `for (auto& x : range)` | 可修改元素 | 需要修改容器内容 |
| `for (const auto& x : range)` | 只读访问，避免拷贝 | 大对象或只读场景 |

### 3.3 引用类型选择
| 引用类型 | 能否修改元素 | 拷贝开销 | 示例 |
|----------|-------------|----------|------|
| `T item` | ❌（修改副本） | 有 | `int item : items` |
| `T& item` | ✅ | 无 | `int& item : items` |
| `const T& item` | ❌ | 无 | `const int& item : items` |

### 3.4 C++17 范围 `for` 初始化器
- 语法：`for (初始化; 声明 : 范围)`
- 初始化部分声明的变量作用域覆盖整个循环，但不污染外层作用域。
- 示例中 `runningTotal` 在循环内维护累计值，优雅且简洁。

---

## 4. 编译与运行

### 4.1 编译（需 C++20 支持 `<format>`）
```bash
g++ -std=c++20 array_range_for.cpp -o array_range_for
```

### 4.2 运行输出
```
items before modification: 1 2 3 4 5 
items after modification: 2 4 6 8 10 
calculating a running total of items' values: 
item: 2; runningTotal: 2
item: 4; runningTotal: 6
item: 6; runningTotal: 12
item: 8; runningTotal: 20
item: 10; runningTotal: 30
```

---

## 5. 代码风格与改进

### 5.1 使用 `auto` 简化循环变量
```cpp
for (const auto& item : items) { ... }  // 自动推导类型
for (auto& item : items) { ... }
```

### 5.2 使用 `std::ranges`（C++20）
C++20 引入 `<ranges>`，提供更强大的视图和管道操作：
```cpp
#include <ranges>
for (const auto& item : items | std::views::filter(...)) { ... }
```

### 5.3 使用 `std::accumulate` 计算总和
```cpp
#include <numeric>
int total = std::accumulate(items.begin(), items.end(), 0);
```

### 5.4 使用 `std::format` 的高级格式
```cpp
std::cout << std::format("{:>10}\n", item); // 右对齐，宽度 10
```

---

## 6. 练习建议

1. **修改循环变量类型**：将 `const int&` 改为 `int`，观察能否修改数组元素（提示：不能，修改的是副本）。
2. **尝试 CTAD 失败**：用 `std::array items{1, 2.5, 3};` 观察编译错误。
3. **在范围 `for` 中使用 `auto`**：改写所有循环，使用 `auto&` 或 `const auto&`。
4. **扩展 `std::array` 大小**：添加更多元素，观察 CTAD 自动推导。
5. **用传统 `for` 循环重写**：对比两种写法的简洁性。

---

## 7. 注意事项

- 范围 `for` 循环在遍历过程中**修改容器大小**（如插入、删除）会导致**未定义行为**（`std::array` 大小固定，不存在此问题）。
- 范围 `for` 循环底层使用 `begin()` / `end()`，因此适用于所有支持迭代器的容器。
- C++17 初始化器中的变量（如 `runningTotal`）不能是 `const`，否则无法修改。

---

**基于范围的 `for` 循环让容器遍历变得更安全、更简洁。配合 C++17 的初始化器和 CTAD，现代 C++ 代码更清晰、更易维护。继续探索 C++ 的现代特性！** 🚀
