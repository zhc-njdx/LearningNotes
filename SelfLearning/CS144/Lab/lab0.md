## Lab 0



### 1 实验

#### 1.1 telnet 远程连接获取网页文本

#### 1.2 smtp 发送电子邮件



### 2 Network Programming

#### 2.1 get_URL (sponge/apps/webget.cc)

> 2022.05.18 完成

```cpp
void get_URL(const string &host, const string &path){
    Address host_addr(host, "80");
    TCPSocket client;
    client.connect(host_addr);
    
    client.write("GET " + path + " GTTP/1.1\r\n" + 
                 "Host: " + host + "\r\n" + 
                 "COnnection: close\r\n\r\n");
    
    string response;
    while(!client.eof()){
        client.read(response);
        std::cout << response;
    }
}
```

> 类似于C的socket programming

完成前

```shell
[100%] Testing webget...
Test project /home/cs144/sponge/build
    Start 31: t_webget
1/1 Test #31: t_webget .........................***Failed    0.01 sec
Function called: get_URL(cs144.keithw.org, /nph-hasher/xyzzy).
Warning: get_URL() has not been implemented yet.
ERROR: webget returned output that did not match the test's expectations


0% tests passed, 1 tests failed out of 1

Total Test time (real) =   0.01 sec

The following tests FAILED:
         31 - t_webget (Failed)
Errors while running CTest
CMakeFiles/check_webget.dir/build.make:57: recipe for target 'CMakeFiles/check_webget' failed
make[3]: *** [CMakeFiles/check_webget] Error 8
CMakeFiles/Makefile2:195: recipe for target 'CMakeFiles/check_webget.dir/all' failed
make[2]: *** [CMakeFiles/check_webget.dir/all] Error 2
CMakeFiles/Makefile2:202: recipe for target 'CMakeFiles/check_webget.dir/rule' failed
make[1]: *** [CMakeFiles/check_webget.dir/rule] Error 2
Makefile:181: recipe for target 'check_webget' failed
make: *** [check_webget] Error 2
```

完成后

```shell
Scanning dependencies of target check_webget
[100%] Testing webget...
Test project /home/cs144/sponge/build
    Start 31: t_webget
1/1 Test #31: t_webget .........................   Passed    6.23 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   6.24 sec
[100%] Built target check_webget
```

#### 2.2 in-memory reliable byte stream(sponge/libsponge/byte_stream.cc && byte_stream.hh)

> 2022.05.21 完成

##### 要点

实验目的是完成一个 ByteStream 类，使得该类可以抽象一个 reliable byte stream (关键在于reliable，建立在reliable的前提下，所以后续很多情况并未考虑)

要点在于理解ByteStream类的工作过程，虽说是模拟TCP协议下双方的数据传输，但是 ByteStream只是一个简单的抽象：1、不考虑数据传输的时间，也不考虑数据丢失乱序等情况，是直接的 input side write into buffer while output side read from the buffer；2、存在流量控制，即buffer的大小（需要设计buffer的数据结构）

##### 过程

1、一开始还考虑了字节的传输过程(stream)，但是根据类中的成员函数可以得出是不需要的

2、对于buffer的数据结构，很快就想到了环形数组

3、抓住了上面两点，整体很快就实现好了

4、debug

- pop_output 就是 read 的意思
- 在write的时候没考虑data的长度（这个有点离谱）
- output达到ending有一个前提，inout终止了数据传输
- peek_output忘记了环形数组的数据结构

##### 结果

```shell
cs144@cs144vm:~/sponge/build$ make check_lab0
[100%] Testing Lab 0...
Test project /home/cs144/sponge/build
    Start 26: t_byte_stream_construction
1/9 Test #26: t_byte_stream_construction .......   Passed    0.00 sec
    Start 27: t_byte_stream_one_write
2/9 Test #27: t_byte_stream_one_write ..........   Passed    0.00 sec
    Start 28: t_byte_stream_two_writes
3/9 Test #28: t_byte_stream_two_writes .........   Passed    0.00 sec
    Start 29: t_byte_stream_capacity
4/9 Test #29: t_byte_stream_capacity ...........   Passed    0.44 sec
    Start 30: t_byte_stream_many_writes
5/9 Test #30: t_byte_stream_many_writes ........   Passed    0.01 sec
    Start 31: t_webget
6/9 Test #31: t_webget .........................   Passed    6.18 sec
    Start 53: t_address_dt
7/9 Test #53: t_address_dt .....................   Passed    5.04 sec
    Start 54: t_parser_dt
8/9 Test #54: t_parser_dt ......................   Passed    0.00 sec
    Start 55: t_socket_dt
9/9 Test #55: t_socket_dt ......................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 9

Total Test time (real) =  11.72 sec
[100%] Built target check_lab0
```



![pass截图](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220521185945943.png)

