## Lab 0



### 1 实验

#### 1.1 telnet 远程连接获取网页文本

#### 1.2 smtp 发送电子邮件



### 2 Network Programming

#### 2.1 get_URL (webget.cc)

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

