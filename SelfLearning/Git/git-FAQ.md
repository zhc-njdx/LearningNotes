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

#### 4 remote: Support for password authentication was removed on August 13, 2021. Please use a personal access token instead.
remote: Please see https://github.blog/2020-12-15-token-authentication-requirements-for-git-operations/ for more information.
fatal: Authentication failed for 'https://github.com/zhc-njdx/sponge.git/'

> 不能使用用户名+密码的方式验证身份

在github申请 Personal Access Token

[解决](https://stackoverflow.com/questions/68775869/support-for-password-authentication-was-removed-please-use-a-personal-access-to)

> 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
>
> 有效期：05-21——06.21
>
> git push https://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@github.com/zhc-njdx/sponge.git

#### 5 fatal: unable to access 'https://github.com/zhc-njdx/sponge.git/': gnutls_handshake() failed: Error in the pull function.

```shell
apt-get -y install build-essential nghttp2 libnghttp2-dev libssl-dev
```

[解决](https://stackoverflow.com/questions/52379234/git-gnutls-handshake-failed-error-in-the-pull-function)
