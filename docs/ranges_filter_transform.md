# C++ 入门笔记：C++20 Ranges 库与函数式编程

> 本笔记通过一系列 ranges 操作示例，演示 C++20 引入的 `<ranges>` 库的核心概念：视图（views）、管道操作符（`|`）、惰性求值、以及 `filter`、`transform` 等适配器。同时涵盖 lambda 表达式、`std::accumulate` 和 `std::array` 的综合应用。

---

## 1. 完整代码示例

```cpp
#include <array>
#include <format>
#include <iostream>
#include <numeric>
#include <ranges>

int main() {
   // lambda to display results of range operations
   auto showValues{
      [](auto& values, const std::string& message) {
         std::cout << std::format("{}: ", message);

         for (const auto& value : values) {
            std::cout << std::format("{} ", value);
         }

         std::cout << '\n';
      }
   };

   auto values1{std::views::iota(1, 11)}; // generate integers 1-10
   showValues(values1, "Generate integers 1-10");

   // filter each value in values1, keeping only the even integers
   auto values2{values1 |
      std::views::filter([](const auto& x) {return x % 2 == 0;})};
   showValues(values2, "Filtering even integers");

   // map each value in values2 to its square
   auto values3{
      values2 | std::views::transform([](const auto& x) {return x * x;})};
   showValues(values3, "Mapping even integers to squares");

   // combine filter and transform to get squares of the even integers
   auto values4{
      values1 | std::views::filter([](const auto& x) {return x % 2 == 0;})
              | std::views::transform([](const auto& x) {return x * x; })};
   showValues(values4, "Squares of even integers");

   // total the squares of the even integers 
   std::cout << std::format("Sum squares of even integers 2-10: {}\n",
      std::accumulate(std::begin(values4), std::end(values4), 0));

   // process a container's elements
   constexpr std::array numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
   auto values5{
      numbers | std::views::filter([](const auto& x) {return x % 2 == 0;})
              | std::views::transform([](const auto& x) {return x * x;})};
   showValues(values5, "Squares of even integers in array numbers");
}
```

---

## 2. 代码逐行解析

### 2.1 头文件
```cpp
#include <array>    // std::array
#include <format>   // C++20 格式化输出
#include <iostream> // 标准输入输出
#include <numeric>  // std::accumulate
#include <ranges>   // C++20 ranges 库
```
- `<ranges>` 是 C++20 新增的头文件，包含视图（views）、范围适配器（range adaptors）等核心组件。

### 2.2 通用输出 lambda
```cpp
auto showValues{
   [](auto& values, const std::string& message) {
      std::cout << std::format("{}: ", message);
      for (const auto& value : values) {
         std::cout << std::format("{} ", value);
      }
      std::cout << '\n';
   }
};
```
- 这是一个**泛型 lambda**，接受任意类型 `values`（需要支持范围 `for` 循环）。
- 输出自定义消息和范围中的所有元素。
- 使用 `auto&` 接收范围，避免复制视图（视图是轻量级对象，但传递引用更高效）。

### 2.3 生成整数序列：`std::views::iota`
```cpp
auto values1{std::views::iota(1, 11)};
showValues(values1, "Generate integers 1-10");
```
- `std::views::iota(1, 11)` 生成一个**视图**，表示从 1 到 10 的整数序列（左闭右开区间 `[1, 11)`）。
- `values1` 的类型是一个**视图**（`ranges::iota_view`），它并不实际存储数据，而是按需生成。
- 输出：`Generate integers 1-10: 1 2 3 4 5 6 7 8 9 10`

### 2.4 过滤偶数：`std::views::filter`
```cpp
auto values2{values1 |
   std::views::filter([](const auto& x) {return x % 2 == 0;})};
showValues(values2, "Filtering even integers");
```
- **管道操作符 `|`**：将左侧的范围（视图）送入右侧的适配器。
- `std::views::filter` 接受一个谓词（返回 `bool` 的函数），保留满足条件的元素。
- `values2` 是一个**惰性视图**，只有在遍历时才会实际计算过滤结果。
- 输出：`Filtering even integers: 2 4 6 8 10`

### 2.5 映射到平方：`std::views::transform`
```cpp
auto values3{
   values2 | std::views::transform([](const auto& x) {return x * x;})};
showValues(values3, "Mapping even integers to squares");
```
- `std::views::transform` 对每个元素应用转换函数，生成新值。
- `values3` 是另一个惰性视图，遍历时计算平方。
- 输出：`Mapping even integers to squares: 4 16 36 64 100`

### 2.6 组合操作：管道链
```cpp
auto values4{
   values1 | std::views::filter([](const auto& x) {return x % 2 == 0;})
           | std::views::transform([](const auto& x) {return x * x; })};
showValues(values4, "Squares of even integers");
```
- 将 `filter` 和 `transform` **链式组合**，形成一步到位的处理管道。
- 数据流：`values1` → 过滤偶数 → 平方 → `values4`。
- 输出：`Squares of even integers: 4 16 36 64 100`

### 2.7 对视图求和：`std::accumulate`
```cpp
std::cout << std::format("Sum squares of even integers 2-10: {}\n",
   std::accumulate(std::begin(values4), std::end(values4), 0));
```
- `std::begin(values4)` 和 `std::end(values4)` 获取视图的迭代器。
- `std::accumulate` 对视图中的元素求和，得到 `4+16+36+64+100=220`。

### 2.8 处理已有容器
```cpp
constexpr std::array numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
auto values5{
   numbers | std::views::filter([](const auto& x) {return x % 2 == 0;})
           | std::views::transform([](const auto& x) {return x * x;})};
showValues(values5, "Squares of even integers in array numbers");
```
- 直接用 `std::array` 作为管道起点。
- `numbers` 是常量数组，过滤和转换操作不修改原数据。
- 输出：`Squares of even integers in array numbers: 4 16 36 64 100`

---

## 3. 核心知识点

### 3.1 Ranges 库的核心概念
| 概念 | 说明 |
|------|------|
| **范围（Range）** | 任何可遍历的序列（容器、视图、数组）。 |
| **视图（View）** | 轻量级、**惰性求值**的范围，不拥有数据，只提供变换逻辑。 |
| **适配器（Adaptor）** | 如 `filter`、`transform`，将输入范围转换为新视图。 |
| **管道操作符 `|`** | 将范围送入适配器，形成函数式链式调用。 |

### 3.2 惰性求值（Lazy Evaluation）
- 视图操作**不会立即执行**，只有在遍历（如范围 `for` 循环）或转换为容器时，才进行实际计算。
- 这避免了中间临时对象的创建，提高了性能，尤其适合大数据集。

### 3.3 常用视图适配器
| 适配器 | 作用 | 示例 |
|--------|------|------|
| `views::iota(a, b)` | 生成 `[a, b)` 的整数序列 | `views::iota(1, 5)` → `1,2,3,4` |
| `views::filter(pred)` | 保留满足谓词的元素 | `filter([](int x){ return x%2==0; })` |
| `views::transform(f)` | 对每个元素应用转换函数 | `transform([](int x){ return x*x; })` |
| `views::take(n)` | 取前 n 个元素 | `take(3)` |
| `views::drop(n)` | 跳过前 n 个元素 | `drop(2)` |
| `views::reverse` | 反转顺序 | `reverse` |
| `views::keys` / `views::values` | 提取 `pair` 的键/值 | 适用于 `std::map` |

### 3.4 与标准算法的比较
| 传统 STL 算法 | Ranges 版本 | 优点 |
|--------------|-------------|------|
| 需传递 `begin`/`end` | 直接传递容器/视图 | 更简洁 |
| 中间结果需额外容器 | 惰性视图，无额外分配 | 性能更好 |
| 难以组合多个操作 | 管道链式调用 | 更直观的声明式风格 |

### 3.5 迭代器与视图
- 视图可以像容器一样使用 `std::begin` / `std::end` 获取迭代器。
- 某些视图（如 `filter`）的迭代器类型较复杂，但用法与普通迭代器一致。
- `std::accumulate` 等算法可以直接处理视图。

---

## 4. 编译与运行

### 4.1 编译（需 C++20）
```bash
g++ -std=c++20 ranges_demo.cpp -o ranges_demo
```

### 4.2 运行输出
```
Generate integers 1-10: 1 2 3 4 5 6 7 8 9 10 
Filtering even integers: 2 4 6 8 10 
Mapping even integers to squares: 4 16 36 64 100 
Squares of even integers: 4 16 36 64 100 
Sum squares of even integers 2-10: 220
Squares of even integers in array numbers: 4 16 36 64 100 
```

---

## 5. 改进建议

### 5.1 使用 `std::ranges::accumulate`（C++23 或 range-v3）
- 目前标准库的 `std::accumulate` 需要迭代器，C++23 将引入 `std::ranges::accumulate`，可直接传递范围。

### 5.2 使用 `auto` 简化 lambda 参数
```cpp
auto isEven = [](auto x) { return x % 2 == 0; };
auto square = [](auto x) { return x * x; };
auto values = iota(1, 11) | filter(isEven) | transform(square);
```

### 5.3 使用 `std::views::common` 转换为可迭代范围
- 若某个算法不支持视图，可转换为通用范围。

### 5.4 尝试其他适配器
```cpp
auto first5 = values1 | views::take(5);  // 取前 5 个
auto skipped = values1 | views::drop(3); // 跳过前 3 个
```

### 5.5 使用 `constexpr` 视图（C++20）
- `std::views::iota` 支持 `constexpr` 上下文。

---

## 6. 练习建议

1. **修改过滤条件**：改为过滤奇数，观察输出。
2. **添加 `take` 操作**：在管道末尾添加 `| views::take(3)`，仅输出前三个平方数。
3. **使用 `drop` 操作**：跳过第一个偶数，再计算平方。
4. **处理字符串**：创建字符串数组，使用 `transform` 转换为大写。
5. **组合多个 `filter`**：用两个 `filter` 替代 `x % 2 == 0`，如先 `x > 0` 再 `x % 2 == 0`。

---

## 7. 注意事项

- Ranges 是 **C++20** 的新特性，需编译器支持（GCC 10+、Clang 13+、MSVC 2019 16.10+）。
- 视图默认是**惰性**的，若多次遍历同一视图，会重新计算（除非缓存结果）。
- 某些视图（如 `filter`）的迭代器**不是双向迭代器**，因此不支持 `std::reverse` 等算法（除非额外转换）。
- 视图不拥有数据，因此原数据（如 `values1`）的生命周期必须长于视图。

---

**Ranges 库为 C++ 带来了声明式、函数式的编程风格，让数据处理更清晰、更高效。掌握视图和管道操作，你将能以更优雅的方式处理集合数据。继续探索 Ranges 的更多可能性！** 🚀
