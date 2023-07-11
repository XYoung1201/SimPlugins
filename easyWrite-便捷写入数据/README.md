# Easy Write

`easyWrite` is a C++ library designed to simplify file writing operations. With this library, you can easily write multiple data types, such as integers, floating-point numbers, boolean values, and characters, to text files. It features a linked list structure for data storage, flexible data naming, automatic header writing, and significantly simplifies input when recording the same block of memory data multiple times.

## Features

- Automatic file creation
- Linked list structure for data storage
- Support for multiple data types
- Flexible data naming
- Automatic header writing
- Simplified writing operations with overloaded operators
- Automatic file closing
- Greatly simplifies input operations when recording the same block of memory data multiple times

## Usage

1. Add `easyWrite.h` and `easyWrite.cpp` to your project.
2. In the source file where you want to use `easyWrite`, include the header file `#include "easyWrite.h"`.
3. Create an object of the `easyWrite` class and write data and data names using the overloaded `<<` operator.

Example:

```cpp
#include "easyWrite.h"

int main() {
    int a = 42;
    double b = 3.14;
    bool c = true;
    const char* str_a = "Integer";
    const char* str_b = "Floating-point";
    const char* str_c = "Boolean";

    easyWrite ew("output.txt", true); // Create an easyWrite object, specifying the file name and whether to write a header
    ew << &a << str_a << &b << str_b << &c << str_c; // Use the << operator to write data and data names
    ew.write(); // Write the data to the file

    a = 100;
    b = 6.28;
    c = false;
    ew.write(); // Write the data to the file again, without re-adding the data and data names

    return 0;
}
```



# Easy Write

`easyWrite` 是一个 C++ 类库，旨在简化文件写入操作。这个类库允许您将多种数据类型（如整数、浮点数、布尔值和字符）写入文本文件。它的特点在于使用链表结构存储数据并支持灵活的数据命名、自动表头写入功能，以及在需要多次记录同一块内存数据时大大简化输入。

## 功能

- 自动创建文件
- 使用链表结构存储数据
- 支持多种数据类型
- 灵活的数据命名
- 自动表头写入
- 使用重载操作符简化写入操作
- 自动关闭文件
- 大大简化在多次记录同一块内存数据时的输入操作

## 使用方法

1. 将 `easyWrite.h` 和 `easyWrite.cpp` 添加到您的项目中。
2. 在需要使用 `easyWrite` 的源文件中，包含头文件 `#include "easyWrite.h"`。
3. 创建 `easyWrite` 类的对象，并通过重载的 `<<` 操作符写入数据和数据名称。

示例：

```cpp
#include "easyWrite.h"

int main() {
    int a = 42;
    double b = 3.14;
    bool c = true;
    const char* str_a = "整数";
    const char* str_b = "浮点数";
    const char* str_c = "布尔值";

    easyWrite ew("output.txt", true); // 创建一个 easyWrite 对象，指定文件名和是否写入表头
    ew << &a << str_a << &b << str_b << &c << str_c; // 使用 << 操作符写入数据和数据名称
    ew.write(); // 将数据写入文件

    a = 100;
    b = 6.28;
    c = false;
    ew.write(); // 再次将数据写入文件，无需重新添加数据和数据名称

    return 0;
}
```