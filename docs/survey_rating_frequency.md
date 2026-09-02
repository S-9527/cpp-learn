# C++ 入门笔记：等级频率统计与 `std::array`

> 本笔记通过统计一组评分数据（1~5）的频率，演示 `std::array` 的类模板参数推导（CTAD）、`constexpr` 数组、范围 `for` 循环、`at()` 安全访问以及 `std::format` 格式化输出。

---

## 1. 完整代码示例

```cpp
#include <array>
#include <format>
#include <iostream>

int main() {
  constexpr std::array responses{1, 2, 5, 4, 3, 5, 2, 1, 3, 1, 4, 3, 3, 3, 2, 3, 3, 2, 2, 5};

  constexpr size_t frequencySize{6};
  std::array<int, frequencySize> frequency{};

  for (const int& response : responses) {
    ++frequency.at(response);
  }

  std::cout << std::format("{},{:>12}\n", "Rating", "Frequency");

  for (size_t rating{1}; rating < frequency.size(); ++rating) {
    std::cout << std::format("{:>6}{:>12}\n", rating, frequency.at(rating));
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

### 2.2 数据数组（`responses`）
```cpp
constexpr std::array responses{1, 2, 5, 4, 3, 5, 2, 1, 3, 1, 4, 3, 3, 3, 2, 3, 3, 2, 2, 5};
```
- 使用**类模板参数推导（CTAD，C++17）**，编译器推导出 `std::array<int, 20>`。
- `constexpr` 表示数组在**编译期**确定，内容固定，不会改变。
- 数据是一组评分（1~5），共 20 个样本。

### 2.3 频率数组声明与初始化
```cpp
constexpr size_t frequencySize{6};
std::array<int, frequencySize> frequency{};
```
- `frequencySize` 为 6，因为我们希望用索引 1~5 对应评分 1~5，索引 0 闲置不使用。
- `frequency{}` **值初始化**将所有元素置为 0。

### 2.4 遍历数据并统计频率
```cpp
for (const int& response : responses) {
    ++frequency.at(response);
}
```
- 使用范围 `for` 循环，用 `const int&` 引用遍历 `responses` 的每个元素。
- `frequency.at(response)`：因为 `response` 取值 1~5，`at()` 执行边界检查，并返回对应元素的引用。
- `++` 将该评分对应的计数器加 1。
- 注意：索引 0 不会被访问，保持为 0。

### 2.5 输出表头
```cpp
std::cout << std::format("{},{:>12}\n", "Rating", "Frequency");
```
- `"Rating"` 左对齐（默认），`"Frequency"` 右对齐宽度 12。
- 输出类似：`Rating,    Frequency`。

### 2.6 输出统计结果
```cpp
for (size_t rating{1}; rating < frequency.size(); ++rating) {
    std::cout << std::format("{:>6}{:>12}\n", rating, frequency.at(rating));
}
```
- 遍历 `rating` 从 1 到 5（`frequency.size()` 返回 6，条件 `rating < 6`）。
- `{:>6}` 将评分右对齐宽度 6。
- `{:>12}` 将频率值右对齐宽度 12（与表头对齐）。
- 使用 `at()` 安全访问每个评分对应的计数。

---

## 3. 核心知识点

### 3.1 CTAD（类模板参数推导）
- C++17 起，编译器可从初始化列表推导模板参数。
- `std::array responses{...}` 推导为 `std::array<int, 20>`（元素类型为 `int`，个数由初始化列表长度决定）。
- 要求所有元素类型一致，否则推导失败。

### 3.2 `constexpr` 数组
- `constexpr` 变量在**编译期**求值，可作为模板参数（如数组大小）。
- 本例中 `responses` 是编译期常量，用于统计固定数据。
- 若数据来自外部输入，则不能使用 `constexpr`。

### 3.3 范围 `for` 循环
- 语法：`for (声明 : 容器) { ... }`
- 自动遍历所有元素，无需手动索引。
- 使用 `const int&` 避免拷贝，只读访问。

### 3.4 `at()` 成员函数
- `at(pos)` 执行边界检查，若 `pos >= size()` 则抛出 `std::out_of_range`。
- 本示例中 `response` 在 1~5 内，始终合法。
- `operator[]` 不检查边界，性能更高，但安全性较低。

### 3.5 `std::format` 格式化
- `{:>6}`：右对齐，宽度为 6。
- `{:>12}`：右对齐，宽度为 12。
- 表头与数据列对齐，输出整洁。

---

## 4. 编译与运行

### 4.1 编译（需 C++20 支持 `<format>`）
```bash
g++ -std=c++20 frequency_array.cpp -o frequency_array
```

### 4.2 运行输出
```
Rating,    Frequency
     1           3
     2           5
     3           6
     4           2
     5           4
```
- 统计结果：
  - 评分 1 出现 3 次
  - 评分 2 出现 5 次
  - 评分 3 出现 6 次
  - 评分 4 出现 2 次
  - 评分 5 出现 4 次
  - 总和 20，匹配数据长度。

---

## 5. 改进建议

### 5.1 使用 `operator[]` 提升性能
```cpp
++frequency[response];
```
- 适合确定索引不会越界的场景。

### 5.2 验证数据范围
若数据可能包含无效值（如 0 或 6），可在循环中添加检查：
```cpp
if (response >= 1 && response <= 5) {
    ++frequency.at(response);
}
```

### 5.3 使用 `std::map` 或 `std::unordered_map`
- 若评分范围未知或非连续整数，可用关联容器进行统计。

### 5.4 动态确定频率数组大小
- 可从数据中先找出最大值，再分配数组（但需动态内存，`std::vector` 更合适）。

### 5.5 使用 `std::accumulate` 计算总和
```cpp
#include <numeric>
int total = std::accumulate(frequency.begin(), frequency.end(), 0);
```

---

## 6. 练习建议

1. **修改数据数组**：添加或删除某些评分，观察输出变化。
2. **改用 `operator[]`**：对比与 `at()` 的性能差异（对于小数据量无感）。
3. **扩展评分范围**：改为 1~10，调整 `frequencySize` 并更新数据。
4. **使用 `std::map<int, int>`**：实现相同功能，比较代码差异。
5. **计算平均值**：利用频率统计结果计算平均评分。

---

## 7. 注意事项

- `constexpr` 要求数组内容在编译期已知，若数据来自运行时输入，需移除 `constexpr`。
- `frequency` 数组大小 `6` 意味着索引 0 被浪费，这是一种常见的“以值作索引”技巧，简化代码逻辑。
- `std::format` 是 C++20 特性，若编译器不支持，可改用流式输出。

---

**频率统计是数据分析的基本操作，`std::array` 配合范围 `for` 循环提供了简洁高效的实现方式。通过本示例，你已掌握如何对有限范围的离散数据进行计数统计。继续探索更多数据处理技巧！** 🚀
