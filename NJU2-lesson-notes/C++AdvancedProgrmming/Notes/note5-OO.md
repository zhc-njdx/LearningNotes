> 2022.04.27

- 虚函数限制

  - 类的成员函数才可以是虚函数

  - 静态成员函数不能是虚函数

  - 内联成员函数不能是虚函数

    > 因为内联函数在静态编译时就要确定时哪段代码

  - 构造函数不能是虚函数

    > 不会通过父类指针或引用来调用

  - 析构函数可以（往往）是虚函数

    ```cpp
    p = &b;
    delete p;
    // 派生类中的资源不同于基类，需要通过指针调用到正确的析构函数
    ```

- 后期绑定的实现

  ```cpp
  class A{
      int x, y;
    public:
      virtual f();
      virtual g();
      h();
  };
  class B : public A{
      int z;
    public:
      f();
      h();
  };
  A a;
  B b;
  A *p;
  
  // case 1
  p = &a;
  p->f();
  
  // case 2
  p = &b;
  p->f();
  
  // 和之前new数组对象存放元素个数一样
  // 对象指针所指向的内存空间的前面存放了一个指针，指向其虚函数表
  // (**((char *)p - 4))(p)
  // (char *)p - 4 指向存放指向虚函数表的指针的内存空间
  // *((char *)p - 4) 指向虚函数表的指针
  // **((char *)p - 4) 指向虚函数表的第一个函数
  // (p) this指针
  ```

  ![image-20220427181524990](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220427181524990.png)

  ```cpp
  class A{
    public:
      A(){f();}
      virtual void f();
      void g();
      // 非虚接口: 非虚函数也可以呈现出多态
      // 使一个函数内部部分呈现d
      // template method pattern
      void h(){f();g();} // void h(A* const this){this->f(); this->g();}
  };
  class B : public A{
    public:
      void f();
      void g();
  }
  
  B b;		// A::A(),A::f,B::B() 直到构造函数返回后，对象方可正常使用
  A *p = &b;
  p->f();		// B::f
  p->g();		// A::g // 普通成员函数，静态绑定
  p->h();		// A::h, B::f, A::g // 普通成员函数，静态绑定
  
  
  // ----------------- 另一个例子 --------------------
  class A{
    public:
      virtual void f();
      void g();
  };
  
  class B : public A{
    public:
      void f(){g();} // void f(B *const this){this->g();}
      void g();
  };
  
  B b;
  A *p = &b;
  p->f(); // B::f, B::g
  
  ```

- final, override

  ```cpp
  struct B{
      virtual void f1(int) const;
      virtual void f2();
      void f3();
      virtual void f5(int) final;
  };
  
  struct D : B{
      void f1(int) const override;	// 正确
      void f2(int) override;			// 错误: 函数形式要相同，包括参数和返回类型
      void f3() override;				// 错误: f3不是虚函数
      void f4() override;				// 错误: B中没有f4函数
      void f5(int);					// 错误: f5是final函数
  }
  ```

- 纯虚函数

  - 声明时在函数原型后面加上 <font color="red">=0</font> (Means "not there")
  - 往往只给出函数声明，不给出实现

  ```cpp
  class AbstractClass{
    public:
      virtual int f() = 0; // 告诉编译器在虚函数表中留一个位置，但是不放地址，放_pure_virtual_called。在派生类中实现了之后，在派生类的虚函数表中填上地址。
  }
  ```

- 抽象类

  - 至少包含一个纯虚函数
  - 不能用于创建对象（因为纯虚函数在虚函数表中没有地址）
  - 为派生类提供框架，派生类提供抽象基类的所有成员函数的实现。
  - **抽象类提供接口，派生类提供实现**
  - **抽象类不能以传值的方式调用，防止对象切片。**

  ```cpp
  class Figure{
    public:
      virtual void display() = 0;
  };
  
  class Rectangle{
    public:
      virtual void display(){
          // ...
      }
  };
  
  class Ellipse{
    public:
      virtual void display(){
          // ...
      }
  };
  
  class Line{
    public:
      virtual void display(){
      	// ...
      }
  };
  
  Figure *a[100];
  a[0] = new Rectangle();
  a[1] = new Ellipse();
  a[2] = new Line();
  // ...
  for (int i = 0; i < num_of_figures; i++){
      a[i]->display();
  }
  ```

  ```cpp
  // Abstract Factory Pattern
  
  ```

- 虚析构函数

  - 析构函数应当被声明为虚函数，以销毁多出来的资源
  - 派生类的析构函数应该只负责销毁派生类中多出来的资源

- 绝对不要重新定义继承而来的缺省参数值（无效）

  - 静态绑定

    将默认参数值静态绑定到函数上，继承之后连带默认参数也继承

  - 效率

    不用另外存储缺省参数

  ```cpp
  class A{
    public:
      virtual void f(int x = 0) = 0;
  };
  
  class B : public A{
    public:
      virtual void f(int x = 1){
          cout << x << endl;
      }
  };
  
  A *p_a;
  B b;
  p_a = &b;
  p_a->f(); // 输出0 => p_a->f(0)
  
  class C : public A{
      virtual void f(int x){
          cout << x << endl;
      }
  };
  
  A *p_a1;
  C c;
  p_a1 = &c;
  p_a1->f(); // 输出0 => p_a1->f(0)
  ```



> 复用接口 interface => type
>
> 复用实现 implementation
>
> 复用接口要优先于复用实现

- 纯虚函数

  只有函数接口会被继承

  - 子类必须继承函数接口
  - 必须提供实现代码

- 一般虚函数

  函数接口及缺省实现代码都会被继承

  - 子类必须继承函数接口

  - 可以继承缺省实现代码

- 非虚函数

  函数的接口和其实现代码都会被继承

  - 必须同时继承接口和实现代码

```cpp
class Shape{
  public:
    virtual void draw() const = 0;
    
    virtual void error(const string & msg);
    
    int objectID() const;
};
```



替换原则

- 确定 public inheritance 是真正意义的 is_a 关系
- 不要定义与继承而来的非虚成员函数同名的成员函数

```cpp
// 例子

// 错误
// 由于客户代码中已经存在大量的fly调用，对于Penguin类中重新定义的fly函数抛出异常，是预期之外的
// 会造成客户代码的错误、
// 不满足契约式设计
class Penguin : public Bird{
	virtual void fly(){ error("Penguin can't fly!");}
}
```

- 契约式设计

  Pre-condition：子类中的方法的前置条件必须比超类中被覆盖的方法的前置条件更加宽松或者一致（使得调用超类方法的位置也可以调用子类的方法）

  Post-condition：字类中的方法的后置条件必须比超类中被覆盖的方法的后置条件更加严格或者一致（保证方法调用之后客户代码是可以继续执行的）

```cpp

//--------------------------- version 1 -------------------------
class Rectangle{
  public:
    void setHeight(int);
    void setWidth(int);
    int width() const;
    int height() const;
};
// assert(width() == height())
class Square : public Rectangle {
  public:
    void setLength(int);
  private:
    void setHeight(int);
    void setWidth(int);
}

Square s;
Rectangle * r = & s;
r->setHeight(10); // 静态绑定，会调用基类的setHeight

//--------------------------- version 2 -------------------------
class Rectangle{
  public:
    virtual void setHeight(int);
    virtual void setWidth(int);
    int width() const;
    int height() const;
};
// assert(width() == height())
class Square : public Rectangle {
  public:
    void setLength(int);
  public:
    void setHeight(int);
    void setWidth(int);
}

// 当传入正方形时，函数中的assert不满足
void Widen(Rectangle & r, int w){
    int oldHeight = r.height();
    r.setWidth(r.width() + w);
    assert(oldHeight == r.height());
}

//--------------------------- version 3 -------------------------
class Rectangle{
  public:
    virtual void setHeight(int);
    virtual void setWidth(int);
    int width() const;
    int height() const;
};
// assert(width() == height())
class Square : public Rectangle {
  public:
    void setLength(int);
  private:
    void setHeight(int);
    void setWidth(int);
}

Rectangle *p = &s;
p->setHeight(100); // 仍可以调用。因为访问控制是静态绑定的，p是Rectangle类型的，setHeight是public的，所有编译通过。动态绑定只是去找到合适的函数版本
```

> 程序（语言）中的继承并不是只要满足逻辑上的继承就可以，而是要满足接口方法的一致性！

```cpp
// 定义与继承而来的非虚成员函数同名的成员函数而引发的问题
class B{
  public:
    void mf();
};

class D : public B{
  public:
    void mf();
};

D x;
B* pB = &x;
pB->mf(); // 调用 B::mf()
D* pD = &x;
pD->mf(); // 调用 D::mf()
```

- private Inheritance
  - Implemented-in-term-of
    - has-a
    - 需要使用Base Class中的protected成员，或重载virtual function
    - 不希望一个 Base Class 被 client 使用
  - 在设计层面无意义，只用于实现层面

> private inheritance 不能实现派生类向基类的类型转换

```cpp
class CHumanBeing{...};
class CStudent : private CHumanBeing{...};
void eat(const CHumanBeing& h){...}

CHumanBeing a; CStudent b;
eat(a);
eat(b); // Error
```

#### 多继承

- 定义

```cpp
class <派生类名> : [<继承方式>] <基类名1>,
				  [<继承方式>] <基类名2>, ...
{...}
```

- 继承方式
  - public, private, protected
- 继承方式及访问控制的规定同单继承
- 派生类拥有所有基类的所有成员

##### 初始化问题

- **基类的声明次序**决定：
  - 对基类构造函数/析构函数的调用次序
  - 对基类数据成员的存储安排

```cpp
class A{};
class B{};
class C: A, B; // 先初始化A，再初始化B
// class C : B, A; 先初始化B，再初始化A
```

##### 同名问题

> virtual inheritance

- <基类名>::<基类成员名>

- 采用虚基类

  ```cpp
  // 虚基类
  // 在B和C的类中存在一个指向A的指针，使得B和C共用一份A中的数据成员
  // 在新的派生类对象生成时才会调用A的构造函数
  class A;
  class B : virtual public A;
  class C : public virtual A;
  class D : B, C;
  ```

如果基类B和基类C中存在同名的虚函数，派生类重写该虚函数会覆盖B和C的虚函数

> 如何只覆盖其中一个基类的虚函数？



多继承中（继承n个基类）的派生类的内存空间中，有n个虚函数表指针，指向各自的虚函数表。



> 如果虚基类无法解决同名问题，尽量将继承数减少，改为组合关系。只继承“is-a”关系够强的


