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

    