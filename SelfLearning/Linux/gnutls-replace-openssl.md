### gnutls替换为penssl

#### 背景

环境：Windows 10下Vitrual Box中的Ubuntu虚拟机(Ubuntu 18.04.1 LTS)

场景：该虚拟机是为cs144 lab服务。在写完lab后，准备向github提交代码（由于用户名验证码登录当时已经失效，所以使用Personal Access Token来进行登录提交 `git push https://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@github.com/zhc-njdx/sponge.git`），但是报错

```shell
fatal: unable to access 'https://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@github.com/zhc-njdx/sponge.git/': gnutls_handshake() failed: Error in the pull function.
```

#### 过程

到网上查找解决方法，大概有几种：1、关掉VPN；2、输入命令`apt-get -y install build-essential nghttp2 libnghttp2-dev libssl-dev`（来自[stackoverflow](https://stackoverflow.com/questions/52379234/git-gnutls-handshake-failed-error-in-the-pull-function)）；3、在~/.gitconfig中增加代理ip和端口号。4、将gnutls替换为openssl。

1、前面三种都无效后，开始尝试第4种：

```shell
sudo apt-get update
sudo apt-get install build-essential fakeroot dpkg-dev libcurl4-openssl-dev
sudo apt-get build-dep git
```

`sudo apt-get build-dep git`命令运行之后可能会出现错误

```shell
E: You must put some 'source' URIs in your sources.list
```

就是apt下载更新软件的源缺少了，可以去更改 /etc/apt/source.list 文件，增加软件源

在网上找了几篇教程（都给了一些国内外的源）：1、[stackoverflow](https://askubuntu.com/questions/496549/error-you-must-put-some-source-uris-in-your-sources-list)；2、[csdn](https://blog.csdn.net/yitian_z/article/details/84883882) 。增加了源之后，一定要运行命令 `sudo apt-get update`

增加了在csdn上找的那些源，可能会出现如下错误

```shell
E: The repository 'https://mirrors.tuna.tsinghua.edu.cn/ubuntu focal Release' does not have a Release file.
N: Updating from such a repository can't be done securely, and is therefore disabled by default.
```

[解决方案](https://blog.csdn.net/qlexcel/article/details/120642914)：将那些源的 `https` 改成 `http`

2、之后再运行

```shell

mkdir ~/git-openssl
cd ~/git-openssl
apt-get source git
cd git-2.17.0/ # 注：git的版本后由ubuntu系统决定，这里ubuntu18.04.1是git-2.17.0

# 进入目录后，需要修改debian/下的两个文件 control 和 rules
# 在 debian/control 中将 libcurl4-gnutls-dev 替换为 libcurl4-openssl-dev
# 在 debian/rules 中删除 TEST =test行
# 可以直接在vim命令模式下操作 :%s/libcurl4-gnutls-dev/libcurl4-openssl-dev/g
# 也可以使用命令sed
sed 's/libcurl4-gnutls-dev/libcurl4-openssl-dev/g' ./debian/control
sed '/TEST =test/d' ./debian/rules
```

[vim查找和替换](https://harttle.land/2016/08/08/vim-search-in-file.html) [sed命令](https://www.runoob.com/linux/linux-comm-sed.html) 

3、然后

```shell
# g
sudo dpkg-buildpackage -rfakeroot -b -uc -us
```

这条命令失败！！报错：

```shell
dpkg-shlibdeps: error: cannot read /home/cs144/git-openssl/git-2.7.4/debian/git/usr/lib/git-core/mergetools: Is a directory
debian/rules:353: recipe for target 'binary-arch' failed
make: *** [binary-arch] Error 21
dpkg-buildpackage: error: fakeroot debian/rules binary subprocess returned exit status 2
```

这个错一直没有找到解决方法，所以就没有继续下去。

4、后续的命令

```shell
sudo dpkg -i ../git_2.17.0-1ubuntu1_amd64.deb
```

#### 解决

更换了 Personal Access Token 成功！（给PAT授权要足够，不然会没有权限`The requested URL returned error: 403`）     



> 关于[source.list](https://blog.csdn.net/u012843189/article/details/80964287)的讲解