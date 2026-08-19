# C++ 入门笔记：模拟掷骰子游戏（Craps 游戏）

> 本笔记综合运用枚举类、`switch` 语句、`while` 循环、C++17 `if` 初始化、`<random>` 库以及 `std::format`，实现一个完整的骰子赌博游戏逻辑。

---

## 1. 完整代码示例

```cpp
#include <format>
#include <iostream>
#include <random>

int rollDice();

int main() {
  enum class Status { keepRolling, won, lost };

  int myPoint{0};
  Status gameStatus{Status::keepRolling};

  switch (const int sumOfDice{rollDice()}) {
    case 7:
    case 11:
      gameStatus = Status::won;
      break;
    case 2:
    case 3:
    case 12:
      gameStatus = Status::lost;
      break;
    default:
      myPoint = sumOfDice;
      std::cout << std::format("Point is {}\n", myPoint);
      break;
  }

  while (Status::keepRolling == gameStatus) {
    if (const int sumOfDice{rollDice()}; sumOfDice == myPoint) {
      gameStatus = Status::won;
    } else if (sumOfDice == 7) {
      gameStatus = Status::lost;
    }
  }

  if (Status::won == gameStatus) {
    std::cout << "Player win\n";
  } else {
    std::cout << "Player loses\n";
  }

  return 0;
}

int rollDice() {
  static std::random_device rd;
  static std::default_random_engine engine{rd()};
  static std::uniform_int_distribution randomDie{1, 6};

  const int die1{randomDie(engine)};
  const int die2{randomDie(engine)};
  const int sum{die1 + die2};

  std::cout << std::format("Player rolled {} + {} = {} \n", die1, die2, sum);

  return sum;
}
```

---

## 2. 游戏规则说明

**Craps 游戏规则（简化版）**：
1. 玩家第一次掷两颗骰子：
   - 若点数和为 **7 或 11** → 立即获胜（Win）。
   - 若点数和为 **2、3 或 12** → 立即输掉（Lose）。
   - 否则，点数和成为玩家的 **目标点数（Point）**，游戏继续。
2. 进入循环后，玩家不断掷骰子：
   - 若掷出 **目标点数** → 获胜。
   - 若掷出 **7** → 输掉。
   - 否则继续掷骰。

---

## 3. 代码逐行解析

### 3.1 头文件与函数声明
```cpp
#include <format>   // C++20 格式化输出
#include <iostream> // 输入输出流
#include <random>   // 随机数生成

int rollDice();     // 函数声明（原型）
```

### 3.2 `main` 函数：枚举类与变量定义
```cpp
enum class Status { keepRolling, won, lost };
```
- `enum class`（强类型枚举）定义了三种游戏状态，作用域限定，避免命名冲突。
- 与普通 `enum` 不同，使用时必须加上作用域 `Status::keepRolling`。

```cpp
int myPoint{0};
Status gameStatus{Status::keepRolling};
```
- `myPoint` 存储目标点数，初始为 0。
- `gameStatus` 初始为 `keepRolling`。

### 3.3 第一次掷骰子（`switch` 与 C++17 初始化）
```cpp
switch (const int sumOfDice{rollDice()}) {
    case 7:
    case 11:
      gameStatus = Status::won;
      break;
    case 2:
    case 3:
    case 12:
      gameStatus = Status::lost;
      break;
    default:
      myPoint = sumOfDice;
      std::cout << std::format("Point is {}\n", myPoint);
      break;
}
```
- `switch` 的条件部分使用了 C++17 的**初始化语句**：`const int sumOfDice{rollDice()}`。
- `sumOfDice` 的作用域仅限于 `switch` 语句内部。
- `case` 可堆叠（如 `case 7:` 和 `case 11:` 共享同一代码块）。
- 默认分支（`default`）设置目标点数并输出提示。

### 3.4 后续掷骰循环（`while` 与 `if` 初始化）
```cpp
while (Status::keepRolling == gameStatus) {
    if (const int sumOfDice{rollDice()}; sumOfDice == myPoint) {
        gameStatus = Status::won;
    } else if (sumOfDice == 7) {
        gameStatus = Status::lost;
    }
}
```
- `while` 条件中使用了 Yoda 风格（`Status::keepRolling == gameStatus`），但直接写 `gameStatus == Status::keepRolling` 同样清晰。
- 在 `if` 条件中，再次使用了 C++17 的初始化语句声明 `sumOfDice`，作用域仅限于该 `if` 语句及其 `else if` 分支。
- 如果掷出的点数等于目标点数，获胜；如果等于 7，输掉；否则继续循环。

### 3.5 最终结果输出
```cpp
if (Status::won == gameStatus) {
    std::cout << "Player win\n";
} else {
    std::cout << "Player loses\n";
}
```

### 3.6 `rollDice` 函数：随机数生成与输出
```cpp
int rollDice() {
  static std::random_device rd;
  static std::default_random_engine engine{rd()};
  static std::uniform_int_distribution randomDie{1, 6};

  const int die1{randomDie(engine)};
  const int die2{randomDie(engine)};
  const int sum{die1 + die2};

  std::cout << std::format("Player rolled {} + {} = {} \n", die1, die2, sum);

  return sum;
}
```
- `static` 局部变量在**第一次调用时初始化**，后续调用保留状态，避免重复构造。
- `std::random_device` 用于获取真随机种子。
- `std::default_random_engine` 是伪随机数引擎。
- `uniform_int_distribution` 生成 `[1, 6]` 的均匀分布整数。
- 每次调用掷两颗骰子，输出结果并返回点数和。

---

## 4. 核心知识点汇总

| 知识点 | 说明 | 示例 |
|--------|------|------|
| **函数声明** | 在调用前声明函数 | `int rollDice();` |
| **强类型枚举** | `enum class`，作用域限定 | `Status::won` |
| **`switch` 初始化** | C++17，在条件中声明变量 | `switch (int x = f(); x)` |
| **`if` 初始化** | C++17，在条件中声明变量 | `if (int x = f(); x > 0)` |
| **静态局部变量** | 初始化一次，跨调用保留 | `static int count{0};` |
| **`<random>` 库** | 现代随机数生成 | `engine`, `distribution` |
| **`std::format`** | C++20 格式化输出 | `std::format("{} + {}", a, b)` |
| **Yoda 风格** | 常量在前，避免误赋值 | `Status::won == gameStatus` |

---

## 5. 编译与运行

### 5.1 编译（需要 C++20 支持）
```bash
g++ -std=c++20 craps.cpp -o craps
```

### 5.2 运行示例
```
Player rolled 4 + 2 = 6
Point is 6
Player rolled 3 + 1 = 4
Player rolled 2 + 5 = 7
Player loses
```

```
Player rolled 5 + 6 = 11
Player win
```

```
Player rolled 2 + 2 = 4
Point is 4
Player rolled 4 + 3 = 7
Player loses
```

```
Player rolled 6 + 5 = 11
Player win
```

---

## 6. 改进建议

1. **使用 `std::mt19937`**：更高质量的随机数引擎。
2. **添加输入确认**：询问玩家是否继续游戏（循环玩多轮）。
3. **统计胜负次数**：记录总游戏场次和胜率。
4. **使用 `std::optional`**：处理可能的异常状态。
5. **抽离游戏逻辑**：将规则封装到独立的函数或类中。

---

## 7. 练习建议

1. **添加连续游戏**：使用 `do-while` 让玩家可以反复玩。
2. **统计骰子点数频率**：记录并输出每个点数出现的次数。
3. **修改规则**：例如设置目标点数必须精确匹配（不可超过）。
4. **添加赌注机制**：玩家初始有 100 元，每局下注，输赢影响余额。
5. **不使用 `std::format`**：改用传统流式输出，观察区别。

---

**Craps 游戏综合运用了多个 C++ 特性，是学习控制流、函数、随机数、枚举和格式化输出的绝佳练习项目！继续完善它，你会收获更多！** 🎲
