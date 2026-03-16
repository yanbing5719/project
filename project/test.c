//信号处理器
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