# C++ 入门笔记：按值传递 vs 按引用传递

> 本笔记通过求平方的示例，对比 C++ 中两种参数传递方式：**按值传递（pass-by-value）** 与 **按引用传递（pass-by-reference）**，理解它们的区别、适用场景及对实参的影响。

---

## 1. 完整代码示例

```cpp
#include <iostream>

int squareByValue(int number);
void squareByReference(int& numberRef);

int main() {
  int x{2};
  int z{2};

  std::cout << "x = " << x << " before squareByValue\n";
  std::cout << "Value returned by squareByValue: " << squareByValue(x) << '\n';
  std::cout << "x = " << x << " after squareByValue\n\n";

  // demonstrate squareByReference
  std::cout << "z = " << z << " before squareByReference\n";
  squareByReference(z);
  std::cout << "z = " << z << " after squareByReference\n";
}

int squareByValue(int number) { return number *= number; }
void squareByReference(int& numberRef) { numberRef *= numberRef; }
```

---

## 2. 代码逐行解析

### 2.1 头文件与函数声明
```cpp
#include <iostream>

int squareByValue(int number);
void squareByReference(int& numberRef);
```
- 声明了两个函数：
  - `squareByValue`：按值传递，返回平方值。
  - `squareByReference`：按引用传递，无返回值（`void`），直接修改实参。

### 2.2 `main` 函数
```cpp
int x{2};
int z{2};
```
- 初始化两个变量 `x` 和 `z`，值均为 2。`z` 用于演示引用传递的效果。

### 2.3 按值传递的调用
```cpp
std::cout << "x = " << x << " before squareByValue\n";
std::cout << "Value returned by squareByValue: " << squareByValue(x) << '\n';
std::cout << "x = " << x << " after squareByValue\n\n";
```
- 调用 `squareByValue(x)`，传入 `x` 的**副本**。
- 函数返回平方值（4），但 `x` 本身**不变**（仍为 2）。
- 输出结果验证了按值传递的“拷贝”特性。

### 2.4 按引用传递的调用
```cpp
std::cout << "z = " << z << " before squareByReference\n";
squareByReference(z);
std::cout << "z = " << z << " after squareByReference\n";
```
- 调用 `squareByReference(z)`，传入 `z` 的**引用**（别名）。
- 函数内部修改 `numberRef` 即修改 `z` 本身。
- 输出结果显示 `z` 变为 4（平方值）。

### 2.5 函数定义
```cpp
int squareByValue(int number) { return number *= number; }
```
- 形参 `number` 是实参的副本。
- `number *= number` 计算平方，返回结果。
- **注意**：`number *= number` 等价于 `number = number * number`，使用了复合赋值运算符。
- 返回值为 `int`，原始实参不受影响。

```cpp
void squareByReference(int& numberRef) { numberRef *= numberRef; }
```
- 形参 `numberRef` 是实参的引用（别名）。
- `numberRef *= numberRef` 直接修改实参。
- 返回类型为 `void`，因为修改通过引用完成。

---

## 3. 核心知识点

### 3.1 按值传递（Pass-by-Value）
| 特性 | 说明 |
|------|------|
| **机制** | 实参的值被**拷贝**到形参 |
| **对实参的影响** | 函数内修改形参不影响实参 |
| **优点** | 安全，实参不会被意外修改 |
| **缺点** | 对大型对象拷贝开销大 |
| **适用场景** | 小型数据类型（`int`, `double` 等），不希望修改实参时 |

### 3.2 按引用传递（Pass-by-Reference）
| 特性 | 说明 |
|------|------|
| **机制** | 形参是实参的**别名**（引用），共享同一内存 |
| **对实参的影响** | 函数内修改形参即修改实参 |
| **优点** | 避免拷贝开销，可直接修改实参 |
| **缺点** | 可能意外修改实参（若意图是只读，应使用 `const` 引用） |
| **适用场景** | 大型对象、需要修改实参、避免拷贝开销 |

### 3.3 引用的语法
- 声明引用：`类型& 引用名 = 变量;`
- 例如：`int& numberRef = z;`（但通常作为函数形参）
- 引用必须在声明时**初始化**，且不能重新绑定到其他变量。
- 函数形参中的引用在调用时自动绑定到实参。

### 3.4 复合赋值运算符 `*=`
- `number *= number;` 等价于 `number = number * number;`
- 类似的还有 `+=`, `-=`, `/=`, `%=` 等。

---

## 4. 代码风格与改进

### 4.1 使用 `const` 引用（只读）
如果函数不需要修改实参，但希望避免拷贝开销，可用 `const` 引用：
```cpp
void printValue(const int& number) {
    std::cout << number << '\n';
}
```
- 既能避免拷贝，又防止意外修改。

### 4.2 返回引用（需谨慎）
可以返回引用，但必须确保引用的对象在函数返回后仍然有效（如全局变量、静态变量、成员变量）：
```cpp
int& getElement(int* arr, int index) {
    return arr[index];  // 返回数组元素的引用
}
```

### 4.3 使用 `auto` 简化
在 C++11 后，可用 `auto` 推导类型，但引用类型的推导需注意 `auto` 会忽略引用（除非使用 `auto&`）。

---

## 5. 编译与运行

### 5.1 编译
```bash
g++ -std=c++17 square.cpp -o square
```

### 5.2 运行输出
```
x = 2 before squareByValue
Value returned by squareByValue: 4
x = 2 after squareByValue

z = 2 before squareByReference
z = 4 after squareByReference
```

---

## 6. 对比总结

| 方面 | 按值传递 | 按引用传递 |
|------|----------|------------|
| **参数写法** | `int number` | `int& numberRef` |
| **实参是否修改** | 否 | 是 |
| **拷贝开销** | 有（大型对象开销大） | 无 |
| **可读性** | 明确，实参不会变 | 需注意函数可能修改实参 |
| **安全性** | 高（不会意外修改） | 中（可能误改，可用 `const` 提高安全性） |

---

## 7. 练习建议

1. **编写 `increment` 函数**：按引用传递，使实参加 1。
2. **编写 `swap` 函数**：交换两个整数的值（必须用引用）。
3. **将 `squareByValue` 改为 `const` 引用**，观察能否编译（不能，因为 `const` 引用不能修改）。
4. **测试传递大型对象**：如 `std::string`，对比按值传递和按引用传递的性能。
5. **阅读 `std::swap` 源码**，理解它是如何通过引用实现交换的。

---

## 8. 扩展：指针传递（Pass-by-Pointer）

C++ 也支持通过指针传递，类似于引用，但更灵活（可指向 `nullptr`，可重新绑定），但语法更繁琐：

```cpp
void squareByPointer(int* numberPtr) {
    *numberPtr *= *numberPtr;  // 需要解引用
}

int main() {
    int z{2};
    squareByPointer(&z);  // 取地址传递
}
```

| 方式 | 优点 | 缺点 |
|------|------|------|
| **引用** | 语法简洁，自动解引用 | 必须初始化，不能为空 |
| **指针** | 可为空，可重新指向 | 语法繁琐，可能产生空指针错误 |

---

**按值传递与按引用传递是 C++ 函数设计的重要基础，理解它们的差异能帮助你写出更高效、更安全的代码。继续练习，掌握更多传参技巧！** 🚀
