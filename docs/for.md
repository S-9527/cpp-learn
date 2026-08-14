# C++ 入门笔记：`for` 循环与累加偶数

> 本笔记涵盖 `for` 循环的语法、执行流程、作用域，以及 C++20 格式化库 `std::format` 的简介。

---

## 1. 完整代码示例

```cpp
#include <iostream>

int main()
{
  int total{0};

  for (int number{2}; number <= 20; number += 2)
  {
    total += number;
  }

  std::cout << "sum is " << total;

  return 0;
}
```

---

## 2. 代码逐行解析

### 2.1 头文件与入口
```cpp
#include <iostream>   // 输入输出流
int main()            // 程序入口
```

### 2.2 累加器初始化
```cpp
int total{0};         // 存储偶数和，初始为 0
```

### 2.3 `for` 循环
```cpp
for (int number{2}; number <= 20; number += 2)
{
    total += number;
}
```

#### 语法结构
```cpp
for (初始化; 条件; 更新) {
    // 循环体
}
```

#### 执行流程
1. **初始化**：`int number{2}`，只执行一次，在循环开始前。
2. **条件判断**：`number <= 20`，若为 `true`，执行循环体；否则退出循环。
3. **循环体**：`total += number;`，将当前偶数累加到 `total`。
4. **更新**：`number += 2`，执行后回到步骤 2，重复判断。

#### 本循环执行过程
- 第一次：`number = 2`，`2 <= 20` true，累加，更新为 4。
- 第二次：`number = 4`，累加，更新为 6。
- ...
- 最后一次：`number = 20`，累加，更新为 22。
- 再次判断：`22 <= 20` false，退出循环。

> **结果**：`total = 2 + 4 + ... + 20 = 110`。

---

## 3. 核心知识点总结

### 3.1 `for` 循环的要素
| 部分 | 本例 | 说明 |
|------|------|------|
| **初始化** | `int number{2}` | 通常定义循环控制变量，作用域仅限于循环内部 |
| **条件** | `number <= 20` | 每次迭代前判断，为 `true` 继续，`false` 退出 |
| **更新** | `number += 2` | 每次循环体执行后运行，通常递增/递减计数器 |
| **循环体** | `total += number;` | 重复执行的语句，可包含多条语句（需用 `{}`） |

### 3.2 变量作用域
- 在 `for` 循环的**初始化部分**声明的变量（如 `number`），其作用域仅限于循环体内部，在循环外部不可访问。
- 这是 C++ 推荐的写法，能避免变量污染外部作用域。

### 3.3 `for` 循环的变体
- **省略初始化**（需提前定义变量）：
  ```cpp
  int number{2};
  for (; number <= 20; number += 2) { ... }
  ```
- **省略条件**（形成死循环，需内部 `break`）：
  ```cpp
  for (;;) { if (某条件) break; }
  ```
- **省略更新**（在循环体内更新）：
  ```cpp
  for (int n{2}; n <= 20; ) { ... n += 2; }
  ```

### 3.4 `for` vs `while`
- `for` 循环将初始化、条件、更新集中在一起，适合于**已知迭代次数**或**计数循环**。
- `while` 更适合条件变化复杂或需在循环外初始化的情况。

---

## 4. C++20 的 `std::format`（简介）

虽然本代码未使用，但 `std::format` 是 C++20 引入的新型格式化库，提供类似 Python 的 `format()` 语法，更安全、高效。

### 4.1 基本用法
```cpp
#include <format>
std::cout << std::format("sum is {}\n", total);   // 输出 "sum is 110"
```

### 4.2 格式说明
```cpp
std::cout << std::format("{:.2f}  {:.2f}", 3.14159, 2.718);  // 保留两位小数
```
- 支持位置索引：`"{0} + {1} = {2}"`。
- 支持对齐、填充、精度等。

### 4.3 优点
- 类型安全，编译期检查格式字符串与参数类型是否匹配。
- 性能优于 `cout` 流式输出（但不如 `printf` 在极端情况）。
- 可扩展，支持自定义类型格式化。

### 4.4 编译器支持
- GCC 13+，Clang 15+，MSVC 2022 均支持。
- 使用需指定 `-std=c++20`。

> **注意**：当前代码若直接添加 `std::format` 可能会因编译器版本不支持而报错，故未使用。

---

## 5. 改进建议

### 5.1 使用 `constexpr` 明确循环范围
```cpp
constexpr int START{2};
constexpr int END{20};
constexpr int STEP{2};
for (int n = START; n <= END; n += STEP) { ... }
```

### 5.2 替换为 `while` 循环
```cpp
int n = 2;
while (n <= 20) {
    total += n;
    n += 2;
}
```

### 5.3 使用 `std::format`（若支持）
```cpp
#include <format>
std::cout << std::format("sum is {}\n", total);
```

### 5.4 处理任意范围（用户输入）
```cpp
int start, end, step;
std::cin >> start >> end >> step;
for (int n = start; n <= end; n += step) {
    total += n;
}
```

---

## 6. 运行示例

```
sum is 110
```

---

## 7. 练习建议

1. **修改步长**：改为 `number += 3`，计算 2 到 20 的奇数或特定步长和。
2. **倒序输出**：从 20 递减到 2。
3. **同时计算奇数和**：在循环中使用 `if (n % 2 == 0)` 或修改循环条件。
4. **使用 `for` 循环输出乘法表**：嵌套 `for` 循环。
5. **用 `std::format` 输出**（若编译器支持），体会格式化输出的便利。

---

**`for` 循环是 C++ 中最常用的循环结构，掌握它就能流畅地处理各种重复任务！继续加油！** 🚀
