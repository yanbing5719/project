
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

**父进程里面给argv分配内存后必须释放，但是如果是子进程里面分配内存而且还调用了exxe系列函数就不需要释放内存**
### getcwd获取当前工作目录
```c
#include <unistd.h>
char *getcwd(char *buf, size_t size);
```
### chidir 切换当前目录
```c
#include <unistd.h>

int chdir(const char *path);
```
成功返回0,失败返回-1
# 第二十章 信号
**打断程序正常执行流程**
## 20.3改变信号处置：signal（）
### singal函数 让程序在收到特定信号时执行自定义行为，而不是默认动作。
```c
#include <signal.h>   // 或 #include <csignal> 在 C++

void (*signal(int signum, void (*handler)(int)) )(int);
```
signum:希望修改的信号编号
void (*handler)(int)) )(int) ：信号抵达时所调用函数的地址（这个函数实现了你想要改信号实现的功能）
## 20.4信号处理器简介
### 信号处理程序（指定信号传递给进程时调用一个函数，打断主程序执行流程）
```c
#include <stdio.h>

#include<signal.h>

#include<unistd.h>

void handler(int sig)

{

printf("Received signal: %d\n", sig);

}

int main()

{

signal(SIGINT,handler);

while(1)

{

//sleep主要是为了让程序保持运行一段时间，方便你触发和观察信号

sleep(1);

}

return 0;

}
```
### 20.5发送信号：kill（）
一个进程向另一个进程发送信号
```c
#include <siginal>
int kill(pid_t pid, int sig);
```

|pid值|含义|
|---|---|
|`pid > 0`|发送给指定进程|
|`pid = 0`|发送给当前进程组|
|`pid = -1`|发送给所有进程|
|`pid < -1`|发送给指定进程组|
## 第二十四章 进程的创建
### 24.2创建新进程 fork（）
```c
#include <unistd.h>
pid_t fork(void);
```
父进程返回pid，子进程返回0,进程创建失败返回-1.
子进程就是对父进程进行所有内容的拷贝
父子进程共享文件描述符，文件偏移量。
fork 创建子进程时复制父进程的虚拟地址空间，但实际使用写时复制（Copy-On-Write）提高效率。
## 第二十五章 进程的终止 
### 25.1进程的终止 -exit()和exit()
- exit()
正常退出
刷新缓冲区
执行清理函数
**一般程序结束用。**

- _exit()
立即退出
不做任何清理
**一般用于：fork() 子进程，execve() 失败，系统编程**
### 25.3退出处理程序
atexit()
```c
#include <stdlib.h>

void cleanup() {
    // 清理代码
}

int main() {

    if (atexit(cleanup) != 0) {
        printf("注册失败\n");
    }

    // 主程序

    return 0;
}
```
限制：
1.无法获知传递给exit（）的状态
2.无法给退出处理程序指定参数
## 第二十六章 监控子进程
### wait和waitpid
- pid_t wait(int *status);
1.如果没有子进程退出父进程就进行等待。
2.如果有子进程退出，会获取子进程的pid返回值，退出状态
3.彻底删除僵尸进程
- pid_t waitpid(pid_t pid, int *status, int options);
等待“指定的子进程（或一组）”结束，可阻塞也可不阻塞。

|pid值|含义|
|---|---|
|`pid > 0`|等待指定进程|
|`pid = 0`|等待同一进程组的所有进程|
|`pid < -1`|等待进程组标识符与pid绝对值相等的所有子进程|
|`pid = -1`|等待任意子进程|
### 孤儿进程和僵尸进程
- 僵尸进程
僵尸进程 = 已经死了，但还没被父进程回收
只有父进程调用 wait / waitpid，内核才会彻底删除子进程

特点：

❌ 不占内存

❌ 不运行

✅ 占一个 PID

✅ 占一个进程表项
- 孤儿进程
 父进程先结束，而子进程还在运行的进程。
 ## 第二十七章 程序的执行
 **exec系列函数**
在“当前进程”中加载并执行一个新的程序‘
```c
#include <unistd.h>
#include <stdio.h>

int main()
{
    char *args[] = {"ls","-l",NULL};

    execvp("ls",args);

    perror("execvp");
}
```
feecve与exevce类似，只要将路径名换成文件描述符即可
### 27.6执行shell命令：system
创建一个子进程来运行shell，并以之执行命令command。，至少创建两个子进程
```c
#include <stdlib.h>

int system(const char *command);
```
## 第二十九章 线程：介绍
**线程：进程中的执行单元**
一个进程里面可以有多个线程同时执行
**所有线程共用：**
代码段
全局变量
堆
文件描述符
1.**进程修改变量不会影响其他进程**
2.**修改线程会影响整个进程，线程之间会相互影响**
### 29.3 创建线程
```c
int pthread_create(
    pthread_t *thread,
    const pthread_attr_t *attr,
    void *(*start_routine)(void *),
    void *arg
);
```
创建成功0,否则非0
pthread_t *thread 线程号
attr 线程属性，一般设置为nullptr
  void *(*start_routine)(void *) 线程执行的函数
  arg传递给线程函数的参数
  ###  29.4终止线程
  start函数执行return
  调用pthread_exit()
  调用pthread_cancle()取消线程
  任意线程调用exit（）或者主线程执行return，使进程中的所有线程立即终止
  **pthread_exit() 只结束当前线程其他线程继续运行，exit()或者return语句 会结束整个进程**
  ### 29.5线程ID
  ```c
  pthread_self()
  //获取线程ID
  ```
  ```c
  pthread_equal()
  //比较线程ID是否相同
  ```
  ### 29.6 连接已终止的线程
  ```c
  pthread_join()
//连接
  ```
 未能连接线程将产生僵尸线程
 ### 29.7线程的分离
```c
 pthread_detach()
  //线程结束 → 系统自动回收资源
```
## 第三十章线程的同步
   ### 30.1互斥量（使用之前必须初始化）
   保证同一时刻只有一个线程访问某个共享资源
   **互斥量有两种状态**：
   1 未锁定 (unlock)
2 已锁定 (lock)
一般情况下至多只有一个线程可以锁定该互斥量
  **家锁和解锁互斥量**：
 ```c
 int pthread_mutex_lock(pthread_mutex_t *mutex);
 int pthread_mutex_unlock(pthread_mutex_t *mutex);
 ```
 如果有线程已经锁定互斥量，则函数调用会一直阻塞直至互斥量被解锁
 同一个线程再次锁定互斥量造成死锁
 ### 30.2条件变量
 线程需要等待某个条件成立才能继续执行

**互斥量负责：**

保护共享数据

**条件变量负责：**

让线程等待 / 唤醒线程

这是多线程编程里非常重要的 线程同步机制。
 
```c
pthread_cond_wait(pthread_cond_t *cond,
                  pthread_mutex_t *mutex);
```
线程等待条件
```c
pthread_cond_signal(&cond);
```
1 解锁 mutex
2 线程进入等待队列
3 被唤醒
4 再次加锁 mutex
唤醒一个等待线程
```c
pthread_cond_broadcast(&cond);
```
唤醒所有等待线程
**动态分配的条件变量**：
```c
pthread_cond_t* cond;

cond = (pthread_cond_t*)malloc(sizeof(pthread_cond_t));

pthread_cond_init(cond,NULL);
```
销毁
```c
pthread_cond_destroy(cond);
free(cond);
```
## 第三十一章线程安全和每线程存储
函数可同时供多个线程安全调用0
**实现线程安全**：
函数与互斥量关联使用（调用函数锁住，函数返回解锁）
共享变量与互斥量关联
### 31.2一次性初始化
某段初始化代码在整个程序运行期间只执行一次
即使有多个线程同时调用
```c
int pthread_once(pthread_once_t *once_control,
                 void (*init_routine)(void));
```
  ### 31.3线程特有数据API
  每个线程拥有自己的独立数据副本
  **创建线程独有的key**
```c
int pthread_key_create(pthread_key_t *key,
                       void (*destructor)(void *));
```
destructor 清理函数
**获取当前线程的数据**：
```c
void *pthread_getspecific(pthread_key_t key);
```
**删除key**：
```c
int pthread_key_delete(pthread_key_t key);
```
## 第三十二章 线程取消
取消一个线程
```c
pthread_cancle()
```
```c
int pthread_setcancelstate(int state, int *oldstate);
//取消状态
int pthread_setcanceltype(int type, int *oldtype);
//取消类型
```
线程只有在取消点才会检查取消请求
例如sleep（1）
### 32.5 清理函数
```c
pthread_cleanup_push(void (*routine)(void *), void *arg);
pthread_cleanup_pop(int execute);
```
execute 
1 → 执行清理函数
0 → 不执行
