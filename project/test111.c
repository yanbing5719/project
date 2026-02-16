#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main(){
   int x=10;
   pid_t child=fork();
   if(child==0){
    x=20;
    printf("%d\n",x);
   }else{
    x=30;
    printf("%d\n",x);
   }
   return 0;
}