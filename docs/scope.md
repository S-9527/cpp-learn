# C++ 入门笔记：作用域与存储类别

> 本笔记通过一个综合示例，演示 C++ 中全局变量、局部变量、块作用域、静态局部变量以及变量隐藏（名称遮蔽）等核心概念。

---

## 1. 完整代码示例

```cpp
#include <iostream>
using namespace std;

void useLocal();       // 函数声明
void useStaticLocal();
void useGlobal();

int x{1}; // 全局变量

int main() {
  cout << "global x in main is " << x << '\n';

  const int x{5}; // main 的局部变量

  cout << "local x in main's outer scope is " << x << '\n';

  {                 // 内部块开始
    const int x{7}; // 遮蔽外层 x 和全局 x
    cout << "local x in main's inner scope is " << x << '\n';
  }

  cout << "local x in main's outer scope is " << x << '\n';

  useLocal();       // useLocal 有局部 x
  useStaticLocal(); // useStaticLocal 有静态局部 x
  useGlobal();      // useGlobal 使用全局 x
  useLocal();       // useLocal 重新初始化局部 x
  useStaticLocal(); // 静态局部 x 保留上次的值
  useGlobal();      // 全局 x 也保留上次的值

  cout << "\nlocal x in main is " << x << '\n';
}

void useLocal() {
  int x{25}; // 每次调用时重新初始化

  cout << "\nlocal x is " << x << " on entering useLocal\n";
  ++x;
  cout << "local x is " << x << " on exiting useLocal\n";
}

void useStaticLocal() {
  static int x{50}; // 仅在第一次调用时初始化

  cout << "\nlocal static x is " << x << " on entering useStaticLocal\n";
  ++x;
  cout << "local static x is " << x << " on exiting useStaticLocal\n";
}

void useGlobal() {
  cout << "\nglobal x is " << x << " on entering useGlobal\n";
  x *= 10;
  cout << "global x is " << x << " on exiting useGlobal\n";
}
```

---

## 2. 代码逐行解析

### 2.1 全局变量
```cpp
int x{1}; // 全局变量
```
- 定义在**所有函数之外**的变量称为**全局变量**。
- 作用域：从定义点开始到文件末尾，在所有函数中均可见。
- 生命周期：从程序启动到程序结束。
- 本例中，全局变量初始值为 `1`。

### 2.2 `main` 函数中的局部变量与块作用域
```cpp
cout << "global x in main is " << x << '\n';  // 输出全局 x = 1

const int x{5}; // main 的局部变量，遮蔽全局 x
cout << "local x in main's outer scope is " << x << '\n'; // 输出 5

{ // 内部块
    const int x{7}; // 遮蔽外层 x 和全局 x
    cout << "local x in main's inner scope is " << x << '\n'; // 输出 7
}

cout << "local x in main's outer scope is " << x << '\n'; // 输出 5（恢复）
```
- `main` 中声明了局部变量 `x`，它**遮蔽**了全局变量 `x`。
- 在 `main` 的**内部块**（`{}`）中，又声明了新的局部变量 `x`，遮蔽了 `main` 的局部变量。
- 离开内部块后，`main` 的局部变量 `x` 重新可见。

### 2.3 `useLocal` 函数——普通局部变量
```cpp
void useLocal() {
  int x{25}; // 每次调用都重新初始化

  cout << "\nlocal x is " << x << " on entering useLocal\n";
  ++x;
  cout << "local x is " << x << " on exiting useLocal\n";
}
```
- `x` 是普通局部变量（自动存储期），**每次调用** `useLocal` 时都会重新初始化为 `25`。
- 函数返回后，该变量被销毁，下次调用重新创建。
- 输出：第一次调用 `25 → 26`，第二次调用再次 `25 → 26`。

### 2.4 `useStaticLocal` 函数——静态局部变量
```cpp
void useStaticLocal() {
  static int x{50}; // 仅在第一次调用时初始化

  cout << "\nlocal static x is " << x << " on entering useStaticLocal\n";
  ++x;
  cout << "local static x is " << x << " on exiting useStaticLocal\n";
}
```
- `static int x{50};` 是**静态局部变量**。
- 只在**第一次调用**时初始化，后续调用保留上次的值。
- 生命周期贯穿整个程序运行，但作用域仅限于该函数内部。
- 输出：第一次调用 `50 → 51`，第二次调用 `51 → 52`。

### 2.5 `useGlobal` 函数——修改全局变量
```cpp
void useGlobal() {
  cout << "\nglobal x is " << x << " on entering useGlobal\n";
  x *= 10;
  cout << "global x is " << x << " on exiting useGlobal\n";
}
```
- 直接操作全局变量 `x`（未声明同名局部变量遮蔽）。
- 每次调用都会修改全局变量，且修改会**持久保留**。
- 输出：第一次 `1 → 10`，第二次 `10 → 100`。

---

## 3. 核心知识点

### 3.1 作用域（Scope）
| 类型 | 定义位置 | 作用域 | 示例 |
|------|----------|--------|------|
| **全局作用域** | 函数外 | 从定义点到文件末尾 | `int x{1};` |
| **局部作用域** | 函数内（块内） | 从声明点到函数（块）结束 | `int x{5};` |
| **块作用域** | `{}` 内 | 仅限该块内部 | `{ int x{7}; }` |

### 3.2 存储类别（Storage Class）
| 存储类别 | 关键字 | 生命周期 | 初始化时机 | 示例 |
|----------|--------|----------|------------|------|
| **自动存储期** | `auto`（默认） | 从声明到作用域结束 | 每次进入作用域 | `int x{25};` |
| **静态存储期（局部）** | `static` | 整个程序运行期 | 仅第一次执行到声明时 | `static int x{50};` |
| **静态存储期（全局）** | 无（或 `static`） | 整个程序运行期 | 程序启动时 | `int x{1};` |
| **动态存储期** | `new` / `delete` | 手动控制 | 显式调用 `new` | `int* p = new int{10};` |

### 3.3 名称遮蔽（Name Hiding / Shadowing）
- 当内层作用域声明与外层作用域同名的变量时，内层变量会**遮蔽**外层变量。
- 本例中：
  - `main` 的局部 `x` 遮蔽全局 `x`。
  - 内部块的 `x` 遮蔽 `main` 的 `x` 和全局 `x`。
- 离开内层作用域后，外层的变量恢复可见。

### 3.4 静态局部变量的特点
- 仅初始化一次（在程序启动时或第一次执行到声明时）。
- 函数返回后值保留，下次调用保留上次的值。
- 适合用作函数内部的“状态记忆”（如计数器、缓存结果等）。

---

## 4. 程序运行输出（逐行预测）

```
global x in main is 1
local x in main's outer scope is 5
local x in main's inner scope is 7
local x in main's outer scope is 5

local x is 25 on entering useLocal
local x is 26 on exiting useLocal

local static x is 50 on entering useStaticLocal
local static x is 51 on exiting useStaticLocal

global x is 1 on entering useGlobal
global x is 10 on exiting useGlobal

local x is 25 on entering useLocal
local x is 26 on exiting useLocal

local static x is 51 on entering useStaticLocal
local static x is 52 on exiting useStaticLocal

global x is 10 on entering useGlobal
global x is 100 on exiting useGlobal

local x in main is 5
```

---

## 5. 关键对比总结

| 变量类型 | 声明方式 | 作用域 | 生命周期 | 初始化次数 |
|----------|----------|--------|----------|------------|
| 全局变量 | 函数外定义 | 全局 | 整个程序 | 1 次 |
| 局部变量（自动） | 函数内（无修饰） | 函数/块内 | 函数调用期间 | 每次进入作用域 |
| 静态局部变量 | 函数内 + `static` | 函数/块内 | 整个程序 | 1 次 |
| 块作用域变量 | `{}` 内声明 | 块内 | 块执行期间 | 每次进入块 |

---

## 6. 练习建议

1. **预测输出**：在不运行代码的情况下，手写出完整的输出顺序，检验对作用域和存储类别的理解。
2. **修改全局变量名**：将全局 `x` 改为 `globalX`，观察不再发生遮蔽时的输出变化。
3. **在 `useGlobal` 中声明同名局部变量**，观察它是否会遮蔽全局变量。
4. **测试 `static` 在函数中的计数器**：编写一个函数，利用静态局部变量记录被调用的次数。
5. **使用 `::x` 访问全局变量**：在 `main` 中尝试 `::x` 强制访问全局变量，即使有同名局部变量。

---

## 7. 扩展：`extern` 关键字与跨文件全局变量

- 若要在多个文件共享全局变量，可在头文件中声明 `extern int x;`，在一个 `.cpp` 文件中定义 `int x = 1;`。
- `extern` 告知编译器该变量在其他文件中定义，避免重复定义错误。

---

**理解作用域和存储类别是编写高质量 C++ 代码的基础。掌握这些概念，你就能更精确地控制变量的可见性和生命周期，写出更清晰、更健壮的程序。继续探索！** 🚀
