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