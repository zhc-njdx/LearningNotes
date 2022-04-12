### OOP



OO是给程序员看的

编译器在编译时会为程序员增加很多语句和限制，例如构造函数中的初始化语句、访问访问限制

但是最终还是在底层运行的，最后运行的代码还是Strcuture-Programming



### OO十个问题

1、当类中未自主定义构造函数，compiler会提供默认构造函数，why? What does compiler do for an "Empty" class?

<font color="red">why?:完成对象的初始化</font>

<font color="red">what?:1、建立标识符，开辟内存空间，</font>

2、When构造函数、析构函数被定为private?友元、static成员的使用，When?



3、Why引入成员初始化表？Why初始化表执行次序只与类数据成员的定义次序相关？

<font color="red">const 成员 reference 成员 对象成员效率高 数据成员太多时不适用</font>

4、Why引入Copy构造函数、=操作符重载？Why Compiler 定义的=操作符重载不够，需要自己定义？



5、What is Late Binding（多态，运行时绑定）？How C++ implement virtual？（虚函数）



6、When we use virtual ？



7、What does public 继承 和 non-public 继承 mean？



8、Why = () [] -> 不能作为全局函数重载？



9、When成员函数能返回&(引用)?



10、When and How to 重载 new、 delete？





析构函数声明为private：强制自主控制对象存储分配

需要再定义一个public的成员函数来delete

适用于占空间有限，而对象较大，这样就能避免对象声明在栈中



拷贝构造函数、

创建对象时，用一同类的对象对其初始化

```cpp
f(A a){...}
A f(){A a;...;return a;}

public:
	A(const A& a);
```

何时需要copy constructor?

通常来说，需要deep copy时。

