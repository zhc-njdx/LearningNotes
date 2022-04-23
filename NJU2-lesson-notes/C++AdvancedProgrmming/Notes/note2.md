### 指针数组

main函数

`int main(int argc, char *argv[], char *env[])`



可变参数函数

`printf(char *s, ...)`

```cpp
#include <iostream>
#include <stdarg.h>
using namespace std;

void myPrintf(char *s, ...){
    va_list marker;
    va_start(marker,s);

    int i = 0; char c;
    while ((c=s[i]) != '\0'){
        if (c != '$') cout << c;
        else{
            i++;
            switch (c = s[i]) {
                case 'f':cout << va_arg(marker,double);break;
                case 'd':cout << va_arg(marker,int);break;
                case 'c':cout << va_arg(marker, char);break;
            }
        }
        i++;
    }
    cout << endl;

    va_end(marker);
}
```



如果不按照约定（即s中需要3个参数，但是实际只传进来1个），就会改写不该写的地址内容，造成**格式化串攻击**。



### 函数指针

- 写框架

降低耦合度

利用函数指针组织改善

利用define，结合IDE

```cpp
/**
* 运算的框架
*/
enum OPRAND_TYPE{END=-1,ADD,MINUS};

struct Task{
    int 		op1;
    OPRAND_TYPE op;
    int 		op2;
};

int add(int a, int b){return a + b;}
int minus(int a, int b){return a - b;}
// 此处就可以加上其他需要的运算函数
// 只需修改表和枚举值就可以

typedef int (*FP) (int,int);

// table driven
FP op[2] = {add, minus};

void executeTask(const Task task){
    op[task.op](task.op1, task.op2);
}

OPRAND_TYPE getTask(Task & task){
    //...
}

void main(){
    Task task;
    while(getTask(task) != END){
        executeTask(task);
    }
}
```

- 泛型

以冒泡排序为例

```cpp
/**
* 冒泡排序的泛型
* 每次只需要重新定义compare函数即可
*/ 

void MySort(void *base, unsigned width, unsigned num, int (*compare)(const void* elem1, const void* elem2)){
    char *A = (char *)base;
    char *tmp = (char *)malloc(width);
    for(unsigned i = 1; i < num; i++){
        for(unsigned j = 0; j < num - i; j++){
            if(compare(A+j*width,A+(j+1)*width)>0){
                memcpy(tmp,A+j*width,width);
                memcpy(A+j*width,A+(j+1)*width,width);
                memcpy(A+(j+1)*width,tmp,width);
            }
        }
    }
    free(tmp);
}
```

计算一元函数在某区间上的定积分

```cpp
//...
```



### 多级指针

基类型为指针类型

交换两个字符串

```cpp
void swap(char **p1, char **p2){
    char *tmp = *p1;
    *p1 = *p2;
    *p2 = *tmp;
}

void main(){
    
}

// 不能使用上述swap
// 因为p1和p2被创建下来后是固定的，不能被移动的
// 所以其交换只能使用 strcpy
char p1[] = "1234";
char p2[] = "abcd";

```

### 引用

> 为一块已有的内存空间取一个别名

- 引用变量和被引用变量，必须是同类型
- 引用变量定义中的&不是取地址操作符
- 定义引用变量时，必须初始化

函数返回值类型为引用（操作符重载-->体现为左值）

**不能返回局部变量**

```cpp
// 使得x[j]所对应的地址空间有了一个别名 max2
// 可以做赋值操作（作为左值）
int &max2(int x[], int num){
    int i,j;
    j = 0;
    for(i = 1; i < num; i++){
        if(x[i] > x[j]) j = i;
    }
    return x[j];
}
```
