# C++ 入门笔记：大规模掷骰子模拟与频率统计

> 本笔记通过 6000 万次掷骰子模拟，演示 `std::random` 随机数生成、`std::array` 频率统计、`constexpr` 常量、`at()` 安全访问以及 C++14 数字分隔符的使用。

---

## 1. 完整代码示例

```cpp
#include <array>
#include <format>
#include <iostream>
#include <random>

int main() {
  std::random_device rd;
  std::default_random_engine engine{rd()};
  std::uniform_int_distribution randomDie{1, 6};

  constexpr size_t arraySize{7};
  std::array<int, arraySize> frequency{};

  for (int roll{1}; roll <= 60'000'000; ++roll) {
    ++frequency.at(randomDie(engine));
  }

  std::cout << std::format("{}{:>13}\n", "Face", "Frequency");

  for (size_t face{1}; face < frequency.size(); ++face) {
    std::cout << std::format("{:>4}{:>13}\n", face, frequency.at(face));
  }

  return 0;
}
```

---

## 2. 代码逐行解析

### 2.1 头文件
```cpp
#include <array>    // std::array 容器
#include <format>   // C++20 格式化输出
#include <iostream> // 标准输入输出流
#include <random>   // 随机数生成库
```
- `<random>` 提供 `std::random_device`、`std::default_random_engine` 和 `std::uniform_int_distribution`。

### 2.2 随机数生成器初始化
```cpp
std::random_device rd;
std::default_random_engine engine{rd()};
std::uniform_int_distribution randomDie{1, 6};
```
- `std::random_device` 用于获取真随机种子（通常基于硬件熵源）。
- `std::default_random_engine` 是伪随机数引擎，用 `rd()` 的返回值作为种子，确保每次运行产生的随机序列不同。
- `std::uniform_int_distribution randomDie{1, 6}` 定义了一个均匀分布，生成 `[1, 6]` 范围内的整数（C++17 起可省略模板参数 `<int>`，由构造函数推导）。

### 2.3 频率数组声明与初始化
```cpp
constexpr size_t arraySize{7};
std::array<int, arraySize> frequency{};
```
- `arraySize` 为 7，因为骰子面值为 1~6，索引 0 不使用（便于直接用 `face` 作为索引）。
- `frequency{}` **值初始化**将所有元素置为 0。
- 如果不用 `{}`，数组元素将处于未初始化状态，行为未定义。

### 2.4 大规模模拟循环
```cpp
for (int roll{1}; roll <= 60'000'000; ++roll) {
    ++frequency.at(randomDie(engine));
}
```
- 循环 6000 万次（`60'000'000` 使用 C++14 数字分隔符 `'`，提高可读性）。
- 每次调用 `randomDie(engine)` 生成一个 1~6 的随机数。
- `frequency.at(randomDie(engine))` 返回该面值对应的元素引用，`++` 将其加 1。
- 使用 `at()` 进行边界检查，若索引越界（如生成 0 或 7）会抛出 `std::out_of_range` 异常（但分布保证在 1~6 内，所以安全）。

### 2.5 输出表头
```cpp
std::cout << std::format("{}{:>13}\n", "Face", "Frequency");
```
- `"Face"` 左对齐（默认），`"Frequency"` 右对齐宽度 13。
- 输出：`Face     Frequency`

### 2.6 输出统计结果
```cpp
for (size_t face{1}; face < frequency.size(); ++face) {
    std::cout << std::format("{:>4}{:>13}\n", face, frequency.at(face));
}
```
- 遍历 `face` 从 1 到 6（`frequency.size()` 返回 7，所以 `face < 7`）。
- `{:>4}` 将面值右对齐宽度 4。
- `{:>13}` 将频率值右对齐宽度 13（与表头对齐）。
- `frequency.at(face)` 安全访问每个面的计数。

---

## 3. 核心知识点

### 3.1 数字分隔符（C++14）
- 使用单引号 `'` 分隔数字字面量，提高可读性。
- 示例：`60'000'000` 等价于 `60000000`。
- 可用于整数、浮点数：`3.141'592'653`。

### 3.2 随机数生成流程
| 步骤 | 组件 | 作用 |
|------|------|------|
| 1 | `std::random_device` | 获取真随机种子 |
| 2 | `std::default_random_engine` | 伪随机数引擎，生成随机比特序列 |
| 3 | `std::uniform_int_distribution` | 将引擎输出映射到指定整数范围 |

### 3.3 统计频率的模式
- **索引即值**：数组索引直接对应骰子面值（1~6），索引 0 闲置。
- **累计计数**：`++frequency.at(roll)` 简洁地更新计数。
- 这种模式适用于统计有限范围的枚举/整数。

### 3.4 性能考虑
- 6000 万次循环在现代 CPU 上约需 0.3~1 秒（取决于引擎和优化）。
- `at()` 的边界检查在循环中会带来微小开销，但对于 6000 万次迭代，差异可能较明显。
- 若确定索引绝对安全，可改用 `operator[]` 提升性能：
  ```cpp
  ++frequency[randomDie(engine)];
  ```

### 3.5 `constexpr` 与数组大小
- `arraySize` 必须是编译期常量，因为它是 `std::array` 的模板参数。
- `constexpr size_t arraySize{7};` 确保编译期求值。

---

## 4. 编译与运行

### 4.1 编译（需 C++20 支持 `<format>`）
```bash
g++ -std=c++20 dice_simulation.cpp -o dice_simulation
```
若编译器不支持 `<format>`，可改用流式输出：
```cpp
std::cout << "Face" << std::setw(13) << "Frequency\n";
```

### 4.2 运行输出（示例）
```
Face     Frequency
   1      10000321
   2       9998456
   3       9999123
   4      10000124
   5       9999234
   6      10002742
```
- 各面频率接近 10,000,000（`60000000 / 6`），验证均匀分布。

---

## 5. 改进建议

### 5.1 使用 `std::mt19937` 替代 `default_random_engine`
```cpp
std::mt19937 engine{rd()};  // 梅森旋转，质量更高
```

### 5.2 使用 `operator[]` 提升性能
```cpp
++frequency[randomDie(engine)];
```
- 无边界检查，速度更快（适合确定不会越界的场景）。

### 5.3 使用 `std::array::fill` 重置统计
```cpp
frequency.fill(0);  // 若需要重置
```

### 5.4 使用 `long long` 防止溢出
- 若模拟次数极大（数十亿），`int` 可能溢出，可用 `long long`。
- 本例 6000 万仍远在 `int` 范围内（约 21 亿）。

### 5.5 添加耗时测量
```cpp
#include <chrono>
auto start = std::chrono::high_resolution_clock::now();
// ... 模拟 ...
auto end = std::chrono::high_resolution_clock::now();
std::cout << "Time: " << (end - start).count() << " ns\n";
```

---

## 6. 练习建议

1. **修改骰子面数**：改为 1~20 的骰子，调整数组大小并观察分布。
2. **改用 `operator[]`**：对比 `at()` 和 `[]` 的性能差异（可用 `std::chrono` 测量）。
3. **使用 `std::map` 或 `std::unordered_map`**：针对未知范围或稀疏数据的统计。
4. **增加理论频率输出**：计算理论概率（1/6），与实际频率对比。
5. **并行优化**：使用多线程并行生成随机数（需注意引擎线程安全）。

---

## 7. 扩展：大数定律验证

- 随着模拟次数增加，各面出现频率趋近于 1/6。
- 本例 6000 万次模拟，频率相对误差通常在万分之一以内。
- 这是统计模拟（Monte Carlo 方法）的基础。

---

**大规模模拟是验证随机算法和统计理论的重要手段。掌握 `std::random` 和 `std::array` 的配合使用，能让你轻松处理各类频率统计问题。继续探索随机模拟的更多应用！** 🚀
