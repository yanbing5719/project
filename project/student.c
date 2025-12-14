#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdio.h>
/*
int main(){
    int mem[]={
        3,10,3,7,3,8,5,7,6,7,2,3,3,9,9,
        3,0,8,1,5,8,1,5,2,2,8,1,6,7,0,-15,6,7,9,
        2,10,4,6,-1,-1,-1,-1,38,7,9,10,11,
        0,0,0,0,0,0,0,0,
    };
    int *p=mem;
    int *s=mem+sizeof(mem)/sizeof(int)-1;
    int a=0;
    for(;;){
        switch(*p++){
        case 0:if(!--*s)break;
        case 1:p+=*p;break;
        case 2:s-=*p++;break;
        case 3:*--s=0;
        case 4:*s+=*p++;break;
        case 5:s[1]+=s[0];
        case 6:s++;break;
        case 7:printf("%d",*s);break;
        case 8:a=s[0];s[0]=s[*p];s[*p++]=a;break;
        case 9:printf("\n");break;
        case 10:
            for(int i=0;i<8;i++){
                printf("%d,",mem[sizeof(mem)/sizeof(int)-8+i]);
                if(i==3){printf("\n");}
            }
            printf("\n");
            break;
        case 11:
            return 0;
        }
    }
}
*/

/*typedef struct student{
    int id;
    char name[20];
    float score[3];
}stu;
void input (stu st[],int n);
void output(stu st[],int n);
void sort(stu st[],int n);
void search(stu st[],int n,int num);
int main(){
    stu st[10];
    int n;
    int num;
    scanf("%d",&n);
    scanf("%d",&num);
   input (st,n);
   output(st,n);
   sort(st,n);
   search(st,n,num);

   return 0;
}
void input (stu st[],int n){
    for(int i=0;i<n;i++){
       scanf("%d  %s",&st[i].id,&st[i].name);
       for(int j=0;j<3;j++){
        scanf("%f",&st[i].score[j]);
       }
    }
}
void sort(stu st[],int n){
   float average[3];
   for(int i=0;i<n;i++){
    float sum=0;
   for(int j=0;j<3;j++){
    sum+=st[i].score[j];
   }
   average[i]=sum/3;
   }
   for(int i=0;i<n-1;i++){
    for(int j=i+1;j<n;j++){
        if(average[i]>average[j]){
            int t=st[i].id;
            st[i].id=st[j].id;
            st[j].id=t;
            float t1=average[i];
            average[i]=average[j];
            average[j]=t1;
            char t2[20];
            strcpy(t2,st[i].name);
            strcpy(st[i].name,st[j].name);
            strcpy(st[j].name,t2);
        }
    }
   }
   output(st,n);
}
void search(stu st[],int n,int num){
        int i=num-1;
     printf("%d  %s  ",st[i].id,st[i].name);
     for(int j=0;j<3;j++){
        printf("%f ",st[i].score[j]);
    }
    printf("\n");
    
}
void output(stu st[],int n){
    for(int i=0;i<n;i++){
    printf("%d  %s  ",st[i].id,st[i].name);
    for(int j=0;j<3;j++){
        printf("%f ",st[i].score[j]);
    }
    printf("\n");
   }
   printf("\n");
}*/

