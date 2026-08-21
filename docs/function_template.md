# C++ 入门笔记：函数模板（Function Templates）

> 本笔记通过求最大值的示例，介绍 C++ 中函数模板的语法、实例化机制及其与函数重载的关系，实现类型无关的通用算法。

---

## 1. 完整代码示例（修正版）

原始代码中存在错误：模板定义被错误地放在了 `main` 函数内部。以下是正确版本：

### 方式一：单文件实现（推荐学习用）
```cpp
#include <iostream>

// 函数模板定义
template <typename T>
T maximum(T value1, T value2, T value3) {
    T maximumValue{value1};

    if (value2 > maximumValue) {
        maximumValue = value2;
    }
    if (value3 > maximumValue) {
        maximumValue = value3;
    }
    return maximumValue;
}

int main() {
    // 测试 int
    std::cout << "Input three integer values: ";
    int int1, int2, int3;
    std::cin >> int1 >> int2 >> int3;
    std::cout << "The maximum integer value is: " << maximum(int1, int2, int3) << '\n';

    // 测试 double
    std::cout << "\nInput three double values: ";
    double double1, double2, double3;
    std::cin >> double1 >> double2 >> double3;
    std::cout << "The maximum double value is: " << maximum(double1, double2, double3) << '\n';

    // 测试 char
    std::cout << "\nInput three characters: ";
    char char1, char2, char3;
    std::cin >> char1 >> char2 >> char3;
    std::cout << "The maximum character value is: " << maximum(char1, char2, char3) << '\n';

    return 0;
}
```

### 方式二：分文件组织（大型项目常用）
**maximum.h**
```cpp
#ifndef MAXIMUM_H
#define MAXIMUM_H

template <typename T>
T maximum(T value1, T value2, T value3);

// 模板定义通常放在头文件中（因为实例化需要完整定义）
template <typename T>
T maximum(T value1, T value2, T value3) {
    T maxVal = value1;
    if (value2 > maxVal) maxVal = value2;
    if (value3 > maxVal) maxVal = value3;
    return maxVal;
}

#endif
```

**main.cpp**
```cpp
#include "maximum.h"
#include <iostream>

int main() {
    // 同上述 main 函数
}
```

编译命令：
```bash
g++ -std=c++17 main.cpp -o max
```

---

## 2. 代码逐行解析（单文件版）

### 2.1 函数模板定义
```cpp
template <typename T>
T maximum(T value1, T value2, T value3) {
    T maximumValue{value1};
    if (value2 > maximumValue) maximumValue = value2;
    if (value3 > maximumValue) maximumValue = value3;
    return maximumValue;
}
```
- `template <typename T>` 声明这是一个模板，`T` 是一个**类型参数**，代表任意类型。
- 函数体中使用 `T` 来声明变量、参数和返回值。
- 在编译时，编译器会根据调用时传入的实参类型，**实例化**出具体的函数版本（例如 `int maximum(int,int,int)`）。

### 2.2 `main` 函数中的调用
```cpp
maximum(int1, int2, int3)   // 推断 T = int
maximum(double1, double2, double3) // 推断 T = double
maximum(char1, char2, char3) // 推断 T = char
```
- 每次调用，编译器自动从实参推导出 `T` 的具体类型，并生成对应版本的代码。
- 整个过程是**编译期多态**，没有运行时开销。

---

## 3. 核心知识点

### 3.1 模板的基本语法
| 部分 | 说明 |
|------|------|
| `template <typename T>` | 模板参数列表，`typename` 也可用 `class`（效果相同） |
| `T` | 类型参数，可被任意类型替换 |
| 函数体 | 使用 `T` 作为类型，定义通用算法 |

### 3.2 模板实例化
- **隐式实例化**：编译器根据实参类型自动推导 `T`，生成对应的函数定义。
- **显式实例化**：`template int maximum<int>(int, int, int);`（较少用）。

### 3.3 模板参数推断
- 编译器从实参类型推断 `T`。若实参类型不一致，可能导致推断失败（例如 `maximum(1, 2.5, 3)`，`T` 无法统一），此时需显式指定类型或转换。

### 3.4 模板与重载的对比
| 特性 | 函数模板 | 函数重载 |
|------|----------|----------|
| **代码量** | 一份通用代码 | 每个类型单独定义 |
| **类型安全** | 是（编译期检查） | 是 |
| **可维护性** | 高（修改一处即可） | 低（需修改多处） |
| **适用场景** | 算法与类型无关 | 不同类型有不同行为 |
| **实例化** | 按需生成 | 已预先定义 |

---

## 4. 代码风格与改进

### 4.1 使用 `const` 引用避免拷贝
对于大型对象，可改为 `const T&` 传递：
```cpp
template <typename T>
const T& maximum(const T& value1, const T& value2, const T& value3) {
    const T* maxVal = &value1;
    if (value2 > *maxVal) maxVal = &value2;
    if (value3 > *maxVal) maxVal = &value3;
    return *maxVal;
}
```
- 返回 `const` 引用，避免拷贝。

### 4.2 使用 `std::max` 简化
```cpp
#include <algorithm>
template <typename T>
T maximum(T a, T b, T c) {
    return std::max({a, b, c}); // C++11 initializer_list
}
```

### 4.3 处理不同类型混合的情况
若希望接受不同类型，可使用多个模板参数：
```cpp
template <typename T1, typename T2, typename T3>
auto maximum(T1 a, T2 b, T3 c) {
    // 需要确定返回类型，可用 decltype 或 common_type
    using common = std::common_type_t<T1, T2, T3>;
    return std::max({common(a), common(b), common(c)});
}
```

### 4.4 头文件中的模板
- 模板的定义通常放在头文件中，因为编译器需要在实例化点看到完整定义。
- 使用头文件保护符（`#ifndef`）避免重复包含。

---

## 5. 编译与运行

### 5.1 编译（单文件）
```bash
g++ -std=c++17 max_template.cpp -o max_template
```

### 5.2 运行示例
```
Input three integer values: 5 8 3
The maximum integer value is: 8

Input three double values: 4.5 9.2 6.1
The maximum double value is: 9.2

Input three characters: z a m
The maximum character value is: z
```

---

## 6. 常见错误与注意事项

1. **模板定义放在 `.cpp` 文件**：通常会导致链接错误，除非显式实例化。应放在头文件中。
2. **类型不匹配**：如 `maximum(1, 2.5, 3)` 会导致 `T` 推导失败，需显式转换或使用多模板参数。
3. **运算符支持**：模板中使用的运算符（如 `>`）必须对实例化类型有效，否则编译错误。
4. **默认模板参数**：C++11 允许默认模板参数（如 `template <typename T = int>`）。
5. **分离编译**：模板不支持传统的声明与定义分离，除非使用 `export`（C++20 已移除）或显式实例化。

---

## 7. 练习建议

1. **修改为 `const` 引用版本**，观察对 `std::string` 的支持。
2. **编写 `minimum` 模板**，返回最小值。
3. **编写 `print` 模板**，输出任意类型和数量的参数（使用变参模板）。
4. **使用 `std::common_type` 实现混合类型的最大值**。
5. **显式实例化 `maximum<int>` 和 `maximum<double>`**，观察生成的汇编代码。

---

## 8. 扩展：类模板简介

类似地，也可定义类模板，例如：
```cpp
template <typename T>
class Box {
    T value;
public:
    Box(T v) : value(v) {}
    T get() const { return value; }
};
```
使用：`Box<int> b(5);`

---

**函数模板是 C++ 泛型编程的基石，让你能编写与类型无关的通用代码。掌握它，你就能写出更灵活、更可复用的程序！继续探索模板的威力！** 🚀
