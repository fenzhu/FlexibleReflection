This project presents a small, flexible runtime reflection system using C++11 language features.

For more information, see the blog series ["A Flexible Reflection System in C++"](http://preshing.com/20180116/a-primitive-reflection-system-in-cpp-part-1).

## Build Instructions

[CMake](https://cmake.org/) is required. Quick start:

    $ git clone https://github.com/preshing/FlexibleReflection
    $ cd FlexibleReflection
    $ mkdir build
    $ cd build
    $ cmake ..

For detailed build instructions, see ["How to Build a CMake-Based Project"](http://preshing.com/20170511/how-to-build-a-cmake-based-project).

## Implementation
如何使用C++实现反射
1. 对于需要实现反射的类，通过宏展开，向类中注入2个成员
- typeDescriptor，作为实际保存反射相关信息的对象。
- typeDescriptor的初始化函数。
2. 初始化类中反射相关的数据
- 声明typeDescriptor，调用初始化函数
- 初始化内容包括：名称、大小、成员名称、成员offset（运行时获取成员对象的指针）、成员的typeDescriptor（递归dump反射信息）
3. 提供查询反射数据的接口
- 通过helper对象获取类型T的typeDescriptor，获取方式为模板SFINAE，判断类型T是否存在反射注入。
- 拥有反射注入的类，返回typeDescriptor对象。
- 没有反射注入的语言自有类型，返回源文件中定义，而不是模板生成的，primitiveDescriptor对象。