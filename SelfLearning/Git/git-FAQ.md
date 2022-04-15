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

