
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
#include <stdio.h>
#include <stdlib.h>
typedef struct list{
  int data;
  struct list *next;
  struct list *pre;
}l;
int main(){
 l*head=creat( );
}
//循环链表
l*creat( ){
  l*head,*tail;
  head=(l*)malloc(sizeof(l));
  head->next=head;
  tail=head;
  int x;
  while((scanf("%d",&x))!=EOF){
    l*node=(l*)malloc(sizeof(l));
    node->data=x;
    node->next=head;
    tail->next=node;
    tail=node;
  }
  return head;
}
void input(l*head){
  l*current=head->next;
  while(current!=head){
    printf("%d ",current->data);
    current=current->next;
  }
}
void add(l*head,int key,int value){
  l*p=head->next;
  while(p!=head){
  if(p->data==key){
    l*node=(l*)malloc(sizeof(l));
    node->data=value;
    node->next=p->next;
    p->next=node;
  }
  p=p->next;
    }
}
void delete(l*head,int key){
  l*pre=head;
  l*p=head->next;
  while(p!=head){
    if(p->data==key){
      pre->next=p->next;
      free(p);
      return ;
    }
    pre=p;
    p=p->next;
  }
}
void freelist(l*head){
  l*current=head;
  while(current!=head){
    l*temp=current;
    current=current->next;
    free(temp);
  }
}
//双向链表（头节点和首元节点不一样）
l*creat1(){
  l*head=(l*)malloc(sizeof(l));
  if(!head){
    perror("malloc filed");
    exit(1);
  }
  head->pre=NULL;
  head->next=NULL;
  return head;
}
void tailadd(l*head){
   l*p=head;
   while(p->next!=NULL){
    p=p->next;
  }
  int x;
    while(scanf("%d",&x)!=EOF){
    l*node=(l*)malloc(sizeof(l));
    node->data=x;
    node->next=NULL;
    node->pre=p;
    p->next=node;
    p=node;
    }
   }
void headadd(l*head){
  int x;
  while(scanf("%d",&x)!=EOF){
     l*node=(l*)malloc(sizeof(l));
    node->data=x;
    node->next=head->next;
    if(head->next!=NULL){
    head->next->pre=node;
    }
    node->pre=head;
    head->next=node;
  }
}
void backspace(l*head,int key){
      l*p=head;
      l*cur=head->next;
      while(cur!=NULL){
        if(cur->data==key){
        p->next=cur->next;
        if(cur->next!=NULL){
        cur->next->pre=p;
        }
        free(cur);
        break;
        }
        p=cur;
        cur=cur->next;
      }
}
void freelist(l*head){
  l*current=head;
  while(current!=NULL){
    l*temp=current;
    current=current->next;
    free(temp);
  }
}
