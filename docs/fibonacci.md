# C++ 入门笔记：递归函数与斐波那契数列

> 本笔记通过斐波那契数列的递归实现，介绍递归函数的基本概念、执行流程、优缺点，并对比递归与迭代的差异。

---

## 1. 完整代码示例

```cpp
#include <format>
#include <iostream>

long fibonacci(long number);

int main() {
  for (int counter{0}; counter <= 10; ++counter) {
    std::cout << std::format("fibonacci({}) = {}\n", counter,
                             fibonacci(counter));
  }

  std::cout << std::format("\nfibonacci(20) = {}\n", fibonacci(20))
            << std::format("fibonacci(30) = {}\n", fibonacci(30))
            << std::format("fibonacci(35) = {}\n", fibonacci(35));
}

long fibonacci(long number) {
  if ((0 == number) || (1 == number)) {
    return number;
  }

  return fibonacci(number - 1) + fibonacci(number - 2);
}
```

---

## 2. 代码逐行解析

### 2.1 头文件
```cpp
#include <format>   // C++20 格式化输出
#include <iostream> // 标准输入输出
```

### 2.2 函数声明（原型）
```cpp
long fibonacci(long number);
```
- 声明一个返回 `long` 类型的函数，接收一个 `long` 参数。

### 2.3 `main` 函数
```cpp
for (int counter{0}; counter <= 10; ++counter) {
    std::cout << std::format("fibonacci({}) = {}\n", counter,
                             fibonacci(counter));
}
```
- 循环 0 到 10，依次调用 `fibonacci(counter)` 并输出结果。
- 使用 `std::format` 格式化字符串，占位符 `{}` 依次替换为 `counter` 和返回值。

```cpp
std::cout << std::format("\nfibonacci(20) = {}\n", fibonacci(20))
          << std::format("fibonacci(30) = {}\n", fibonacci(30))
          << std::format("fibonacci(35) = {}\n", fibonacci(35));
```
- 分别计算并输出第 20、30、35 项斐波那契数。
- 注意：`fibonacci(35)` 的计算量已经较大，递归效率低下。

### 2.4 递归函数定义
```cpp
long fibonacci(long number) {
  if ((0 == number) || (1 == number)) {
    return number;
  }

  return fibonacci(number - 1) + fibonacci(number - 2);
}
```
- **递归终止条件**：当 `number` 为 0 或 1 时，直接返回 `number`（斐波那契数列前两项为 0 和 1）。
- **递归步骤**：否则返回 `fibonacci(number-1) + fibonacci(number-2)`，即前两项之和。
- 该函数采用 **递归调用**，不断将问题分解为更小的子问题，直到达到基准情形。

---

## 3. 核心知识点：递归（Recursion）

### 3.1 什么是递归？
- 递归是指函数直接或间接调用自身的一种编程技巧。
- 递归函数必须包含两个基本部分：
  1. **基准情形（Base Case）**：问题规模足够小，可以直接解决，不再递归。
  2. **递归步骤（Recursive Step）**：将原问题分解为更小的同类型子问题，并通过递归调用来解决。

### 3.2 斐波那契数列定义
- 数学定义：
  - `F(0) = 0`
  - `F(1) = 1`
  - `F(n) = F(n-1) + F(n-2)`（n ≥ 2）
- 本例的递归实现直接映射了该定义。

### 3.3 递归执行过程（以 `fibonacci(4)` 为例）
```
fibonacci(4)
├── fibonacci(3)
│   ├── fibonacci(2)
│   │   ├── fibonacci(1) → 1
│   │   └── fibonacci(0) → 0
│   └── fibonacci(1) → 1
└── fibonacci(2)
    ├── fibonacci(1) → 1
    └── fibonacci(0) → 0
```
- 总调用次数：9 次（其中包含大量重复计算）。

### 3.4 递归的优缺点
| 优点 | 缺点 |
|------|------|
| 代码简洁，易于理解，直接反映数学定义 | 效率低下（大量重复计算） |
| 适合解决具有递归结构的问题（如树、图遍历） | 可能导致栈溢出（递归深度过大） |
| 逻辑清晰，易于调试 | 每次调用有函数调用开销 |

---

## 4. 性能分析

- **时间复杂度**：`O(2^n)`（指数级），因为每个调用会产生两个分支。
- **空间复杂度**：`O(n)`（调用栈深度）。
- 对于 `n=35`，计算量已相当庞大（约 1840 万次调用），速度明显变慢。

---

## 5. 改进方案

### 5.1 迭代实现（高效）
```cpp
long fibonacci_iterative(long n) {
    if (n <= 1) return n;
    long prev2 = 0, prev1 = 1, current = 0;
    for (long i = 2; i <= n; ++i) {
        current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }
    return current;
}
```
- 时间复杂度：`O(n)`，空间复杂度：`O(1)`。

### 5.2 记忆化递归（带缓存）
```cpp
#include <unordered_map>
long fibonacci_memo(long n, std::unordered_map<long, long>& memo) {
    if (memo.count(n)) return memo[n];
    if (n <= 1) return n;
    long result = fibonacci_memo(n-1, memo) + fibonacci_memo(n-2, memo);
    memo[n] = result;
    return result;
}
```
- 时间复杂度：`O(n)`，空间复杂度：`O(n)`（缓存 + 栈）。

### 5.3 使用 `constexpr`（编译期计算）
若 `n` 在编译期已知，可将函数设为 `constexpr`，在编译期求值。

---

## 6. 编译与运行

### 6.1 编译（需 C++20 支持 `<format>`）
```bash
g++ -std=c++20 fibonacci_recursive.cpp -o fibonacci_recursive
```
若编译器不支持 `<format>`，可改用传统流式输出：
```cpp
std::cout << "fibonacci(" << counter << ") = " << fibonacci(counter) << '\n';
```

### 6.2 运行输出（部分）
```
fibonacci(0) = 0
fibonacci(1) = 1
fibonacci(2) = 1
fibonacci(3) = 2
fibonacci(4) = 3
fibonacci(5) = 5
fibonacci(6) = 8
fibonacci(7) = 13
fibonacci(8) = 21
fibonacci(9) = 34
fibonacci(10) = 55

fibonacci(20) = 6765
fibonacci(30) = 832040
fibonacci(35) = 9227465
```

---

## 7. 常见问题与注意事项

- **栈溢出**：递归深度过大（如 `n=100000`）可能导致栈溢出。迭代可避免此问题。
- **重复计算**：递归会产生大量重复子问题，可通过记忆化优化。
- **尾递归优化**：某些编译器可优化尾递归，但本例不是尾递归（最后操作是加法，不是直接返回递归调用结果）。

---

## 8. 练习建议

1. **改为迭代实现**，对比两种实现的计算速度（例如 `n=40`）。
2. **实现记忆化递归**，利用 `std::map` 或 `std::unordered_map` 缓存已计算结果。
3. **改为 `constexpr` 函数**，在编译期计算 `fibonacci(10)`。
4. **分析递归调用次数**：编写一个计数器，统计 `fibonacci` 函数被调用的总次数。
5. **探索其他递归问题**：如阶乘、汉诺塔、归并排序等。

---

## 9. 扩展：尾递归与编译优化

- **尾递归**：递归调用是函数体中的最后一个操作，且不涉及额外运算（如加法）。本例的 `fibonacci` 不是尾递归，因为最后一步是加法。
- 尾递归可被编译器优化为循环，但标准 C++ 不强制要求。可通过手动改写为尾递归形式：
```cpp
long fibonacci_tail(long n, long a = 0, long b = 1) {
    if (n == 0) return a;
    if (n == 1) return b;
    return fibonacci_tail(n - 1, b, a + b);
}
```
该版本是尾递归，某些编译器可能会优化。

---

**递归是强大的思维工具，但需警惕其性能开销。学会识别适合递归的场景，并掌握优化技巧，才能写出既清晰又高效的程序。继续探索更多递归应用！** 🚀
