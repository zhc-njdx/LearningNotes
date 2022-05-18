> Part3

### 多态



- 同一论域中的同一元素可有多种解释

- 提高语言灵活性

- 程序设计语言
  - 一名多用 					<font color='blue'>函数重载（虚函数的多态是动态的多态，而函数重载是静态多态）</font>
  - 类属                            template
  - OO程序设计



#### 操作符重载



- 函数重载
  - 名同，参数不同
  - 静态绑定

> 歧义控制:
>
> 1.顺序
>
> 2.更好匹配
>
> - 每个实参的匹配不比其他的差
>
> - 至少一个实参的匹配比其他更好
>
> 精确匹配
>
> 整型提升
>
> **标准转换中不存在更好，一视同仁的**
>
> <font color='red'>窄转换？</font>存在可以



- 操作符重载（<font color='red'>就是函数重载</font>）

  - 动机

    让复杂的、自定义的数据类型也能使用常见的操作符

  - 操作符语义

    - built_in 类型			       Complier
    - 自定义数据类型               程序员

  - 作用

    - 提高可读性
    - 提高可扩充性

```cpp
class Complex{
    double real, imag;
  public:
    Complex(){}
    Complex(double r, double i){real=r;img=i;}
    // version 1
    Complex operator + (Complex& x){ // operator + 就是一个函数名
        Complex temp;
        temp.real = real + x.real;
        temp.imag = imag + x.imag;
        return temp;
    }
    // version 2
    friend Complex operator + (Complex& x, Complex& y);
};

Complex operator + (Complex& x, Complex& y){ // 一定要有一个自定义类型
    Complex temp;
    temp.real = y.real + x.real;
    temp.imag = y.imag + x.imag;
    return temp;
}

Complex a, b, c;
c = a.operator +(b); // => c = a + b;
```



```cpp
enum Day{SUN, ... ,SAT};

void main(){
    Day d = SAT;
    ++d; // 重载++
    cout << d;
}

Day& operator++(Day& d){
    return d = (d == SAT) ? SUN : Day(d+1);
}

ostream& operator<<(ostream& o, Day& d){ // return ostream& 支持链式调用
    switch(d){
        // ...
    }
    return o;
}
```



- 可重载的操作符

  - .(成员访问运算符)、.*(成员指针访问运算符)、::(域运算符)、?:(条件运算符，存在跳转性质，防止程序控制流发生混乱)

    ```cpp
    // .*
    class A{
        int x;
      public:
        A(int i):x(i){}
        void f(){}
        void g(){}
    };
    
    void (A::*p_f)();
    
    p_f = &A::f;
    (a.*p_f)();
    ```

- 基本原则

  - 方式
    - 类成员函数
    - 带有类参数的全局函数
  - 遵循原有语法
    - 单目/双目
    - 优先级
    - 结合性



- 双目操作符重载

  - 类成员函数

    - 格式

      ```cpp
      <ret type> operator # (<arg>)
      ```

    - this    隐含

    - 使用

      ```cpp
      <class name> a, b;
      a # b;
      a.operator#(b);
      ```

  - 全局函数

    - 友元

      ```cpp
      friend <ret type> operator # (<arg1>,<arg2>)
      ```

    - 格式

      ```cpp
      <ret type> operator # (<arg1>,<arg2>)
      ```

    - 限制

      ```cpp
      // =(赋值运算符) ()(函数调用运算符) [](下标运算符) ->(箭头运算符) 不能作为全局函数重载
      // WHY?
      // ()	[]	->
      // 保留的调用顺序，第一个是对象，第二个是相关的参数
      // 全局函数无法保证调用的顺序
      ```

  - 全局函数作为补充

    ```cpp
    obj + 10;// 成员函数只支持这种情况
    10 + obj;// ? 成员函数不支持
    
    class CL{
        int count;
      public:
        friend CL operator+(int i, CL& a);
        friend CL operator+(CL& a, int i);
    }
    ```

    > 重载规则：
    >
    > 单目运算符使用成员函数
    >
    > 双目运算符使用友元函数
    >
    > 存在隐式转换的使用友元函数（成员函数只能精确匹配）
    >
    > 类型转换只能用成员函数
    >
    > 运算符的操作会修改对象的状态时重载为类的成员函数

- 永远不要重载 && 和 ||

  > 短路

  ```cpp
  char *p;
  if((p != 0) && (strlen(p) > 10)) ...
  
  // 但是重载之后就是函数调用， && 和 || 两边的表达式都会执行，不存在短路规则
  ```



```cpp
class Rational{
  public:
    Rational(int, int);
    const Ration& operator*(const Rational& r) const;
  private:
    int n, d;
};

// ----------------- operator * 函数体 ----------------------
// --- version 1 --- 一般 + - * / 都采用这种
return Rational(n*r.n, d*r.d);
// 存在对象拷贝
// 返回值优化，能够避免对象拷贝
// --- version 2 ---
Rational * result = new Rational(n*r.n, d*r.d);
return *result;
// 对于 w = x * y * z 只能看到第二次new的result，而没有第一次new的result，会造成内存泄露
// --- version 3 ---
static Rational result;
result.n = n*r.n; result.d = d*r.d; return result;
// if((a*b) == (c*d)) 同时需要两个结果就不够用了
```



- 单目操作符的重载

  - 类成员函数

    - this     隐含

    - 格式

      ```cpp
      <ret type> operator # ()
      ```

  - 全局函数

    ```cpp
    <ret type> operator # (<arg>)
    ```

  - `a++` vs `++a`

    - prefix ++ 左值
    - postfix ++ 右值

    ```cpp
    class Counter{
        int value;
      public:
        Counter(){value = 0;}
        Counter& operator ++(){ // ++a
            value++;
            return *this;
        }
        Counter operator ++(int){ // a++ 	int (dummy argument) 哑元参数，区分函数签名
            Counter temp = *this;
            value++;
            return temp;
        }
    }
    ```




#### 特殊操作符重载

- **=**

  - 默认赋值操作符重载函数

    - 逐个成员赋值
    - 对含有对象成员的类，该定义是递归的

  - 赋值操作符重载不能被继承

    Why？派生出来的类存在基类中没有的资源，继承来的赋值操作符不能对额外的资源进行赋值

  - ```cpp
    // 返回值是什么？
    // 应该返回该类型的引用，支持链式赋值
    // (a = b).f() 返回值前不能加const，返回值有可能被改变 f()不一定是常成员函数
    <Type>& operator=(<Type>& ){
        //...
        return *this;
    }
    ```

  - ```cpp
    class A{
        int x, y;
        char* p;
      public:
        A(){}
        ~A(){}
        // 区别于拷贝构造函数：此时对象已经创建，已经分配了内存
        // 而拷贝构造函数中对象并未创建
        A& operator=(A& a){
            x = a.x; y = a.y;
            delete[] p; // 先把分配的空间释放
            // 有可能出现异常，空间不够，导致该对象不完整
            // 可以先将p保存下来，然后对p赋值，最后再delete p
            p = new char[strlen(a.p)+1];
            strcpy(p, a.p);
            return *this;
        }
    }
    
    A a1, b;
    a1 = b; // 调用赋值操作符重载，a1已创建
    
    A a2 = b; // 调用拷贝构造函数，a2此时并未创建，可以写成 A a2(b)
    ```

  - 避免自我赋值

    ```cpp
    // Identity test	证同测试
    // Content	
    // Same memory location	是否是相同地址，但是存在不同对象但是其中的内容相同的，例如有相同的指针
    // Object identifier	
    
    // 先创建后删除
    // 也可以保证自我赋值时的正确性
    A& operator=(A& a){
        x = a.x; y = a.y;
        char *oldp_lhs = p; // 赋值失败时可以回滚
        char *oldp_rhs = a.p; // 避免自我赋值时，失去对原来那块地址空间的引用
        p = new char[strlen(oldp_rhs)+1];
        strcpy(p, oldp_rhs);
        delete[] oldp;
        return *this;
    }
    ```

- **[]**(下标操作符)

  - ```cpp
    class string{
        char *p;
      public:
        string(){}
        // ------- version1 --------
        char& operator[](int i) const{ // 可以声明为const成员函数，因为没有更改 p
            return p[i];
        }
        // ------- version2 --------
        // 参数是：string* const this, int i
        char& operator[](int i){ return p[i]; }
        // 参数是：const string* const this, int i
        const char operator[](int i) const { return p[i]; }
    };
    
    string s("aacd"); s[2] = 'b'; // 针对非const string对象，[]应该返回 char& 能更改，能打印
    const string cs("const"); cout << cs[0]; cs[0]='D'; // 针对const string对象，[]应该返回 const char 不能更改，只能打印
    ```

  - 多维数组

    ```cpp
    // wrapper
    // 用wrapper类来封装!!!
    class Array2D{
      public:
        class Array1D(int *p){
          public:
            // 加上explicit可以避免隐式类型转换
            Array1D(int *p){this->p = p;}
            int& operator[](int i){return p[i];}
            const int operator[](int i) const {return p[i];}
          private:
            int *p;
        };
        Array2D(int n1, int n2){
            p = new int[n1*n2];
            num1 = n1;
            num2 = n2;
        }
        virtual ~Array2D(){delete[] p;}
        // 存在隐式类型转换
        Array1D operator[](int i){return p + i * num2;}
        const Array1D operator[](int i) const {return p + i * num2;}
      private:
        int *p;
        int num1, num2;
    };
    ```

- **()**(函数调用操作符、类型转换操作符)

  - 函数调用操作符

    ```cpp
    class Func{
        double para;
        int lowerBound, upperBound;
      public:
        double operator()(double, int, int);
    };
    
    Func f; // 函数对象，让对象像函数一样去使用
    f(2.4,0,8);
    ```

  - 类型转换操作符

    - 基本数据类型
    - 自定义类

    ```cpp
    // 减少混合运算中需要定义的操作符重载函数的数量
    class Rational{
      public:
        Rational(){}
        // 没有参数和返回类型，返回类型由函数名指定
        operator double(){return (double)n/d;}
      private:
        int n, d;
    };
    
    Rational r(1,2);
    double x = r; x = x + r; // 由于类型转换操作符的重载，可以不必重载+、*d
    
    //
    ostream f("abc.txt");
    if (f) ... // 存在类型转换操作符的重载
    ```

    