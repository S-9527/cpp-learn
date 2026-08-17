# C++ 入门笔记：随机数生成（`<random>` 库）

> 本笔记涵盖 C++ 标准库 `<random>` 的基本用法：随机数引擎与分布，模拟骰子掷出 1~6 的随机整数。

---

## 1. 完整代码示例

```cpp
#include <iostream>
#include <random>

int main()
{
  std::default_random_engine engine{};

  std::uniform_int_distribution randomDie{1, 6};

  for (int counter{1}; counter <= 10; ++counter)
  {
    std::cout << randomDie(engine) << " ";
  }

  std::cout << '\n';
}
```

---

## 2. 代码逐行解析

### 2.1 头文件
```cpp
#include <iostream>   // 标准输入输出流
#include <random>     // 随机数生成库（C++11 起）
```
- `<random>` 提供了高质量的随机数引擎和多种分布，相比 C 语言的 `rand()` 更可控、更灵活。

### 2.2 创建随机数引擎
```cpp
std::default_random_engine engine{};
```
- `std::default_random_engine` 是标准库定义的**伪随机数引擎**，具体类型由实现决定（通常为 `mt19937` 或类似）。
- 使用 `{}` 进行值初始化，调用默认构造函数，引擎会使用默认的种子（通常为固定值，导致每次运行产生的随机序列相同）。
- **注意**：若不显式设置种子，每次程序运行将产生相同的随机序列，这在调试时有用，但在实际应用中需要随机性时需提供随机种子。

### 2.3 创建均匀整数分布
```cpp
std::uniform_int_distribution randomDie{1, 6};
```
- `std::uniform_int_distribution` 是一个类模板，用于生成指定范围内均匀分布的整数。
- 从 C++17 起，可以省略模板参数（`<int>`），编译器通过构造函数参数推导为 `int`。
- 构造函数参数 `{1, 6}` 指定分布的闭区间 `[1, 6]`，即最小值为 1，最大值为 6。
- 该对象本身是可调用对象（仿函数），调用时需要传入一个随机数引擎。

### 2.4 生成并输出随机数
```cpp
for (int counter{1}; counter <= 10; ++counter)
{
    std::cout << randomDie(engine) << " ";
}
```
- 循环 10 次，每次调用 `randomDie(engine)` 生成一个 `[1, 6]` 内的随机整数。
- `randomDie` 是函数对象（重载了 `operator()`），接受一个引擎引用，返回一个随机整数。
- 输出时以空格分隔，最后输出换行。

---

## 3. 核心知识点

### 3.1 `<random>` 库的基本构成
| 组件 | 作用 | 示例 |
|------|------|------|
| **随机数引擎** | 生成均匀分布的随机比特序列（核心） | `std::default_random_engine`, `std::mt19937` |
| **分布** | 将引擎的输出映射到特定统计分布 | `std::uniform_int_distribution`, `std::normal_distribution` |
| **种子** | 初始化引擎，决定随机序列的起始点 | `engine.seed(42)` 或使用 `std::random_device` |

### 3.2 为什么不用 `rand()`？
- `rand()` 质量较低，周期短，且全局状态不易控制。
- `<random>` 提供多种引擎（如梅森旋转 `mt19937`），质量高、可重复、线程安全（需各自独立实例）。

### 3.3 分布的使用方式
- 分布对象是**可调用对象**，其 `operator()` 接受一个引擎引用。
- 典型用法：`dist(engine)`，返回一个随机数。
- 分布对象通常无状态，可安全地在多线程中共享（但引擎不行）。

### 3.4 类模板参数推导（C++17）
- 在 C++17 之前，必须显式指定模板参数：`std::uniform_int_distribution<int> randomDie{1, 6};`
- C++17 允许省略 `<int>`，编译器从 `{1, 6}` 推导出 `int`。

---

## 4. 进阶：设置随机种子

为了每次运行产生不同的随机序列，通常使用 `std::random_device` 提供真随机种子：

```cpp
#include <iostream>
#include <random>

int main()
{
    std::random_device rd;                     // 获取真随机数（如果可用）
    std::default_random_engine engine{rd()};   // 用随机设备生成种子

    std::uniform_int_distribution randomDie{1, 6};

    for (int i = 0; i < 10; ++i)
        std::cout << randomDie(engine) << ' ';
    std::cout << '\n';
}
```

- `std::random_device` 通常基于硬件熵源，产生不可预测的随机值。
- 但某些实现可能是伪随机（如 MinGW），此时需注意。

---

## 5. 其他常用分布

| 分布 | 用途 | 示例 |
|------|------|------|
| `uniform_real_distribution<double>` | 均匀浮点数（[a, b)） | `std::uniform_real_distribution<double> dist(0.0, 1.0);` |
| `normal_distribution<double>` | 正态分布（高斯分布） | `std::normal_distribution<double> dist(0.0, 1.0);` |
| `bernoulli_distribution` | 伯努利分布（true/false） | `std::bernoulli_distribution dist(0.5);` |

---

## 6. 编译与运行

### 6.1 编译（需要 C++11 或更高）
```bash
g++ -std=c++11 random_dice.cpp -o random_dice
```

### 6.2 运行示例（未设置随机种子时）
```
5 2 6 1 3 4 2 5 1 6
```
（每次运行可能相同，因为默认种子固定）

### 6.3 运行示例（设置随机种子后）
```
4 1 5 3 6 2 1 4 5 3
```
（每次运行可能不同）

---

## 7. 改进建议

1. **使用更高质量的引擎**：`std::mt19937`（梅森旋转）比 `default_random_engine` 更可预测其质量。
2. **使用 `std::random_device` 作为种子源**。
3. **将随机数生成封装为函数**，便于复用。
4. **指定范围时注意边界**：`uniform_int_distribution` 包含两端。

---

## 8. 练习建议

1. **模拟掷骰子 100 次**，统计每个点数出现的次数。
2. **生成 0.0 到 1.0 的随机浮点数**，并输出。
3. **生成正态分布的随机数**，查看输出范围。
4. **尝试使用 `std::seed_seq` 组合多个种子值**。
5. **比较 `rand()` 与 `<random>` 生成随机数的质量**（例如生成大量样本观察分布均匀性）。

---

**C++ 的 `<random>` 库提供了现代、安全、高效的随机数生成工具，掌握它能让你的程序更可靠。继续练习，应用到实际问题中！** 🚀
