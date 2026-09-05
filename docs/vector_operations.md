# C++ 入门笔记：`std::vector` 动态数组

> 本笔记通过一个完整的示例，演示 `std::vector` 的声明、初始化、大小获取、元素访问（`at()`）、拷贝构造、赋值、关系运算符比较、动态扩容（`push_back`）以及异常处理。

---

## 1. 完整代码示例

```cpp
#include <iostream>
#include <vector>    
#include <stdexcept> 

void outputVector(const std::vector<int>& items); // 显示向量内容
void inputVector(std::vector<int>& items);        // 向向量输入值

int main() {
   std::vector<int> integers1(7); // 7 个元素的 vector<int>
   std::vector<int> integers2(10); // 10 个元素的 vector<int>

   // 输出 integers1 的大小和内容
   std::cout << "Size of vector integers1 is " << integers1.size()
      << "\nvector after initialization: ";
   outputVector(integers1);

   // 输出 integers2 的大小和内容
   std::cout << "\nSize of vector integers2 is " << integers2.size()
      << "\nvector after initialization: ";
   outputVector(integers2);

   // 输入并输出 integers1 和 integers2
   std::cout << "\nEnter 17 integers:\n";
   inputVector(integers1);
   inputVector(integers2);

   std::cout << "\nAfter input, the vectors contain:\n"
      << "integers1: ";
   outputVector(integers1);
   std::cout << "integers2: ";
   outputVector(integers2);

   // 使用不等号运算符 (!=)
   std::cout << "\nEvaluating: integers1 != integers2\n";
   if (integers1 != integers2) {
      std::cout << "integers1 and integers2 are not equal\n";
   }

   // 用 integers1 拷贝构造 integers3
   std::vector integers3{integers1}; // 拷贝构造（C++17 类模板推导）
   std::cout << "\nSize of vector integers3 is " << integers3.size()
      << "\nvector after initialization: ";
   outputVector(integers3);

   // 使用赋值运算符 (=)
   std::cout << "\nAssigning integers2 to integers1:\n";
   integers1 = integers2;

   std::cout << "integers1: ";
   outputVector(integers1);
   std::cout << "integers2: ";
   outputVector(integers2);

   // 使用相等运算符 (==)
   std::cout << "\nEvaluating: integers1 == integers2\n";
   if (integers1 == integers2) {
      std::cout << "integers1 and integers2 are equal\n";
   }

   // 使用 at() 作为右值
   std::cout << "\nintegers1.at(5) is " << integers1.at(5);

   // 使用 at() 作为左值
   std::cout << "\n\nAssigning 1000 to integers1.at(5)\n";
   integers1.at(5) = 1000;
   std::cout << "integers1: ";
   outputVector(integers1);

   // 尝试越界访问
   try {
      std::cout << "\nAttempt to display integers1.at(15)\n";
      std::cout << integers1.at(15) << '\n'; // 抛出 out_of_range 异常
   }
   catch (const std::out_of_range& ex) {
      std::cerr << "An exception occurred: " << ex.what() << '\n';
   }

   // 改变向量大小（动态扩容）
   std::cout << "\nCurrent integers3 size is: " << integers3.size();
   integers3.push_back(1000); // 在末尾添加元素
   std::cout << "\nNew integers3 size is: " << integers3.size()
      << "\nintegers3 now contains: ";
   outputVector(integers3);
}

// 输出向量内容
void outputVector(const std::vector<int>& items) {
   for (const int& item : items) {
      std::cout << item << ' ';
   }
   std::cout << '\n';
}

// 输入向量内容
void inputVector(std::vector<int>& items) {
   for (int& item : items) {
      std::cin >> item;
   }
}
```

---

## 2. 代码逐行解析

### 2.1 头文件
```cpp
#include <iostream>   // 标准输入输出流
#include <vector>     // std::vector 容器
#include <stdexcept>  // std::out_of_range 异常
```
- `<vector>` 提供动态数组容器 `std::vector`。
- `<stdexcept>` 定义了标准异常类，如 `std::out_of_range`。

### 2.2 函数声明
```cpp
void outputVector(const std::vector<int>& items);
void inputVector(std::vector<int>& items);
```
- `outputVector`：常量引用传递，只读访问。
- `inputVector`：非 const 引用，可修改向量内容。

### 2.3 构造向量
```cpp
std::vector<int> integers1(7);  // 7 个元素，默认初始化为 0
std::vector<int> integers2(10); // 10 个元素，默认初始化为 0
```
- `vector<int>(n)` 构造一个包含 `n` 个元素的向量，元素值初始化为 0（对于基本类型）。
- 此构造函数是 `explicit` 的，不能隐式转换。

### 2.4 输出初始向量
```cpp
std::cout << "Size of vector integers1 is " << integers1.size()
          << "\nvector after initialization: ";
outputVector(integers1);
```
- `size()` 返回向量中元素个数，类型为 `size_t`。
- `outputVector` 用范围 `for` 循环遍历并输出所有元素。

### 2.5 输入数据
```cpp
inputVector(integers1);
inputVector(integers2);
```
- `inputVector` 通过引用修改向量，用 `std::cin` 逐个读取元素。
- 注意：输入数量必须匹配向量大小，否则 `cin` 会出错。

### 2.6 向量比较（`!=` 和 `==`）
```cpp
if (integers1 != integers2) { ... }
if (integers1 == integers2) { ... }
```
- `std::vector` 重载了关系运算符，按元素依次比较（字典序）。
- 先比较大小，再逐个元素比较。

### 2.7 拷贝构造与赋值
```cpp
std::vector integers3{integers1}; // 拷贝构造（C++17 类模板推导）
integers1 = integers2;            // 赋值运算符
```
- 拷贝构造：用 `integers1` 创建 `integers3` 的副本。
- 赋值：将 `integers2` 的内容复制给 `integers1`，`integers1` 原来的元素被替换。
- 两者都是深拷贝（新分配内存）。

### 2.8 访问元素：`at()` 与边界检查
```cpp
std::cout << integers1.at(5);
integers1.at(5) = 1000;
```
- `at(pos)` 返回索引 `pos` 处元素的引用，并**进行边界检查**。
- 若 `pos >= size()`，抛出 `std::out_of_range` 异常。
- 可作为右值（读取）或左值（赋值）使用。

### 2.9 异常捕获
```cpp
try {
    std::cout << integers1.at(15) << '\n';
} catch (const std::out_of_range& ex) {
    std::cerr << "An exception occurred: " << ex.what() << '\n';
}
```
- 尝试访问越界索引 15（`integers1` 大小为 10），抛出异常。
- `ex.what()` 返回描述错误的 C 风格字符串。
- 捕获后程序继续执行，不会崩溃。

### 2.10 动态扩容：`push_back`
```cpp
integers3.push_back(1000);
```
- `push_back` 在向量末尾添加一个新元素，若容量不足则自动重新分配内存（扩容）。
- `size()` 增加 1，`capacity()` 可能增大。

---

## 3. 核心知识点

### 3.1 `std::vector` 的构造方式
| 写法 | 说明 |
|------|------|
| `vector<int> v;` | 空向量 |
| `vector<int> v(n);` | n 个元素，值初始化（基本类型为 0） |
| `vector<int> v(n, val);` | n 个元素，每个初始化为 `val` |
| `vector<int> v{1,2,3};` | 列表初始化（C++11） |
| `vector<int> v = {1,2,3};` | 同上 |
| `vector<int> v(other);` | 拷贝构造 |

### 3.2 成员函数
| 函数 | 说明 |
|------|------|
| `size()` | 返回元素个数 |
| `capacity()` | 返回当前分配的内存能容纳的元素数 |
| `empty()` | 是否为空 |
| `at(pos)` | 访问元素，边界检查 |
| `operator[](pos)` | 访问元素，无边界检查 |
| `push_back(val)` | 在末尾添加元素 |
| `pop_back()` | 删除末尾元素 |
| `insert(pos, val)` | 在指定位置插入 |
| `erase(pos)` | 删除指定位置元素 |
| `clear()` | 清空所有元素 |
| `resize(n)` | 调整大小，新元素值初始化 |
| `reserve(n)` | 预分配内存，但不改变大小 |
| `assign(n, val)` | 重新赋值 |

### 3.3 迭代器
- `begin()` / `end()` 返回迭代器，支持 STL 算法。
- 范围 `for` 循环基于迭代器实现。

### 3.4 深拷贝与浅拷贝
- `std::vector` 拷贝构造和赋值执行**深拷贝**，独立管理各自的内存。
- 修改一个向量的元素不会影响另一个。

### 3.5 动态扩容机制
- 当 `push_back` 导致大小超过容量时，`vector` 会分配更大的内存（通常翻倍），将所有元素迁移到新内存，再添加新元素。
- 扩容开销较大，但平均复杂度为 `O(1)`（摊还分析）。

### 3.6 异常安全
- `at()` 提供边界检查，在越界时抛出 `std::out_of_range`。
- 使用 `try-catch` 可安全处理，避免程序崩溃。

---

## 4. 编译与运行

### 4.1 编译（需 C++17 或更高，支持类模板推导）
```bash
g++ -std=c++17 vector_demo.cpp -o vector_demo
```

### 4.2 运行示例（输入 17 个整数）
```
Size of vector integers1 is 7
vector after initialization: 0 0 0 0 0 0 0 

Size of vector integers2 is 10
vector after initialization: 0 0 0 0 0 0 0 0 0 0 

Enter 17 integers:
1 2 3 4 5 6 7
8 9 10 11 12 13 14 15 16 17

After input, the vectors contain:
integers1: 1 2 3 4 5 6 7 
integers2: 8 9 10 11 12 13 14 15 16 17 

Evaluating: integers1 != integers2
integers1 and integers2 are not equal

Size of vector integers3 is 7
vector after initialization: 1 2 3 4 5 6 7 

Assigning integers2 to integers1:
integers1: 8 9 10 11 12 13 14 15 16 17 
integers2: 8 9 10 11 12 13 14 15 16 17 

Evaluating: integers1 == integers2
integers1 and integers2 are equal

integers1.at(5) is 13

Assigning 1000 to integers1.at(5)
integers1: 8 9 10 11 12 1000 14 15 16 17 

Attempt to display integers1.at(15)
An exception occurred: vector::_M_range_check: __n (which is 15) >= this->size() (which is 10)

Current integers3 size is: 7
New integers3 size is: 8
integers3 now contains: 1 2 3 4 5 6 7 1000 
```

---

## 5. 改进建议

### 5.1 使用 `std::vector` 的 `reserve` 预分配容量
```cpp
integers3.reserve(100); // 提前分配，避免多次扩容
```

### 5.2 使用 `emplace_back` 代替 `push_back` 构造对象
```cpp
integers3.emplace_back(1000); // 直接构造，避免临时对象
```

### 5.3 使用 `std::array` 替代固定大小向量
- 若大小在编译期确定且不变，`std::array` 更轻量。

### 5.4 使用 `const_iterator` 输出
- `outputVector` 已用 `const` 引用，合理。

### 5.5 使用 `std::initializer_list` 初始化
```cpp
std::vector<int> v{1, 2, 3, 4, 5};
```

---

## 6. 练习建议

1. **测试 `operator[]` 越界**：用 `integers1[15]` 替换 `at(15)`，观察行为（可能崩溃或返回垃圾值）。
2. **添加 `reserve` 和 `capacity` 输出**：查看扩容过程。
3. **使用 `insert` 和 `erase`** 在任意位置操作元素。
4. **尝试 `resize`** 改变向量大小，观察新增元素的默认值。
5. **使用 `std::sort` 对向量排序**，结合 `<algorithm>`。

---

## 7. 注意事项

- `at()` 比 `operator[]` 更安全，但稍慢（有边界检查开销）。
- 拷贝和赋值操作涉及深拷贝，性能代价较大，考虑使用移动语义（C++11）避免不必要的复制。
- `push_back` 在元素类型为自定义类时，需确保该类可拷贝/移动。
- `vector` 在重新分配内存时会使所有迭代器、引用和指针失效，需谨慎。

---

**`std::vector` 是 C++ 中最常用的动态数组容器，灵活且强大。掌握它的构造、访问、比较和动态扩容机制，你就能高效地管理动态数据集合。继续探索其他 STL 容器！** 🚀
