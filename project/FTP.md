# 实现 Linux FTP 服务器

## 概述[](https://plan.xiyoulinux.com/project/ftp#%E6%A6%82%E8%BF%B0)

本项目旨在实现一个基于 RFC959 FTP 协议的 Linux FTP 服务器，支持基本的 FTP 操作，包括文件上传、下载、列出目录等功能。该服务器需要能够在被动模式（PASV）下正常工作。

## 知识要点[](https://plan.xiyoulinux.com/project/ftp#%E7%9F%A5%E8%AF%86%E8%A6%81%E7%82%B9)

1. Linux 系统编程
2. 网络编程
3. 多线程编程
4. 并发编程

## 任务说明[](https://plan.xiyoulinux.com/project/ftp#%E4%BB%BB%E5%8A%A1%E8%AF%B4%E6%98%8E)

FTP（文件传输协议）是 TCP/IP 协议族中的一种应用层协议，基于 TCP 传输。

通常情况下，FTP 使用 TCP 的 20 和 21 端口，其中 20 端口用于数据传输，21 端口用于控制信息传输。是否使用 20 端口传输数据取决于 FTP 的传输模式：

- 主动模式：数据传输使用 20 端口；
- 被动模式：数据传输端口由服务器和客户端协商决定。

本项目要求实现一个支持被动模式（PASV）的 FTP 服务器，支持基本的上传、下载、列出目录等功能，并使用 2100 端口作为控制连接端口。

### 任务流程[](https://plan.xiyoulinux.com/project/ftp#%E4%BB%BB%E5%8A%A1%E6%B5%81%E7%A8%8B)

                                            `-------------                                            |/---------\|                                            ||   User  ||    --------                                            ||Interface|<--->| User |                                            |\----^----/|    --------                  ----------                |     |     |                  |/------\|  FTP Commands  |/----V----\|                  ||Server|<---------------->|   User  ||                  ||  PI  ||   FTP Replies  ||    PI   ||                  |\--^---/|                |\----^----/|                  |   |    |                |     |     |      --------    |/--V---\|      Data      |/----V----\|    --------      | File |<--->|Server|<---------------->|  User   |<--->| File |      |System|    || DTP  ||   Connection   ||   DTP   ||    |System|      --------    |\------/|                |\---------/|    --------                  ----------                -------------                  Server-FTP                   USER-FTP`

1. FTP 客户端通过一个随机端口 N（通常大于 1024）向 FTP 服务器的 2100 端口发起连接请求。
    
2. FTP 服务器的主进程接收到请求后，创建一个服务端控制线程，与客户端控制线程建立控制连接，开始会话。
    
3. 当 FTP 客户端需要传输数据文件时，客户端控制线程向服务端控制线程发送 PASV 命令。
    
4. 服务端控制线程接收到 PASV 请求后，创建一个数据传输线程，并将生成的端口号告知客户端控制线程，返回 227 entering passive mode (h1,h2,h3,h4,p1,p2)，其中端口号为 p1*256+p2，IP 地址为 h1.h2.h3.h4。
    
    `假设服务器的 IP 地址为 192.168.1.1，生成的端口号为 5000那么返回的响应将是：227 entering passive mode (192,168,1,1,19,136)其中 19 和 136 分别是 5000 的高位和低位字节（5000 = 19*256 + 136）`
    
5. 客户端控制线程收到响应后，创建一个客户端数据传输线程，随机选择一个客户端数据传输端口，连接到服务端的数据传输端口（即前述的 IP 和端口号），然后进行数据文件传输。
    
6. 数据传输完成后，服务端数据传输进程通知传输结束，关闭数据连接通道，但保留控制连接通道。
    
7. 如果没有其他文件需要传输，控制连接通道也将关闭。
    

### 客户端设计[](https://plan.xiyoulinux.com/project/ftp#%E5%AE%A2%E6%88%B7%E7%AB%AF%E8%AE%BE%E8%AE%A1)

1. 连接服务器：通过控制连接连接到服务器的 2100 端口。
2. 请求被动模式（PASV）：发送 PASV 命令请求服务器提供用于数据传输的端口。
3. 获取文件列表：通过控制连接发送 LIST 命令，并通过数据连接接收文件数据。
4. 文件上传与下载：
    - 上传：通过控制连接发送 STOR 命令，并使用数据连接上传文件。
    - 下载：通过控制连接发送 RETR 命令，并使用数据连接下载文件。
5. 完成文件传输后，客户端关闭数据连接。

### 服务器设计[](https://plan.xiyoulinux.com/project/ftp#%E6%9C%8D%E5%8A%A1%E5%99%A8%E8%AE%BE%E8%AE%A1)

1. 监听客户端连接：监听 2100 端口，等待客户端建立控制连接。
2. 处理被动模式请求：当客户端请求进入被动模式时，服务器生成一个随机端口用于数据传输。
3. 文件传输：通过数据连接传输文件数据。
4. 完成操作后，关闭本次数据连接。

## 提高要求（选做）[](https://plan.xiyoulinux.com/project/ftp#%E6%8F%90%E9%AB%98%E8%A6%81%E6%B1%82%E9%80%89%E5%81%9A)

- 支持用户身份验证。
- 支持断点续传。
- 使用线程池优化服务器性能。
- 使用非阻塞 I/O 和 epoll 优化服务器性能。
- 优化大文件传输。

## 验收要求[](https://plan.xiyoulinux.com/project/ftp#%E9%AA%8C%E6%94%B6%E8%A6%81%E6%B1%82)

- 实现 FTP 服务器的基本功能，支持被动模式（PASV）。
- 支持文件上传、下载、列出目录等功能。
- 支持提高要求中的部分或全部功能。
- 界面美观。
- 无资源与内存泄漏。



客户端
   │
   │ connect
   ▼
listenfd（控制监听）
   │ accept
   ▼
clientfd（控制连接） ←────── 命令交互
   │
   │ PASV
   ▼
data_listenfd（数据监听）
   │ accept
   ▼
datafd（数据连接） ←────── 文件/目录传输

# 粘包问题
在接受数据时解决，recv不知道边界在那里，容易将命令混淆。
解决粘包问题要用“\r\n"为边界拆包，解析出正确命令
但是当传输字节流时，不会出现粘包问题，字节流没有”\r\n"的边界
```c
bool cmd_recv(int fd,string cache,string &cmd){

while(true){

size_t pos=cache.find("\r\n");

if(pos!=string::npos){

cmd=cache.substr(0,pos);

cache.erase(0,pos+2);

return true;

}

char buf[1024];

int n=recv(fd,buf,sizeof(buf),0);

if(n<=0)return false;

cache+=string(buf,n);

}

}
```

# 第一版服务器
```c
#include <iostream>

#include <unistd.h>

#include <cstring>

#include <sys/socket.h>

#include <arpa/inet.h>

#include <dirent.h>

#include <fstream>

  

using namespace std;

  

//工具函数

string tool(const string &f_cmd){

string filename;

for(int i=5;i<f_cmd.size();i++){

if((f_cmd[i]=='\r')||(f_cmd[i]=='\n')){

break;

}

filename+=f_cmd[i];

}

return filename;

}

  

//拆包

bool cmd_recv(int fd,string &cache,string &cmd){

while(true){

size_t pos=cache.find("\r\n");

if(pos!=string::npos){

cmd=cache.substr(0,pos);

cache.erase(0,pos+2);

return true;

}

char buf[1024];

int n=recv(fd,buf,sizeof(buf),0);

if(n<=0)return false;

cache+=string(buf,n);

}

}

//解析命令

int explain(string &cmd){

if(cmd.substr(0,4)=="USER")return 1;

if(cmd.substr(0,4)=="PASS")return 2;

if(cmd.substr(0,4)=="PASV")return 3;

if(cmd.substr(0,4)=="LIST")return 4;

if(cmd.substr(0,4)=="RETR")return 5;

if(cmd.substr(0,4)=="STOR")return 6;

if(cmd.substr(0,4)=="QUIT")return 7;

return 0;

}

  

//user

void cmd_user(int clientfd){

string username="331 ice\r\n";

send(clientfd,username.c_str(),username.size(),0);

}

  

//pass

void cmd_pass(int clientfd,bool &islogin){

islogin=true;

string password="230 login successful\r\n";

send(clientfd,password.c_str(),password.size(),0);

}

  

//pasv

void cmd_pasv(int clientfd,int &d_listenfd){

d_listenfd=socket(AF_INET,SOCK_STREAM,0);

sockaddr_in addr;

addr.sin_family=AF_INET;

addr.sin_port=0;

addr.sin_addr.s_addr=INADDR_ANY;

//监听

bind(d_listenfd,(sockaddr*)&addr,sizeof(addr));

listen(d_listenfd,1);

//获取地址，生成端口

socklen_t len=sizeof(addr);

getsockname(d_listenfd,(sockaddr*)&addr,&len);

int port=ntohs(addr.sin_port);

//返回FTP要求的端口号

int p1=port/256;

int p2=port%256;

string report="227 Entering Passive Mode (127,0,0,1,"+

to_string(p1)+","+to_string(p2)+")\r\n";

send(clientfd,report.c_str(),report.size(),0);

}

  

//list

void cmd_list(int clientfd,int &d_listenfd,bool&islogin){

if(!islogin){

string resp="530 please login first\r\n";

send(clientfd,resp.c_str(),resp.size(),0);

return ;

}

if(d_listenfd==-1){

string resp="425 use pasv first\r\n";

send(clientfd,resp.c_str(),resp.size(),0);

return ;

}

string resp="150 opening data connection\r\n";

send(clientfd,resp.c_str(),resp.size(),0);

int datafd=accept(d_listenfd,nullptr,nullptr);

//对目录进行操作

DIR *dir=opendir(".");

struct dirent *entry;

string file;

while((entry=readdir(dir))!=nullptr){

file+=entry->d_name;

file+="\r\n";

}

closedir(dir);

send(datafd,file.c_str(),file.size(),0);

close(datafd);

close(d_listenfd);

d_listenfd=-1;

string complete="226 transfer complete\r\n";

send(clientfd,complete.c_str(),complete.size(),0);

}

  

//retr

void cmd_retr(int clientfd,int &d_listenfd,bool&islogin,string &f_cmd){

if(!islogin){

string resp="530 please login first\r\n";

send(clientfd,resp.c_str(),resp.size(),0);

return ;

}

if(d_listenfd==-1){

string resp="425 use pasv first\r\n";

send(clientfd,resp.c_str(),resp.size(),0);

return ;

}

string filename=tool(f_cmd);

ifstream file(filename,ios::binary);

if(!file){

string resp="550 can't open the file\r\n";

send(clientfd,resp.c_str(),resp.size(),0);

return ;

}

int datafd=accept(d_listenfd,nullptr,nullptr);

char buf[1024];

while(1){

file.read(buf,sizeof(buf));

int n=file.gcount();

if(n<=0)break;

send(datafd,buf,n,0);

}

close(datafd);

close(d_listenfd);

d_listenfd=-1;

string resp="226 transfer complete\r\n";

send(clientfd,resp.c_str(),resp.size(),0);

}

  

//stor

void cmd_stor(int clientfd,int &d_listenfd,bool&islogin,string &f_cmd){

if(!islogin){

string resp="530 please login first\r\n";

send(clientfd,resp.c_str(),resp.size(),0);

return ;

}

if(d_listenfd==-1){

string resp="425 use pasv first\r\n";

send(clientfd,resp.c_str(),resp.size(),0);

return ;

}

string filename=tool(f_cmd);

ofstream file(filename,ios::binary);

send(clientfd, "150 Opening data connection\r\n", 31, 0);

int datafd=accept(d_listenfd,nullptr,nullptr);

char buf[1024];

string cache;

while(1){

int n=recv(datafd,buf,sizeof(buf),0);

if(n<=0)break;

file.write(buf,n);

}

close(datafd);

close(d_listenfd);

d_listenfd=-1;

string resp = "226 Transfer complete\r\n";

send(clientfd, resp.c_str(), resp.size(), 0);

}

  

//quit

void cmd_quit(int clientfd){

string resp = "221 goodbye\r\n";

send(clientfd, resp.c_str(), resp.size(), 0);

}

  

int main(){

int listenfd=socket(AF_INET,SOCK_STREAM,0);

//设置地址

sockaddr_in addr;

addr.sin_family=AF_INET;

addr.sin_port=htons(2100);

addr.sin_addr.s_addr=INADDR_ANY;

bind(listenfd,(sockaddr*)&addr,sizeof(addr));

//监听

listen(listenfd,5);

cout<<"服务器启动，端口2100..."<<endl;

int clientfd=accept(listenfd,nullptr,nullptr);

cout<<"客户端连接成功"<<endl;

string welcome="220 Welcome to Simple FTP Server\r\n";

send(clientfd,welcome.c_str(),welcome.size(),0);

bool islogin=false;

int d_listenfd=-1;

char buf[1024];

bool isrun=true;

string cache;

while(isrun){

//初始化

memset(buf,0,sizeof(buf));

string cmd;

bool ok=cmd_recv(clientfd,cache,cmd);

if(!ok){

cout<<"断开连接"<<endl;

break;

}

cout<<"收到命令"<<cmd;

int choose=explain(cmd);

switch(choose){

case 1:cmd_user(clientfd); break;

case 2:cmd_pass(clientfd,islogin);break;

case 3:cmd_pasv(clientfd,d_listenfd);break;

case 4:cmd_list(clientfd,d_listenfd,islogin);break;

case 5:cmd_retr(clientfd,d_listenfd,islogin,cmd);break;

case 6:cmd_stor(clientfd,d_listenfd,islogin,cmd);break;

case 7:cmd_quit(clientfd);isrun=false;break;

default:{

string resp = "500 Unknown command\r\n";

send(clientfd, resp.c_str(), resp.size(), 0);

break;

}

}

}

close(listenfd);

close(clientfd);

return 0;

}
```


`SIZE` 是 FTP 协议中的一个命令，用于**获取远程服务器上指定文件的大小**（以字节为单位）
### 主要用途

| 用途        | 说明                   |
| --------- | -------------------- |
| **下载前预估** | 提前知道文件大小，可以显示下载进度条   |
| **断点续传**  | 获取已下载部分的大小，确定从何处继续下载 |
| **空间检查**  | 确认本地是否有足够空间存储文件      |
| **文件验证**  | 下载后比对大小，确认传输是否完整     |
# add threadpool 
```

                ┌────────────┐
                │ 主线程     │
                │ accept     │
                └─────┬──────┘
                      │
                      ▼
              ┌─────────────┐
              │ 任务队列    │
              │ clientfd    │
              └─────┬───────┘
                    │
        ┌───────────┼───────────┐
        ▼           ▼           ▼

    工作线程1    工作线程2    工作线程3

        │           │           │

 handleClient  handleClient  handleClient
```

# client 组成
```
┌──────────────────────┐
│      shell层         │
│ 用户输入命令         │
└─────────┬────────────┘
          │
          ▼
┌──────────────────────┐
│     协议层           │
│ FTP命令封装          │
│ login/list/retr      │
└─────────┬────────────┘
          │
          ▼
┌──────────────────────┐
│     连接层           │
│ control/data socket  │
└─────────┬────────────┘
          │
          ▼
┌──────────────────────┐
│      TCP层           │
│ send/recv/connect    │
└──────────────────────┘
```

# ftp client 逻辑
你现在不要把这个客户端当成：

```text
“几个socket函数拼起来”
```

而是应该把它理解成：

# 一个“FTP协议状态机”

客户端本质上是在：

```text
按照FTP协议规则
控制整个通信流程
```

所以你设计代码时。

真正重要的是：

# “职责划分”

而不是：

# “代码写在哪”

---

# 一、FTP客户端整体架构

整个客户端其实应该分成：

```text
┌──────────────────────┐
│      shell层         │
│ 用户输入命令         │
└─────────┬────────────┘
          │
          ▼
┌──────────────────────┐
│     协议层           │
│ FTP命令封装          │
│ login/list/retr      │
└─────────┬────────────┘
          │
          ▼
┌──────────────────────┐
│     连接层           │
│ control/data socket  │
└─────────┬────────────┘
          │
          ▼
┌──────────────────────┐
│      TCP层           │
│ send/recv/connect    │
└──────────────────────┘
```

---

# 二、为什么必须这样设计

因为：

# FTP不是“一个send一个recv”

而是：

```text
协议
+
状态
+
双连接
```

如果不分层。

后面：

```text
PASV
LIST
RETR
STOR
```

会直接乱掉。

---

# 三、第一层：TCP层

这一层只负责：

# 最底层网络通信

它根本不关心：

```text
FTP
USER
LIST
```

它只知道：

```text
send
recv
connect
```

---

# 四、这一层应该有哪些函数

比如：

```cpp
bool connectServer()
bool sendAll()
string recvResponse()
```

---

# 五、为什么要封装 sendAll

因为：

# TCP不是消息协议

很多人最大误区：

```text
send一次
对面就recv一次
```

错。

TCP只有：

# 字节流

比如：

```cpp
send(10000字节)
```

可能：

```text
只发送3000
```

所以：

# 必须循环send

---

## 所以：

```cpp
sendAll()
```

本质是在：

# 保证完整发送

---

# 六、recvResponse 为什么单独封装

因为：

# FTP所有响应都要recv

比如：

```text
220 welcome
331 password required
230 login success
150 opening data connection
226 transfer complete
```

以后你还会升级：

```text
recvLine()
recvMultiLine()
```

所以必须独立。

---

# 七、第二层：控制连接层

这是：

# FTP核心

FTP最特殊的地方：

```text
有两个socket
```

---

# 八、为什么必须有两个socket

FTP早期设计目标：

```text
命令控制
和
数据传输
分离
```

因为：

```text
文件传输可能很慢
```

如果：

```text
文件和命令走同一个socket
```

那么：

```text
下载文件时
控制命令会阻塞
```

所以：

# FTP设计了：

---

## 控制连接

专门：

```text
发命令
```

比如：

```text
USER
PASS
PWD
QUIT
```

---

## 数据连接

专门：

```text
传输文件
```

比如：

```text
LIST
RETR
STOR
```

---

# 九、所以为什么有：

```cpp
controlSock
```

因为：

# 它贯穿整个会话

从：

```text
连接开始
到QUIT结束
```

一直存在。

---

# 十、为什么 dataSock 不作为成员变量

因为：

# 数据连接是“临时”的

比如：

```text
LIST
```

流程：

```text
创建data socket
↓
传目录
↓
关闭
```

---

```text
RETR
```

也是：

```text
创建
↓
下载
↓
关闭
```

所以：

# data socket 生命周期很短

---

# 十一、第三层：协议层

这是：

# 真正的FTP逻辑层

比如：

```cpp
login()
list()
retr()
stor()
```

---

# 十二、为什么要封装 login()

因为：

# 登录其实是一个协议流程

不是：

```text
一个命令
```

而是：

```text
USER
↓
331
↓
PASS
↓
230
```

这是：

# 状态机

---

# 十三、为什么 LIST 要单独函数

因为：

# LIST不是简单命令

它流程很复杂：

```text
PASV
↓
解析端口
↓
建立data socket
↓
发送LIST
↓
recv目录数据
↓
关闭data socket
```

所以：

```cpp
list()
```

本质是：

# 一整套协议流程

---

# 十四、RETR/STOR 为什么复杂

因为：

# 文件传输 = 网络IO + 文件IO

比如：

```text
recv(dataSock)
↓
write(file)
```

或者：

```text
read(file)
↓
send(dataSock)
```

这是：

# 双IO模型

---

# 十五、为什么 createDataConnection 特别重要

因为：

# FTP真正复杂的核心就在这里

---

## 普通TCP：

```text
connect一次
一直通信
```

---

## FTP：

每次：

```text
LIST
RETR
STOR
```

都必须：

```text
重新建立数据连接
```

所以：

```cpp
createDataConnection()
```

本质是：

# FTP协议核心

---

# 十六、为什么 shell 单独一层

因为：

# shell负责“用户交互”

它不应该：

```text
直接处理socket细节
```

否则：

```text
业务逻辑和网络逻辑耦合
```

会特别乱。

---

# 十七、shell真正职责

```text
读取用户输入
↓
解析命令
↓
调用协议层函数
```

比如：

---

## 用户输入：

```text
LIST
```

shell：

```cpp
list();
```

---

## 用户输入：

```text
RETR a.txt
```

shell：

```cpp
retr("a.txt");
```

---

# 十八、为什么不能所有命令都 sendCommand

因为：

# LIST/RETR/STOR 需要数据连接

而：

```text
PWD
TYPE
QUIT
```

不需要。

所以：

# 必须区分：

---

## 普通控制命令

```cpp
sendCommand()
recvResponse()
```

---

## 数据命令

```text
PASV
↓
创建data socket
↓
数据传输
```

---

# 十九、你这个项目真正练的是什么

你以为你在练：

```text
FTP
```

其实你在练：

---

# 1. TCP流模型

包括：

- 粘包
    
- 半包
    
- send不完整
    
- recv不完整
    

---

# 2. 协议设计

比如：

```text
状态码
命令解析
状态机
```

---

# 3. IO模型

包括：

```text
socket IO
+
文件 IO
```

---

# 4. 软件架构

包括：

```text
分层
解耦
封装
```

---

# 二十、你后面应该怎么继续优化

现在这个版本其实还是：

# “学习版”

后面真正应该升级：

---

## 1. recvLine()

现在：

```cpp
recv一次
```

不安全。

应该：

```text
一直recv
直到\r\n
```

---

## 2. 命令解析器

现在：

```cpp
if(cmd=="LIST")
```

后面应该：

```cpp
map<string,function>
```

---

## 3. Socket类封装

现在：

```text
FTP和socket耦合
```

后面应该：

```text
TcpSocket类
FtpClient类
```

分离。

---

## 4. 多线程

比如：

```text
上传下载后台执行
```

---

## 5. epoll

真正高性能网络模型。

---

# 二十一、你现在最该真正理解的一句话

# FTP客户端不是：

```text
“发命令”
```

而是：

# “维护协议状态”

因为整个过程中：

```text
当前是否登录
当前是否有data socket
当前是否正在传输
```

这些：

# 全都是状态。

**TCP没有“消息边界”
TCP只负责：
字节流**

# 服务端和客户端互相接受信息时顺序不可以乱
- 客户端
**PASV
收到227
发送LIST/RETR/STOR
收到150
connect data socket**
- 服务端
**发送150
accept()
开始传输**



# FTP服务器可用版
```c
//explain command

string exp_cmd(string &ans){

if(ans=="ls"){

cmd="LIST";

}else if(ans.substr(0,3)=="get"){

cmd="RETR "+ans.substr(4);

}else if(ans.substr(0,3)=="put"){

cmd="STOR "+ans.substr(4);

}else if(ans.substr(0)=="quit"){

cmd="QUIT";

}else{

cmd=ans;

}

return cmd;

}
```

**RETR 是“连接先建立，再判断文件”
STOR 是“先判断文件，再建立连接”**

# ftpserver
1. 创建监听socket
2. bind
3. listen
4. accept客户端
5. 把客户端交给线程池
# ftpsession
1. recv命令
2. 解析命令
3. USER
4. PASS
5. LIST
6. RETR
7. STOR
8. QUIT
# threadpool
1. 创建多个线程
2. 保存任务队列
3. 工作线程取任务执行

# ofstream和fstream的区别

| 特性         | `ofstream`          | `fstream`                       |
| ---------- | ------------------- | ------------------------------- |
| **默认打开模式** | `ios::out` (输出)     | `ios::in` \| `ios::out` (输入+输出) |
| **文件不存在时** | **自动创建**新文件         | **自动创建**新文件                     |
| **文件已存在时** | **清空**原文件内容 (长度变为0) | **不会清空**，打开后可直接读写原内容            |
# 最终的代码
## 服务器
```c
#include <iostream>

#include <unistd.h>

#include <cstring>

#include <sys/socket.h>

#include <arpa/inet.h>

#include <dirent.h>

#include <fstream>

#include <signal.h>

#include <mutex>

#include <fcntl.h>

#include <sys/sendfile.h>

#include <sys/stat.h>

  

#include "threadpool.cpp"

  

using namespace std;

  

mutex mtx;

// ----------tool function-----------

//command parameter

  

string tool(const string &f_cmd){

string filename;

size_t pos=f_cmd.find(' ');

if(pos==string::npos){

return "";

}

return f_cmd.substr(pos+1);

}

  

//send data

bool send_all(int fd,char *buf,int len){

int total=0;

while(total<len){

int n= send(fd,buf+total,len-total,0);

if(n<=0)return false;

total+=n;

}

return true;

}

  

//send response

void send_response(int fd,const string&resp){

send_all(fd,(char*)resp.c_str(),resp.size());

}

  

//unpack

bool cmd_recv(int fd,string &cache,string &cmd){

while(true){

size_t pos=cache.find("\r\n");

if(pos!=string::npos){

cmd=cache.substr(0,pos);

cache.erase(0,pos+2);

return true;

}

char buf[1024];

int n=recv(fd,buf,sizeof(buf),0);

if(n<=0)return false;

cache+=string(buf,n);

}

}

  

//check pasv

bool check_pasv(int fd,int &d_listenfd){

if(d_listenfd==-1){

string resp="425 use pasv first\r\n";

send_response(fd,resp);

return false;

}

return true;

}

  

//explain command

int explain(string &cmd){

if(cmd.substr(0,4)=="USER")return 1;

if(cmd.substr(0,4)=="PASS")return 2;

if(cmd.substr(0,4)=="PASV")return 3;

if(cmd.substr(0,4)=="LIST")return 4;

if(cmd.substr(0,4)=="RETR")return 5;

if(cmd.substr(0,4)=="STOR")return 6;

if(cmd.substr(0,4)=="QUIT")return 7;

if(cmd.substr(0,4)=="SIZE")return 8;

if(cmd.substr(0,4)=="TYPE")return 9;

if(cmd.substr(0,4)=="REST")return 10;

return 0;

}

  

//user

void cmd_user(int clientfd,string &cmd){

string username=tool(cmd);

string uname="yanbing";

if(username==uname){

string resp="331 password required\r\n";

send(clientfd,resp.c_str(),resp.size(),0);

return ;

}

string resp= "530 invalid username\r\n";

send(clientfd,resp.c_str(),resp.size(),0);

}

  

//pass

void cmd_pass(int clientfd,string &cmd,bool&isright){

string pword="123";

string password=tool(cmd);

if(password==pword){

string password="230 login successful\r\n";

send(clientfd,password.c_str(),password.size(),0);

isright=true;

}

else{

send_response(clientfd,

"530 login incorrect\r\n");

  

isright=false;

}

}

  

//check login

bool check_login(int fd,bool &islogin,bool &isright){

if(isright){

islogin=true;

return true;

}

string resp="530 please login first\r\n";

send_response(fd,resp);

return false;

}

  

//pasv

void cmd_pasv(int clientfd,int &d_listenfd){

if(d_listenfd!=-1){

close(d_listenfd);

}

d_listenfd=socket(AF_INET,SOCK_STREAM,0);

sockaddr_in addr;

addr.sin_family=AF_INET;

addr.sin_port=0;

addr.sin_addr.s_addr=INADDR_ANY;

//监听

bind(d_listenfd,(sockaddr*)&addr,sizeof(addr));

listen(d_listenfd,1);

//获取地址，生成端口

socklen_t len=sizeof(addr);

getsockname(d_listenfd,(sockaddr*)&addr,&len);

int port=ntohs(addr.sin_port);

//返回FTP要求的端口号

int p1=port/256;

int p2=port%256;

//获取服务器地址

sockaddr_in localaddr;

socklen_t locallen=sizeof(localaddr);

getsockname(clientfd,(sockaddr*)&localaddr,&locallen);

// 转换成字符串

string ip=inet_ntoa(localaddr.sin_addr);

  

// 192.168.1.100 -> 192,168,1,100

for(char &c:ip){

if(c=='.'){

c=',';

}

}

  

string report=

"227 Entering Passive Mode ("+

ip+","+

to_string(p1)+","+

to_string(p2)+")\r\n";

send(clientfd,report.c_str(),report.size(),0);

}

  

//list

void cmd_list(int clientfd,int &d_listenfd,

bool &islogin,bool &isright){

if(!check_login(clientfd,islogin,isright))return ;

if(!check_pasv(clientfd,d_listenfd))return ;

string resp="150 opening data connection\r\n";

send(clientfd,resp.c_str(),resp.size(),0);

int datafd=accept(d_listenfd,nullptr,nullptr);

//对目录进行操作

DIR *dir=opendir(".");

struct dirent *entry;

string file;

while((entry=readdir(dir))!=nullptr){

//skip "."and ".."

if(strcmp(entry->d_name,".")==0||

strcmp(entry->d_name,"..")==0){

continue;

}

file+=entry->d_name;

file+="\r\n";

}

closedir(dir);

send_all(datafd,(char*)file.c_str(),file.size());

close(datafd);

close(d_listenfd);

d_listenfd=-1;

string complete="226 transfer complete\r\n";

send(clientfd,complete.c_str(),complete.size(),0);

}

  

//retr

void cmd_retr(int clientfd,int &d_listenfd,bool &islogin,

bool &isright,string &f_cmd,long long&file_pos){

if(!check_login(clientfd,islogin,isright))return ;

if(!check_pasv(clientfd,d_listenfd))return ;

int datafd=accept(d_listenfd,nullptr,nullptr);

if(datafd<0){

send_response(clientfd,

"425 data connection failed\r\n");

close(datafd);

close(d_listenfd);

d_listenfd=-1;

return;

}

  

string filename=tool(f_cmd);

filename.erase(0, filename.find_first_not_of(" \t"));

filename.erase(filename.find_last_not_of(" \t\r\n") + 1);

if(filename.empty()){

send_response(clientfd, "550 No filename given\r\n");

close(datafd); close(d_listenfd); d_listenfd=-1;

return;

}

int fd=open(filename.c_str(),O_RDONLY);

//ifstream file(filename,ios::binary);

if(fd<0){

string resp="550 can't open the file\r\n";

send(clientfd,resp.c_str(),resp.size(),0);

close(datafd);

close(d_listenfd);

d_listenfd=-1;

file_pos=0;

return ;

}

/* file.seekg(0,ios::end);

long long filesize=file.tellg();*/

struct stat st;

fstat(fd,&st);

off_t filesize=st.st_size;

if(file_pos>filesize){

send_response(clientfd,

"554 invalid restart position\r\n");

close(datafd);

close(d_listenfd);

d_listenfd=-1;

file_pos=0;

return;

}

//file.seekg(file_pos,ios::beg);

send_response(clientfd,"150 opening data connection\r\n");

off_t offset=file_pos;

/* char buf[1024];

while(1){

file.read(buf,sizeof(buf));

int n=file.gcount();

if(n<=0)break;//the last n=0

if(!send_all(datafd,buf,n)){

break;

}

}*/

while(offset<filesize){

ssize_t n=sendfile(datafd,fd,&offset,filesize-offset);

if(n<=0){

break;

}

}

close(fd);

close(datafd);

close(d_listenfd);

d_listenfd=-1;

file_pos=0;

string resp="226 transfer complete\r\n";

send(clientfd,resp.c_str(),resp.size(),0);

}

  

//stor

void cmd_stor(int clientfd, int &d_listenfd, bool &islogin,

bool &isright, string &f_cmd, long long &file_pos){

if(!check_login(clientfd, islogin, isright)){

file_pos = 0;

return;

}

if(!check_pasv(clientfd, d_listenfd)){

file_pos = 0;

return;

}

// 先回应150

send_response(clientfd,

"150 Opening data connection\r\n");

// 再accept

int datafd = accept(d_listenfd, nullptr, nullptr);

if(datafd < 0){

send_response(clientfd,

"425 data connection failed\r\n");

close(d_listenfd);

d_listenfd = -1;

file_pos = 0;

return;

}

string filename = tool(f_cmd);

filename.erase(0,

filename.find_first_not_of(" \t"));

filename.erase(

filename.find_last_not_of(" \t\r\n") + 1);

if(filename.empty()){

send_response(clientfd,

"550 No filename given\r\n");

close(datafd);

close(d_listenfd);

d_listenfd = -1;

file_pos = 0;

return;

}

fstream file;

  

if(file_pos > 0){

file.open(filename,

ios::binary |

ios::in |

ios::out);

if(!file.is_open()){

file.clear();

ofstream create_file(filename,

ios::binary |

ios::out);

  

create_file.close();

  

file.open(filename,

ios::binary |

ios::in |

ios::out);

}

  

if(file.is_open()){

file.seekp(file_pos, ios::beg);//从指定位置写入文件

}

}

else{

file.open(filename,

ios::binary |

ios::out |

ios::trunc);

}

if(!file.is_open()){

send_response(clientfd,

"550 can't open or create file\r\n");

close(datafd);

close(d_listenfd);

d_listenfd = -1;

file_pos = 0;

return;

}

  

// 接收文件

char buf[4096];

while(1){

int n = recv(datafd,

buf,

sizeof(buf),

0);

if(n <= 0){

break;

}

file.write(buf, n);

if(!file){

break;

}

}

file.flush();

file.close();

close(datafd);

close(d_listenfd);

d_listenfd = -1;

file_pos = 0;

send_response(clientfd,

"226 Transfer complete\r\n");

}

//quit

void cmd_quit(int clientfd){

string resp = "221 goodbye\r\n";

send(clientfd, resp.c_str(), resp.size(), 0);

}

  

//size

void cmd_size(int clientfd,string&cmd){

//string filenaetool(cmd);

string filename=tool(cmd);

filename.erase(0, filename.find_first_not_of(" \t"));

filename.erase(filename.find_last_not_of(" \t\r\n") + 1);

if(filename.empty()){

send_response(clientfd, "550 No filename\r\n");

return;

}

ifstream file(filename,ios::binary);

if(!file){

string resp="550 can't open the file 123\r\n";

send(clientfd,resp.c_str(),resp.size(),0);

return ;

}

if(file.is_open()){

//指针移动到文件末尾

file.seekg(0,ios::end);

long long size=file.tellg();

string resp="213 "+to_string(size)+"\r\n";

send_response(clientfd,resp);

}

return ;

}

  

//type

//type

void cmd_type(int clientfd, string&cmd){

string param = tool(cmd);

if(param == "I" || param == "i"){

string resp = "200 Switching to Binary mode.\r\n";

send_response(clientfd, resp);

}

else if(param == "A" || param == "a"){

string resp = "200 Switching to ASCII mode.\r\n";

send_response(clientfd, resp);

}

else{

string resp = "200 Type set to I (Binary).\r\n";

send_response(clientfd, resp);

}

}

  

//rest

void cmd_rest(int clientfd,string &cmd,long long &file_pos){

string pos_line=tool(cmd);

file_pos=stoll(pos_line);//将字符串改为long long 类型的整数

string resp="350 Restart position accepted\r\n";

send_response(clientfd,resp);

}

  
  

void process_client(int clientfd){

string welcome="220 Welcome to Simple FTP Server\r\n";

send(clientfd,welcome.c_str(),welcome.size(),0);

bool isright=false;

bool islogin=false;

int d_listenfd=-1;

char buf[1024];

long long file_pos=0;

bool isrun=true;

string cache;

while(isrun){

//初始化

memset(buf,0,sizeof(buf));

string cmd;

bool ok=cmd_recv(clientfd,cache,cmd);

if(!ok){

cout<<"断开连接"<<endl;

break;

}

{

lock_guard<mutex> lock(mtx);

cout<<"收到命令"<<cmd<<endl;

}

int choose=explain(cmd);

switch(choose){

case 1:cmd_user(clientfd,cmd); break;

case 2:cmd_pass(clientfd,cmd,isright); break;

case 3:cmd_pasv(clientfd,d_listenfd);break;

case 4:cmd_list(clientfd,d_listenfd,islogin,isright);break;

case 5:cmd_retr(clientfd,d_listenfd,islogin,isright,cmd,file_pos);break;

case 6:cmd_stor(clientfd,d_listenfd,islogin,isright,cmd,file_pos);break;

case 7:cmd_quit(clientfd);isrun=false;break;

case 8:cmd_size(clientfd,cmd);break;

case 9:cmd_type(clientfd,cmd);break;

case 10:cmd_rest(clientfd,cmd,file_pos);break;

default:{

string resp = "500 Unknown command\r\n";

send(clientfd, resp.c_str(), resp.size(), 0);

break;

}

}

}

close(clientfd);

}

  
  

int main(){

//当程序向一个已经关闭的连接（管道或Socket）写入数据时，

//不要终止程序，而是忽略这个错误，让系统直接返回一个错误码给函数。

signal(SIGPIPE,SIG_IGN);

int listenfd=socket(AF_INET,SOCK_STREAM,0);

//设置地址

sockaddr_in addr;

addr.sin_family=AF_INET;

addr.sin_port=htons(2100);

addr.sin_addr.s_addr=INADDR_ANY;

//允许在 TIME_WAIT 状态立即重启服务器

//允许多个 socket 绑定到同一端口（需配合其他条件）

int opt = 1;

setsockopt(listenfd,

SOL_SOCKET,

SO_REUSEADDR,

&opt,

sizeof(opt));

  

bind(listenfd,(sockaddr*)&addr,sizeof(addr));

//监听

listen(listenfd,5);

cout<<"服务器启动，端口2100..."<<endl;

threadpool pool(4);

while(1){

int clientfd=accept(listenfd,nullptr,nullptr);

if(clientfd<0){

continue;

}

cout<<"客户端连接成功"<<endl;

pool.enqueue([clientfd](){

process_client(clientfd);

});

}

  

close(listenfd);

return 0;

}
```

## 客户端
```c
#include <iostream>

#include <fstream>

#include <string>

#include <vector>

#include <sys/socket.h>

#include <arpa/inet.h>

#include <unistd.h>

  

using namespace std;

  

class FtpClient{

  

private:

  

int consocket;

string recvbuffer;//Temporary buffer

string cmd;

string ans;

  

public:

  

FtpClient(){

consocket=-1;

}

  

~FtpClient(){

if(consocket!=-1){

close(consocket);

}

}

  

//-------------------------tool-----------------------------

//tool connect

int connect_socket(const string ip,int ports){

int sock=socket(AF_INET,SOCK_STREAM,0);

if(sock<0){

perror("socket");

return -1;

}

sockaddr_in addr;

addr.sin_family=AF_INET;

addr.sin_port=htons(ports);

inet_pton(AF_INET,ip.c_str(),&addr.sin_addr);

if(connect(sock,(sockaddr*)&addr,sizeof(addr))<0){

perror("connect");

return -1;

}

return sock;

}

  

//explain command

  

string exp_cmd(string &ans){

if(ans=="ls"){

cmd="LIST";

}else if(ans.substr(0,3)=="get"){

cmd="RETR "+ans.substr(4);

}else if(ans.substr(0,3)=="put"){

cmd="STOR "+ans.substr(4);

}else if(ans.substr(0)=="quit"){

cmd="QUIT";

}else{

cmd=ans;

}

return cmd;

}

  

//explain pathname

string exp_path(const string&path){

size_t pos=path.find_last_of('/');

if(pos==string::npos){

return path;

}

return path.substr(pos+1);

}

  

//send command ftp

bool send_cmd(const string &cmd){

string data=cmd+"\r\n";

if(sendall(consocket,data.c_str(),data.size())){

return true;

}

return false;

}

  

//send all data

bool sendall(int sock,const char * data,int len){

int total=0;

  

while(total<len){

int n=send(sock,data+total,len-total,0);

if(n<=0){

return false;

}

total+=n;

}

return true;

}

  
  
  

//recieve recvbuffer response

string recv_buffer(){

char buf[1024];

  

while(1){

  

size_t pos=recvbuffer.find("\r\n");

if(pos!=string::npos){

string line=recvbuffer.substr(0,pos);

recvbuffer.erase(0,pos+2);

return line;

}

  

int n=recv(consocket,buf,sizeof(buf),0);

if(n<=0){

return "";

}

  

recvbuffer+=string(buf,n);

}

}

  

//creat sock and print cmd

int creat_sock(const string cmd,int code){

string ip;

int port;

if(!pasv(ip,port)){

return -1;

}

int datasock=connect_socket(ip,port);

if(datasock<0){

return -1;

}

send_cmd(cmd);

string resp=recv_buffer();

cout<<resp<<endl;

if(resp.size()<3){

cout<<"服务器响应异常"<<endl;

return -1;

}

int re_code=stoi(resp.substr(0,3));

if(re_code!=code){

close(datasock);

return -1;

}

return datasock;

}

//-----------------------------------------------------------

//connect servre

bool ConnectServer(const string &ip,int ports){

consocket=connect_socket(ip,ports);

if(consocket<0){

return false;

}

string resp=recv_buffer();

cout<<resp<<endl;

return resp.substr(0,3)=="220";

}

  

//client pasv（send data)

bool pasv(string &ip,int &port){

  

send_cmd("PASV");

string resp=recv_buffer();

if(resp.substr(0,3)!="227")return -1;

cout<<resp<<endl;

  

//recv ip (127,0,0,1,220,147)

int p1=resp.find('(');

int p2=resp.find(')');

if(p1==string::npos||p2==string::npos){

return false;

}

  

string np=resp.substr(p1+1,p2-p1-1);

vector<int> nip;

while(1){

int pos=np.find(',');

if(pos==string::npos){

nip.push_back(stoi(np));

break;

}

nip.push_back(stoi(np.substr(0,pos)));

np.erase(0,pos+1);

}

  

port=nip[4]*256+nip[5];

ip=to_string(nip[0])+"."+to_string(nip[1])

+"."+to_string(nip[2])+"."+to_string(nip[3]);

return true;

}

  

//Login

bool login(const string&user,const string&pass){

send_cmd("USER "+user);

string resp=recv_buffer();

//cout<<resp<<endl;

if(resp.substr(0,3)!="331"){

return false;

}

  

send_cmd("PASS "+pass);

string resp1=recv_buffer();

cout<<resp1<<endl;

return resp1.substr(0,3)=="230";

  

}

  

//type

bool type(){

send_cmd("TYPE I");

string resp=recv_buffer();

cout<<resp<<endl;

return resp.substr(0,3)=="200";

}

//rest

bool rest(long long pos){

send_cmd("REST "+to_string(pos));

string recv=recv_buffer();

cout<<recv<<endl;

if(recv.size()<3){

return false;

}

return recv.substr(0,3)=="350";

}

  

//list

void list( ){

int datasock=creat_sock("LIST",150);

if(datasock<0)return ;

char buf[4096];

while(1){

int n=recv(datasock,buf,sizeof(buf)-1,0);

if(n<=0)break;

buf[n]=0;

cout<<buf;

}

close(datasock);

cout<<recv_buffer()<<endl;

}

  

//retr

void retr(const string &filename){

long long pos=0;

string local_file=filename;

size_t pos_last = local_file.find_last_of("/\\");

if(pos_last != string::npos){

local_file= filename.substr(pos_last + 1);

}

ifstream checkfile(local_file,ios::binary);

if(checkfile){

checkfile.seekg(0,ios::end);

pos=checkfile.tellg(); //获取当前指针的位置

checkfile.close();

}

long long server_size=cmd_size(filename);

if(server_size<0){

cout<<"服务器文件不存在"<<endl;

return ;

}

if(server_size==pos&&pos>0){

cout<<"文件下载完成"<<endl;

return ;

}

if(pos>server_size){

cout<<"本地文件大于服务器文件"<<endl;

return ;

}

if(pos>0){

if(!rest(pos)){

cout<<"REST failed"<<endl;

pos=0;

}

}

int datasock=creat_sock("RETR "+filename,150);

if(datasock<0)return ;

ofstream file(local_file,ios::binary|ios::app);

if(!file){

cout<<"文件创建失败"<<endl;

close(datasock);

return ;

}

char buf[4096];

while(1){

int n=recv(datasock,buf,sizeof(buf),0);

if(n<=0)break;

file.write(buf,n);

}

file.close();

close(datasock);

string resp=recv_buffer();

cout<<resp<<endl;

if(stoi(resp.substr(0,3))==226){

cout<<"下载完成"<<endl;

}else{

cout<<"传输异常"<<endl;

}

}

  

//stor

  

void stor(const string &localpath,

const string &remotepath){

long long pos=0;

long long server_size=cmd_size(remotepath);

if(server_size>=0){

pos=server_size;

if(!rest(pos)){

cout<<"REST failed"<<endl;

pos=0;

}

}

ifstream file(localpath,ios::binary);

if(!file.is_open()){

cout<<"can't find the file"<<endl;

return ;

}

long long local_size = 0;

file.seekg(0, ios::end);

local_size = file.tellg();

file.seekg(0, ios::beg);

if(pos<0)pos=0;

if(local_size==pos){

cout<<"文件已成功上传或本地文件更小"<<endl;

file.close();

return;

}

if(pos>0){

if(!rest(pos)){

cout<<"REST failed"<<endl;

pos=0;

file.seekg(0,ios::beg);

}

}

file.seekg(pos,ios::beg);

int datasock=creat_sock("STOR "+remotepath,150);

if(datasock<0)return ;

  

char buf[4096];

while(1){

file.read(buf,sizeof(buf));

int n=file.gcount();

if(n<=0)break;

if(!sendall(datasock,buf,n))break;

}

file.close();

close(datasock);

string resp=recv_buffer();

cout<<resp<<endl;

if(resp.size()<3){

cout<<"服务器响应异常"<<endl;

return;

}

int code=stoi(resp.substr(0,3));

if(code==226){

cout<<"上传完成"<<endl;

}else{

cout<<"上传异常"<<endl;

}

}

  
  

//size

long long cmd_size(string filename){

send_cmd("SIZE "+filename);

string resp=recv_buffer();

cout<<resp<<endl;

if(resp.substr(0,3)!="213"){

return -1;

}

string num=resp.substr(4);

size_t pos=num.find("\r\n");

if(pos!=string::npos){

num=num.substr(0,pos);

}

return stoll(num);

}

  

//shell

void shell(){

while(1){

string cmd;

cout<<"ftp> ";

getline(cin,ans);

cmd=exp_cmd(ans);

if(cmd.empty()){

continue;

}

if(cmd=="LIST"){

list();

continue;

}

if(cmd.substr(0,4)=="RETR"){

string filename=cmd.substr(5);

//delete 空格

while(!filename.empty()&&filename[0]==' '){

filename.erase(0,1);

}

retr(filename);

continue;

}

if(cmd.substr(0,4)=="STOR"){

string localpath=cmd.substr(5);

while(!localpath.empty()&&localpath[0]==' '){

localpath.erase(0,1);

}

string remotepath=exp_path(localpath);

stor(localpath,remotepath);

continue;

}

send_cmd(cmd);

string resp=recv_buffer();

cout<<resp<<endl;

if(resp.size()<3){

cout<<"服务器响应异常"<<endl;

return;

}

int code=stoi(resp.substr(0,3));

if(cmd=="QUIT"){

if(code==221){

break;

}

}

}

}

};

  

int main(){

FtpClient client;

string ip;

int port;

cout<<"ip: ";

cin>>ip;

cout<<"port: ";

cin>>port;

if(!client.ConnectServer(ip,port))return 0;

string user;

string pass;

cout<<"username:"<<endl;

cin>>user;

cout<<"password:"<<endl;

cin>>pass;

//delete th last char

cin.ignore();

if(client.login(user,pass))

{

client.type();

client.shell();

}

else

{

cout << "登录失败\n";

}

return 0;

}
```