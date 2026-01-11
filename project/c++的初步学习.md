# 基本框架
```c
#include "iostream"
using namespace std
itn main( ){
return 0;
}
```
# 头文件
#include "iostream"
c++里面头文件基本都是c......  例如*< cmath >
# 输入和输出
```c
int num=-1;
char c='a';
cin>>num>>c;
cout<<num<<c<<endl;//endl为换行
```
不用说明输入和输出格式
# 基本数据类型
c语言和c++基本数据类型几乎都一样
只有bool类型在c++中不需要头文件，可以用boolapha打印ture和false;
```c
bool cmpare(int a,int b){
return a>b;
}
cout<<boolalpha<<compare(2,3)<<endl;
//输出false.
```
# 强弱类型
c语言：强类型，弱检查
```c
void *p=NULL;
int *p1=p;
int *p2=NULL;
void *p3=p2;
```
该程序不会报错
c++强类型，弱检查
```c
void *p=NULL;
int *p1=p;
//类型不符，void无法直接转为其他类型，必须强制转换
p=(int *)p;//正确

int *p1=NULL;
void *p2=p1;
//任意类型的均可以转化为void类型
```
NULL在c语言里面打印出来是0,但是nullptr会编译错误类型不符，更加安全。
# const
const在c语言里面只是表示const修饰的变量为只读变量，并不是一个常量，但是在c++里面是常量
c语言(const修饰的变量被放在栈区）
```c
const int n=18;
int arr[n]; //此处编译器会报错，const 不是常量
int *p1=&n;
*p1=20;
printf("%d",n);
//此处n的值被间接修改为20。
```
c++（const是常量，被放在堆区）
```c
const int n=90;
int arr[n];
//可以正常编译。
int *p1;
(const int *)p1=&n;
*p1=20;
cout<<n<<*p1<<endl;
//此处n还是等于90.但是*p1是20
//p1指向的是n的数据赋值在栈区的地址，不会去改变n原本的值，但是为了和c语言兼容，他会隐藏拷贝过来的地址现实的是堆区的地址，应此&n和p1的地址是一样的。
```
同样的道理对于字符串字面量，在c++里面char *str=“你好”是错误的，必须用const char *.
# 三元运算符
在C语言里面三元运算符返回的是一个数值，不是一个可以修改的左值，但是c++里面返回可以是一个左值，变量。
**c语言**
```c
int a=6;
int b=5;
int c=(a>b?a:b); //正确
(a>b?a:b)=20;  //这种写法在c语言里面具有语法错误
```
```c
int a=6;
int b=5;
int c=(a>b?a:b); //正确
(a>b?a:b)=20;  //这种写法在c++里面同样正确
```
# 引用
c语言里面函数里面改变参数的值要用到指针
```c
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}
int x = 1, y = 2;
swap(&x, &y);
```
c++里面引入引用的概念
```c
int x = 10;
int& r = x;
/*r 是 x 的 别名
r 和 x 指向 同一块内存
对 r 的操作 = 对 x 的操作*/
r = 20;
printf("%d\n", x);  // 20
```
# 函数参数
c语言
```c
void inc(int *x) {
    (*x)++;
}
inc(&a);//调用
```
c++
```c
void inc(int& x) {
    x++;
}
int(a);
//调用直接传入值但是起到了指针的效果
```
函数返回值的区别
c语言
```c
int* f() {
    static int x = 10;
    return &x;
}
//改函数返回的是一个指针
```
c++
```c
int& f() {
    static int x = 10;
    return x;
}
f() = 100;   // 直接修改 x
```
# 函数重载
一般情况下int和double类型的加法运算要写两个名字不同的函数
```c
int Intadd(int a,int b){
    return a+b;
}
double Doubleadd(double a,double b){
    return a+b;
}
```
函数重载可以让两个函数的名字相同（**在同一个作用域内，函数名相同，但参数列表不同，编译器可以根据调用时传入的参数来判断到底调用哪一个函数。**）
```c
nt add(int a,int b){
    return a+b;
}
double add(double a,double b){
    return a+b;
}
int main( ){
int a,b;
   cin>>a>>b;
   int x=add(a,b);
   double c,d;
   cin>>c>>d;
   double y=add(c,d);
}
```
# c++里面namespace 的应用
避免名字冲突
```c
#include <iostream>
using namespace std;
namespace A{
    int x=10;
    void func1();
}
void A::func1(){
    cout<<"hello"<<' ';
}
namespace B{
    int x=20;
    void func2();
}
void B::func2(){
    cout<<"winter vocation"<<endl;
}
int main(){
    cout<<A::x<<' '<<B::x<<endl;
    A::func1();
    B::func2();
    return 0;
}
```

# 结构体定义的区别
```c
#include <iostream>
#include <string>
 using namespace std;
struct student{
    string name;
    int age;
    int score[3];
    void setname(string name1){
        name=name1;
    }
    void setage(int age1){
        age=age1;
    }
    void output(){
            cout<<"name: "<<name<<endl;
            cout<<"age: "<<age<<endl;
        }
    void setscore(int score1[3]){
        for(int i=0;i<3;i++){
            score[i]=score1[i];
        }
    }
    void outputscore(){
        cout<<"chushiscore: ";
        for(int i=0;i<3;i++){
            cout<<score[i]<<' ';
        }
        cout<<endl;
    }
        void paixu(){
            for(int i=0;i<2;i++){
                for(int j=0;j<2-i;j++){
                    if(score[j]>score[j+1]){
                        int temp=score[j];
                        score[j]=score[j+1];
                        score[j+1]=temp;
                    }
                }
            }
            for(int i=0;i<3;i++){
                cout<<score[i]<<' ';
            }
        }
};
int main(){
    student st;
    st.setname("zhangsan");
    st.setage(18);
    st.output();
    int arr[3]={90,80,70};
    st.setscore(arr);
    st.outputscore();
    st.paixu();
    return 0;
}
```
c++可以将函数定义在结构体里面，初始化一般都用函数来实现，定义变量的时候可以不加struct
# string 字符串及其相关函数
- string创建字符串，末尾没有'/0'结尾
```c
string s("hello world");
string s1("nihao");
s=s1;
//可以直接进行复制
```
- 用getline来读取字符串与fgets类似，都是以'\n'结尾，可以读取空格但是getline可以指定结束条件
```c
string s1,s2;
getline(cin,s1);
getline(cin,s2,'a');
```

- 用size计算字符串长度
```c
string s1="hello";
string s2="world ";
cout<<s1.size()<<' '<<s2.size()<<endl;
```

- 迭代器类似于c语言里面对一个字符串设置start 和end 指针
begin( )获得指向第一个字符的指针，end( )获得指向最后一个字符的后一个指针
```c
//用迭代器实现对字符串的遍历
string s1="hello";
string::iterator it1=s1.begin();
string ::iterator it2=s1.end();
cout<<it2-it1<<endl;
while(it1<it2){
cout<<*it1;
it1++;
}
return 0;
```
- push_back( )在字符串末尾插入一个字符
```c
string s1="hello";
cout<<s1<<endl;
s1.push_back(' ');
s1.push_back('w');
s1.push_back('o');
s1.push_back('r');
s1.push_back('l');
s1.push_back('d');
cout<<s1<<endl;
return 0;
```
- string类型的字符串可以直接加法运算
```c
 string s1("hello");
      string s2("world");
      s1+=s2;
      cout<<s1<<endl;
      s2="hello"+s2;
        cout<<s2<<endl;
      return 0;
 ```
 - pop_back 删除末尾字符
  ```c
string s1("hello");
      while(s1.size()>=1){
    s1.pop_back();
      }
      cout<<s1<<endl;
      return 0;
```
- insert在指定位置插入字符串
 ```c
    string s("hello");
      cout<<s<<endl;
      s.insert(1,"xxx");
        cout<<s<<endl;
        s.insert(2,3,'m');
        cout<<s<<endl;
      return 0;
  ```
  - find( ) 返回子串在字符串中第一次出现的起始下标值，未找到返回整数值npos=18446744073709551615
  ```c
 // find 函数的几种常见用法
 string s1="hello nihao l lo niidgllhasyudcllo";
  string s2("llo");
   //size_t n=s1.find(s2);
   //cout<<n<<endl; //2
//    size_t n=s1.find(s2,6);
//    cout<<n<<endl; //12
size_t n=s1.find("llo",6,2);
   cout<<n<<endl; //22
   ```
   - substr( )截取字符串中指定位置字串的长度,通常和find函数一起用
   ```c
     string s1="hello nihao";
    size_t n=s1.find("ni");
   string s3=s1.substr(n,2);
   cout<<s3;//ni
   ```
-  string 关系运算(至少有一个string类型的字符串才可以比较）类似于strcmp比较ascall码
```c
  string s1("hello");
    string s2=" world";
    string s3("hello world");
     if(s1==s2){
        cout<<"no"<<endl;
     }
     if(s3==s1+s2){
        cout<<"yes"<<endl;
     }
     return 0;
  ```
# swap函数
```c
//数组的交换
 int arr1[5]={1,2,3,4,5};
  int arr2[5]={6,7,8,9,10};
  swap(arr1,arr2);
   for(int e:arr1){
        cout<<e<<' ';
   } //“从 arr1 中依次取出每一个元素，赋值给变量 e”,经常用于数组和for循环
 ```

# 运算符的重载
 ```c
 struct student{
    string name;
    int age;
    int score[3];
};
ostream& operator<<(ostream &os,const student &st){
    os<<st.name<<endl;
    os<<st.age<<endl;
    return os;
}
istream& operator>>(istream &is,student &st){
    is>>st.name;
    is>>st.age;
    return is;
}       
int main(){
    student st;
    cin>>st;
   cout<<st<<endl;
   return 0;
}
```
# sort函数(类似于qsort函数）
```c
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
//设计比较函数
bool cmp(int x,int y){
    return x>y;
}
//设计仿函数
struct CMP{
    bool operator()(int x,int y){
        return x>y;
    }
}cmp1;
struct Student{
    string name;
    int age;
};
//结构体排序函数
bool cmp_name(Student s1,Student s2){
    return s1.name<s2.name;
};
int main(){
    int arr[5]={3,1,4,5,2};
    sort(arr,arr+5);
    for(int i=0;i<5;i++){
        cout<<arr[i]<<' ';
    }
    sort(arr,arr+5,cmp);
    cout<<endl;
    for(int i=0;i<5;i++){
        cout<<arr[i]<<' ';
    }
    cout<<endl;
    string s("treltrhujhbxbghfdshauihiubvhd");
    sort(s.begin(),s.end(),cmp1);
    cout<<s<<endl;
    Student arrs[3]={{"zhangsan",18},{"lisi",17},{"wangwu",19}};
    sort(arrs,arrs+3,cmp_name);
    for(int i=0;i<3;i++){
        cout<<arrs[i].name<<' '<<arrs[i].age<<endl;
    }
    return 0;
}
```
sort函数可以比较已经定义的几种数据类型（默认为从小到大排序），如果要按照其他顺序去排序要自定义比较函数或者仿函数。要比较类似于结构体类型的数据也要给他传入一个自定义的比较函数。



