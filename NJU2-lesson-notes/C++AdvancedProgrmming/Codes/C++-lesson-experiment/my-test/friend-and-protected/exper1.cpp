/**
 * @file exper1.cpp
 * @author zhc
 * @brief 
 * 探究友元与受保护成员
 * 1、f()和g()都是B的友元函数，所以只能访问B的受保护成员，不能访问基类A的受保护成员
 * 2、友元函数是独立的，定义在外部，并不是类的成员函数，
 * 只是被赋予了访问类中protected和private成员的权限而已
 * 3、友元类的作用类似。
 * 4、友元函数或友元类，不能传递也不能继承。
 * @version 0.1
 * @date 2022-04-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
using namespace std;

class B; // 前项声明
// .\exper1.cpp:21:21: error: 'B' has not been declared
//     friend void a_g(B& b);

class C{
private:
    int z;
protected:
    int c_prot;    
    friend class A; // A是C的友元类，所以在A中可以访问C对象的protected和private成员
};

class A{
protected:
    int x;
    C c;
    friend void a_f(A& a);
    friend void a_g(B& b);
public:
    void a_h(){
        x = c.c_prot = c.z = 0;
    }
};

class B : public A{
    int y;
public:
    friend void f(B& b);
    friend void g(A& a);
    void h(A& a){
        x = 0; // 派生类能够访问基类的受保护成员
        // a.x = 0; 但不能访问基类对象的受保护成员
    }
};

void f(B& b){
    b.y = b.x = 0;
} 

void g(A& a){
    // a.x = 0; 错误，不能访问基类对象a的受保护成员
}

void a_f(A& a){
    a.x = 0;
}

void a_g(B& b){
    // b.x = b.y = 0; 错误，a_g不是B的友元函数，不能访问派生类对象b中的private成员变量
}


int main(){
}