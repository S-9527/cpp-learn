# C++ 入门笔记：函数定义与参数传递（求最大值）

> 本笔记涵盖函数声明（原型）、函数定义、参数传递、局部变量、返回值，以及如何通过函数封装逻辑。

---

## 1. 完整代码示例

```cpp
#include <iostream>

int maximum(int x, int y, int z);

int main()
{
  std::cout << "Enter three integer values: ";
  int int1, int2, int3;
  std::cin >> int1 >> int2 >> int3;

  std::cout << "The maximum integer value is: "
            << maximum(int1, int2, int3) << '\n';
  return 0;
}

int maximum(int x, int y, int z)
{
  int maximumValue{x};

  if (y > maximumValue)
  {
    maximumValue = y;
  }

  if (z > maximumValue)
  {
    maximumValue = z;
  }

  return maximumValue;
}
```

---

## 2. 代码逐行解析

### 2.1 头文件
```cpp
#include <iostream>
```
- 标准输入输出流，用于 `std::cin` 和 `std::cout`。

### 2.2 函数声明（原型）
```cpp
int maximum(int x, int y, int z);
```
- **函数原型**：告诉编译器函数的存在，包括返回类型、函数名和参数列表（类型及可选的参数名）。
- 原型放在调用之前，以便 `main` 函数在调用 `maximum` 时知道它的签名。
- 如果省略原型，编译器会报错“未声明标识符”。

### 2.3 `main` 函数
```cpp
int main()
{
  std::cout << "Enter three integer values: ";
  int int1, int2, int3;
  std::cin >> int1 >> int2 >> int3;

  std::cout << "The maximum integer value is: "
            << maximum(int1, int2, int3) << '\n';
  return 0;
}
```
- 提示用户输入三个整数。
- 声明三个 `int` 变量，从 `std::cin` 读取。
- 调用 `maximum` 函数，传入三个参数，返回值直接插入到输出流中。
- 输出结果并换行。

### 2.4 函数定义
```cpp
int maximum(int x, int y, int z)
{
  int maximumValue{x};

  if (y > maximumValue)
  {
    maximumValue = y;
  }

  if (z > maximumValue)
  {
    maximumValue = z;
  }

  return maximumValue;
}
```
- 函数定义以返回类型 `int` 开头，后跟函数名和形参列表。
- 形参 `x, y, z` 是局部变量，在函数调用时由实参初始化。
- 内部声明 `maximumValue`，初始化为 `x` 的值。
- 依次比较 `y` 和 `z`，若比当前最大值大则更新。
- 最后返回 `maximumValue`。

---

## 3. 核心知识点

### 3.1 函数的基本结构
| 组成部分 | 说明 |
|----------|------|
| **返回类型** | 函数返回值的类型（`int`, `void`, 自定义等） |
| **函数名** | 标识符，用于调用 |
| **形参列表** | 括号内用逗号分隔的参数类型和名称（可为空） |
| **函数体** | 用 `{}` 包裹的语句块，包含实现逻辑 |
| **返回值** | 使用 `return` 语句返回结果（若返回类型非 `void`） |

### 3.2 函数声明 vs 定义
- **声明（原型）**：只提供签名，不包含函数体，通常放在头文件或调用之前。
- **定义**：包含完整的函数体，编译时生成代码。
- **规则**：函数在使用前必须被声明或定义。如果定义在调用之后，必须提供原型。

### 3.3 参数传递（按值传递）
- C++ 默认使用**按值传递**：实参的值被拷贝给形参，函数内对形参的修改不影响实参。
- 优点：安全，避免副作用。
- 缺点：对大型对象可能开销大（可使用引用或指针避免拷贝）。

### 3.4 局部变量与作用域
- 函数内部声明的变量（如 `maximumValue`, `x`, `y`, `z`）是局部变量，作用域仅限于该函数内部。
- 在 `main` 中声明的 `int1` 等变量与 `maximum` 中的 `x` 等是完全独立的，它们占用不同的内存。

### 3.5 函数调用过程
1. 实参 `int1, int2, int3` 的值被拷贝到形参 `x, y, z`。
2. 控制权转移到 `maximum` 函数。
3. 执行函数体，计算最大值。
4. `return` 语句返回结果，控制权回到调用点，返回值替换函数调用表达式。

---

## 4. 代码风格与改进

### 4.1 使用 `const` 参数（如果参数不应被修改）
虽然本例中不修改形参，但可以显式声明为 `const` 以表明意图：
```cpp
int maximum(const int x, const int y, const int z);
```

### 4.2 使用条件运算符简化
```cpp
int maximum(int x, int y, int z) {
    return (x > y) ? (x > z ? x : z) : (y > z ? y : z);
}
```

### 4.3 使用 `std::max` 算法
```cpp
#include <algorithm>
int maximum(int x, int y, int z) {
    return std::max({x, y, z});
}
```
- `std::max` 的 initializer_list 重载（C++11）可以比较多个值。

### 4.4 添加参数合法性检查
- 例如如果所有参数相等，函数仍可正常工作。

---

## 5. 编译与运行

### 5.1 编译
```bash
g++ -std=c++17 maximum.cpp -o maximum
```

### 5.2 运行示例
```
Enter three integer values: 3 7 5
The maximum integer value is: 7
```

---

## 6. 练习建议

1. **编写 `minimum` 函数**：返回三个整数中的最小值。
2. **改写为 `double` 版本**：支持浮点数比较。
3. **编写 `maxOfFour` 函数**：找出四个整数中的最大值。
4. **将函数声明移到头文件**，并创建多文件项目。
5. **使用引用参数**：改为传递引用，观察是否影响实参（但求最大值不需要修改实参，故按值传递更安全）。

---

## 7. 扩展：函数重载与默认参数

- **重载**：可以定义同名函数，但参数列表不同（参数个数或类型）。
- **默认参数**：可以为形参指定默认值，调用时可省略。
```cpp
int maximum(int x, int y, int z = 0); // z 默认为 0
```

---

## 8. 扩展：内联函数（`inline`）

### 8.1 什么是内联函数？
- 内联函数是一种请求编译器将函数体代码**直接插入到调用点**的机制，目的是减少函数调用的开销（如参数压栈、跳转、返回等）。
- 使用 `inline` 关键字建议编译器进行内联展开，但**该请求并非强制**，编译器有权忽略。

### 8.2 语法
在函数定义前加上 `inline` 关键字即可：
```cpp
inline int maximum(int x, int y, int z) {
    int maxVal = x;
    if (y > maxVal) maxVal = y;
    if (z > maxVal) maxVal = z;
    return maxVal;
}
```

### 8.3 适用场景
- 函数体**非常短小**（通常只有几行）。
- 函数被**频繁调用**（如循环内、性能敏感区域）。
- 类中定义的成员函数默认是内联的（如果定义在类体内）。

### 8.4 优点与缺点
| 优点 | 缺点 |
|------|------|
| 消除函数调用开销，提高运行速度 | 可能导致**代码膨胀**（二进制体积增大） |
| 允许编译器进行更深入的优化（如常量传播） | 内联失败时可能产生重复定义错误（需注意头文件管理） |
| 适用于小型函数 | 递归函数不能完全内联 |

### 8.5 注意事项
- **定义通常放在头文件**中，因为内联函数需要在每个调用点可见。
- 在类定义体内定义的成员函数默认是 `inline`，无需显式声明。
- 编译器可能忽略 `inline` 请求（例如函数体过大或包含循环/递归时）。
- 使用 `inline` 并不意味着强制，现代编译器也会自动对短小函数进行内联，即使没有 `inline` 关键字。

### 8.6 示例：将 `maximum` 改为内联
```cpp
// maximum.h
#ifndef MAXIMUM_H
#define MAXIMUM_H

inline int maximum(int x, int y, int z) {
    int maxVal = x;
    if (y > maxVal) maxVal = y;
    if (z > maxVal) maxVal = z;
    return maxVal;
}

#endif
```
然后在多个 `.cpp` 文件中包含该头文件，无需担心重复定义（因为内联函数具有外部链接但允许重复定义）。

### 8.7 何时避免使用内联
- 函数体复杂（例如包含循环、递归、大型 switch 语句）。
- 函数不是性能瓶颈。
- 函数被许多不同编译单元调用，内联可能导致代码膨胀。

---

**函数是 C++ 程序的基本模块，学会封装逻辑能大大提高代码的复用性和可读性！继续练习，掌握更复杂的函数用法。** 🚀
