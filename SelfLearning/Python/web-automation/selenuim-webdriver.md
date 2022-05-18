***"element not interactable"***

















### 关于requests.get(url)的问题

> 报错信息：
>
> **"requests.exceptions.SSLError: HTTPSConnectionPool(host='teachingoss.applysquare.com', port=443): Max retries exceeded with url: /mp4MultibitrateIn42/2020/05/24/11/56/16/8481/o_1e92d60vf1qoa12otoq0qo41ja1p.mp4/960.mp4?OSSAccessKeyId=LTAI5tRvp4vmhaFUwAAcBybz&Expires=1652764605&Signature=QG7sf93f7Fyrg4IftbJ%2FDDxv%2BPI%3D (Caused by SSLError(SSLEOFError(8, 'EOF occurred in violation of protocol (_ssl.c:1124)')))"**

#### 历程：

最初是想根据[教程](https://www.superweb999.com/article/7172.html)通过requests.get(url)来下载视频的

但是报错

stackoverflow上关于这个问题的[答案](https://stackoverflow.com/questions/51925384/unable-to-get-local-issuer-certificate-when-using-requests-in-python?rq=1)

[证书下载](https://medium.com/@menakajain/export-download-ssl-certificate-from-server-site-url-bcfc41ea46a2)

`pip install certifi`的过程中，发现`requirement already satisfied`，因为工程目录下已经存在这个包了，如果想下载到别处，可以加 `--target={路径}`。参考[教程](https://blog.51cto.com/u_15178976/4761870)

#### 结果

都说是证书问题，但是我在对应的python解释器路径下(E:\python3.8\Lib\site-packages\certifi)和项目对应路径下(D:\study\GitHub_Res\12306\venv\Lib\site-packages\certifi)的cacert.pem中都复制了相应的证书信息，都无济于事。

> 后来发现url中截取一部分就可以直接通过webdriver.get(url)直接下载，就跳过了这个问题。
>
> 先把这个问题记录一下。

