# 第四章
## 字符串
用双引号引起来的内容叫字符串字面量（字符串常量），编译器为其末尾自动加入“\0"。字符串常量属于静态存储类别，用双引号引起来的内容被视为指向字符串位置的指针。
- 字符数组和字符串
```c
\\字符数组,结尾编译器不会再加一个终止符。而且不能用字符串函数。
char p1[] = { 'W', 'e', 'l', 'c', 'o', 'm', 'e'};
\\字符串，结尾编译器会再加一个终止符。（特殊的字符数组）
char p2[] = "Join us\0";字符串字面值，编译器为其再加一个'\0'
char p1[] = { 'W', 'e', 'l', 'c', 'o', 'm', 'e','\0'};字符数组初始化，需手动添加'\0';
```
## 字符串函数
- 1.sizeof 是一个编译时运算符，以字节为单位返回类型或值的大小，它计算的是类型或变量的总字节数，包括数组中的所有元素（包括结尾的 \0）。sizeof 运算符的返回值类型是 size_t（无符号整型）！
- 2.strlen 是一个库函数，用来计算字符串（以 \0 结尾的字符数组）的长度，不包括结尾的 \0。strlen返回值类型也是size_t。
- 3.strcpy复制字符串，不检查目标缓冲区的大小，容易造成缓冲区溢出
- 4.strncpy 与strcpy类似，但是会限制复制长度
- 5strcmp 比较ascall码，遇到不一样或者其中一个结束

## printf` 函数的**返回值**和**输出内容**是两个完全不同的概念，主要区别如下：
### 1. 本质不同
- **输出内容**：是 `printf` 函数向标准输出设备（通常是屏幕）打印的**可见字符序列**，由格式字符串（双引号引起来的内容）和对应参数决定。  
  例如 `printf("a=%d", 10)` 的输出内容是屏幕上显示的 `a=10`。

- **返回值**：是 `printf` 函数执行成功后**返回的一个整数**，表示本次调用实际打印的**字符总数**（包括所有字符，如数字、字母、符号、空格、换行符 `\n` 等），如果错误返回负数。  
  例如 `printf("a=%d", 10)` 输出的 `a=10` 共 4 个字符（`a`、`=`、`1`、`0`），因此返回值为 `4`。
  ### 2. 用途不同
- **输出内容**：是函数的**主要功能**，用于向用户展示信息（如数据、提示文本等），是直观可见的结果。
  
- **返回值**：是函数执行状态的**辅助反馈**，主要用于程序内部判断输出是否成功（例如返回值为负数时表示输出失败，通常由错误导致）。  
  例如：
  ```c
  int ret = printf("test");
  if (ret < 0) {
      // 输出失败的处理逻辑
  }
  ```
  ### 3. 表现形式不同
- **输出内容**：直接显示在标准输出设备（屏幕）上，是用户能直接看到的字符串。
  
- **返回值**：不会主动显示，需要通过变量接收后显式打印才能看到。  
  例如：
  ```c
  int num = printf("hello"); // 输出 "hello"，返回值 5 存储在 num 中
  printf("\n返回值是：%d", num); // 显式打印返回值，输出 "返回值是：5"
  ```
### 总结
- `printf` 的**输出**是“打印到屏幕的内容”，是函数的核心功能，用于信息展示。  
- `printf` 的**返回值**是“打印的字符总数”（或错误标识），是函数的执行结果反馈，用于程序内部判断。  

两者没有直接关联，返回值不包含输出内容本身，仅表示输出内容的长度（成功时）。
## printf中的标记
|标记 | 名称 | 功能描述 | 语法示例 | 输出示例 |
|------|------|----------|-----------|----------|
| `-` | **左对齐** | 在指定字段宽度内将输出左对齐，右边填充空格 | `"%-10d"`, 123 | `"123       "` |
| `+` | **总显示符号** | 强制在非负数前也显示正号 (`+`) | `"%+d"`, 123 | `"+123"` |
| ` ` (空格) | **空格符号** | 在正数前保留一个空格，负数前仍显示负号 | `"% d"`, 123 | `" 123"` |
| `0` | **零填充** | 用前导零 `0` 而不是空格来填充字段宽度 | `"%05d"`, 123 | `"00123"` |
| `#` | **替代形式** | 根据转换说明符改变输出格式 | `"%#x"`, 255 | `"0xff"` |
| `*` | **动态宽度** | 字段宽度由函数的参数提供 | `"%*d"`, 5, 10 | `"   10"` |
| `.*` | **动态精度** | 精度由函数的参数提供 | `"%.*f"`, 2, 3.14159 | `"3.14"` |
## 打印字符值超出最大类型时就截取低n位
int截取32位即4*8（比特）
char 类型的336 打印%c
0000000101010000   取低八位 对256取余=80  就是P
## scanf
返回成功读取的项数，没有读取任何值或类型不匹配，返回0
%d  从第一个非空白字符开始读取,直到遇到非数字字符
%s 读取没有空白字符的字符串
%*d 跳过相应的输出项
scanf("%c ")从第一个非空白字符开始读取，跳过后面所有空白字符，直到遇到非空白字符
scanf("  %c")跳过所有前导字符，从第一个非空白字符开始读取
scanf("%c")不会跳过空白字符

## 习题
 ```c
#include <stdio.h>
#include <string.h>
int main(void) {
  char str1[10];
  char str2[10];
  scanf("%s %s",str1,str2);
  printf("%s %s\n",str1,str2);
  int len1=strlen(str1);
  int len2=strlen(str2);
 printf("%*d%*d\n",len1,len1,len2,len2);
 printf("%s %s\n",str1,str2);
 printf("%-*d%-*d",len1,len1,len2,len2);
return 0;
}
zahngsan wangwu
zahngsan wangwu
       8     6
zahngsan wangwu
8       6  
```
```c
#include <stdio.h>
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
}
FLT_DIG=6  //float从6位开始精度缺失
DBL_DIG=15  //double从15位开始缺失
0.333333 0.333333
0.333333333333 0.333333343267
0.3333333333333333 0.3333333432674408
```
```c
#include <stdio.h>
#define GALLON 3.785
#define MILE 1.609
int main(){
double distance,gas;
scanf("%lf%lf",&distance,&gas);
double ame=distance/gas;
double eng=(gas * GALLON * 100.0) / (distance * MILE); 
printf("%f\n%f",ame,eng);
}
return 0;
```
# 第五章
## 左值和右值
复制表达语句的目的是把值储存到内存位置上，储存值的数据储存区为数据对象
- 左值（不能被const修饰）
用于标识或定位储存位置的标签通常出现在赋值运算符的左边，代表一个可修改的内存位置，有标识符（通常有名字）。
- 右值
只能出现在赋值运算符右边的表达式，通常是临时值或字面量。
## 除法运算
浮点数除法是浮点数，整数除法是整数
整数除法时小数部分被截掉（截断）不会四舍五入，直接截掉后面的数
## 取模运算%
第一个运算对象时负数，结果就为负数，如果是正数，结果就为正数
## a++和++a
p=2*a++   2先乘a  a再++
q=2*++a     a先++再乘以2
## 类型转换
- 升级
当混合类型出现在表达式里面时，会从较小类型转化为较大类型
char short 升级为int   int float升级为double
- 降级
在某些赋值表达式中，结果会被转化为被赋值的变量的类型，可能会造成降级
float 23.12降级为int 会截断小数部分
## 习题
```c
#include <stdio.h>
int main() {
	int num; int week;
	int day;
	scanf("%d", &num);
	while (num > 0) {
		week = num / 7;
		day = num % 7;
		printf("%d days are %d weeks,%d days.", num,week,day);
		scanf("%d", &num);
	}
	return 0;
}
```
```c
#include <stdio.h>
void temperatures(double num) {
	const double ZHUANHUAN = 5.0 / 9.0;
	const double JIESHU = -32.0;
	const double KAISHI = 273.16;
	double sheshi = ZHUANHUAN * (num - JIESHU);
	double kelvin = sheshi + KAISHI;
	printf("huashi=%.2f\n", num);
	printf("sheshi=%.2f\n", sheshi);
	printf("kelvin=%.2f\n", kelvin);
}
int main() {
	double num; 
	while (scanf("%lf", &num)==1) {
		temperatures(num);
	}
	while (getchar() != '\n') 
		continue;
		
	return 0;
}
```
## 第六章
```c
#include <stdio.h>
int main() {
	for (int i = 0; i < 4; i++) {
		if (i != 0) {
			printf("\n");
		}
		for (int j = 0; j < 8; j++) {
			printf("$");
		}
	
	}
}
```
```c
#include <stdio.h>
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		if (i != 0) {
			printf("\n");
		}
		for (int j = (2 * n - 1) / 2; j >i; j--) {
			printf(" ");
		}
		for (char k = 'A'; k < 'A' + i; k++) {
			printf("%c", k);
		}
		for (char c = 'A' + i ; c >= 'A'; c--) {
			printf("%c", c);
		}
		
	}
	
    A
   ABA
  ABCBA
 ABCDCBA
ABCDEDCBA
```
```c
#include <stdio.h>
#define DUNBAR 150
int main() {
	int friend = 5;
	int week = 1;
	while (friend <= DUNBAR) {
		friend = friend - week;
		friend *= 2;
		week++;
		if (friend > DUNBAR) {
			break;
		}
			printf("%d\n", friend);
	}
}
```
# 第七章
## continue(只适用于循环）
continue语句，跳过本次循环开始下一轮迭代，嵌套在循环里面时，只会影响包含该语句的内层循环。
## break（可用于循环和switch)
break会终止包含他的程序，并执行下一阶段，嵌套在循环里面时，只会影响包含该语句的内层循环。
## switch()测试的表达值必须是一个整数值（包括char类型）
## goto(直接跳转到指定语句） 
goto label;
.
.
lable : statement
## 习题
```c
#include <stdio.h>
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
}
```
```c
#include <stdio.h>
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
}
```
```c
#include <stdio.h>
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
}
```
# 第八章
## 缓冲区（将字符作为块传输比逐个发送节约时间，如果打错也可以修正）
回显用户输入的字符后立即重复打印该字符是无缓冲输入
用户输入的字符被收集储存在缓冲区，按下ENTER后程序才可以使用用户输入的字符(**最麻烦的是要处理换行符**）
- 完全缓冲
缓冲区被填满时刷新缓冲，通常在文件输入中
- 行缓冲
出现换行符时刷新缓冲（键盘输入）
## c语言中getchar()，scanf()读取文件检测到*文件结尾*返回EOF(-1),
键盘上输入EOF，一般通过ctrl+D 或者ctrl+Z
## 重定向
允许我们改变程序的输入来源和输出目的地。
- 输出重定向 
\> 覆盖文件（将程序的输出保存到文件（如果文件已存在，会覆盖原有内容）
\>> 追加到文件（将程序的输出追加到文件末尾（不会覆盖原有内容））
- 输入重定向
\< 从文件读取 （让程序从文件读取输入，而不是从键盘）
-组合重定向
evho_eof\<mywords>sayewords
-注意事项
只能连接一个可执行数据和数据文件
不能读取多个文件的输入，不能把输出定向多个文件
## 输入实际上是字节流（将其看为字符编码），由字符组成，scanf()可以把输入转换为指定的类型，getchar() %c的scanf() 接受所有字符
例如 %d   %f 限制可接受字符类型
scanf("%c") 会读取空白字符 - 包括空格、制表符、换行符
    scanf("  %c") 会跳过空白字符 - 开头的空格使其跳过所有前导空白，只读取第一个非空白字符
    **菜单程序中的"接受所有字符" 实际上是因为**：
     使用了 scanf(" %c") 跳过前导空白
   或者通过 getchar() 清空了输入缓冲区
 或者程序逻辑本身就允许空白字符作为有效输入
 ## 习题
 ```c
 #include <stdio.h>
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
```
```c
#include <stdio.h>
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

}
```
```c
#include <stdio.h>
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
}
```
# 第九章
## 形式参数和实际参数
- 黑盒视角下，主函数和定义的函数互不影响，形参和实参互不影响，如果主函数和定义的函数中有相同的变量，也是互不影响的
- 形式参数的作用域只在函数内部
## 设计被用于测试函数的程序被称为驱动程序
## 递归
函数自己调用自己，使用循环的地方都可以使用递归，**结束递归**是递归的难点
- 1.每级函数调用都有自己的变量
- 2.每一次调用函数都会返回一次。函数执行完毕后，控制权被传回上一级递归
- 3.函数中位于递归调用之后的语句，按相反顺序执行
- 4.递归可以与循环互换
- 5.必须包含能让递归终止的条件
- 优点
为某些题提供简单的解决方案
- 缺点
难以理解，耗费巨大的内存
## 习题
```c
#include <stdio.h>
#include <ctype.h>
int character(char ch);
int main() {
	printf("输入字符，以ctrl+D结束");
	char ch;
	int position;
   while ((ch = getchar()) != EOF) {
		if (ch == '\n') {
			continue;
		}
		position=character(ch);
		printf("%d", position);
	}
   return 0;
}
int character(char ch) {
	
	if(isalpha(ch)){
		if (islower(ch)) {
			return  ch - 'a' + 1;
		}
		else {
		return ch - 'A' + 1;
		}
		}
	return -1;
}
```
```c
#include <stdio.h>
void to_base_n(unsigned long num, int n);
int main() {
	int n ;
	unsigned long num;
	while (scanf("%d %d", &num, &n) == 2) {
		if (n < 2 || n > 10) {
			printf("重新输入");
			continue;

		}
		to_base_n(num, n);
	}
}
void to_base_n(unsigned long num, int n) {
	int r;
	r = num % n;
	if (num >= n) {
		to_base_n(num / n, n);
	}
	putchar(r+'0');
}
```
```c
#include <stdio.h>
double average(double, double);
int main() {
	double a, b;
	scanf("%lf %lf", &a, &b);
	double c = average(a,b);
	printf("%lf", c);
}
double average(double a, double b) {
	double average1 = (1 / a + 1 / b) / 2;
	double average2 = 1 / average1;
	return average2;
	
}
```
# 第十章
## 间接运算符（*）优先级高于（+）
*（date+2) date第三个元素
*date+2,第一个元素再加2.
## 空指针和野指针
 - 空指针：不指向任何有效内存地址的指针，通常用来初始化指针。解引用空指针会导致未定义行为，通常是程序崩溃。
 - 野指针：指向无效内存位置的指针。
未初始化指针  指向的内存被释放  局部变量作用域结束<返回函数里面的地址>
## 只有在函数原型或函数定义头中，才可以用 int arr[ ]代替int *arr. int arr[ ]只能用于声明形式参数。
## ++优先级高于*
```c
total+=*start++;        *（start++）
start++先求值，再指向
total+=*++start；
先递增指针，再指向
total+=（*start)++;
先使用start的值，再递增这个值
```
## 只有程序需要在函数中改变该数值时，才会传递指针。处理数组的函数通常需要用原始数据，这样函数才可以修改原始数组
## const 相关内容
- 指向const 的指针通常用于函数行参中，表明函数不会使用指针改变数据
 const double * P =3;
 - 把const数据或者非const数据的地址初始化为指向const的指针或为其赋值是合法的
 ```c
 double rate=5;
 const double lock=7;
 const double *p=&rate;
 p=&lock;
 ```
- 对函数的行参使用const不仅能保护数据，还能让函数处理const数组
- 声明并初始化一个不能指向别处的指针
```c
double *const ptr1 = &p1;
```
- 使用两次const使其不能改变指向的地址，也不能修改指向地址上的值
```c
const double * const ptr3 = &p3;
```
## 指针数组和数组指针
```c
int a[2] = {4, 8};  //数组
int(*b)[2] = &a;  //数组指针   指向内含两个int 变量的指针
 int *c[2] = {a, a + 1};  //指针数组  内含两个int 类型指针的数组
 []的优先级高于*
```
## 变长数组
变长数组不能改变已创建数组的大小，只能用变量指定数组的维度
```c
int sun(int rows,int cols,int arr[rows][cols]){
    int r,c;
    int tot=0;
    for(r=0;r<rows;r++){
        for(c=0;c<cols;c++){
            tot+=arr[r][c];
        }
    }
    return tot;
}
```
## 复合字面量
```c
int arr[2]={10,20}
(int [2]){10,20} //复合字面量  int [2]复合字面量的类型名，2可以省略
int *p;
p=(int [2]){10,20} ;
```
把信息传入函数前不必先创建数组
## 习题
```c
int max(double arr[],int n){
    double max=arr[0];
    int m=0;
     for(int i=0;i<n;i++){
        if(arr[i]>max){
            max=arr[i];
         m=i;
        }
     }
     return m;
}
```
```c
void copy1(double target1[],double source[],int n){
    for(int i=0;i<n;i++){
        target1[i]=source[i];
    }
}
void copy2(double * target2,double *source,int n){
      for(int i=0;i<n;i++){
        *(target2+i)=*(source+i);
      }
}
void copy3(double * target3,double *start,double*end){
    while(start<end){
        *target3=*start;
        target3++;
        start++;
    }
}
```
```c
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
double average_all(double arr1[][5], int n)
{
    if (n <= 0) return 0.0;
    double sum = 0.0;
    int num = n * 5;
    
   for(int i=0;i<n;i++){
        for(int j=0;j<5;j++){
            sum += arr1[i][j];
        }
    }
    
    return sum/num;
}
double MAX(double arr1[][5], int n){
    double max=arr1[0][0];
    for(int i=0;i<n;i++){
        for(int j=0;j<5;j++){
            if(arr1[i][j]>max){
                max=arr1[i][j];
            }
        }
    }
    return max;
}
void print(double arr1[][5], int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<5;j++){
            printf("%lf",arr1[i][j]);
        }
    }
}
```
# 第十一章
## 字符串函数
- 1.strcmp(p1, p2) 用来比较两个字符串，比较ACALL码。它逐个字符地比较 p1 和 p2，直到遇到不同的字符或字符串结束符 \0。如果字符串相等，strcmp 返回0；如果不同，则返回非零值（p1>p2)返回正值，（p1<p2)返回负值。
- 2strncmp 可以比较到指定的字符数strcmp(p1, p2,5)只比较到第五个字符
- 2.sizeof 是一个编译时运算符，它计算的是类型或变量的总字节数，包括数组中的所有元素（包括结尾的 \0）。sizeof 运算符的返回值类型是 size_t！
- 3.strlen 是一个库函数，用来计算字符串（以 \0 结尾的字符数组）的长度，不包括结尾的 \0。strlen返回值类型也是size_t。
- 4.strcpy复制字符串，不检查目标缓冲区的大小，容易造成缓冲区溢出（声明数组分配储存数据的空间，声明指针只分配一个地址的空间）
- 5.strncpy 与strcpy类似，但是会限制复制长度
- 6 strcat 拼接字符串strcat(p1,p2)将p2的内容拼接到p1后面，无法检测p1空间够不够。
- 7.strncat  strncat(p1,p2,13),限制最大字符数

## 字符串
用双引号引起来的内容叫字符串字面量（字符串常量），编译器为其末尾自动加入“\0"。字符串常量属于静态存储类别（储存在数据段），用双引号引起来的内容被视为指向字符串位置的指针。
字符串储存在静态储存区，程序开始运行时为其分配内存，将字符串拷贝到数组中，此时字符串有两个副本，一个是字符串字面量，一个是数组中的字符串。
**初始化数组把静态储存区的字符串拷贝到数组中，初始化指针把字符串的地址拷贝给指针。**
**字符串字面量是const数据**
- 字符数组和字符串
```c
\\字符数组,结尾编译器不会再加一个终止符。而且不能用字符串函数。
char p1[] = { 'W', 'e', 'l', 'c', 'o', 'm', 'e'};
\\字符串，结尾编译器会再加一个终止符。（特殊的字符数组）
char p2[] = "Join us\0";字符串字面值，编译器为其再加一个'\0'
char p1[] = { 'W', 'e', 'l', 'c', 'o', 'm', 'e','\0'};字符数组初始化，需手动添加'\0';
```
- 用指针和数组声明数组的区别
```c
char p2[] = "Join us";
char * p1="Join us";
```
只有指针可以进行自增  putchar(*(p1++))
不修改字符串，不要用指针指向字符串字面量。
-用指针数组和多维数组
```c
const *p1[2]={"abcd","defg"};
char p2[2][4]={"abcd","defg"};
```
单纯显示字符串，用指针数组，效率高。改变字符串用多维数组。
## gets()   puts函数
gets
读取整行输入，直到遇到换行符，再丢弃换行符。但是无法检测数组是否能装的下行，可能导致缓冲区溢出
 puts 函数
stdio.h系列的输出函数，只显示字符串，遇到空字符停止输出，末尾自动补换行符。
## fgets()  fputs()
fgets(str,5,stdin)  fgets将限制读入的字符数，或遇到第一个换行符停止，且将换行符储存
fputs(str,stdout)不会加换行符，返回指针，如果顺利，返回的地址与第一个参数相同。如果读到文件末尾，返回**空指针**
## gets_s()
gets_s(str,5)
在没有超出最大字符数时，与gets()一样
超出时，把首字符设置为i空字符，读取并丢弃随后输入直至读到换行符或者文件结尾，然后返回**空指针**

