#### 模板



- 模板

  - 源代码复用机制

    只是减少程序员的工作量，编译器会在编译时根据调用的情况自动生成对应的版本。

  - 参数化模块

    - 对程序模块（类、函数）加上类型参数
    - 对不同类型的数据施加相同的操作

  - 多态的一种形式

  - C++

    - 类属函数=》模板函数
    - 类属类=》模板类

- 模板函数（template function）

  - 同一函数对不同类型的数据完成相同的操作

  - 使用其他方式实现

    - 宏实现
      - `#define max(a, b) ((a)>(b)?(a):(b))`
      - 缺陷
        - 只能实现简单的功能
        - 没有类型检查
    - 函数重载
      - `int max(int, int);` 	`double max(double, double);`
      - 缺陷
        - 每种类型都需要定义，太多而且不可能定义完全
    - 函数指针
      - `void sort(void*,unsigned int, unsigned int, int (*cmp)(void*, void*));`
      - 缺陷
        - 复杂、可读性差...
    - 函数模板
      - <font color='red'>完全、清晰</font>

  - ```cpp
    template <typename T>
    void sort(T A[], unsigned int num);
    // 函数模板一般都和重载运算符一起使用
    // 重载 = copy-constructor > 等等
    
    // 函数模板可有多个类型参数
    template <typename T1, typename T2>
    
    // 可带普通参数
    template <typename T, int size>
    void f(T a){
        T temp[size];
        ...
    }
    f<int,10>(1); // 调用时需要显式实例化
    
    // 函数模板可配合函数重载一起使用，而且函数重载的匹配优先级更高
    ```

- 模板类（template class）

  - 类定义带有类型参数

    ```cpp
    template <typename T, int size>
    class stack{
        T buffer[size];
      public:
        void push(T x);
        T pop();
    };
    
    template <typename T, int size>
    void stack<T,size>::push(T x){} // 名称空间需要指明数据类型，因为不同数据类型对应不同的类，名称空间也是不一样的
    
    template <typename T, int size>
    T stack<T, size>::pop(){}
    
    stack<int, 100> st1; // 需要显式实例化
    ```

- 模板的实例化

  - 实例化：生成具体的函数/类

  - 函数模板的实例化

    - 隐式实现
    - 根据具体模板函数调用

  - 类模板的实例化

    - 创建对象时显式指定

  - 原则

    > 是否实例化模板的某个实例由使用点来决定；如果未使用到一个模板的某个实例，则编译系统不会生成相应实例的代码

  - **例子**

    > C++中模板的完整定义通常出现在头文件中
    >
    > 如果在模块A中要使用模块B中定义的某模板的实例，而在模块B中未使用这个实例，则模块A无法使用这个实例

    ```cpp
    // file1.cpp
    #include "file1.h"
    template <class T>
    void S<T>::f(){}
    
    template <class T>
    T max(T x, T y){
        return x > y ? x : y;
    }
    
    void main(){
        int a, b;
        max(a, b);
        s<int> x;
        x.f();
    }
    
    // file1.h
    template <class T>
    class S{
        T a;
      public:
        void f();
    };
    
    // file2.cpp
    #include "file1.h"
    extern double max(double,double);
    void sub(){
        max(1.1, 2.2);	// Error
        s<float> x;
        x.f();			// Error
    }
    
    // 原因:
    // 在编译阶段，double max(double,double);的声明、S的声明和定义以及f的声明都存在，所以不会报错
    // 但是在链接阶段，file1.cpp被链接进入，此时发现，并没有double max(double,double)的定义以及S<float>::f()的定义，所以就会报错
    // 是因为file1.cpp在编译阶段对file2.cpp不可见，所以导致max函数模板和f类成员函数模板无法生成对应版本。进入链接阶段，file1.cpp对file2.cpp可见，但此时模板已无法实例化，就导致两个函数缺少定义。
    ```

- 元编程（template programming）

  > 图灵完备

  ```cpp
  template<int N>
  class Fib{
    public:
      enum {value = Fib<N - 1>::value + Fib<N - 2>::value};
  };
  template<>
  class Fib<0>{
    public:
      enum{value = 1};
  };
  template<>
  class Fib<1>{
    public:
      enum{value = 1};
  };
  void main(){
      cout << Fib<8>::value << endl; // calculated at compile time
  }
  ```



#### 异常处理

- 错误

  - 语法错误
    - 编译错误
  - 逻辑错误
    - 测试

- 异常 Exception

  - 运行环境造成
    - 内存不足、文件操作失败等
  - 异常处理

- 异常处理

  - 特征
    - 可以预见
    - 无法避免
  - 作用
    - 提高程序鲁棒性(Robustness)
  - 常见处理方法
    - 函数参数
      - 返回值
      - 引用参数
    - 逐层返回
    - 缺陷
      - 程序结构不清晰

- C++异常处理

  - 一种专门、清晰描述异常处理过程的机制

  - 处理机制

    - `try{<语句序列>}`
      - 监控
      - 其后可接多个catch语句，用于捕获不同类型的异常
    - `throw <表达式>`
      - 抛掷异常对象
      - <font color='red'>throw出去的对象采用**拷贝构造**</font>
    - `catch(<类型>[<变量>]){<语句序列>}`
      - 捕获并处理
      - 类型：异常类型，匹配规则同函数重载
      - 变量：存储异常对象，可省

  - 异常处理的嵌套

    ```cpp
    f()
    {     try
         {     g();    }
         catch (int)
         { … }
        catch (char *)
        { … }
    }
    
    g()
    {    try
        {    h();  }
        catch (int)
        { …  }
    }
    
    h()
    {    …
      throw 1;   //由g捕获并处理
         …
      throw “abcd”; //由  f捕获并处理
    }
    // 如果所抛掷的异常对象在调用链上未被捕获，则由系统的abort处理
    ```

  - 定义异常类

    - 注意catch块排列顺序

  - 特例

    - 无参数throw

      - 将捕获到的异常对象重新抛掷出去

        `catch(int) {throw;}`

    - `catch(...)`

      - 默认异常处理

##### C++默认提供的成员函数

```cpp
class Empty{};
class Empty{
    //拷贝构造
    Empty();
    // 拷贝构造函数
    Empty(const Empty&);
    // 析构函数
    ~Empty();
    // 赋值操作符重载
    Empty& operator=(const Empty&);
    // 取地址操作符重载 两个版本
    // 第二个版本，防止通过指针修改对象内容
    Empty *operator &();
    const Empty* operator &() const;
};
```





##### 使用析构函数防止内存泄露

Java中有finally，但是C++中没有，因为认为RAII的风格要优于finally

```cpp
// 使用 smart pointer
template <class T>
class auto_ptr{
  public:
    auto_ptr(T *p = 0): ptr(p){}
    ~auto_ptr() {delete ptr;}
    T* operator->() const {return ptr;}
    T& operator*() const {return *ptr;}
  private:
    T* ptr;
}
```

使用智能指针类来将堆中的内存转换为栈中内存，这样就不用程序员手动释放内存，当离开作用于后，就会自动调用析构函数销毁指针多指向的内存空间



> 将申请的资源封装在一个对象
>
> 每一个资源的获取都是一个对象的初始化
>
> 使得资源的生命周期和对象的生命周期等同起来



```cpp
class WindowHandle{
  public:
    WindowHandle(WINDOW_HANDLE handler):w(handler){}
    ~WindowHandle(){destoryWindow(w);}
    // 重载了类型转换操作符
    operator WINDOW_HANDLE(){return w;}
  private:
    WINDOW_HANDLE w;
    WindowHandle(const WindowHandle&);
    WindowHandle& operator=(const WindowHandle&);
};
```

可以使用->操作符，重载了类型转换操作符，可以进行隐式类型转换。

> 重载类型转换操作符和重载->操作符的区别：
>
> 前者更优，将资源的管理所有权限定在自己手中。



- 操作符<<和>>重载

  - 全局友元函数重载

  - 对于自定义类的对象的IO

  - 支持链式调用，支持左值调用

  - ```cpp
    // 返回的是引用，需要支持链式调用
    // 第一个参数是ostream，所以需要只能全局函数实现
    // 第二个参数是对象，需要访问内部资源，所以需要声明称友元
    ostream& operator <<(ostream& out, Type& a){
        
    }
    
    
    class CPoint2D{
        double x, y;
      public:
        friend ostream& operator<<(ostream&, CPoint2D&);
        // Solution2
        virtual void display(ostream&);
    };
    ostream& operator<<(ostream& out, CPoint2D& a){
        out << a.x << "," << a.y << endl;
        return out;
    }
    
    class CPoint3D : public CPoint2D{
        double z;
    };
    
    // 问题：如何输出CPoint3D类型的对象？
    // 1、再重载一个<<函数，使得支持CPoint3D对象
    // 但是当出现CPoint2D的指针指向CPoint3D的对象时，由于是静态绑定所以还是会调用CPoint2D的重载<<函数。
    // 在框架式编程中，一般都是用基类指针或引用来指向派生类，在运行时再体现出具体类型
    // 2、所以可以考虑非虚接口
    // 在函数是全局函数时，又需要展现出多态性，可以考虑非虚接口，在全局函数中调用虚成员函数
    
    void CPoint2D::display(ostream& out){
        out << x << "," << y << endl;
    }
    
    ostream& operator<<(ostream& out, CPoint2D& a){
        a.display(out);// 虚函数，体现多态 
        return out;
    }
    
    void CPoint3D::display(ostream& out){
        CPoint2D::display(out); out << "," << z << endl;
    }
    ```

-  virtual constructor

  - virtual function
  - constructor

  ```cpp
  class NLComponent{...};
  class TextBlock:public NLComponent{...};
  class Graphic:public NLComponent{...};
  class NewsLetter{
    public:
      NewsLetter(istream& str){
          while(str) component.push_back(readComponent(str));
      }
      static NLComponent* readComponent(istream& str);
    private:
      list<NLComponent *> components;
  };
  
  // 在运行时创造出不同子类型的对象
  virtual NLComponent* clone() const = 0;
  
  virtual TextBlock* clone() const{
      return new TextBlock(*this);
  }
  
  virtual Graphic* clone() const{
      return new Graphic(*this);
  }
  
  NewsLetter(const NewsLetter& rhs){
      for(list<NLComponent *>::iterator it = rhs.components.begin; it != rhs.components.end(); ++it){
          components.push_back(???);
          // components.push_back((*it)->clone());
      }
  }
  ```

- 例子

```cpp
class BST{...};
class BalancedBST : public BST{...};

void printBSTArray(ostream& s, const BST array[], int numElements){
    for(int i = 0; i < numElements; i++) s << array[i];
}

BalancedBST bBSTArray[10];

printBSTArray(cout, bBSTArray, 10); 
// 错误。
// array[i]其实本质是指针: *(array + i * sizeof(BST))
// 由于还是静态绑定所以在调用时sizeof的对象依旧是BST而不是BalancedBST，而BalancedBST的对象大小肯定和BST不一样，所以寻址就会出现错误。
```

