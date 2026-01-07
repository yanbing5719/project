## 链表的定义和使用

```c
  

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

  

printf("%s",current->str);

  

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

```
## 加一
这个题不可以先转化为整数再进行加以操作，因为可能导致整数溢出，所以必须在原有的数组上面在直接操作，引入一个新的变量来进行进位操作。
```c
int* plusOne(int* digits, int digitsSize, int* returnSize) {

int *result=(int *)malloc(digitsSize*sizeof(int));

int idx=digitsSize;

if(digits[digitsSize-1]==9){

result[digitsSize-1]=0;

result[digitsSize-2]=digits[digitsSize-2]+1;

}else{

digits[digitsSize-1]=digits[digitsSize-1]+1;

}

for(int i=0;i<digitsSize;i++){

result[i]=digits[i];

}

*returnSize=digitsSize;

return result;

}
```
## 最接近的三数之和
```c
int threeSumClosest(int* nums, int numsSize, int target) {

for(int i=0;i<numsSize-1;i++){

for(int j=0;j<numsSize-1-i;j++){

if(nums[j]>nums[j+1]){

int t=nums[j];

nums[j]=nums[j+1];

nums[j+1]=t;

}

}

}

int sum1=0,sum=nums[0]+nums[1]+nums[2];

int min=INT_MAX;

for(int i=0;i<numsSize-2;i++){

int start=i+1,end=numsSize-1;

while(start<end){

sum=nums[start]+nums[end]+nums[i];

int object=abs(sum-target);

if(object<min){

min=object;

sum1=sum;

}

if(sum<target){

start++;

}else if(sum>target){

end--;

}else{

return target;

}

}

}

return sum1;

}
```
**要点**：不断向目标值逼近，利用双指针的方式，每次根据与目标值的偏差移动开始或者结尾一个指针