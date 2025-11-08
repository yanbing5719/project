
#include <stdio.h>

#include <string.h>

#include <stdlib.h>

struct film{

char str[45];

struct film * nest;

};

char * s_gets(char *st,int n);

int main(){

struct film *head=NULL;

struct film *prev=NULL;

struct film *current;

char input[45];
puts("please input film name");

while(s_gets(input,45)!=NULL&&input[0]!='\0'){

current=(struct film *)malloc(sizeof(struct film));
strcpy(current->str,input);//初始化新节点
current->nest = NULL;
if(head==NULL){
head=current;
}else{
prev->nest=current;
}
prev=current;
}
current=head;
while(current!=NULL){

puts(current->str);

current=current->nest;

}
current =head;
while(current!=NULL){
    struct film *temp=current;
    current=current->nest;
    free(temp);
}
head=NULL;
return 0;

}

  



char * s_gets(char *st,int n){

char *ret_val;

char *find;

ret_val=fgets(st,n,stdin);

if(ret_val){

find=strchr(st,'\n');

if(find){

*find='\0';

}

else{

while(getchar()!='\n'){

continue;

}

}

}

return ret_val;

}
