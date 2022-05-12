## FAQ

### git push

#### 1 OpenSSL SSL_read: Connection was reset, errno 10054

```shell
git config --global http.sslVerify "false"
```

#### 2 Failed to connect to github.com port 443: Timed out

```shell
git config --global http://127.0.0.1:<代理端口号> # mine is 3
git config --global https://127.0.0.1:<代理端口号>
```

#### 3  Failed to connect to 127.0.0.1 port 33210: Connection refused

> 取消代理

```shell
git config --global --unset http.proxy
git config --global --unset https.proxy
```
