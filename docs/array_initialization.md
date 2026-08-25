# C++ 入门笔记：`std::array` 固定大小数组

> 本笔记涵盖 `std::array` 的声明与初始化、元素访问（`at()`）、大小获取（`size()`）、C++17 类模板参数推导（CTAD）以及 C++20 `std::format` 输出。

---

## 1. 完整代码示例

```cpp
#include <format>
#include <iostream>
#include <array>

int main() {
   std::array<int, 5> values{32, 27, 64, 18, 95}; // 大括号初始化

   // 输出每个数组元素
   for (size_t i{0}; i < values.size(); ++i) {
      std::cout << std::format("{}  ", values.at(i));
   }

   std::cout << "\n\n";

   // 使用类模板参数推导（CTAD）确定 values2 的类型
   std::array values2{1.1, 2.2, 3.3, 4.4};

   // 输出每个数组元素
   for (size_t i{0}; i < values2.size(); ++i) {
      std::cout << std::format("{}  ", values2.at(i));
   }

   std::cout << '\n';
}
```

---

## 2. 代码逐行解析

### 2.1 头文件
```cpp
#include <format>   // C++20 格式化输出
#include <iostream> // 标准输入输出流
#include <array>    // std::array 容器
```
- `<array>` 定义了 `std::array`，是 C++11 引入的固定大小数组容器。

### 2.2 声明与初始化 `std::array`
```cpp
std::array<int, 5> values{32, 27, 64, 18, 95};
```
- `std::array<int, 5>` 表示一个包含 5 个 `int` 元素的数组。
- 使用**大括号初始化列表**（`{}`）初始化所有元素。
- 如果初始化列表元素个数少于数组大小，剩余元素会被**值初始化**（对于基本类型为 0）。
- 如果元素个数多于数组大小，会编译错误。

### 2.3 访问元素：`at()` 与 `[]`
```cpp
for (size_t i{0}; i < values.size(); ++i) {
    std::cout << std::format("{}  ", values.at(i));
}
```
- `values.size()` 返回 `size_t` 类型，表示数组元素个数。
- `values.at(i)` 访问索引 `i` 处的元素，并**进行边界检查**，若越界则抛出 `std::out_of_range` 异常。
- 对应的 `operator[]` 不检查边界，效率稍高但更危险。
- 推荐在调试阶段使用 `at()`，性能敏感且确保不越界时可用 `[]`。

### 2.4 类模板参数推导（CTAD）
```cpp
std::array values2{1.1, 2.2, 3.3, 4.4};
```
- C++17 起，编译器可以从初始化列表推导出模板参数。
- 此处推导为 `std::array<double, 4>`（因为所有元素都是 `double`）。
- 注意：`std::array` 的 CTAD 需要所有元素类型一致，否则推导失败。

### 2.5 输出与格式化
- 使用 `std::format` 输出，占位符 `{}` 依次替换为后面的值。
- `std::format` 是 C++20 新增的类型安全格式化库，优于 `printf` 和流式输出。

---

## 3. 核心知识点

### 3.1 `std::array` 的模板参数
```cpp
std::array<类型, 大小> 变量名;
```
- `类型`：元素类型（如 `int`, `double`）。
- `大小`：编译期常量表达式（如 `5`, `N`）。

### 3.2 成员函数
| 函数 | 说明 |
|------|------|
| `at(pos)` | 访问指定位置，边界检查（抛出异常） |
| `operator[](pos)` | 无边界检查访问 |
| `size()` | 返回元素个数（`constexpr`） |
| `empty()` | 判断是否为空（恒为 `false`，但用于泛型） |
| `front()` / `back()` | 访问首/尾元素 |

### 3.3 与 C 风格数组的比较
| 特性 | `std::array` | C 风格数组 |
|------|--------------|------------|
| 类型安全 | 是 | 否（退化指针） |
| 边界检查（`at()`） | 支持 | 需手动 |
| 复制/赋值 | 支持（`=`） | 不支持 |
| 作为函数参数 | 按值传递（复制）或引用 | 退化为指针，需传递大小 |

### 3.4 类模板参数推导（CTAD）
- 从初始化列表自动推导模板参数（C++17）。
- 需要包含 `<array>` 头文件，并确保所有元素类型相同。

---

## 4. 编译与运行

### 4.1 编译（需 C++20 支持 `<format>`）
```bash
g++ -std=c++20 array_demo.cpp -o array_demo
```
若编译器不支持 `<format>`，可用传统输出替代：
```cpp
std::cout << values.at(i) << "  ";
```

### 4.2 运行输出
```
32  27  64  18  95  

1.1  2.2  3.3  4.4  
```

---

## 5. 改进建议

1. **使用范围 `for` 循环简化输出**：
   ```cpp
   for (const auto& v : values) {
       std::cout << std::format("{}  ", v);
   }
   ```
2. **使用 `std::span`（C++20）** 传递数组视图（更灵活）。
3. **用 `constexpr` 数组**：若数组内容编译期已知，可声明为 `constexpr std::array<int, 5> values{...};`。
4. **边界检查性能**：在性能关键路径用 `operator[]`，调试用 `at()`。

---

## 6. 练习建议

1. **修改数组大小**，观察编译期常量的要求。
2. **尝试 `operator[]` 越界访问**，对比 `at()` 的行为。
3. **使用类模板参数推导**，并测试不同元素类型（如混合 `int` 和 `double`）会导致错误。
4. **用 `std::array` 存储自定义类型**（如 `struct`），练习初始化。
5. **复制和赋值**：将一个 `std::array` 赋值给另一个（支持 `=`）。

---

## 7. 扩展：为什么不用 C 风格数组？

- 缺乏成员函数，不便于获取大小。
- 容易退化为指针，丢失大小信息。
- 复制和赋值需手动。
- `std::array` 提供了标准容器接口，便于泛型算法（如 `std::sort`）。

---

**`std::array` 是 C++ 中替代原生数组的首选容器，兼顾了性能与安全性。掌握它，让你的代码更现代、更健壮！** 🚀
```
