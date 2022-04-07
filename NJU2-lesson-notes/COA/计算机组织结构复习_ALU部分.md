## 一、计算机系统概述

### 1、什么是计算机

#### 1）计算机是指“通用电子数字计算机”

> 通用：不是一种专用设备
>
> - 所有计算机在给予足够时间和容量存储器的条件下，都可以完成同样的计算
> - 当希望完成新的计算时，不需要对计算机重新设计
>
> 电子（非机械）：采用电子元器件
>
> 数字（非模拟）：信息采用数字化的形式表示

#### 2）计算机系统

硬件：处理器，存储器，外部设备，.......

软件：程序，文档，.......

### 2、组织与结构

- #### 组织

> 对编程人员不可见（透明）

操作单元及其相互连接

包括：控制信号，存储技术，......

例如：实现乘法是通过硬件单元还是重复加法？（底层实现，编程人员不知道）

- #### 结构

> 对编程人员可见

直接影响程序逻辑执行的属性

包括：指令集，表示数据类型的位数，......

例如：是否有乘法指令？

### 3、计算机简史

#### 1）第一代：真空管

- ##### ENIAC

第一台通用电子计算机，十进制，手动编程

- ##### ABC

第一台电子计算机，不可编程

- ##### EDVAC（==冯·诺依曼结构==）

##### **==冯诺依曼结构==**

![image-20220107151920225](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220107151920225.png)

又称“普林斯顿结构”

三个基本原则：

- ###### 二进制

- ###### 存储程序

- ###### 5个组成部分

​			主存储器：地址和存储的内容

​			算术逻辑单元/处理单元：执行信息的实际处理

​			程序控制单元/控制单元：指挥信息的处理

​			输入设备：将信息送入计算机中

​			输出设备：将处理结果以某种形式显示在计算机外

![image-20220105083619534](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105083619534.png)

#### 2）第二代：晶体管

#### 3）第三代及后续几代：集成电路

### 4、摩尔定律

#### 内容

> 单芯片上所能包含的晶体管数量每年翻一番（1965-1969）/1970年起减慢为每18个月翻一番

#### 影响

- 更小的尺寸带来更多灵活性和可能性
- 由于单个芯片的成本几乎不变，计算机逻辑电路和存储电路的成本显著下降
- 减少了对电能消耗和冷却的要求
- 集成电路上的内部连接比焊接更可靠，芯片间的连接更少

### 5、计算机发展：变与不变

#### 基本功能

![image-20220105084645646](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105084645646.png)

![image-20220105084656048](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105084656048.png)

#### 运算速度

![image-20220105084714738](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105084714738.png)

### 6、==计算机性能==

#### 性能评价标准

- CPU：速度
- 存储器：速度、容量
- I/O：速度、容量
- ......

> <font color='red'>计算机设计的主要目的：提高CPU性能</font>

#### CPU的性能

##### 系统时钟

###### 时钟频率/时钟速度（Hz）

计算机在单位时间内执行最基本操作的次数

###### 时钟周期/周期时间（s）

执行每次最基本操作的时间

- 时钟滴答：CPU中用于同步执行最基本操作的单个电子脉冲
- 因此，周期时间即为两个电子脉冲之间的时间

##### 指令执行

处理器由时钟驱动，时钟具有固定的频率f，或等价为固定的时钟周期t

如果用CPI~i~来表示指定类型指令i所需要的周期数，用I~i~表示在某一给定程序中所执行的i类指令的条数

###### CPI计算

$$
CPI=\frac{\sum_{i=1}^{n}(CPI_{i}\times I_{i})}{I_{c}}
\\ I_{c}=\sum_{i=1}^{n}I_{i}
$$

###### 给定程序的处理时间

$$
T=I_{c} \times CPI \times t
\\ T=I_{c}\times [p+(m\times k)]\times t
$$

![image-20220105090509398](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105090509398.png)

###### 每秒百万条指令（MIPS）

$$
MIPS=\frac{I_{c}}{T\times 10^{6}}=\frac{f}{CPI\times 10^{6}}
$$

###### 每秒百万条浮点数操作（MFLOPS）

$$
MFLOPS=\frac{N_{floating-point-op}}{T\times 10^{6}}
$$

#### 基准程序

使用一系列基准程序来测量系统的性能

- 算数平均值：$R_{A}=\frac{1}{m}\sum_{i=1}^{m}R_{i}$
- 调和平均值：$R_{H}=\frac{m}{\sum_{i=1}^{m}\frac{1}{R_{i}}}$

### 7、相关习题

![image-20220105093027018](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105093027018.png)

![image-20220105093051165](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105093051165.png)

## 二、计算机的顶层视图

### 1、计算的不同视图

![image-20220105093956088](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105093956088.png)

![image-20220105094002373](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105094002373.png)

### 2、计算机顶层结构

![image-20220105094518774](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105094518774.png)

![image-20220105094314827](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105094314827.png)

### 3、计算机的工作原理

- 指令和数据存储在单个读写存储器中
- 主存中的内容按位置访问，无需考虑其中包含的类型（不管是数据还是指令都一样访问）
- CPU从一条指令到下一条指令以顺序的方式执行（除非明确修改）
- I/O模块与CPU、主存交换计算机系统外部的数据

### 4、计算机体系结构遇到的问题及解决方案

#### CPU

- CPU从一条指令到下一条指令以顺序的方式执行（除非明确修改）
- 指令和数据存储在单个读写存储器中
- 主存中的内容按位置访问，无需考虑其中包含的类型（不管是数据还是指令都一样访问）

##### 问题1：CPU的频率不能无限提高

- 理论限制

  mos管开关、脉冲通过门电路需要时间

  为了信号同步，每个脉冲信号需要持续一定的时间

  ......

- 制造限制

  芯片面积越来越大，导致连线延迟越来越大，需要保证信号在设计指定时钟周期内从芯片的一角到达另一角

  频率越高（即mos管的开关频率也越高）会导致开关损耗也越高，cpu会费电和散热高

##### 解决1：改进CPU结构

![image-20220105100051274](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105100051274.png)

##### 问题2、内存墙的存在

主存和CPU之间传输数据的速度跟不上CPU的速度

![image-20220105100154535](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105100154535.png)

##### 解决2：采用高速缓存（Cache）

添加一级或多级缓存以减少存储器访问频率并提高数据传输速率

增大总线的数据宽度，来增加每次所能取出的位数

...

![image-20220105100347975](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105100347975.png)

##### 问题3：CPU等待I/O传输数据

CPU在等待I/O设备时保持空闲

##### 解决3：采用中断机制

<font color='red'>中断</font>：其他模块（例如I/O）可以正常中断处理顺序的机制

![image-20220105100612647](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105100612647.png)

中断检测：将中断周期加入指令周期

![image-20220105100707359](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105100707359.png)

![image-20220105100742148](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105100742148.png)

#### 存储器

- 指令和数据存储在单个读写存储器中
- 主存中的内容按位置访问，无需考虑其中包含的类型

##### 问题4：兼容存储容量、速度和成本

约束

- 容量：越大越好
- 速度：跟上存储器
- 成本：相对于其他组件合理

约束之间的关系：

更短的访问时间，更高的每比特成本

##### 解决4：层次式存储结构

需求

- 大容量数据存储
- 高速性能

解决方案

使用存储器层次结构而不是依赖单个存储器结构

![image-20220105101336872](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105101336872.png)

#### I/O

与CPU和内存交换从外部来源收集的数据

##### 问题5：I/O设备传输速率差异大

I/O性能跟不上CPU速度的提升

![image-20220105101603943](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105101603943.png)

##### 解决5：采用缓冲区和改进I/O操作技术

- 设立缓冲区
- 新的接口技术
- 不同的I/O操作技术

![image-20220105101730791](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105101730791.png)

#### 总线

总线是连接两个或多个设备的通信通路

##### 问题6：计算机部件互连复杂

互连方案

![image-20220105103050266](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105103050266.png)

![image-20220105103115831](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105103115831.png)

<font color='red'>共享传输介质，简化互连布局和处理器控制</font>

##### 解决6：采用总线

数据传输类型：

- 控制线：控制 数据线和地址线的访问和使用
- 地址线：指定数据总线和地址I/O端口上数据的来源或去向
- 数据线：在系统模块之间传送数据

![image-20220105103335526](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105103335526.png)

## 三、数据的机器级表示

### 1、信息的二进制编码

在冯诺依曼结构中，所有信息（代码和数据）都采用二进制编码

- <font color='red'>编码</font>：用少量简单的基本符号对复杂多样的信息进行一定规律的组合

- 采用二进制的原因

  多种物理器件可以表示两种稳定的状态，用于表示0和1

  二进制编码和运算规则简单

  1和0可以对应逻辑运算中的真和假

- K位二进制编码至多可以表示2^k^个不同的值

![image-20220105104358139](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105104358139.png)

### 2、整数的二进制表示

无符号整数：原码

有符号整数：原码、反码、补码、移码

- 原码、反码、移码在进行加法运算时都会造成不必要的硬件需求，因此目前计算机中普遍使用补码
- 二进制补码的运算
- 二进制-十进制的转换

### 3、补码表示

#### 1）优势

无论是同号还是异号都有可以直接相加

#### 2）表示

相对于原码，补码的 000....000 ~ 011....111 所表示的值没有改变

但是 100....000 ~ 111....111 所表示的值从原来的  2^k-1^~2^k^-1  变为  -2^k-1^~-1

即由原码的值减去2^k^得到

#### 3）真值

$$
[X]_{C}=X_{n}X_{n-1}...X_{2}X_{1}
\\ X=-X_{n}\times 2^{n-1}+...+X_{2}\times 2^{1}+X_{1}\times 2^{0}
$$

#### 4）值的范围

$$
-2^{n-1}\le X \le 2^{n-1}-1
$$

### 3、其他类型编码

#### 1）原码

>直观
>
>0不唯一、加法复杂
>
>浮点数的尾数由定点原码小数表示

#### 2）反码

> 原码取反
>
> 0不唯一
>
> 很少使用

#### 3）移码

>用于浮点数的阶码表示，简化对阶操作
>
>$[E]_{移}=2^{n-1}+E$
>
>1、$E的范围:-2^{n-1} \le E \le 2^{n-1}-1$
>
>2、移码为0的真值为$-2^{n-1}$。即$[-2^{n-1}]_{移}=000...00$
>
>3、0的移码是唯一的。即$[+0]_{移}=[-0]_{移}=2^{n-1}=100...00$
>
>4、如果将移码的第一位看成符号位，那么同一个真值的移码和补码仅符号位不同

> ==定点小数==的表示
>
> $X_{T}=\pm 0.X_{n-1}'X_{n-2}'...X_{1}'X_{0}'$

### 4、浮点数的二进制表示

采用科学计数法
$$
\pm S(尾数/有效值) \times B(底/基)^{E(阶码/指数)}
$$

### 5、<font color='red'>**IEEE 754表示法**</font>

> 1位符号+8位阶码+23位尾数=32位
>
> 1位符号+11位阶码+52位尾数=64位

其中尾数带一个隐藏位；阶码采用移码，偏置常数为$2^{n-1}-1$

> 尾数可表示的尾数多一位，使浮点数的精度更高
>
> 指数可表示范围更大，因而使浮点数范围更大

#### 1）规格化数

$$
\pm 1.bbb...b \times 2^{e}
$$

特点：

- 尾数的隐藏位为1
- 阶码 0 < e < 255
- 范围：$2^{-126}\sim(2-2^{-23})\times2^{127}$

#### 2）非规格化数

$$
\pm0.bbb...b\times 2^{e}
$$

特点：

- 尾数隐藏位为0
- 阶码为 e = 0 即全0
- 范围：$0 \sim (1-2^{-23})\times2^{-126}$

#### 3）特殊其他数

- $0$

除符号位，全为0

- $\infty/-\infty$

阶码全为1，尾数全为0

- $NaN$

阶码全为1，尾数不全为0

### 6、二进制编码的十进制数表示

##### **自然BCD码（NBCD，8421码）**

- 0-9：0000-1001
- 符号：正（1100）/负（1101）

### 7、相关习题

![image-20220105155157197](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105155157197.png)

![image-20220105155537201](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105155537201.png)

![image-20220105155602338](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105155602338.png)

![image-20220105155215147](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105155215147.png)

![image-20220105155643198](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105155643198.png)

![image-20220105155251237](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105155251237.png)

> True；True
>
> 第一个表达式将i强制转换为float类型，和最开始给f赋值是一样的结果。
>
> 第二个表达式由于i强制转换为double类型不会发生精度损失，值不变，但强制转换为float的时候损失了精度，和f一样。

![image-20220105155921989](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105155921989.png)

![image-20220105160142411](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105160142411.png)

![image-20220105160222034](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105160222034.png)

![image-20220105160239346](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105160239346.png)

![image-20220105160338997](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105160338997.png)

## 四、数据校验码

### 1、差错

数据在计算机内部进行计算、存取和传送的过程中，由于元器件故障或噪音干扰等原因，会出现差错

以存储为例

- 硬故障：永久性的物理障碍，以至于受影响的存储单元不能可靠地存储数据，成为固定的“1”或“0”障碍，或者在0和1之间不稳定地跳变。由恶劣环境、制造缺陷和旧损引起
- 软故障：随机非破坏性事件，它改变了某个或某些存储单元地内容，但没有损坏机器。由电源问题或$\alpha$例子引起

解决方案

- 从计算机硬件可靠性入手，在电路、电源、布线等方面采取必要措施，提高计算机地抗干扰能力
- 采取数据校验和校正措施，自动发现并纠正错误

### 2、纠错

#### 1）基本思想

存储额外的信息以进行检错和校正

#### 2）处理过程

- 数据输入：使用函数f在M位数据D上生成K位校验码C
- 数据输出：使用函数f在M位数据D'上生成新的K位代码C''，并和取出的K位代码C'进行比较
  - 没有检测到差错：使用数据D'
  - 检测到差错且可以校正：校正数据D'来生成数据D''，并用数据D''
  - 检测到差错但无法校正：报告

### 3、奇偶校验码

#### 1）基本思想

增加一位校验码来表示数据中1的数量是奇数还是偶数

#### 2）处理过程

假设数据D=D~M~...D~2~D~1~

数据输入

- 奇校验：$C=D_{M}\oplus...\oplus D_{2}\oplus D_{1}\oplus 1$
- 偶校验：$C=D_{M}\oplus...\oplus D_{2}\oplus D_{1}$

数据输出

- 奇校验：$C''=D'_{M}\oplus...\oplus D'_{2}\oplus D'_{1} \oplus1$
- 偶校验：$C''=D'_{M}\oplus...\oplus D'_{2}\oplus D'_{1}$

检错

- $S=C''\oplus C'$

- S=0：正确/数据中出错的位数为偶数
- S=1：数据中出错的位数为奇数

优点：代价低

缺点：不能发现出错位数为偶数的情形，发现错误后不能校正

适用于对较短长度的数据进行校验

### 4、海明码

#### 1）基本思想

将数据分成几组，对每一组都是用奇偶校验码进行较错

#### 2）处理过程

- 将M位数据分成K组

- 数据输入：为数据D中每组生成1位校验码，合并得到K位校验码C

- 数据输出：为数据D'中每组生成1位校验码，合并得到新的K位校验码C''

- 检错：将校验码C''和取出的校验码C'按位进行异或，生成K位故障字

- 校验码长度

  - 假设最多一位发生错误

  - 可能的差错

    - 数据中有一位出现错误：M
    - 校验码中有一位出现错误：K
    - 没有错误：1

  - 校验码的长度

    $2^{K} \ge M+K+1$

故障字的作用

- 每种取值都反映一种情形（数据出错、校验码出错、未出错）
- 规则
  - 全部都是0：没有检测到错误
  - 有且仅有1位是1：错误发生在校验码中的某一位，不需要纠正
  - 有多位1：错误发生在数据中的某一位，将D'中对应的数据位取反即可纠正（得到D''）

- 数据位的划分（根据校验码的长度）

  - 假定数据位8位D=D~8~...D~2~D~1~，检验码为4位C=C~4~C~3~C~2~C~1~

  - 数据位/校验码与故障字的关系

    ![image-20220105144809500](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105144809500.png)

  - 数据位的划分

![image-20220105144835595](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105144835595.png)

- 位安排

  将位设置在与其故障字值相同的位置

![image-20220105145213175](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105145213175.png)

### 5、循环冗余校验

奇偶校验问题：额外成本很大、要求将数据分成字节

循环冗余校验：适用于以流的格式存储和传输大量数据、用数学函数生成数据和校验码之间的关系

#### 1）基本思想

假设数据有M位，左移数据K位（右侧补0），并用K+1位<font color='red'>生成多项式</font>除它（<font color='red'>模2运算</font>）

采用K位余数作为检验码

把校验码放在数据（不含补的0）后面，一同存储或传输

#### 2）校错

如果M+K位内容可以被生成多项式除尽，则没有检测到错误

否则，发生错误

#### 3）示例

假设数据是100011，生成多项式是1001，校验码是111

![image-20220105150544425](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105150544425.png)

## 五、整数运算

### 1、加减

#### 1）算数逻辑单元（ALU）

算数逻辑单元是计算机实际完成数据逻辑算术运算的部件

- 数据由寄存器提交给ALU，运算结果也存于寄存器
- ALU可能根据运算结果设置一些标志（Flags），标志值也保存在处理器内的寄存器中
- 控制器提供控制ALU操作和数据传入送出ALU的信号

![image-20220105161044044](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105161044044.png)

#### 2）全加器

1位加法：$X_{i}+Y_{i}$

- 与门延迟：1级门延迟(1ty)

- 或门延迟：1级门延迟(1ty)

- 异或门延迟：3级门延迟(3ty)

![image-20220105161936808](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105161936808.png)

第一位加法：

$S_{i}=X_{i}\oplus Y_{i}\oplus C_{i-1}$（6ty）

$C_{i}=X_{i}C_{i-1}+Y_{i}C_{i-1}+X_{i}Y_{i}$（2ty）

![image-20220105162109665](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105162109665.png)

#### 3）串行进位加法器

> 算完一位再算下一位

==延迟：C~n~：2nty；S~n~：(2n+1)ty==

缺点：慢

![image-20220105163017904](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105163017904.png)

#### 4）全先行进位加法器

![image-20220105164043357](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105164043357.png)

![image-20220105164050546](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105164050546.png)

![image-20220105164215913](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105164215913.png)

#### 5）部分先行进位加法器

思路：采用多个CLA并将其串联，取得计算时间和硬件复杂度之间的权衡

![image-20220105164314276](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105164314276.png)

> (第一个1ty，所有CLA都完成了P~i~和G~i~的计算)
>
> 3ty：第一个CLA算出所有的C~i~，并将C~8~作为下一个CLA的C~0~输入的延迟
>
> 中间两个2ty：是中间两个CLA算出相应模块的C~i~后，传入下一个CLA的延迟
>
> 5ty：最后一个CLA算出C~i~需要2ty，算出S~i~需要3ty。

#### 6）加减法

$[X+Y]_{C}=[X]_{C}+[Y]_{C}(MOD2^{n})$

$[X-Y]_{C}=[X]_{C}+[-Y]_{C}(MOD2^n)$

溢出

![](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105183849842.png)

### 2、乘法

#### 1）无符号整数乘法

笔算！

#### 2）带符号整数乘法（布斯算法）

![image-20220105185001944](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105185001944.png)

布斯算法：

- 增加Y~0~=0
- 根据Y~i~-Y~i+1~，决定是否增加+X,-X,+0
- 右移部分积（<font color='red'>右移，左边补符号位</font>）
- 重复步骤2和步骤3共n次，得到最终结果

### 3、除法

#### 物理实现

![image-20220105185914240](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105185914240.png)

#### “够减”

> 结果的符号和中间余数一样就是够减

![image-20220105190032450](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105190032450.png)

#### 1）恢复余数

- n位符号扩展被除数，并存储在余数寄存器和商寄存器中（扩展的符号放在余数寄存器中，原来的被除数放在商寄存器中）
- 余数和商左移，判断是否“够减”（判断“够减不够减”是先减掉，然后判断，“不够”就要恢复）
  - “够”，则做减法（同号）或者做加法（异号），并上商为1
  - “不够”，则上商为0
- 重复上述步骤
- 如果除数和被除数不同号，则将商替换为其相反数
- 余数存在余数寄存器中

![image-20220105190930868](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105190930868.png)

#### 2）不恢复余数

问题：恢复余数成本高

##### 大致思路：不恢复余数

- 如果余数R~i~足够大

  ​	$R_{i+1}=2R_{i}-Y$

- 如果余数不够大

  ​	$R_{i+1}=2(R_{i}+Y)-Y=2R_{i}+Y$

##### 步骤过程

- n位符号扩展被除数，并存储在余数寄存器和商寄存器中
- 如果除数和被除数符号相同，则做减法；否则，做加法
  - 如果==余数和除数==符号相同，则商Q~n~=1；否则Q~n~=0
- 如果==余数和除数==符号相同，R~i+1~=2R~i~-Y；否则，R~i+1~=2R~i~+Y
  - 如果新的==余数和除数==符号相同，使商为1；否则使商为0
- 重复上述步骤

- 调整结果
  - 左移商
    - 如果商是负的（被除数和除数符号不同），商加一
  - 余数和被除数符号不同，修正余数
    - 若被除数和除数符号相同，最后余数加除数；否则，最后余数减除数

![image-20220105193047930](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105193047930.png)

## 六、浮点数运算

### 1、加减

### ![image-20220105205238387](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105205238387.png)

### 2、乘法

![image-20220105205336095](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105205336095.png)

### 3、除法

![image-20220105205412861](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105205412861.png)

### 4、精度考虑

#### 1）保护位

- 寄存器的长度几乎总是大于有效值位长与一个隐含位之和
- 寄存器包含的这些附加位，称为保护位
- 保护位用0填充，用于扩充有效值的右端

#### 2）舍入

- 对有效值操作的结果通常保存在更长的寄存器中
- 当结果转换回浮点格式时，必须要去掉多余的位
  - 就近舍入：结果被舍入成最近的可表示数
  - 朝$+\infty$舍入：结果朝正无穷大方向舍入
  - 朝$-\infty$舍入：结果朝负无穷大方向舍入
  - 朝0舍入：结果朝0舍入

## 七、二进制编码的十进制数运算

### 1、加法

原理：$[X+Y]_{C}=[X]_{C}+[Y]_{C}(MOD 2^{n})$

判定溢出：当值在[10,19)范围内时，需要对结果进行调整，+0110

![image-20220105210814749](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220105210814749.png)

### 2、减法

原理：$[X-Y]_{C}=[X_{C}]+[-Y]_{C}(MOD 2^{n})$

将减数“反转”后，做加法

- 反转数字

​		==“取反”==加一：取反是指 1001(9) - XXXX

- 结果调整

   如果没有进位，对结果==“取反”==加一，并结果符号反转
