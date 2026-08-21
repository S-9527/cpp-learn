# C++ 入门笔记：默认参数（Default Arguments）

> 本笔记通过计算长方体体积的函数，演示 C++ 中默认参数的语法、规则及其在函数重载中的替代作用。

---

## 1. 完整代码示例

```cpp
#include <iostream>

int boxVolume(int length = 1, int width = 1, int height = 1);

int main() {
  std::cout << "The default box volume is: " << boxVolume();

  std::cout << "\n\nThe volume of a box with length 10,\n"
            << "width 1 and height 1 is: " << boxVolume(10);

  std::cout << "\n\nThe volume of a box with length 10,\n"
            << "width 5 and height 1 is: " << boxVolume(10, 5);

  std::cout << "\n\nThe volume of a box with length 10,\n"
            << "width 5 and height 2 is: " << boxVolume(10, 5, 2) << '\n';
}

int boxVolume(int length, int width, int height) {
  return length * width * height;
}
```

---

## 2. 代码逐行解析

### 2.1 头文件
```cpp
#include <iostream>
```
- 标准输入输出流库，用于 `std::cout` 和 `std::endl`。

### 2.2 函数声明（原型）与默认参数
```cpp
int boxVolume(int length = 1, int width = 1, int height = 1);
```
- 这里声明了一个函数 `boxVolume`，接收三个 `int` 参数，返回 `int`。
- **关键**：每个形参都被赋予了**默认值** `1`。
- 这意味着调用时如果省略某个实参，编译器会使用对应的默认值。

### 2.3 `main` 函数中的调用
```cpp
std::cout << "The default box volume is: " << boxVolume();
```
- 不传递任何参数，全部使用默认值：`length=1, width=1, height=1`，体积为 `1`。

```cpp
std::cout << boxVolume(10);
```
- 只传递一个参数，自动匹配到第一个形参 `length`，其余使用默认值：`length=10, width=1, height=1`，体积为 `10`。

```cpp
std::cout << boxVolume(10, 5);
```
- 传递两个参数，匹配 `length` 和 `width`，`height` 使用默认值：`length=10, width=5, height=1`，体积为 `50`。

```cpp
std::cout << boxVolume(10, 5, 2);
```
- 传递全部三个参数，不使用默认值：体积为 `100`。

### 2.4 函数定义
```cpp
int boxVolume(int length, int width, int height) {
  return length * width * height;
}
```
- 函数定义与普通函数相同，**不重复指定默认参数**。默认参数只在声明处指定。
- 计算并返回体积。

---

## 3. 核心知识点：默认参数

### 3.1 基本语法
- 在函数声明（或定义）中，为形参指定默认值：
  ```cpp
  返回类型 函数名(类型 形参1 = 默认值1, 类型 形参2 = 默认值2, ...);
  ```

### 3.2 调用规则
- 调用时可以省略尾部的实参，但不能省略中间的实参。
  - **合法**：`boxVolume()`、`boxVolume(10)`、`boxVolume(10,5)`、`boxVolume(10,5,2)`
  - **非法**：`boxVolume(,5,2)`（不能跳过第一个参数）
- 实参从左到右依次匹配形参，未匹配的形参使用默认值。

### 3.3 默认参数的放置位置
- **默认参数只能从右向左连续提供**，不能在中间留空。
  - 正确：`int f(int a, int b = 1, int c = 2);`
  - 错误：`int f(int a = 1, int b, int c = 2);`（中间有参数无默认值，无法省略）
- 在同一个作用域中，默认参数只能指定一次（通常在声明中指定，定义中不重复）。

### 3.4 默认参数的作用域与生命周期
- 默认值在函数调用时求值，但通常为常量表达式或全局变量。
- 默认参数可以在多个声明中累积（只适用于不同作用域），但一般不推荐。

### 3.5 默认参数与函数重载的关系
- 默认参数可以模拟函数重载（如本例中一个函数替代了多个重载版本）。
- 但重载可以用于不同参数类型或数量，而默认参数仅适用于参数数量变化且类型相同的情况。

---

## 4. 代码风格与改进

### 4.1 使用 `constexpr` 或常量表达式作为默认值
```cpp
constexpr int DEFAULT_SIZE = 1;
int boxVolume(int length = DEFAULT_SIZE, int width = DEFAULT_SIZE, int height = DEFAULT_SIZE);
```

### 4.2 使用 `inline` 或 `constexpr` 函数
如果函数体很短，可声明为 `inline` 或 `constexpr`（C++11）：
```cpp
constexpr int boxVolume(int length = 1, int width = 1, int height = 1) {
    return length * width * height;
}
```

### 4.3 处理参数合法性
可添加检查，确保参数为正数。

### 4.4 使用 `std::format`（C++20）改进输出
```cpp
std::cout << std::format("The default box volume is: {}\n", boxVolume());
```

---

## 5. 编译与运行

### 5.1 编译
```bash
g++ -std=c++17 default_args.cpp -o default_args
```

### 5.2 运行输出
```
The default box volume is: 1

The volume of a box with length 10,
width 1 and height 1 is: 10

The volume of a box with length 10,
width 5 and height 1 is: 50

The volume of a box with length 10,
width 5 and height 2 is: 100
```

---

## 6. 默认参数 vs 函数重载

| 特性 | 默认参数 | 函数重载 |
|------|----------|----------|
| **适用场景** | 参数类型相同，数量不同 | 参数类型或数量不同 |
| **代码量** | 一个函数定义 | 多个函数定义 |
| **灵活性** | 较低（只能省略尾部参数） | 较高（可自由组合参数类型） |
| **可读性** | 较好（调用简洁） | 可能产生歧义（需注意重载决议） |
| **示例** | `int f(int a=1, int b=2);` | `int f(int a); int f(int a, int b);` |

---

## 7. 注意事项与常见错误

1. **默认参数不能重复指定**：在多个声明中指定默认参数可能导致冲突。
2. **默认参数不是函数类型的一部分**：函数类型只包含参数类型和返回类型，不包含默认值。
3. **默认参数不能被覆盖**：如果声明处有默认值，定义处不能再次指定。
4. **默认参数的作用域**：默认参数在编译时解析，因此不能用局部变量作为默认值（除非是 `static` 或全局）。

---

## 8. 练习建议

1. **修改默认值**：将默认值改为 `2`，观察输出变化。
2. **增加参数**：添加一个 `bool` 参数表示是否打印详细信息，并设置默认值。
3. **使用重载代替默认参数**：编写多个 `boxVolume` 重载版本，比较代码差异。
4. **使用 `constexpr`**：将函数改为 `constexpr`，并在编译期计算体积。
5. **测试非法调用**：尝试 `boxVolume(,5)` 观察编译错误。

---

**默认参数使函数调用更加灵活，减少了冗余的重载定义。掌握它的规则，能让你写出更简洁、更易用的接口。继续探索 C++ 的更多特性！** 🚀
