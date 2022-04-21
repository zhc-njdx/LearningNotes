### C++ reference 的理解



#### 1 认识

C++中引入了一种特殊的类型——引用类型，我们常称它为变量的别名。它既不同于普通变量，也不同于指针类型，它的引入让程序员不用通过指针（表面上）就可以直接操纵变量或者对象，好处之一就是作为函数的参数，使函数对变量的作用保留下来，最经典的就是swap函数了。

```cpp
void swap(int & a, int & b){
    int c = a;
    a = b;
    b = c;
}
```

#### 2 深入理解

那引用类型究竟是什么呢？它是如何实现的呢？

以下面的程序为例

```cpp
#include<iostream>
using namespace std;

int main(){
    int a = 0;
    int b = 1;
    int & c = a;
    c = b;
    cout << a << b << c;
}
```

经过g++编译并通过objdump反汇编得到如下汇编代码（只摘录了main）

```shell
0000000000000000 <main>:
   0:   55                      push   %rbp
   1:   48 89 e5                mov    %rsp,%rbp
   4:   48 83 ec 40             sub    $0x40,%rsp
   8:   e8 00 00 00 00          callq  d <main+0xd>
   d:   c7 45 ec 00 00 00 00    movl   $0x0,-0x14(%rbp) # int a = 0;
  14:   c7 45 fc 01 00 00 00    movl   $0x1,-0x4(%rbp) # int b = 1;
  1b:   48 8d 45 ec             lea    -0x14(%rbp),%rax 
  1f:   48 89 45 f0             mov    %rax,-0x10(%rbp) #1b 1f: int & c = a;
  23:   48 8b 45 f0             mov    -0x10(%rbp),%rax
  27:   8b 55 fc                mov    -0x4(%rbp),%edx
  2a:   89 10                   mov    %edx,(%rax) #27 2a: c = b;
  2c:   8b 45 ec                mov    -0x14(%rbp),%eax
  2f:   89 c2                   mov    %eax,%edx
  31:   48 8b 0d 00 00 00 00    mov    0x0(%rip),%rcx        # 38 <main+0x38>
  38:   e8 00 00 00 00          callq  3d <main+0x3d>
  3d:   48 89 c1                mov    %rax,%rcx
  40:   8b 45 fc                mov    -0x4(%rbp),%eax
  43:   89 c2                   mov    %eax,%edx
  45:   e8 00 00 00 00          callq  4a <main+0x4a>
  4a:   48 89 c1                mov    %rax,%rcx
  4d:   48 8b 45 f0             mov    -0x10(%rbp),%rax
  51:   8b 00                   mov    (%rax),%eax
  53:   89 c2                   mov    %eax,%edx
  55:   e8 00 00 00 00          callq  5a <main+0x5a>
  5a:   b8 00 00 00 00          mov    $0x0,%eax
  5f:   48 83 c4 40             add    $0x40,%rsp
  63:   5d                      pop    %rbp
  64:   c3                      retq
```

从汇编代码中我们很容易可以发现`int & c = a;`这条语句对应的是`lea    -0x14(%rbp),%rax`和`mov    %rax,-0x10(%rbp)`这两条指令。前一条指令的意思是将`%rbp-0x14`处的地址放到`%rax`中，后一条指令是将`%rax`中的内容放到`%rbp-0x10`中（因为c是main函数中的局部变量，需要放在栈中）。所以c的内容实际上是a的地址。

然后我们可以看到，`c = b;`这条语句对应的是`mov    -0x4(%rbp),%edx`和`mov    %edx,(%rax)`这两条指令，前一条指令是将b的值放在`%edx`寄存器中，后一条指令是将`%edx`中的值移到`%rax`的内容所指向的内存块中（就是`%rbp-0x14`，即a）。

所以，通过对这份代码的解读可以发现，引用本质上还是通过指针实现的。只是编译器帮助我们做了一些事情，使得我们的使用更加简单。

#### 3 总结

可以粗略地认为：引用变量 = 指针变量 + 编译器自动地解引用。

也正是因为有编译器的帮助，引用变量比指针更安全更容易使用，但是却没有指针那么强大。