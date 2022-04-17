

> 记录在VirtualBox使用Ubuntu虚拟机时的问题



#### 1 共享文件夹

- setting(设置) => 共享文件夹 => 

  设置windows端共享文件夹的路径和名称

  **只勾选固定分配**

- 进入虚拟机 => 

  ```shell
  sudo apt-get install virtualbox-guest-x11
  ```

  => 重启

  => `mkdir /mnt/{w-dir-name(windows下共享文件夹的名字)}`

  => `sudo mount -t vboxsf w-dir-name /mnt/w-dir-name `

- 完成挂载

