/*#include <stdio.h>
#include<float.h>
int main(void) {
 double a=1.0/3.0;
 float b=1.0/3.0;
 printf("FLT_DIG=%d\n",FLT_DIG);
 printf("DBL_DIG=%d\n",DBL_DIG);
 printf("%.6f %.6f\n",a,b);
 printf("%.12f %.12f\n",a,b);
 printf("%.16f %.16f\n",a,b);
return 0;
}*/
/*#include <stdio.h>
#define GALLON 3.785
#define MILE 1.609
int main(){
double distance,gas;
scanf("%lf%lf",&distance,&gas);
double ame=distance/gas;
double eng=(gas * GALLON * 100.0) / (distance * MILE); 
printf("%f\n%f",ame,eng);
}*/
/*#include <stdio.h>
#include <ctype.h>
int main(){
    char ch;
    scanf("%c",&ch);
    if(islower(ch)){
        printf("%c",ch);
    }
    else {
        printf("false");
    }
}*/
/*#include <stdio.h>
int main(){
    char ch;
    int num=0;
    while((ch=getchar())!='#'){
        num++;
        printf("%d ",ch);
        if(num%8==0){
            printf("\n");
        }
    }
}*/
/*#include <stdio.h>
int main(){
     char ch;
    int num=0;
    while((ch=getchar())!='#'){
        switch(ch){
            case '.':
            putchar('!');
            num++; break;
            case '!':
            putchar('!');
            putchar('!');
            num++;
            default: putchar(ch);
        }
    }
    return 0;
}*/
/*#include <stdio.h>
#define BASE_HOURS 40
#define MORE_HOURS 1.5
#define RATE1 0.15
#define RATE2 0.2
#define RATE1 0.25
#define ARATE1 300
#define ARATE2 150
#define PAY_RATE1 8.75
#define PAY_RATE2 9.33
#define PAY_RATE3 10.00
#define PAY_RATE4 11.20
void menu(void);
int main(){
    
    int n;
    double pay_rate,pay,shuijing,pure_money;
    scanf("%d",&n);
    while(1){
        void menu();
        if(scanf("%d",&n)!=1){
            rintf("please input number fron 1 to 5");
        }
        if(n==5){
            break;
        }
    }
    
    while(1){
    switch(n){
        case 1:pay_rate=PAY_RATE1;break;
        case 2:pay_rate=PAY_RATE2;break;
        case 3:pay_rate=PAY_RATE3;break;
        case 4:pay_rate=PAY_RATE4;break;
        default : printf("please input number fron 1 to 5");
        continue;
    }
}
}

void menu(void){
 printf("*****************************************************************");
 printf("Enter the number corresponding to the desired pay rate or action");
 printf("1) $%.2f/hr        2) $%.2f/hr",PAY_RATE1,PAY_RATE2);
 printf("3) $%.2f/hr        4.) $%.2f/hr",PAY_RATE3,PAY_RATE4);
 printf("5) quit");
 printf("*****************************************************************");
}
double calculate_gross_pay(double pay_rate, double hours) {
    if (hours > BASE_HOURS) {
        return BASE_HOURS * pay_rate + 
               (hours - BASE_HOURS) * pay_rate * MORE_HOURS;
    } else {
        return hours * pay_rate;
    }
}

double calculate_taxes(double gross_pay) {
    double taxes = 0.0;

    if (gross_pay > ARATE1 + ARATE2) {
        // 超过450的部分税率25%
        taxes = ARATE1* ARATE1 + 
               ARATE2 * ARATE2+ 
                (gross_pay - TAX_BRACKET1 - TAX_BRACKET2) * TAX_RATE3;
    } else if (gross_pay > TAX_BRACKET1) {
        // 300-450的部分税率20%
        taxes = TAX_BRACKET1 * TAX_RATE1 + 
                (gross_pay - TAX_BRACKET1) * TAX_RATE2;
    } else {
        // 300以内的部分税率15%
        taxes = gross_pay * TAX_RATE1;
    }*/
   /*#include <stdio.h>
   int isprime(int n);
   int main(){
     int n;
     scanf("%d",&n);
     for(int i=2;i<n;i++){
        if(isprime(i)){
            printf("%d  ",i);
        }
     }
     return 0;
   }
int isprime(int n){
    if(n<=1)return 0;
    if(n==2)return 1;
    if(n%2==0)return 0;
    for(int i=3;i*i<=n;i+=2){
        if(n%i==0){
            return 0;
        }
    }
    return 1;
}*/
/*#include <stdio.h>
#include <ctype.h>
int main(){
    int ch;
    int upper=0,lower=0;
    printf("请输入字符，用ctrl+D结束输入\n");
    while((ch=getchar())!=EOF){
        if(isupper(ch)){
        upper++;
    }
     else if(islower(ch)){
        lower++;
     }
    }
    printf("upper=%d\n",upper);
    printf("lower=%d\n",lower);
    return 0;
}
*/
/*#include <stdio.h>
int main(){
    int guess=50;
    int lower=1,upper=100;
    char ch;
    printf("is your number is %d?",guess);
    while((ch=getchar())!='='){
         if(ch=='>'){
              upper=guess;
              guess=(upper+lower)/2;
              printf("is your number is %d?",guess);
         }else if(ch=='<'){
            lower=guess;
            guess=(upper+lower)/2;
            printf("is your number is %d?",guess);
         }
    }
    printf("number is %d",guess);
    return 0;

}*/
/*#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
int main(){
    printf("请输入单词,用ctrl+D结束输入\n");
    int ch;
    bool inword=false;
    int words=0;
    while((ch=getchar())!=EOF){
      if(!isspace(ch)&&!(inword)){
        inword=true;
        words++;}
        else if(isspace(ch)&&inword){
            inword=false;
            
        }
      
    }
    printf("\nwords=%d",words);
}*/
// int sun(int rows,int cols,int arr[rows][cols]){
//     int r,c;
//     int tot=0;
//     for(r=0;r<rows;r++){
//         for(c=0;c<cols;c++){
//             tot+=arr[r][c];
//         }
//     }
//     return tot;
// }
// int max(double arr[],int n){
//     double max=arr[0];
//     int m=0;
//      for(int i=0;i<n;i++){
//         if(arr[i]>max){
//             max=arr[i];
//          m=i;
//         }
//      }
//      return m;
// }
// int main(){
//     double arr[4]={2.0,5.0,1.0,6.0};
//     int a=max(arr,4);
//     printf("%d",a);
// }
// void copy1(double target1[],double source[],int n){
//     for(int i=0;i<n;i++){
//         target1[i]=source[i];
//     }
// }
// void copy2(double * target2,double *source,int n){
//       for(int i=0;i<n;i++){
//         *(target2+i)=*(source+i);
//       }
// }
// void copy3(double * target3,double *start,double*end){
//     while(start<end){
//         *target3=*start;
//         target3++;
//         start++;
//     }
// }
#include <stdio.h>
void input(double arr1[][5],int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<5;j++){
            scanf("%lf",&arr1[i][j]);
        }
    }
}
void average(double arr1[][5],double result[],int n){
   
     for(int i=0;i<n;i++){
         double sum=0;
        for(int j=0;j<5;j++){
         sum+=arr1[i][j];
        }
        result[i]= sum/5.0;
    }

}

int main(){
    double arr1[][5]={0};
    int n=5;
    double result[3];
    void input(arr1,n);
     average(arr1,result,n);
}