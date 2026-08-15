# C++ 入门笔记：复利计算与 `std::format` 格式化输出

> 本笔记涵盖 `for` 循环、`std::pow` 指数运算、`std::format`（C++20）格式化输出，以及浮点数精度控制。

---

## 1. 完整代码示例

```cpp
#include <format>
#include <iostream>
#include <cmath>

int main()
{
  double principal{1000.00};
  double rate{0.05};

  std::cout << std::format("Initial principal: {:>7.2f}\n", principal)
            << std::format("    Interest rate: {:>7.2f}\n", rate);

  std::cout << std::format("\n{}{:>20}\n", "Year", "Amount on deposit");

  for (int year{1}; year <= 10; ++year)
  {
    double amount{principal * std::pow(1.0 + rate, year)};
    std::cout << std::format("{:>4d}{:>20.2f}\n", year, amount);
  }
}
```

---

## 2. 代码逐行解析

### 2.1 头文件
```cpp
#include <format>   // std::format（C++20）
#include <iostream> // 标准输入输出流
#include <cmath>    // std::pow（指数函数）
```
- `<format>` 是 C++20 新增的格式化库，提供类型安全、类似 Python 的字符串格式化功能。
- `<cmath>` 提供数学函数，此处使用 `std::pow` 计算 (1+rate)^year。

### 2.2 变量定义
```cpp
double principal{1000.00};  // 初始本金
double rate{0.05};          // 年利率（5%）
```

### 2.3 输出初始信息（使用 `std::format`）
```cpp
std::cout << std::format("Initial principal: {:>7.2f}\n", principal)
          << std::format("    Interest rate: {:>7.2f}\n", rate);
```
- `std::format` 返回格式化后的字符串，然后通过 `std::cout` 输出。
- 格式说明符 `{:>7.2f}`：
  - `:` 开始格式说明。
  - `>` 表示右对齐。
  - `7` 设置最小字段宽度为 7 个字符。
  - `.2f` 表示浮点数保留 2 位小数（定点表示，即 `fixed` 模式）。
- 注意：`principal` 和 `rate` 分别被插入到格式字符串中，替代 `{}` 占位符。

### 2.4 输出表头
```cpp
std::cout << std::format("\n{}{:>20}\n", "Year", "Amount on deposit");
```
- `"Year"` 和 `"Amount on deposit"` 分别填入两个 `{}`。
- `{:>20}` 表示将字符串右对齐，宽度 20（适用于标题与数据对齐）。

### 2.5 `for` 循环计算并输出每年的金额
```cpp
for (int year{1}; year <= 10; ++year)
{
    double amount{principal * std::pow(1.0 + rate, year)};
    std::cout << std::format("{:>4d}{:>20.2f}\n", year, amount);
}
```
- 循环从 1 到 10，共 10 年。
- `std::pow(1.0 + rate, year)` 计算 (1+rate)^year，即复利因子。
- `amount = principal * 复利因子`。
- 输出：`year` 占 4 位右对齐（`{:>4d}`），`amount` 占 20 位右对齐，保留 2 位小数（`{:>20.2f}`）。

---

## 3. 核心知识点

### 3.1 `std::format` 语法

#### 基本语法
```cpp
std::format("text {} text", arg1, arg2, ...)
```
- 占位符 `{}` 按顺序替换参数。
- 可指定索引：`{0}`, `{1}` 等。

#### 常用格式说明符
| 说明符 | 含义 | 示例 |
|--------|------|------|
| `d` | 十进制整数 | `{:d}` |
| `f` | 定点小数（`fixed`） | `{:.2f}`（两位小数） |
| `e` | 科学计数法 | `{:e}` |
| `g` | 一般格式（自动选择） | `{:g}` |
| `s` | 字符串（默认） | `{:s}` |

#### 宽度与对齐
| 说明 | 语法 | 效果 |
|------|------|------|
| 左对齐 | `{:<10}` | 在宽度内左对齐 |
| 右对齐 | `{:>10}` | 右对齐（默认） |
| 居中 | `{:^10}` | 居中 |

#### 填充字符
- 默认用空格填充，可指定其他字符，例如 `{:0>6d}` 用 0 填充。

#### 精度
- 对浮点数 `{:.2f}` 表示保留两位小数。

### 3.2 `std::pow` 函数
- 声明于 `<cmath>`，计算指数。
- 用法：`std::pow(base, exponent)`，返回 `double`。
- 注意：此处 `1.0 + rate` 是 `double`，避免整数除法。

### 3.3 `for` 循环与浮点数计算
- 循环变量 `year` 为整数，`year++` 可写为 `++year`（前缀递增效率略高，但对现代编译器无差别）。
- 浮点数计算可能产生舍入误差，但此处金额保留两位小数足够。

### 3.4 浮点数格式化与精度控制
- 在 `std::format` 中，`.2f` 会**四舍五入**到两位小数（符合日常需求）。
- 不同于 `std::cout << std::fixed << std::setprecision(2)`，`std::format` 更简洁且类型安全。

---

## 4. `std::format` vs 传统输出

| 方式 | 优点 | 缺点 |
|------|------|------|
| `std::cout` 流式 | 直观，类型安全 | 格式控制冗长（`setprecision`, `fixed`, `setw`），难以对齐 |
| `printf` | 格式控制强大，紧凑 | 不安全（类型不匹配导致崩溃），不支持自定义类型 |
| `std::format` | 类型安全，语法简洁，性能良好（编译期检查） | 需要 C++20 支持，编译器较新 |

> **建议**：新项目中优先使用 `std::format`（若编译器支持），否则可沿用流式或 `printf`。

---

## 5. 编译与运行

### 5.1 编译（需 C++20 及支持 `<format>` 的编译器）
- **GCC**：13 及以上版本（需 `-std=c++20`）。
- **Clang**：15 及以上版本。
- **MSVC**：Visual Studio 2022 及以上。

```bash
g++ -std=c++20 compound_interest.cpp -o compound_interest
```

### 5.2 运行结果
```
Initial principal: 1000.00
    Interest rate:    0.05

Year        Amount on deposit
   1                1050.00
   2                1102.50
   3                1157.63
   4                1215.51
   5                1276.28
   6                1340.10
   7                1407.10
   8                1477.46
   9                1551.33
  10                1628.89
```

---

## 6. 改进建议

### 6.1 改用 `constexpr` 或 `const` 变量
```cpp
constexpr double PRINCIPAL{1000.00};
constexpr double RATE{0.05};
constexpr int YEARS{10};
```

### 6.2 允许用户输入参数
```cpp
double principal, rate;
int years;
std::cin >> principal >> rate >> years;
// 循环中使用 years
```

### 6.3 使用 `std::format` 的索引占位符
```cpp
std::cout << std::format("{0:>4d}{1:>20.2f}\n", year, amount);
```

### 6.4 添加累计利息信息
在循环中同时计算利息 `amount - principal` 并输出。

### 6.5 利用 `std::format` 的自定义格式（高级）
可自定义类型专门格式化。

---

## 7. 练习建议

1. **修改利率和年限**，观察结果变化。
2. **改为输入本金、利率和年数**，动态计算。
3. **使用流式输出重写**，比较两种写法。
4. **尝试其他格式说明符**：如科学计数法 `{:e}`，或使用 `std::format` 输出十六进制等。
5. **增加利息明细列**：每年输出利息（`amount - principal`）和总金额。
6. **若不支持 C++20**，用 `printf` 或 `cout` 实现相同效果。

---

**你已经掌握了现代 C++ 的格式化输出和复利计算，继续用这些工具解决实际问题吧！** 🚀
