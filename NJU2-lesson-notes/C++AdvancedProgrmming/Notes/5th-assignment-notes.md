#### UDL

> User Defined Literals
>
> added from C+11

为内置数据类型 (for built-in types)

大部分的计算都在编译时间完成

只支持后缀 (only suffix form is supported)

函数原型`<typename1> operator"" _<suffix>(<typename2>);`



`constexpr` 和 `const` 的区别

两个关键字都可以修饰对象或者函数

**对象**

`const`声明一个对象是常量，保证其值不会改变（初始化之后）

`constexpr`声明一个可以用在常量表达式中的对象

**函数**

`const`只能修饰非静态成员函数，保证成员函数不会修改非静态成员变量（除了mutable 修饰的成员变量）

`constexpr`可以修饰成员函数、非成员函数，也可以修饰构造函数。声明适合用在常量表达式（constant expressions）中的函数

- 函数体必须是非虚的，而且要**及其简单**
- 参数和返回值必须是 [`literal types`](https://en.cppreference.com/w/cpp/named_req/LiteralType)

