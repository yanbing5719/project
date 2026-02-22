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
# 第五章
## 5.5复制文件描述符
新的文件描述符可以指向旧的文件描述符所指向的文件
```c
int dup(int oldfd);
//复制 oldfd，返回一个最小可用的新 fd
```
```c
int dup2(int oldfd, int newfd);
//把 newfd 变成 oldfd 的一个副本
```
dup2 比 dup 多了可以指定 newfd
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
### 6.7 环境列表
环境变量是进程的一部分，用来控制程序行为，在 fork 时继承，在 exec 后保留。不改程序代码，就能改变程序行为
- environ（指向环境变量表的全局变量）
 ```
 environ
  |
  v
+------------------+
| "PATH=/bin:..."  |
| "HOME=/home/xx"  |
| "USER=ice"       |
| "LANG=zh_CN..."  |
| ...              |
| NULL             |
+------------------+
```
- 
 ```c
 //getenv(从进程环境中检索单个值）
 char *getenv(const char *name);
 //putenv向调用的进程中添加一个新的变量，或修改一个已经存在的变量,失败返回非0
 int putenv(char *string);
 // setenv添加新变量，<overwrite存在为1覆盖,否则为0>
 //会 复制 name=value
//之后你传入的字符串可以释放 / 失效
 int setenv(const char *name, const char *value, int overwrite);
 //unsetenv移除由name参数标识的变量
 int unsetenv(const char *name);
 //clearenv清除所有环境变量
 int clearenv(void);
 ```
### 管道
- 管道是内核提供的单向、基于文件描述符的进程间通信机制，常用于把一个进程的输出作为另一个进程的输入。
- pipe() 在内核中创建一个缓冲区，并返回两个文件描述符，一个只能读，一个只能写。
创建成功返回0,否则返回-1
- 管道用于在多个进程之间高效、顺序地传递数据，避免中间文件，使程序能够按流水线方式协同工作。
### exec系列函数
在“当前进程”中加载并执行一个新的程序‘
```c
char *argv[] = {"ls", "-l", NULL};
execv("/bin/ls", argv);
```