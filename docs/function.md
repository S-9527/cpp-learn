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

**函数是 C++ 程序的基本模块，学会封装逻辑能大大提高代码的复用性和可读性！继续练习，掌握更复杂的函数用法。** 🚀
