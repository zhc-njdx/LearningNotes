### 函数模板

> 泛型编程

1、使用

```cpp
template <typename T>
T function(T a, T b){
    return a > b ? a : b;
}
```

> 注意：模板不创建任何函数，只是告诉编译器如何定义函数。编译器会检查所使用的参数类型，生成相应的函数。

2、模板亦可重载

> 但是还是要遵守重载(override)的规则：函数特征标必须不同

```cpp
template <typename T>
void swap(T &a, T &b); // 模板那特征标为 (T &, T &)

template <typename T>
void swap(T *a, T *b, int n); // 模板特征标为 (T [], T [], int)
```

3、模板的局限性

由于模板的通用性，不可避免也存在模糊性。

基于某些特征数据类型的操作不能出现在模板中。

4、**显式具体化**

在模板函数中提供某个类型的具体化函数定义——显式具体化

> 之所以要提供显式具体化，是因为按照一般逻辑，应该是重载函数，但是由于函数原型不发生改变，只是实现不一样的逻辑，所以无法重载。

```cpp
template <typename T>
void swap(T &a, T &b){
    // ...
}

template <> void swap<someType> (someTpye &a, someType &b){
    // ...
}
```

> 编译器在选择函数原型时，非模板函数>显式具体化>模板函数

5、实例化

模板函数是不生成函数定义的。编译器会使用模板为指定的类型生成函数定义，称为隐式实例化。

C++中也存在**显式实例化**，即直接命令编译器创建特定的实例

```cpp
template void swap<int> (int, int);
```

> 区别于显式具体化，显式实例化是让编译器直接根据模板和数据类型生成一个函数定义；而显式具体化，是专门为特定的数据类型显式定义了区别于模板的函数定义。

6、





### 函数指针

1、函数地址

函数实际上也是存储在内存空间的一块数据，和其他数据一样也具有地址。直接使用函数名就可以获取函数的地址。

2、函数指针

每一个指针都必须明确所指向数据的类型，函数指针也不例外。函数的返回值和参数列表可以用来指定函数的类型，例如 函数 `int max(int a, int b)` 的函数，其指针类型为 `int (*fp)(int, int)`。

```cpp
int (* fp)(int, int);
int max(int a, int b);
fp = max; // fp指针指向max函数
```

> 借助typedef简化
>
> ```cpp
> typedef int (* fp)(int, int); // fp是一个类型
> fp p1 = max; // p1 执行max 函数
> ```

3、深入探究

`const double * (* fp) (const double *, int)`

- 函数指针数组

  ```cpp
  const double * (* fp[3]) (const double *, int);
  ```

- 指向函数指针数组的指针

  ```cpp
  const double * (*(* fp)[3]) (const double *, int); /
  ```

  