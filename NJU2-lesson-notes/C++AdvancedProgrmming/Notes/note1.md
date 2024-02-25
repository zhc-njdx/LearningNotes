### Language

- Syntax (Backus-Naur Form EBNF/语法图)、Semantics (语义)、Pragmatics

  > <ID>::=

  

  

### Programming



The Science of programming



> Data Flow !!!



The Art of Computer Programming





### Programming Paradigm

Imperative Programming(命令式编程)

- Procedural
  - based upon the concept of the procedure call



- Object-Oriented
  - The theory of concepts, and models of human interaction with real world phenomena



Declarative Programming

给出计算步骤，但不了解计算细节

- Functional

  - "no side effect"

  - Mathematics and the theory of functions
  - Lisp(atom, list, cons)
- Logical

  - Automatic proofs within artificial intelligence
  - Based on axioms, inference rules, and queries
  - prolog





> 3.9 周三34 C++

### function invoke kind:

- _cdecl：caller allocate space and caller free space 



- _stdcall：caller allocate space and callee free space 



- _fastcall：using registers to store parameter to accelerate the speed. 1st argument in %ecx and 2nd argument in %edx and others in stack



- _thiscall：object-oriented



### inline



**1**.used for **small** and **simple** function



**2**.in the file inline function don't need function protype but need the **full function code**

```cpp
/*it is correct*/
inline int add(int x, int y){
    return x + y;
}

int r = add(1,2); // ===> expand to r = 1 + 2;

/*it is wrong*/
inline int add(int x, int y);

int r = add(1,2);
```



**3**.in the inline function, "simple" means its logic is simple, it better not to involve "for" , "switch" these code blocks that need to jump. 

Because of temporal and spatial locality(时间和空间局部性), if the inline function has these code blocks ,it will destory the locality when the inline functions expand in the main function.

when expansion occurs, the .cpp file will largen so that it will be divided into more pages.



说人话就是

1、内联函数的核心是展开。

2、如果内联函数中存在 for switch 等代码时，由于内联函数的展开使得代码变长，被分到更多的页中，原本循环或者跳转所具有的空间和时间局部性会被破坏（被分到不同的页）。而且，cache也会替换频繁，效果严重下降。此外，由于被分到的页增多，OS 调度页时的加载等也会耗费更多的时间，程序性能可能受到较大影响。



### 默认参数



```cpp
/*main.cpp*/
int func(int x, int y, int z); 
// int func(int x, int y = 2, int x = 3) // function protype need to figure out the default parameters and their values.

func(1); // it is a fault

/*func.h*/
int func(int x, int y = 2, int x = 3){ // actually it isn't necessary to write the default parameters...
    //...
}


```



### 关于C/C++的编译函数名

```cpp
int func(int a, int b);

/**
对于这个函数，在C++中，编译器会将函数名定义为 _Z4funcii
而在C中，函数名就是 func
这也是为什么C++支持函数重载而C不支持的原因。
**/

extern "C" int func(int a, int b); // 告诉编译器以C的标准来编译这个函数
```



> 3.11 周五 C++

### "#"

all statement with "#" mean (find and replace || copy and paste).

```cpp
/*a.cpp*/
// scope
static int count = 0; // .. 文件级,仅限于本文件使用==> namespace
float salary = 0;  // ..... 程序级
void show(){...}
void process(){
    int i = 0;     // ...... 函数级
    while(){
        int c = 0; //   .... 块级
    }
}


/*b.cpp*/
extern float salary; // 声明, 不加extern 则为定义，会分配空间
extern void show(); // 可不加extern 



#define PI 3.14 // find and replace
```



### Header File

头文件：

> 头文件放置”引导“，即“引导”cpp文件中的相应变量和函数等找到定义，在链接时再匹配，如果此时找不到相关定义，则为链接错误。只要找到相关的声明(extern ...)，就不会发生编译错误。

- 常量定义

- 变量/函数声明

- inline，基于源代码复用

- 模板，template，基于源代码

- 编译预处理

- 类型定义（class, struct, union...） typedef







### namespace



使用的两种形式

- declaration
- directive

```cpp
namespace  L
{
    int k;
    void f(int);
    ...
}

// using-declaration
using L::k;
using L::f;


// using-directive
using namespace L;
```



```cpp
// 1. 别名
namespace American_Telephone_and_Telegraph{...}
namespace ATT = American_Telephone_and_Telegraph

// 2. 全局
int a;
namespace X{
    int a;
    void f(){
        int a = 0;
        
        a++; // f()里的 a
        X::a++; // X里的 a 
        ::a++; // 全局的 a
    }
}

// 3.开放
namespace A{
    int a;
    ...
}
namespace A{
    void f();
    ...
}

// 4.可嵌套
namespace L1{
    int a;
    ...
    namespace L2{
        void f();
        ...
    }
}
...
L1::L2::f();

using namespace L1;
L2::f();

// 5.重载
namespace B{
    void f(int);
    ...
}
namespace A{
    void f(char);
}

void f();
using namespace A;
void g(){
    f('1');
}

// 不建议在同一作用域两次使用using-directive
// z
using namespace B;
...
using namespace A;
...
void g(){
    f('1');
}
```









### CPP(Compile pre-process)

```cpp
#include ...
/*
* 1. make interface definitions available
* 2. compose source text
*/
#define ...
/**
1. symbolic constants // using 'const' : type-checking
2. open subroutines
	宏定义子程序: 由于没有类型，所以可以无限重载...
	inline 内联函数: inline 存在类型检查，更安全；而且更加完整。
	template: 编译器根据模板创建需要的函数
3. Generic subroutines : template
4. Generic "type" : template
5. renaming : namespace
6. String concatenation : define Func(x, y) x ## y
7. Special purpose syntax
8. General macro processing
*/
#ifdef ...
/**
Version Control : compile option
Commenting out code
*/
#pragma ...
/**
COntrol the layout
informing the compiler: 改变编译器
*/
```



> 3.23 周三

### 指针



#### void *

只管理地址信息

- 指针类型的公共接口

  可以赋值给任何类型的指针

- 任何操作必须做强制类型转换

> 将某块内存清零
>
> ```cpp
> void memset(void *pointer, unsigned size){
>     char *p = (char *)pointer;
>     for(int i = 0; i < size; i++){
>         *p++ = 0;
>     }
> }
>             
> void memcpy(void){
>     
> }
> 
> ```



#### 常量指针和指针常量

- 常量指针

  const <类型> * <指针变量>

  所指向的值是常量

  ![image-20220323094352621](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220323094352621.png)

  **常量指针可以指向变量**

  **变量指针不能指向常量**（可以强制转换）

  `int *q = const_cast<int *>(&c);  `

  编译器会将所有的const常量替换成值

  ![image-20220323100344048](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220323100344048.png)

  > <font color="red">use const whenever possible</font>

  （函数副作用只会发生在传递指针和使用引用的时候）

  函数副作用（swap函数）

  消除函数副作用（const=>只读）`void Func(const int* p)`

- 指针常量

  <类型> * const <指针变量>

  指针不能移动，但可以改变对应空间中的数值。



#### 数组与指针



- 数组变成表达式成分时，会进行类型转换(int *)

```cpp
void f(int a[], int n){
    for (int i = 0; i < n; i++){
    	*(a + i) = 0;
	}
}

int A[10];
sizeof(A); // 10 * sizeof(int) 40
sizeof(A+1); // sizeof(int) 指针类型数据的size(32位下是4;64位下是8) 数组变成表达式后类型变为int *
```

- 二维数组

> 多维数组与一维数组之间的形式转化

```cpp
int a[6][2];
/**  
typedef int T[2];
T a[6];
*/
// T* b <==> int (*b)[2];

// 降维
int *p = &a[0][0];
// p = a[0]; 会越界，但是可以
// p = a; 错的,a的类型是int **;而p的类型是int *

//升维
int x[24];
typedef int T[2];
(T*) x;
```



- 理解x与&x值相等

```cpp
int x[10];
x == &x == &x[0];

int y[10][10];
y == &y == y[0] == &y[0] == &y[0][0]
```

- 一般情况下，数组变成表达式成分时，会进行类型转换变成 `int *`
- 特殊情况：不会发生转换
  - `&`
  - `sizeof`
  - 被字符串常量初始化了的字符数组

### 动态变量

`new` vs `malloc`

> 1、使用malloc需要做类型转换
>
> 2、使用malloc给类数组申请空间时，不会调用类的构造函数；而new会

有效性判定

```cpp
int *p = new int;
if(p != nullptr)...
```

异常处理

```cpp
namespace std{
    typedef void (*new_handler)();
    new_handler set_new_handler(new_handler p) throw(); 
}
```



> exception
>
> 1、可以预见的
>
> 2、无法避免的



**归还**

> 有借用一定要归还，否则会造成memory leak 

delete 和 delete[]

> delete[] 会逐个调用类的析构函数，而delete不会

**为什么delete[]不用写数组大小？**

写和没写一样

C++每次new一个内存空间时，在这段空间的上面放置此次申请的空间大小(cookie)。所以当delete时，只要向上找到这个空间大小，就可以正确释放空间。

但是记住，申请得到的指针一定不要移动！！！否则在delete时，就会释放掉错误的空间。



