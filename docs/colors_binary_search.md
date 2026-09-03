# C++ 入门笔记：`std::array` 排序与二分查找

> 本笔记通过颜色数组的排序与搜索，演示 `std::array` 的类模板参数推导（CTAD）、C++14 字符串字面量、`std::sort` 排序、`std::binary_search` 二分查找以及条件运算符 `?:` 在格式化输出中的应用。

---

## 1. 完整代码示例

```cpp
#include <array>
#include <algorithm> // contains sort and binary_search
#include <format>
#include <iostream>
#include <string>

int main() {
   using namespace std::string_literals; // enables string object literals

   // colors is inferred to be an array<string, 7>
   std::array colors{"red"s, "orange"s, "yellow"s,
      "green"s, "blue"s, "indigo"s, "violet"s};

   // output original array
   std::cout << "Unsorted colors array:\n   ";
   for (const std::string& color : colors) {
      std::cout << std::format("{} ", color);
   }

   // sort contents of colors
   std::sort(std::begin(colors), std::end(colors));

   // output sorted array
   std::cout << "\nSorted colors array:\n   ";
   for (const std::string& color : colors) {
      std::cout << std::format("{} ", color);
   }

   // search for "indigo" in colors
   bool found{std::binary_search(
      std::begin(colors), std::end(colors), "indigo")};
   std::cout << std::format("\n\n\"indigo\" {} found in colors array\n",
      found ? "was" : "was not");

   // search for "cyan" in colors
   found = std::binary_search(
      std::begin(colors), std::end(colors), "cyan");
   std::cout << std::format("\"cyan\" {} found in colors array\n",
      found ? "was" : "was not");
}
```

---

## 2. 代码逐行解析

### 2.1 头文件
```cpp
#include <array>     // std::array 容器
#include <algorithm> // std::sort, std::binary_search
#include <format>    // C++20 格式化输出
#include <iostream>  // 标准输入输出流
#include <string>    // std::string
```
- `<algorithm>` 提供了通用算法，如排序和二分查找。

### 2.2 字符串字面量
```cpp
using namespace std::string_literals; // enables string object literals
```
- 启用 C++14 字符串字面量后缀 `s`。
- `"red"s` 创建一个 `std::string` 对象，而非 C 风格字符串（`const char*`）。
- 这使得 CTAD 能够正确推导元素类型为 `std::string`。

### 2.3 使用 CTAD 声明 `std::array`
```cpp
std::array colors{"red"s, "orange"s, "yellow"s,
   "green"s, "blue"s, "indigo"s, "violet"s};
```
- 使用**类模板参数推导（CTAD，C++17）**，推导出 `std::array<std::string, 7>`。
- 所有元素都是 `std::string` 类型，因为使用了 `s` 后缀。
- 若写成 `"red"` 没有 `s`，元素类型为 `const char*`，比较时按指针地址而非字符串内容，会导致错误。

### 2.4 输出原始数组
```cpp
std::cout << "Unsorted colors array:\n   ";
for (const std::string& color : colors) {
    std::cout << std::format("{} ", color);
}
```
- 范围 `for` 循环遍历所有颜色，用常量引用避免拷贝。
- 输出顺序：`red orange yellow green blue indigo violet`。

### 2.5 排序
```cpp
std::sort(std::begin(colors), std::end(colors));
```
- `std::sort` 对序列进行升序排序。
- `std::begin(colors)` 和 `std::end(colors)` 返回迭代器，指向数组首尾。
- 排序按字典序（字母顺序）排列字符串。
- 排序后顺序：`blue green indigo orange red violet yellow`。

### 2.6 输出排序后的数组
```cpp
std::cout << "\nSorted colors array:\n   ";
for (const std::string& color : colors) {
    std::cout << std::format("{} ", color);
}
```
- 输出排序后的颜色列表。

### 2.7 二分查找 `"indigo"`
```cpp
bool found{std::binary_search(
    std::begin(colors), std::end(colors), "indigo")};
std::cout << std::format("\n\n\"indigo\" {} found in colors array\n",
    found ? "was" : "was not");
```
- `std::binary_search` 在**已排序**序列中执行二分查找，时间复杂度 `O(log n)`。
- 如果找到目标，返回 `true`，否则 `false`。
- `found ? "was" : "was not"` 是条件运算符（三元运算符），根据 `found` 选择字符串。
- 输出：`"indigo" was found in colors array`。

### 2.8 二分查找 `"cyan"`
```cpp
found = std::binary_search(
    std::begin(colors), std::end(colors), "cyan");
std::cout << std::format("\"cyan\" {} found in colors array\n",
    found ? "was" : "was not");
```
- 查找 `"cyan"`，不存在于颜色列表中。
- 输出：`"cyan" was not found in colors array`。

---

## 3. 核心知识点

### 3.1 字符串字面量 `s`（C++14）
- `std::string_literals` 命名空间包含 `operator""s`，用于创建 `std::string`。
- 使用 `s` 后缀可避免类型混淆（`const char*` vs `std::string`）。
- 示例：
  ```cpp
  auto str1 = "hello";   // const char*
  auto str2 = "hello"s;  // std::string
  ```

### 3.2 `std::sort` 排序
- 头文件：`<algorithm>`
- 默认升序排列，使用 `operator<` 比较元素。
- 接受两个迭代器（`begin` 和 `end`），表示要排序的范围。
- 时间复杂度：`O(n log n)`。

### 3.3 `std::binary_search` 二分查找
- 头文件：`<algorithm>`
- 要求序列**已排序**（否则行为未定义）。
- 接受三个参数：`begin`、`end`、`value`，返回 `bool`。
- 时间复杂度：`O(log n)`。
- 只能判断是否存在，不能返回位置（如需位置，用 `std::lower_bound`）。

### 3.4 迭代器
- `std::begin(colors)` 返回指向第一个元素的迭代器。
- `std::end(colors)` 返回指向**最后一个元素之后**的迭代器（哨兵）。
- 迭代器是泛型指针，支持解引用和遍历。

### 3.5 条件运算符 `?:`
- 语法：`条件 ? 表达式1 : 表达式2`
- 若条件为真，返回表达式1；否则返回表达式2。
- 本例中用于根据 `found` 选择字符串 `"was"` 或 `"was not"`。

---

## 4. 编译与运行

### 4.1 编译（需 C++20 支持 `<format>`）
```bash
g++ -std=c++20 color_search.cpp -o color_search
```

### 4.2 运行输出
```
Unsorted colors array:
   red orange yellow green blue indigo violet 
Sorted colors array:
   blue green indigo orange red violet yellow 

"indigo" was found in colors array
"cyan" was not found in colors array
```

---

## 5. 改进建议

### 5.1 使用 `std::ranges` 算法（C++20）
```cpp
#include <ranges>
std::ranges::sort(colors);
auto found = std::ranges::binary_search(colors, "indigo");
```
- `std::ranges` 版本更简洁，可直接传递容器，无需 `begin/end`。

### 5.2 使用 `std::lower_bound` 获取位置
```cpp
auto it = std::lower_bound(colors.begin(), colors.end(), "indigo");
if (it != colors.end() && *it == "indigo") {
    std::cout << "Found at index " << std::distance(colors.begin(), it);
}
```

### 5.3 使用 `std::find`（线性查找）
若序列未排序，用 `std::find`：
```cpp
auto it = std::find(colors.begin(), colors.end(), "indigo");
bool found = (it != colors.end());
```
- 时间复杂度 `O(n)`，但无需排序。

### 5.4 将搜索词作为变量
```cpp
std::string searchTerm{"indigo"};
bool found = std::binary_search(colors.begin(), colors.end(), searchTerm);
```

### 5.5 添加更多颜色
- 扩展 `colors` 数组，观察排序和查找结果。

---

## 6. 练习建议

1. **添加新颜色**：如 `"pink"`、`"cyan"`，重新编译运行，观察查找结果。
2. **使用 `std::ranges::sort`**：尝试用 C++20 的 ranges 版本简化代码。
3. **实现线性查找**：用 `std::find` 搜索 `"cyan"`，与 `std::binary_search` 对比。
4. **自定义排序规则**：按字符串长度排序（使用 lambda 和 `std::sort`）。
5. **查找并输出索引**：用 `std::lower_bound` 找到元素并计算索引位置。

---

## 7. 注意事项

- `std::binary_search` 要求序列**已按升序排列**，且必须使用相同的比较规则（默认 `operator<`）。
- 字符串比较是字典序（区分大小写），"Red" 和 "red" 会被视为不同。
- `std::begin` 和 `std::end` 可作用于所有标准容器和 C 风格数组（需包含 `<iterator>`）。
- `std::format` 是 C++20 特性，若编译器不支持，可改用流式输出。

---

**标准库算法是 C++ 的强大武器，`std::sort` 和 `std::binary_search` 组合可实现高效的排序与查找。掌握这些工具，你就能轻松处理各种数据操作任务。继续探索标准库的更多算法！** 🚀
