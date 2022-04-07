[TOC]





## SQL

> (Structured Query Language，结构化查询语言)

### 1 数据定义

#### 1.1 模式

> [模式（schema）][https://www.cnblogs.com/unique1319/articles/10191566.html]
>
> 大致来看，schema相当于一个大仓库里的一个个房间，table相应于房间里的储物柜。



> database和schema的关系
>
> database相当于一个大仓库，而schema相当于大仓库里的房间。
>
> 有些数据库是一对多的关系（即一个database里有多个schema），有些数据库是一对一的关系（一个database里只有一个schema），而mysql是后者。在mysql中，database和schema是同义词。



#####1.1.1 定义模式

```sql
create schema <schema_name> [authorization <username>];
```

[]中可缺省，默认以schema_name为相应的username。

#####1.1.2 删除模式

```sql
drop schema <schema_name> <cascade|restrict>;
```

cascade(级联)，表示在删除模式的同时把该模式下的所有数据库对象全部删除

restrict(限制)，如果该模式下已经定义了下属的数据库对象，则拒绝该删除语句的执行

#### 1.2  基本表

##### 1.2.1 定义基本表

```sql
create table <table_name>(

<column_name> <dataType> [column-level integrity constraints],
<column_name> <dataType> [column-level integrity constraints]
...

[table-level integrity constraints]
);
```

- <列级完整性约束条件>：涉及相应属性列的完整性约束条件

  比如：PRIMARY_KEY、NOT NULL、UNIQUE

- <表级完整性约束条件>：涉及一个或多个属性列的完整性约束条件 

  比如：FOREIGN KEY (...) REFERENCES Course (...)

```sql
create table student 
(Sno CHAR(9) PRIMARY KEY,
 Sname CHAR(20) UNIQUE,
 Ssex CHAR(2),
 Sage SMALLINT,
 Sdept CHAR(20)
);

create table Course
(Cname CHAR(40) NOT NULL,
 Cpno CHAR(4),
 Ccredit SMALLINT,
 FOREIGN KEY (Cpno) REFERENCES Course(Cno)
);

create table SC
(Sno CHAR(9),
 Cno CHAR(4),
 Grade SMALLINT,
 PRIMARY KEY(Sno, Cno),
 FOREIGN KEY (Sno) REFERENCES Student(Sno),
 FOREIGN KEY (Cno) REFERENCES Course(Cno)
);
```

##### 1.2.2数据类型

![image-20220308094959101](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220308094959101.png)



### 2 数据查询

```sql
select [all|distinct] [,<目标列表达式> [别名]] ...
from <表名或者视图名> [别名] [,<表名或者视图名> [别名]] ... | (<select语句>) [as] <别名> # 这里的select语句生成派生表来查询
[where <条件表达式>]
[group by <列名1> [having <条件表达式>]] # 分组，并使得聚集函数作用于每一个组
[order by <列名2> [asc|desc]] # 对列名2的值进行升序(asc)或降序(desc)排列
```

#### 2.1 where子句

![image-20220313104652299](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220313104652299.png)

> 字符匹配：
>
> ```sql
> [not] like '<匹配串>' [escape '<换码字符>']
> ```
>
> % 表示任意长度的字符串
>
> _ 表示任意的单个字符
>
> 如果用户要查询的字符串中本身就含有通配符，就要使用 `escape '<换码字符>'`进行转义。

#### 2.2 聚集函数

![image-20220313105110994](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220313105110994.png)

<font color='red'>聚集函数除了count(*)以外，都跳过空值，只处理非空值。</font>

#### 2.3 连接查询

##### 2.3.1 等值连接和非等值连接

`[<表名1>.]<列名><比较运算符>[<表名2>.]<列名>`

- 比较运算符为 "=" ，为等值连接。否则为非等值连接

- 等值连接中将目标列中重复的属性列去掉则为自然连接。

##### 2.3.2 自身连接

- 要将表取两个别名：first，second

##### 2.3.3 外连接

> 将相应关系的悬浮元组（关系代数的连接中被舍弃的元组）保存在结果中

`select [属性名] from <表名1(left-relation)> <left|right> outer join <表名2(right-relation)> on (表名1.属性名=表名2.属性名)`

左外连接(left)：列出左边关系(left-relation)

右外连接(right)：列出右边关系(right-relation)

##### 2.3.4 多表连接

`[<表名1>.]<列名1><比较运算符>[<表名2>.]<列名1> <and|or> [<表名2>.]<列名2><比较运算符>[<表名3>.]<列名2> ...`

#### 2.4 嵌套循环

##### 2.4.1 带有 in 谓词的子查询

`where <column_name> in <子查询>`

> 相关子查询和不相关子查询

##### 2.4.2 带有比较运算符的子查询

`where <column_name> <比较运算符> <子查询>`

##### 2.4.3 带有 any(some) 或 all 谓词的子查询

![image-20220313114541813](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220313114541813.png)

##### 2.4.4 带有exists 谓词的子查询

代表存在量词 $\exists$ ，带有 exists 谓词的子查询不返回任何数据，只产生逻辑真假值。

#### 2.5 集合查询

union（并集）、intersect（交集）、except（差集）

先分别查出两个集合然后再作上述的处理。

#### 2.6 基于派生表的查询

子查询不仅可以出现再where子句中，还可以出现在from子句中，这时子查询生成的临时派生表称为主查询的查询对象。

### 3 数据更新

##### 3.1 插入数据

- ```sql
  insert into <表名> [属性列,...]
  values (...)
  ```

- ```sql
  insert into <表名> [属性列,...]
  <子查询>
  # 即将查询结果插入表中
  ```

##### 3.2 修改数据

- ```sql
  update <表名>
  set <列名>=<表达式>[,...]
  [where <条件>] # 条件也可以是子查询
  ```

##### 3.3 删除数据

```sql
delete from <表名>
[where <条件>] # 同样条件可以是子查询
```

### 4 空值

- 空值：“不知道”、“不存在”或“无意义”

- 空值的判断：`is null` 或 `is not null`

- `not null` 、`unique` 和 码属性不能去空值

- 运算

  ![image-20220313095724359](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220313095724359.png)

### 5 视图

#### 5.1 定义

- 视图是从一个或多个基本表中导出的表，是一个虚表
- 数据库中只存放视图的定义，不存放视图的数据（数据仍然在原来的基本表中）

####5.2 操作

- 建立视图

  ```sql
  create view <视图名>[(列名,...)] # 列名要么缺省，要么全部指定
  as <子查询> # 子查询就是选出基本表中的数据
  [with check option] # 表示对视图进行增删改时要满足视图定义中的谓词条件(即子查询中的条件表达式)
  ```

  <font color='red'>数据库执行create view时，只是把视图的定义存入数据字典中，并不执行其中的select语句。而后面对视图进行查询时，再按照视图的定义从基本表中查询数据。</font>

- 删除视图

  ```sql
  drop view <视图名>[cascade];
  ```

- 查询视图

  <font color='red'>视图消解：</font>对视图的查询，是将定义中的子查询和用户的查询结合起来，转换成等价的对基本表的查询。

- 更新视图

  视图只是虚表，所以所有对视图的更新最终都会转换为对基本表的更新。（这也就是为什么在视图中作的增删改会”同步“到基本表中，实际上就是对基本表作增删改操作）





