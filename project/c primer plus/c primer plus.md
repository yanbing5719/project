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
