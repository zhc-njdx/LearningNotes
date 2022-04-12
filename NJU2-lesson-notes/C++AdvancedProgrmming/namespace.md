### 名称空间

#### 1、相关术语

- 声明区域：可以在其中声明变量的区域

- 潜在作用域：变量的声明点到声明区域的结尾

- 作用域：变量可见的区域

#### 2、名称空间

> 新型的声明区域

```cpp
namespace ns{
    int n;
    string name;
    struct info { ... };
    void func();
    //...
}
```

名称空间是可以是全局的，也可以位于另一个名称空间中，但不能位于代码块里。

名称空间是开放的，可以随时把名称加到名称空间中。

使用名称空间中的变量需要使用作用域解析运算符 `::`

#### 3、using 声明和 using 编译指令

3.1 using 声明 使 名称空间中的指定标识符可用

将**特定的名称**添加到它**所属的声明区域**(指using声明所属的声明区域)中

```cpp
int main(){
    using ns::name; // 将名称name添加到main()定义的声明区域，于是在该声明区域中name指ns1::name，且该声明区域不能再定义name名称
    //...
}
```

> using声明，**像是声明了相应名称**，使得在该声明区域中的该名称被占用（`name `被 `ns1::name`占用），所以此名称空间中不能再出现该名称(`name`)(无论是直接声明还是using声明)，否则会出现二义性。

3.2 using 编译指令 使 整个名称空间可用

使该名称空间中的所有名称都可用

```cpp
char name = 'x';
int main(){
    using namespace ns;
    name = "curry";
    cout << name; // error: Reference to 'name' is ambiguous (global name and ns::name)
    int name = 1; // hides ns::name 局部变量隐藏名称空间名
    cout << name; // local name: 1
    cout << ::name; // global name: 'x'
    cout << ns::name; // ns::name: "curry"
}
```



> using编译指令使名称可用的方式和using声明不一样，**更像是自动帮程序员加上作用域解析运算符。**
>
> 所以在编译时就会对名称进行解析，以判断其所属的声明区域。

<font color="red">所以说，使用using 声明比使用 using 编译指令更安全，因为其对名称的指定更加清晰，不易出现二义性。</font>

