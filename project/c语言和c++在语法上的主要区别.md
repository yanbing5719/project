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
**c语言里面函数里面改变参数的值要用到指针**
```c
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}
int x = 1, y = 2;
swap(&x, &y);
```
**c++里面引入引用的概念**
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
inc(a);
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









