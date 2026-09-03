# C++ 入门笔记：二维 `std::array` 与多维数组处理

> 本笔记通过一个 2 行 3 列的二维数组示例，演示 `std::array` 的嵌套声明、初始化、`constexpr` 编译期常量、函数参数传递（引用）以及基于范围的 `for` 循环遍历。

---

## 1. 完整代码示例

```cpp
#include <iostream> 
#include <array> 

constexpr size_t rows{2};
constexpr size_t columns{3};
void printArray(const std::array<std::array<int, columns>, rows>& a);

int main() {
   constexpr std::array values1{std::array{1, 2, 3}, std::array{4, 5, 6}};
   constexpr std::array values2{std::array{1, 2, 3}, std::array{4, 5, 0}};

   std::cout << "values1 by row:\n";
   printArray(values1);

   std::cout << "\nvalues2 by row:\n";
   printArray(values2);
}

// output array with two rows and three columns                 
void printArray(const std::array<std::array<int, columns>, rows>& a) {
   // loop through array's rows             
   for (const auto& row : a) {
      // loop through columns of current row                
      for (const auto& element : row) {
         std::cout << element << ' ';
      }

      std::cout << '\n'; // start new line of output             
   }
}
```

---

## 2. 代码逐行解析

### 2.1 头文件
```cpp
#include <iostream> // 标准输入输出流
#include <array>    // std::array 容器
```
- `<array>` 提供固定大小的数组容器 `std::array`。
- `<iostream>` 提供 `std::cout` 和 `std::endl`。

### 2.2 编译期常量（`constexpr`）
```cpp
constexpr size_t rows{2};
constexpr size_t columns{3};
```
- `rows` 和 `columns` 是 `constexpr` 常量，在编译期确定其值。
- `size_t` 是无符号整数类型，用于表示大小和索引。
- 这些常量作为 `std::array` 的模板参数（必须为编译期常量），同时定义数组的维度。

### 2.3 函数声明（原型）
```cpp
void printArray(const std::array<std::array<int, columns>, rows>& a);
```
- 声明一个函数 `printArray`，接受一个类型为 `std::array<std::array<int, columns>, rows>` 的**常量引用**参数。
- 该参数是一个二维 `std::array`：外层 `std::array` 有 `rows` 个元素，每个元素是一个内层 `std::array<int, columns>`。
- `const` 保证函数不会修改传入的数组。
- 使用引用避免复制整个数组（对于大数组节省性能）。

### 2.4 `main` 函数中的数组初始化
```cpp
constexpr std::array values1{std::array{1, 2, 3}, std::array{4, 5, 6}};
constexpr std::array values2{std::array{1, 2, 3}, std::array{4, 5, 0}};
```
- 使用**类模板参数推导（CTAD，C++17）**：`std::array{1,2,3}` 推导为 `std::array<int, 3>`。
- `values1` 和 `values2` 被推导为 `std::array<std::array<int, 3>, 2>`（即 2 行 3 列）。
- `constexpr` 表示这两个数组可在编译期求值，如果数据是常量，可进一步提升性能。

### 2.5 调用打印函数
```cpp
std::cout << "values1 by row:\n";
printArray(values1);

std::cout << "\nvalues2 by row:\n";
printArray(values2);
```
- 分别打印两个二维数组的内容。

### 2.6 函数定义：`printArray`
```cpp
void printArray(const std::array<std::array<int, columns>, rows>& a) {
   // 遍历行
   for (const auto& row : a) {
      // 遍历当前行的列
      for (const auto& element : row) {
         std::cout << element << ' ';
      }
      std::cout << '\n';
   }
}
```
- 使用**嵌套基于范围的 `for` 循环**遍历二维数组：
  - 外层循环遍历每一行（`row` 是一个 `std::array<int, columns>` 的常量引用）。
  - 内层循环遍历当前行的每个元素（`element` 是 `int` 的常量引用）。
- 每行输出完毕后换行。
- `const auto&` 确保不拷贝元素，提高效率。

---

## 3. 核心知识点

### 3.1 二维 `std::array` 的声明
- **语法**：`std::array<std::array<元素类型, 列数>, 行数> 变量名;`
- 例如：`std::array<std::array<int, 3>, 2> arr;`
- 这是一个嵌套容器，外层管理行，内层管理列。

### 3.2 初始化
- **直接初始化**：`std::array<std::array<int, 3>, 2> arr{{1,2,3},{4,5,6}};`（需双层大括号）。
- **使用 CTAD（C++17）**：`std::array arr{std::array{1,2,3}, std::array{4,5,6}};`（更简洁）。
- 由于内层数组类型相同，CTAD 可推导出完整类型。

### 3.3 函数参数传递
- 传递二维 `std::array` 时，类型声明较长，可使用 `const` 引用避免复制。
- 函数原型中需指定行数和列数（编译期常量），因为它们属于类型的一部分。
- 若行/列为运行时变量，应改用 `std::vector` 或动态分配。

### 3.4 基于范围的 `for` 循环遍历二维数组
- 外层循环遍历行，内层循环遍历列。
- 使用 `auto&` 可自动推导类型，代码简洁且高效。
- 若只需读取，用 `const auto&` 安全并避免拷贝。

### 3.5 `constexpr` 与编译期常量
- 数组维度（`rows`, `columns`）必须是编译期常量，故声明为 `constexpr`。
- `constexpr` 数组也可作为编译期常量，但本例中不是必需的（若数组值在运行时才确定，则不能用 `constexpr`）。

---

## 4. 编译与运行

### 4.1 编译（需 C++17 或更高，CTAD 需要 C++17）
```bash
g++ -std=c++17 array2d.cpp -o array2d
```

### 4.2 运行输出
```
values1 by row:
1 2 3 
4 5 6 

values2 by row:
1 2 3 
4 5 0 
```

---

## 5. 改进建议

### 5.1 使用 `std::array` 的 `size()` 成员
- 在循环中可使用 `row.size()` 获取列数，但这里维度已固定，直接用常量即可。

### 5.2 使用 `using` 别名简化类型
```cpp
using Row = std::array<int, columns>;
using Matrix = std::array<Row, rows>;
void printArray(const Matrix& a);
```

### 5.3 使用 `std::ranges`（C++20）简化遍历
```cpp
#include <ranges>
for (const auto& row : a) {
    for (const auto& elem : row) { ... }
}
```

### 5.4 支持不同行数和列数
- 可将函数改为模板函数，支持任意大小：
```cpp
template<size_t Rows, size_t Cols>
void printArray(const std::array<std::array<int, Cols>, Rows>& a) {
    // ...
}
```

### 5.5 使用 `std::ostream` 进行输出
- 可将 `std::cout` 作为参数传递，更灵活。

---

## 6. 练习建议

1. **修改行列数**：改为 3 行 4 列，更新数据和函数。
2. **使用 `using` 别名**：简化类型声明。
3. **编写模板函数**：使 `printArray` 能处理任意行数和列数的二维数组。
4. **添加 `constexpr` 函数**：尝试在编译期操作二维数组。
5. **初始化时省略类型**：用 CTAD 声明二维数组，验证是否可行（需 C++17）。

---

## 7. 注意事项

- `std::array` 的嵌套要求内部数组类型完全相同（包括元素类型和大小）。
- 函数参数类型中的 `columns` 和 `rows` 必须是编译期常量，因此它们被声明为 `constexpr`。
- CTAD 需要 C++17，若使用 C++14 或更早，需显式指定类型。
- 基于范围的 `for` 循环遍历二维数组时，外层循环的 `row` 是引用，内层循环的 `element` 也是引用（或值，取决于声明）。使用 `const auto&` 可避免复制。

---

**二维 `std::array` 是处理表格数据的轻量级工具，与标准库算法和范围 `for` 循环配合使用，可写出清晰高效的代码。掌握多维数组的用法，为后续学习更复杂的数据结构打下基础。** 🚀
