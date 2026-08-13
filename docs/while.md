# C++ 入门笔记：哨兵控制循环与成绩统计

> 本笔记涵盖哨兵控制循环（`while`）、累加器、计数器、条件判断避免除零，以及浮点数输出格式控制（`std::setprecision` 和 `std::fixed`）。

---

## 1. 完整代码示例

```cpp
#include <iostream>
#include <iomanip>

int main()
{
  double total{0.0};
  int gradeCounter{0};

  std::cout << "Enter grade or -1 to quit: ";
  int grade;
  std::cin >> grade;
  while (grade != -1)
  {
    total = total + grade;
    gradeCounter = gradeCounter + 1;
    std::cout << "Enter grade or -1 to quit: ";
    std::cin >> grade;
  }

  if (gradeCounter != 0)
  {
    double average{total / gradeCounter};
    std::cout << "\nTotal of the " << gradeCounter << " grades entered is " << total;
    std::cout << std::setprecision(2) << std::fixed;
    std::cout << "\nClass average is " << average;
  }
  else
  {
    std::cout << "No grades were entered\n";
  }

  return 0;
}
```

---

## 2. 代码逐行解析

### 2.1 头文件
```cpp
#include <iostream>   // 标准输入输出流
#include <iomanip>    // 格式化输入输出（如 setprecision, fixed）
```
- `<iomanip>` 提供了操纵符，用于控制输出的格式，例如设置小数精度、对齐等。

### 2.2 变量定义与初始化
```cpp
double total{0.0};    // 累加器，用 double 存储总和（支持小数）
int gradeCounter{0};  // 计数器，记录输入的有效成绩个数
```
- 与之前版本不同，`total` 使用 `double` 类型，以支持精确的平均值计算。
- `gradeCounter` 初始化为 `0`，因为用户可能一开始就输入 `-1` 退出，此时没有有效成绩。

### 2.3 哨兵控制循环（Sentinel-Controlled Loop）
```cpp
std::cout << "Enter grade or -1 to quit: ";
int grade;
std::cin >> grade;
while (grade != -1)
{
    total = total + grade;
    gradeCounter = gradeCounter + 1;
    std::cout << "Enter grade or -1 to quit: ";
    std::cin >> grade;
}
```

#### 工作原理：
1. **首轮输入**：在循环外先读取第一个成绩，作为“启动”操作。
2. **循环条件**：判断输入的值是否为哨兵值（`-1`）。
   - 若不为 `-1`，则执行循环体：累加、计数器加一，然后再次提示并读取下一个成绩。
   - 若为 `-1`，则跳过循环，结束输入。
3. **哨兵值**：`-1` 是一个“标记”，用于终止循环，它本身**不是**有效成绩数据。
4. **优点**：用户可输入任意数量的成绩，无需事先指定数量，程序灵活。

#### 为什么不直接在循环内读取？
- 如果使用 `do-while` 或 `while(true)` 并在循环内部读取，也可以，但当前设计是经典的“先读后判断”模式，避免了重复代码（但这里确实重复了提示语句，可优化）。

### 2.4 循环后的判断（防止除零）
```cpp
if (gradeCounter != 0)
{
    double average{total / gradeCounter};
    // 输出...
}
else
{
    std::cout << "No grades were entered\n";
}
```
- **关键**：必须检查 `gradeCounter` 是否为零，否则 `total / 0` 会导致**未定义行为**（程序崩溃）。
- 只有当存在有效成绩时，才计算并输出平均值；否则输出提示信息。

### 2.5 输出格式控制
```cpp
std::cout << std::setprecision(2) << std::fixed;
std::cout << "\nClass average is " << average;
```
- `std::setprecision(2)`：设置浮点数输出精度为 2 位。
- `std::fixed`：以固定小数位格式输出（即小数点后固定 2 位），而不是科学计数法。
- 这两个操纵符会持续生效，直到被修改。例如，`average` 将被输出为 `82.40` 而非 `82.4` 或 `8.24e1`。

---

## 3. 核心知识点总结

### 3.1 哨兵控制循环 vs 计数器控制循环
| 特性 | 计数器控制循环（已知次数） | 哨兵控制循环（未知次数） |
|------|---------------------------|--------------------------|
| **循环次数** | 预先确定（如 10 次） | 由用户输入的特殊值决定 |
| **适用场景** | 固定数量的输入 | 不确定数量的输入，需终止标记 |
| **示例** | `while (i <= 10)` | `while (grade != -1)` |
| **危险** | 可能死循环（若未更新计数器） | 需确保哨兵值不会作为正常数据出现 |

### 3.2 累加器与计数器的初始化
- 累加器 `total` 应初始化为 `0`（或 `0.0`）。
- 计数器 `gradeCounter` 初始化为 `0`，因为循环体只有输入有效成绩时才增加。

### 3.3 避免除零
- 任何除法运算前，都必须确保分母非零。使用 `if` 判断是标准做法。

### 3.4 格式化输出（`<iomanip>`）
| 操纵符 | 作用 |
|--------|------|
| `std::setprecision(n)` | 设置浮点数输出的有效位数（与 `fixed` 配合时表示小数位数） |
| `std::fixed` | 强制使用定点小数表示法（非科学计数法） |
| `std::showpoint` | 强制显示小数点（即使没有小数部分） |
| `std::setw(w)` | 设置字段宽度（用于对齐） |

> **注意**：`std::setprecision` 和 `std::fixed` 会持续影响后续所有浮点数输出，直到再次被修改。

---

## 4. 改进建议

### 4.1 使用 `do-while` 减少重复代码
```cpp
int grade;
do {
    std::cout << "Enter grade or -1 to quit: ";
    std::cin >> grade;
    if (grade != -1) {
        total += grade;
        gradeCounter++;
    }
} while (grade != -1);
```
这种结构避免了循环内外的重复提示语句，逻辑更紧凑。

### 4.2 使用 `+=` 和 `++` 简化
```cpp
total += grade;
gradeCounter++;
```

### 4.3 处理无效输入（非数字）
```cpp
if (!(std::cin >> grade)) {
    std::cout << "Invalid input. Exiting.\n";
    return 1;
}
```

### 4.4 支持更多哨兵值
可将哨兵值定义为常量：
```cpp
const int SENTINEL = -1;
while (grade != SENTINEL) { ... }
```

---

## 5. 运行示例

```
Enter grade or -1 to quit: 85
Enter grade or -1 to quit: 92
Enter grade or -1 to quit: 78
Enter grade or -1 to quit: 88
Enter grade or -1 to quit: 95
Enter grade or -1 to quit: -1

Total of the 5 grades entered is 438
Class average is 87.60
```

**无输入情况**：
```
Enter grade or -1 to quit: -1
No grades were entered
```

---

## 6. 练习建议

1. **改写为 `do-while` 循环**，比较两种写法的优缺点。
2. **添加最大值和最小值跟踪**，在循环中更新 `maxGrade` 和 `minGrade`。
3. **输出所有成绩（可选）**：使用数组或 `std::vector` 存储输入的成绩，便于后续处理。
4. **尝试不同精度**：改为 `setprecision(3)` 或 `setprecision(0)`，观察输出变化。
5. **使用 `std::showpoint`** 强制显示小数点，即使平均值为整数（如 `88.00`）。

---

**你已掌握两种常见的循环控制模式，现在可以灵活处理固定次数和任意数量的输入了！继续探索更多有趣的程序吧！** 🚀
