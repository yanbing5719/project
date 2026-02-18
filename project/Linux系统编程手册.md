# 第三章 系统编程概念
## 3.1 系统调用（进程要求内核以自己的名义去执行某些动作）
- 用户态切换到核心台态
- 每个系统调用都由唯一数字标识
# 第四章，常用的I/O模型
## 执行文件I/O操作的主要系统调用
### fd=open(pathname,flags,mode)打开文件并返回i文件描述符用以在后续函数中打开（open的返回值为进程未用文件描述符中数值最小者
pathname:文件路径字符串
fiags:打开标志（文件访问模式标志)
mode：文件访问权限（文件访问标志，文件创建标志，已打开的文件状态标志）
### numread=read(fd,buffer,count)<调用fd所指代的文件中读取之多count字节的数据储存到buffer中。
读完返回0出现错误返回-1.
默认遇到\n结束
一般要在结尾加终止符
### numwritten=write（fd，buffer，count）调用从buffer中读取的count字节的数据写入由fd所指定的文件中。返回值为实际写入的字节数。
### status=close（fd）释放文件描述符fd及与之相关的内和资源。

# 第六章 进程
**进程 = 一个正在运行的程序 + 它拥有的一切资源**
## 6.2 进程号和父进程号
### pid_t getpid(void)获得进程号
进程号达到32767时会重置为300
### pid_t getppid(void)获得父进程
init进程，所有进程的始祖	
pstree（1）查看家族树
### fork（）创建子进程
父进程返回pid，子进程返回0,进程创建失败返回-1.
子进程就是对父进程进行所有内容的拷贝
### 父子进程之间：

❌ 普通变量（内存）不互相影响

✅ 文件偏移量 会互相影响

✅ 文件状态标志 会互相影响
```c
//利用fork和execve执行ls-l
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
using namespace std;
int main(){
    pid_t pid=fork();
    if(pid==0){
        char* argv[]={
            (char*) "ls",
            (char*) "-l",
            nullptr
        };
        extern char **environ;
        execve("/bin/ls",argv,environ);
    }else{
        wait(nullptr);
        cout<<"child finished"<<endl;
    }
return 0;
}
```
### 进程的终止
void exit(int status)
return
### 僵尸进程
僵尸进程 = 已经死了，但还没被父进程回收
只有父进程调用 wait / waitpid，内核才会彻底删除子进程

特点：

❌ 不占内存

❌ 不运行

✅ 占一个 PID

✅ 占一个进程表项
### wait和waitpid
- pid_t wait(int *status);
1.如果没有子进程退出父进程就进行等待。
2.如果有子进程退出，会获取子进程的pid返回值，退出状态
3.彻底删除僵尸进程
- pid_t waitpid(pid_t pid, int *status, int options);
等待“指定的子进程（或一组）”结束，可阻塞也可不阻塞。# 第三章 系统编程概念
## 3.1 系统调用（进程要求内核以自己的名义去执行某些动作）
- 用户态切换到核心台态
- 每个系统调用都由唯一数字标识
# 第四章，常用的I/O模型
## 执行文件I/O操作的主要系统调用
### fd=open(pathname,flags,mode)打开文件并返回i文件描述符用以在后续函数中打开（open的返回值为进程未用文件描述符中数值最小者
pathname:文件路径字符串
fiags:打开标志（文件访问模式标志)
mode：文件访问权限（文件访问标志，文件创建标志，已打开的文件状态标志）
### numread=read(fd,buffer,count)<调用fd所指代的文件中读取之多count字节的数据储存到buffer中。
读完返回0出现错误返回-1.
默认遇到\n结束
一般要在结尾加终止符
### numwritten=write（fd，buffer，count）调用从buffer中读取的count字节的数据写入由fd所指定的文件中。返回值为实际写入的字节数。
### status=close（fd）释放文件描述符fd及与之相关的内和资源。

# 第六章 进程
**进程 = 一个正在运行的程序 + 它拥有的一切资源**
## 6.2 进程号和父进程号
### pid_t getpid(void)获得进程号
进程号达到32767时会重置为300
### pid_t getppid(void)获得父进程
init进程，所有进程的始祖	
pstree（1）查看家族树
### fork（）创建子进程
父进程返回pid，子进程返回0,进程创建失败返回-1.
子进程就是对父进程进行所有内容的拷贝
### 父子进程之间：

❌ 普通变量（内存）不互相影响

✅ 文件偏移量 会互相影响

✅ 文件状态标志 会互相影响
```c
//利用fork和execve执行ls-l
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
using namespace std;
int main(){
    pid_t pid=fork();
    if(pid==0){
        char* argv[]={
            (char*) "ls",
            (char*) "-l",
            nullptr
        };
        extern char **environ;
        execve("/bin/ls",argv,environ);
    }else{
        wait(nullptr);
        cout<<"child finished"<<endl;
    }
return 0;
}
```
### 进程的终止
void exit(int status)
return
### 僵尸进程
僵尸进程 = 已经死了，但还没被父进程回收
只有父进程调用 wait / waitpid，内核才会彻底删除子进程

特点：

❌ 不占内存

❌ 不运行

✅ 占一个 PID

✅ 占一个进程表项
### wait和waitpid
- pid_t wait(int *status);
1.如果没有子进程退出父进程就进行等待。
2.如果有子进程退出，会获取子进程的pid返回值，退出状态
3.彻底删除僵尸进程
- pid_t waitpid(pid_t pid, int *status, int options);
等待“指定的子进程（或一组）”结束，可阻塞也可不阻塞。# 第三章 系统编程概念
## 3.1 系统调用（进程要求内核以自己的名义去执行某些动作）
- 用户态切换到核心台态
- 每个系统调用都由唯一数字标识
# 第四章，常用的I/O模型
## 执行文件I/O操作的主要系统调用
### fd=open(pathname,flags,mode)打开文件并返回i文件描述符用以在后续函数中打开（open的返回值为进程未用文件描述符中数值最小者
pathname:文件路径字符串
fiags:打开标志（文件访问模式标志)
mode：文件访问权限（文件访问标志，文件创建标志，已打开的文件状态标志）
### numread=read(fd,buffer,count)<调用fd所指代的文件中读取之多count字节的数据储存到buffer中。
读完返回0出现错误返回-1.
默认遇到\n结束
一般要在结尾加终止符
### numwritten=write（fd，buffer，count）调用从buffer中读取的count字节的数据写入由fd所指定的文件中。返回值为实际写入的字节数。
### status=close（fd）释放文件描述符fd及与之相关的内和资源。

# 第六章 进程
**进程 = 一个正在运行的程序 + 它拥有的一切资源**
## 6.2 进程号和父进程号
### pid_t getpid(void)获得进程号
进程号达到32767时会重置为300
### pid_t getppid(void)获得父进程
init进程，所有进程的始祖	
pstree（1）查看家族树
### fork（）创建子进程
父进程返回pid，子进程返回0,进程创建失败返回-1.
子进程就是对父进程进行所有内容的拷贝
### 父子进程之间：

❌ 普通变量（内存）不互相影响

✅ 文件偏移量 会互相影响

✅ 文件状态标志 会互相影响
```c
//利用fork和execve执行ls-l
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
using namespace std;
int main(){
    pid_t pid=fork();
    if(pid==0){
        char* argv[]={
            (char*) "ls",
            (char*) "-l",
            nullptr
        };
        extern char **environ;
        execve("/bin/ls",argv,environ);
    }else{
        wait(nullptr);
        cout<<"child finished"<<endl;
    }
return 0;
}
```
### 进程的终止
void exit(int status)
return
### 僵尸进程
僵尸进程 = 已经死了，但还没被父进程回收
只有父进程调用 wait / waitpid，内核才会彻底删除子进程

特点：

❌ 不占内存

❌ 不运行

✅ 占一个 PID

✅ 占一个进程表项
### wait和waitpid
- pid_t wait(int *status);
1.如果没有子进程退出父进程就进行等待。
2.如果有子进程退出，会获取子进程的pid返回值，退出状态
3.彻底删除僵尸进程
- pid_t waitpid(pid_t pid, int *status, int options);
等待“指定的子进程（或一组）”结束，可阻塞也可不阻塞。