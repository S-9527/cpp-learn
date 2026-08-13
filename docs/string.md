# C++ 入门笔记：`std::string` 字符串基础操作

> 本笔记涵盖 C++ 标准库 `std::string` 的常用操作：声明、初始化、连接、比较、获取长度及判空，并探讨 C++20 新增的 `starts_with()` / `ends_with()` 成员函数。

---

## 1. 完整代码示例

```cpp
#include <iostream>
#include <string>

int main()
{
  std::string s1{"happy"};
  std::string s2{" birthday"};
  std::string s3;

  std::cout << "s1 " << s1 << " length: " << s1.length();
  std::cout << "\ns2 " << s2 << " length: " << s2.length();
  std::cout << "\ns3 " << s3 << "length: " << s3.length();

  std::cout << "\nThe result of compare s2 to s1: "
            << std::boolalpha
            << "\ns2 == s1 " << (s2 == s1)
            << "\ns2 != s1 " << (s2 != s1);

  std::cout << "\nTesting s3.empty(): \n";
  if (s3.empty())
  {
    std::cout << "s3 is empty; assigning to s3;\n";
    s3 = s1 + s2;
    std::cout << "s3: " << s3;
  }

  return 0;
}
```

---

## 2. 代码逐行解析

### 2.1 头文件与 `std::string`
```cpp
#include <iostream>   // 输入输出流
#include <string>     // std::string 类定义
```
- `std::string` 是 C++ 标准库提供的字符串类型，位于 `<string>` 头文件。
- 它自动管理内存，支持动态扩展，比 C 风格字符串（`char*`）更安全、易用。

### 2.2 字符串声明与初始化
```cpp
std::string s1{"happy"};    // 列表初始化（C++11 起推荐）
std::string s2{" birthday"};
std::string s3;             // 默认构造，空字符串
```
- `std::string` 支持多种初始化方式：
  - `std::string s1 = "happy";`    （拷贝初始化）
  - `std::string s2("birthday");`  （直接初始化）
  - `std::string s3{};`            （值初始化，空串）
- 使用 `{}` 列表初始化更为统一，且能防止某些窄化问题。

### 2.3 获取字符串长度
```cpp
std::cout << "s1 " << s1 << " length: " << s1.length();
```
- `length()` 返回字符串中字符的个数（`size_t` 类型），不包括结尾的 `\0`。
- 同义函数 `size()`，行为完全一致（`length()` 是历史遗留，`size()` 为 STL 容器统一接口）。

### 2.4 字符串连接（`+` 运算符）
```cpp
s3 = s1 + s2;
```
- `+` 运算符被重载，用于拼接两个 `std::string` 对象，返回一个新的 `std::string`。
- 也支持 `std::string + const char*` 等混合形式，但此处 `s1` 和 `s2` 均为 `std::string`。

### 2.5 字符串比较（关系运算符）
```cpp
std::cout << std::boolalpha
          << "\ns2 == s1 " << (s2 == s1)
          << "\ns2 != s1 " << (s2 != s1);
```
- `std::string` 重载了 `==`、`!=`、`<`、`>` 等关系运算符，按字典序逐字符比较。
- `std::boolalpha` 是一个 I/O 操纵符，使 `bool` 值输出为 `true`/`false` 而不是 `1`/`0`。
- 括号 `(s2 == s1)` 是必要的，因为 `<<` 优先级高于 `==`，不加括号会解析为 `(cout << s2) == s1` 导致编译错误。

### 2.6 判空操作 `.empty()`
```cpp
if (s3.empty()) {
    // ...
}
```
- `empty()` 返回 `bool`，字符串长度为 0 时为 `true`。
- 通常推荐用 `empty()` 而非 `length() == 0`，语义更清晰且效率更高（O(1)）。

---

## 3. 核心知识点总结

### 3.1 `std::string` 常用成员函数
| 函数 | 说明 | 示例 |
|------|------|------|
| `length()` / `size()` | 返回字符个数 | `s.length()` |
| `empty()` | 判断是否为空串 | `if (s.empty())` |
| `operator+` | 字符串连接 | `s3 = s1 + s2` |
| `operator==` 等 | 字典序比较 | `s1 == s2` |
| `assign()` | 重新赋值（可选） | `s.assign("new")` |
| `c_str()` | 返回 C 风格 `const char*` | `printf("%s", s.c_str())` |

### 3.2 `std::boolalpha` 的作用
- 默认情况下，`bool` 值输出为 `0`（false）或 `1`（true）。
- 使用 `std::boolalpha` 后，输出为 `false` 或 `true`。
- 可通过 `std::noboolalpha` 恢复数字格式。

### 3.3 字符串拼接的几种方式
1. `s3 = s1 + s2;` —— 创建临时对象，然后赋值。
2. `s3 = s1; s3 += s2;` —— 使用 `+=` 直接在 `s3` 后追加，避免临时对象，效率更高。
3. `s3.append(s2);` —— 成员函数方式追加。

> **效率提示**：多次拼接时，考虑 `s3.reserve()` 预分配空间，避免反复重分配。

---

## 4. 编译与运行

### 4.1 编译（需 C++11 或更高）
```bash
g++ -std=c++11 string_demo.cpp -o string_demo
```

### 4.2 运行输出
```
s1 happy length: 5
s2  birthday length: 9
s3 length: 0
The result of compare s2 to s1:
s2 == s1 false
s2 != s1 true
Testing s3.empty():
s3 is empty; assigning to s3;
s3: happy birthday
```

> **注意**：`s2` 以空格开头，故输出为 `" birthday"`，长度 9（空格 + 8 个字母）。

---

## 5. 扩展：C++20 的 `starts_with()` 和 `ends_with()`

自 C++20 起，`std::string` 新增了以下成员函数，用于检查字符串是否以给定前缀/后缀开头或结尾：

```cpp
bool starts_with(std::string_view prefix) const;
bool starts_with(char ch) const;
bool starts_with(const char* prefix) const;

bool ends_with(std::string_view suffix) const;
bool ends_with(char ch) const;
bool ends_with(const char* suffix) const;
```

### 5.1 示例（需要 C++20）
```cpp
#include <iostream>
#include <string>

int main() {
    std::string s = "hello world";
    if (s.starts_with("hello")) {
        std::cout << "Starts with hello\n";
    }
    if (s.ends_with('d')) {
        std::cout << "Ends with d\n";
    }
    return 0;
}
```

### 5.2 为何你的编译器不支持？
- `starts_with()` 是 C++20 的新特性。
- 检查你的编译器版本：`g++ --version`。GCC 从 9.1 开始部分支持，完全支持需 GCC 11.1+ 并启用 `-std=c++20`。
- 若编译器较旧，可通过传统方式实现等效功能：
  ```cpp
  // 模拟 starts_with
  bool starts_with(const std::string& str, const std::string& prefix) {
      return str.rfind(prefix, 0) == 0;   // 从位置0开始查找prefix
  }
  // 或
  bool starts_with(const std::string& str, const std::string& prefix) {
      return str.compare(0, prefix.size(), prefix) == 0;
  }
  ```

### 5.3 何时使用
- 检查文件扩展名：`filename.ends_with(".cpp")`
- 检查 URL 协议：`url.starts_with("https://")`

---

## 6. 练习建议

1. **修改拼接方式**：将 `s3 = s1 + s2;` 改为 `s3 = s1; s3 += s2;`，观察输出是否一致。
2. **测试比较运算符**：尝试 `s1 > s2` 或 `s1 < s2`，理解字典序规则（基于 ASCII 码）。
3. **使用 `size()` 替代 `length()`**：验证二者返回值相同。
4. **模拟 `starts_with`**：若编译器不支持 C++20，编写一个函数实现相同功能，用于检查 `s1` 是否以 `"ha"` 开头。
5. **探索 `std::string_view`**：了解 C++17 引入的只读字符串视图，常与 `starts_with` 配合使用。

---

**你已经从数字世界拓展到了文本处理，`std::string` 是你未来编程中最常用的工具之一！继续前进！** 🚀
