/**
 * @file exper1.cpp
 * @author zhc
 * @brief 
 * 探究虚函数的动态绑定和继承
 * 当将f()声明为虚函数时，p_a->f(); 会调用 B::f()
 * f()不是虚函数时， p_a->f(); 会调用 A::f()
 * 
 * @version 0.1
 * @date 2022-04-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
using namespace std;

class A{
    int a;
    public:
    A():a(0){}
    A(int x):a(x){}
    virtual void f(){
        cout << "a=" << a << endl;
    }
};

class B : public A{
    int b;
public:
    B():b(0){}
    B(int x):b(b){}
    B(int x, int y):b(x),A(y){}
    void f(){
        cout << "b=" << b << endl;
    }
};

int main(){
    A a(1);  // A::a = 1
    B b(2,3);// B::a = 3 B::b = 2 
    A *p_a = &b;
    p_a->f();
}