> 2022.04.08

#### 自定义Stack

- C++结构化编程

```cpp
#include<iostream.h>
#define STACK_SIZE 100
struct Stack{
  int top;
  int buffer[STACK_SIZE];
};
void main(){
    Stack s1, s2;
    // 需要手动初始化
    s1.top = -1;
    s2.top = -1;
    //...
    
    // 可以直接操纵数据
    s1.buffer[2] = 1;
    s2.buffer[2]++;
}

// define the pop and push function
bool push(Stack &s, int i){
    //...
}

bool pop(Stack &s, int &i){
    //...
}
```

从上面可以看出，采用C++结构化编程，不能很好地实现封装和数据隐藏。只能依靠程序员自己对自己的约束来实现。总的来说还是存在安全隐患。

- C++面向对象编程

```cpp
#include<iostream.h>
#define STACK_SIZE 100
class Stack{
  private:
    int top;
    int buffer[STACK_SIZE];
  public:
    Stack(){top = -1;}
    bool push(int i);
    bool pop(int &i);
};

void main(){
    Stack s1,s2;// 不需要手动初始化
    // ...
    
    // 以下行为会被禁止
    s1.buffer[2] = -1;
}

bool Stack::push(int i){ // => bool push(Stack * const this, int i)
    // ...
}

bool Stack::pop(int &i){ // => bool pop(Stack * const this, int &i))
    // ...
}
```

采用以上代码实现，就能很好地实现数据隐藏和封装。

> 但是采用 Cfront 编译后，其代码其实和前面C++结构化编程的代码类似
>
> 只是编译器帮程序员做了初始化和数据访问控制的检查

<font color='red'>将函数放到结构体中，将数据和行为封装(Encapsulation)到一起，形成了抽象数据类型(ADT)，实现information hidden</font>

> 封装：减少类之间的耦合；



#### OOP

- concepts

  Program = Object1 + Object2 + ...

  Object = Data + Operation

  Message: Function call between the instances

- Object-Based（基于对象）: Ada

  - Without Inheritance



#### Encapsulation



```cpp
// a.h 头文件
class TDate{
  public:
    void SetDate(int y, int m , int d);
    int IsLeapYear();
  private:
    int year, month, day;
};

// a.cpp 源文件
void TDate::SetDate(int y, int m , int d){
    
}

int TDate::IsLeapYear(){
    // ...
}
=================================================
// 也可放在一起
// 但是这样就是在建议编译器对该函数进行inline
// 对于setter/getter函数可以放在一起，较大的函数需要采用声明与定义分开
class TDate{
  public:
    void SetDate(int y, int m , int d){
        // ...
    }
    int IsLeapYear(){
        // ...
    }
  private:
    int year, month, day;
};

TDate g; // g 就是一个对象，一块内存空间，不是引用或指针。这里的g已经调用了构造函数，分配了内存，做好了初始化。
int main(){
    TDate t;
    
    TDate * p = new TDate; // 指针
}
```



#### 构造函数

- 对象的初始化

- 描述

  - 与类同名、无返回类型

  - 自动调用，不可直接调用

  - 可重载

- 默认构造函数

  - 当类中未提供构造函数时，编译器系统提供，无参数

- public

  - 可定义为private

    <font color='red'>Why?</font> 单例模式。接管对象创建，在类内控制对象的创建。（限制只能创建一个对象等）



> <font color='red'>为什么要提供默认构造函数？</font>
>
> 默认构造函数不会去完成对象成员数据的初始化（在栈中，堆中）（全局和静态数据类型会被自动初始化）
>
> 因为要完成对 对象的初始化
>
> 1、建立对象标识符
>
> 2、开辟内存空间
>
> 3、执行初始化



- 调用
  - 自动调用

```cpp
class AP{
    public:
    	A();
    	A(int i);
    	A(char *p);
};
A a1 = A(1); // <=> A a1(1); <=> A a1 = 1;  // 调用 A(int i)
A a2 = A(); // <=> A a2; // 调用 A(), 注意: 不能写成 A a2();
A a3 = A("abcd"); // <=> A a3("abcd"); <=> A a3 = "abcd"; // 调用 A(char *p);
A a[4]; // 调用a[0]、a[1]、a[2]、a[3]的A()
A b[5] = {A(), A(1), A("abcd"), 2, "xyz"}; // 分别调用各自的初始化函数
```



#### 成员初始化表

- 构造函数的补充
- 执行
  - 先于构造函数体
  - <font color='red'>按类数据成员声明次序</font>

```cpp
class A{
    int x;
    const int y;
    int &z;
    public:
    A():y(1),z(x),x(0) {x = 100;} // 先x=0,再y=1,再z=x
}
```



> <font color='red'>为什么要有成员初始化表?</font>
>
> 针对const成员，引用类型成员，只能在声明时初始化，不能在函数中初始化。
>
> 所以引入成员初始化表，使得成员变量在声明的时候就进行初始化，也减轻了编译器的负担
>
> 但是C++11标准之后，编译器也允许在声明处直接初始化（和java类似）
>
> （C++98是不允许除静态变量外的变量在声明处初始化）



##### 通过成员初始化表来初始化成员对象

```cpp
class A{
    int m;
  public:
    A(){m=0;}
    A(int m1){m=m1;}
}

class B{
    int x;
    A a;
  public:
    B(){x=0;}
    B(int x1){x=x1;}
    B(int x1, int m1):a(m1){x=x1;} // 通过成员初始化表来初始化成员对象a  
}

void main(){
    B b1; // B::B()和A::A()
    B b2(1); // B::B(int)和A::A()
    B b3(1,2); // B::B(int)和A::A(int)
}
```



在构造函数中尽量使用成员初始化表取代赋值动作

- const成员 / reference成员 / 对象成员 适用
- 效率高
- 数据成员太多时，不宜使用
  - 降低可维护性



#### 析构函数

- ~<类名>()

- 对象消亡时，系统自动调用

  - 对象离开作用域时
  - delete

- public

  - 可定义为private

    <font color='red'>Why?</font>  强制自主控制对象存储分配（例如，对于一些栈空间很小，但是对象很大的情况，就不能在栈上创建对象）



```cpp
class A{
    public:
    	A();
    	void destroy(){delete this;}
    private: // 私有析构函数
 		~A();
}


// 因为编译器无法调用析构函数
A a; // X 报错
int main(){
    A aa; // X 报错
}

A *p = new A; // 在堆上创建，系统不主动调用析构函数
delete p; // X 不能在外部调用析构函数
p->destroy(); // p 有可能为空...

===================================
// better solution: 
static void free(A *p){
    delete p;
}

A::free(p);
```



> Java: finalize()
>
> GC（垃圾回收）：
>
> ​	效率障碍
>
> ​	存在不能用GC的场合
>
> ​	只能回收内存



RAII : Resource Acquisition Is Initialization

在对象初始化时，将获取的资源封装在对象中；当调用析构函数，则将对象中的资源和所占用的内存一并释放掉。



#### 拷贝构造函数

Copy Constructor

- 创建对象时，用一同类对象对其初始化
- 自动调用

- 默认拷贝构造函数

  - 逐个成员初始化
  - 对于对象成员，该定义是递归的（对于成员对象也会调用）

- 何时需要copy constructor?

  当对象的成员数据类型不是简单的数据类型时（比如数组，对象等）需要拷贝构造函数（即需要deep copy）

  否则会造成`悬挂指针`。

```cpp
// 1.赋值
A a;
A b = a;

// 2.传参
f(A a){
    //...
}
A b;
f(b);

// 3.返回值
A f(){
    A a;
    return a;
}
f();

// copy constructor
A(const A& a); // const 和 & 都不能少。（如果不写&，按照上面第二条，传参要进行拷贝构造...就会造成递归调用了）
```



> 2022.04.13

#### 移动构造函数*

由于某些情况下（如下或者swap对象），如果只有拷贝构造函数的话，会使得效率非常低下。

于是引入`移动构造函数`。

```cpp
string generate(){
    return string("test");
}

string S = generate();
```

> **左值和右值**
>
> 左值(lvalue)：可以指代一个地址空间，并且可以通过&来拿到这个地址的变量
>
> 右值(rvalue)：不是左值的值

##### 右值引用

右值引用(X&&)对应于左值引用，即常规引用(X&)。其引入可以解决移动语义(move semantics)的问题，避免在对象之间赋值时大量的构造、复制和销毁。

详见：C++ Rvalue References Expain

> 五三原则：
>
> 五个方法（拷贝构造、拷贝赋值、移动构造、移动赋值、析构函数）或三个方法（拷贝构造、移动构造、析构函数）其中只要有一个自定义了，编译器就不会提供这些相应的默认函数



#### 动态内存

- 内存类型

  - Stack
  - Heap

- C

  - malloc：不调用构造函数
  - free：不调用析构函数

- C++

  - 可重载

  - new

    new primitive:（无构造函数）

    - int *p = new int;

    new class-type:

    - 在程序的heap里申请一块大小为sizeof(A)的内存
    - 调用A的默认构造函数对该空间上的对象初始化
    - 返回创建的对象的地址并赋值给p（malloc返回的是 void *）

  - delete

    - 调用p所指向的对象的析构函数
    - 释放对象空间

    ```cpp
    delete p;
    p = NULL; // 防止很多常见的内存问题，防止意外使用p 或者 double free
    
    void * p;
    delete p; // 只会释放内存而不会调用析构函数，因为delete不知道p的类型，无法调用析构函数。
    // C++中类型是非常重要的！！
    ```

> 堆上的对象是无名的，唯一获得的方式是通过指针！
>
> 指针也是一种数据类型，且大小都一致

##### 动态对象数组

```cpp
A *p;
p = new A[100]; // new[]的时候会多分配4个字节，存储有多个元素。该4个字节在p地址的前面
// 不能显式初始化，相应的类必须有默认构造函数（老标准）
// （C++11）新标准下，使用统一初始化表(new int[5]{1,2,3,4,5})，可以不使用默认构造函数
delete []p; // 获取该块地址空间有多少个元素，然后依次调用这些元素的析构函数，并且释放内存
delete p; // 导致 1.存在内存空间未被释放 2.造成段错误。正确的开始释放地址应该是p-4Bytes。现在从中间开始释放，会造成段错误，程序会崩溃。

// 这段代码没问题！
// 不需要调用析构函数，不会分配前面那4个字节
// delete p 直接将这整块内存删除
int *p;
p = new int[100];
delete p; // delete []p 也可以
```

##### 动态2D数组

```cpp
const int ROWS = 3;
const int COLUMNS = 4;

// ------------------- new 2D array ----------------------------
char ** 2Darray;

2Darray = new char * [ROWS];

for (int i = 0; i < ROWS; i++){
    2Darray[i] = new char [COLUMNS];
}

// ------------------- delete 2D array ----------------------------
for (int i = 0; i < ROWS; i++){
    delete[] 2Darray[i];
    2Darray[i] = NULL;
}
delete[] 2Darray;
2Darray = NULL;

// 上面的定义存在着内存空间的浪费，比如2Darray[i]的三个指针。于是一般采用下面的方式
// ------------- use 1D array to substitute 2D array --------------
int *p = new int[12];
//p[i][j] => p[4*i+j]; // 之后可以重载[][]来实现
```



#### Const成员

- const 成员变量

  const成员变量只是在该实例对象中保持const，不同的实例对象可以是不同的

  ```cpp
  class A{
      const int x;
    public:
      A(int c):x(c){} // 初始化放在构造函数的成员初始化表中进行
  }
  ```

- const 成员函数

  ```cpp
  // ------------------ A.h ---------------------
  class A{
      int x, y;
    public:
      A(int x1, int y1);
      void f();
      void show() const;
  }
  // ------------------ A.cpp ---------------------
  void A::f(){
      x = 1; y = 1; // 如何通过词法句法来检查是否是const？
  }
  
  void A::show() const{
      cout << x << y;
  }
  
  // ------------------ B.cpp ---------------------
  int main(){
      const A a(0,0);
      
      a.f(); // X 报错 const 对象不能调用非const方法
      a.show(); // 对
  }
  ```

- static const 变量

  必须在声明处立刻初始化

  ```cpp
  class A{
      static const x = 100;
  }
  ```

  