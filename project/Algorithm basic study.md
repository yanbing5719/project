# 空间复杂度（**算法在运行过程中，占用的额外内存空间大小与输入规模之间的关系**。）
# 时间复杂度（ **算法运行所需时间随输入规模 n 增大时的增长趋势**。）
## 大O表示法
1.只看影响时间开销最大的一项
2.最高阶项存在且项数不是1统一当作1来看
3.没有N相关项统一认为是1.
4.递归算法时间复杂度的计算
单次递归时间 * 总的递归次数  
# 常见排序算法
```c
//插入排序
void insert_sort(int arr[],int n){
    for(int i=1;i<n;i++){
        int key=arr[i];
        int j=i-1;
        while(j>=1&&arr[j]>key){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;
    }
}
//选择排序
void select_sort(int arr[],int n){
    for(int i=0;i<n-1;i++){
        int pos=i;
        for(int j=i+1;j<n;j++){
         if(arr[j]<arr[pos]){
            pos=j;
         }
        }
        swap(arr[i],arr[pos]);
    }
}
//冒泡排序
void bubble_sort(int arr[],int n){
    for(int i=0;i<n-1;i++){
for(int j=1;j<n-1-i;j++){
    if(arr[j]>arr[j+1]){
        swap(arr[j],arr[j+1]);                  
}
}
}
    }
```
# 模拟
蛇形矩阵
```c
#include <iostream>
using namespace std;
//方向向量 右 下 左 上
int dx[]={0,1,0,-1};
int dy[]={1,0,-1,0};
const int N=10;
int arr[N][N];
int main(){
int n;
cin>>n;
  int count=1;
  int x=1,y=1;
  int pos=0;
  while(count<=(n*n)){
    arr[x][y]=count;
    int a=dx[pos]+x,b=dy[pos]+y;
    if(a<1||a>n||b<1||b>n||arr[a][b]!=0){
        pos=(pos+1)%4;
        a=dx[pos]+x,b=dy[pos]+y;
    }
    x=a,y=b;
    count++;
  }
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
        printf("%3d",arr[i][j]);
    }
    cout<<'\n';
  }
}
```
矩阵类型的题要学会用方向向量
# 高精度（数据特别大的时候来加减乘除）
1.用字符串来读入数据，再用数组逆序存储数的每一位
2.利用数组模拟加减乘除
## 高精度加法
```c
#include <iostream>

using namespace std;

const int N=1e3;

int a[N],b[N],c[N];

int la,lb,lc;

void add(int a[],int b[],int c[]){

for(int i=0;i<lc;i++){

c[i]+=a[i]+b[i];

c[i+1]+=c[i]/10;

c[i]%=10;

}

if(c[lc]!=0)lc++;

}

int main(){

string x,y;

cin>>x>>y;

la=x.size();

lb=y.size();

for(int i=0;i<la;i++){

a[la-1-i]=x[i]-'0';

}

for(int i=0;i<lb;i++){

b[lb-1-i]=y[i]-'0';

}

lc=max(la,lb);

add(a,b,c);

for(int i=lc-1;i>=0;i--){

cout<<c[i];

}

return 0;

}
```
主要注意处理进位和结果位数多一的情况
## 高精度减法
```c
#include <bits/stdc++.h>

using namespace std;

const int N=1e5;

int a[N],b[N],c[N];

int la,lb,lc;

bool cmp(string&x,string&y){

if(x.size()!=y.size()){

return (x.size()>y.size());

}

return (x>y);

}

void sub(int a[],int b[],int c[]){

for(int i=0;i<lc;i++){

c[i]+=a[i]-b[i];

if(c[i]<0){

c[i+1]-=1;

c[i]+=10;

}

}

while(lc>1&&c[lc-1]==0)lc--;

}

int main(){

string x,y;

cin>>x>>y;

if(!cmp(x,y)&&(x!=y)){

swap(x,y);

cout<<'-';

}

la=x.size(),lb=y.size();

lc=max(la,lb);

for(int i=0;i<la;i++){

a[la-1-i]=x[i]-'0';

}

for(int i=0;i<lb;i++){

b[lb-1-i]=y[i]-'0';

}

sub(a,b,c);

for(int i=lc-1;i>=0;i--){

cout<<c[i];

}

return 0;

}
```
处理借位和前导零的情况以及要注意两个数相等的时候的特殊处理法
## 高精度乘法
```c
#include <bits/stdc++.h>

using namespace std;

const int N=1e4;

int a[N],b[N],c[N];

int la,lb,lc;

void mul(int a[],int b[],int c[]){

lc=la+lb;

for(int i=0;i<la;i++){

for(int j=0;j<lb;j++){

c[j+i]=a[i]*b[j];

}

}

for(int i=0;i<lc;i++){

c[i+1]+=c[i]/10;

c[i]%=10;

}

while(lc>1&&c[lc-1]==0)lc--;

}

int main(){

string x,y;

cin>>x>>y;

la=x.size();

lb=y.size();

lc=la+lb;

for(int i=0;i<la;i++){

a[la-1-i]=x[i]-'0';

}

for(int i=0;i<lb;i++){

b[lb-1-i]=y[i]-'0';

}

mul(a,b,c);

for(int i=lc-1;i>=0;i--){

cout<<c[i];

}

return 0;

}
```
重点是会用无进位乘法来进行计算
## 枚举算法
```c
//枚举算法 P1003 [NOIP 2011 提高组] 铺地毯

#include <iostream>

using namespace std;

const int N=1e4+10;

int a[N],b[N],g[N],k[N];

int n;

int main(){

cin>>n;

for(int i=1;i<=n;i++){

cin>>a[i]>>b[i]>>g[i]>>k[i];

}

int x,y;

cin>>x>>y;

for(int i=n;i>=1;i--){

if(x>=a[i]&&x<=a[i]+g[i]&&y>=b[i]&&y<=b[i]+k[i]){

cout<<i;

return 0;

}

}

cout<<-1;

return 0;

}
```
- 二进制枚举
```c

#include <bits/stdc++.h>

using namespace std;

int main(){

int n;

cin>>n;

for(int mask=0;mask<(1<<n);mask++){

for(int i=0;i<n;i++){

if(mask&(1<<i)){

cout<<"所选"<<i<<' ';

}

}

cout<<endl;

}

}
```
- 例题费解的开关
```c
#include <bits/stdc++.h>

using namespace std;

int main(){

//方向向量 右左上下

int dx[5]={0,0,0,1,-1};

int dy[5]={0,1,-1,0,0};

int g[5][5];

int T;cin>>T;

while(T--){

//读入数据

for(int i=0;i<5;i++){

string s;

cin>>s;

for(int j=0;j<5;j++){

g[i][j]=s[j]-'0';

}

}

int ans=1e9;

//枚举第一行

for(int mask=0;mask<(1<<5);mask++){

//拷贝先前的数据

int a[5][5];

memcpy(a,g,sizeof(a));

int cnt=0;

//处理第一行(j代表每一列)

for(int j=0;j<5;j++){

if(mask&(1<<j)){

cnt++;

//翻转按下的周围的灯

for(int k=0;k<5;k++){

int x=0+dx[k];

int y=j+dy[k];

if(x>=0&&x<5&&y>=0&&y<5){

a[x][y]^=1;

}

}

}

}

//根据上一行灯的亮灭来决定下一行

for(int i=1;i<5;i++){

for(int j=0;j<5;j++){

if(a[i-1][j]==0){

cnt++;

for(int k=0;k<5;k++){

int x=i+dx[k];

int y=j+dy[k];

if(x>=0&&x<5&&y>=0&&y<5){

a[x][y]^=1;

}

}

}

}

}

bool ok=true;

for(int i=0;i<5;i++){

if(a[4][i]==0){

ok=false;

break;

}

}

if(ok)ans=min(ans,cnt);

}

if(ans>6)cout<<-1<<endl;

else cout<<ans<<endl;

}

return 0;

}
```
## 前缀和
- 一维前缀和
```c
#include <bits/stdc++.h>

using namespace std;

int main(){

int n,q;

cin>>n>>q;

vector<long long>a(n+1,0);

vector<long long>f(n+1,0);//前缀和数组

for(int i=1;i<=n;i++){

cin>>a[i];

}

//处理前缀和数组

for(int i=1;i<=n;i++){

f[i]=f[i-1]+a[i];

}

while(q--){

int l,r;

cin>>l>>r;

cout<<f[r]-f[l-1]<<endl;

}

return 0;

}
```
- 最大子段和
```c
#include <bits/stdc++.h>

using namespace std;

int main(){

int n;

cin>>n;

vector<int> a(n+1,0);

for(int i=1;i<=n;i++){

cin>>a[i];

}

vector<int>f(n+1,0);

for(int i=1;i<=n;i++){

f[i]=f[i-1]+a[i];

}

int ret=-1e9;

int prev=0;

for(int i=1;i<=n;i++){

ret=max(ret,f[i]-prev);

prev=min(prev,f[i]);

}

cout<<ret<<endl;

}
```
## 差分
- 一维差分
```c
#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m,l,r,k;
    cin>>n>>m;
    //原始数组
    vector<int> a(n+1);
    vector<int> f(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        //差分数组
        f[i]=a[i]-a[i-1];
    }
    
    while(m--){
        cin>>l>>r>>k;
    f[l]+=k;
    f[r+1]-=k;
    }
    //还原原始数组
    for(int i=1;i<=n;i++){
        a[i]=a[i-1]+f[i];
        cout<<a[i]<<' ';
    }
}
```
- 差分的应用----海底高铁
```c
#include <bits/stdc++.h>
using namespace std;
int main(){
    int M,N;
    cin>>N>>M;
    vector<long long>f(N+1,0);
    int x;cin>>x;
    for(int i=2;i<=M;i++){
        int y;
        cin>>y;
    if(x>y){
        f[y]++;
        f[x]--;
    }else{
        f[x]++;
        f[y]--;
    }
    x=y;
}
for(int i=1;i<=N;i++){
    f[i]+=f[i-1];
}
    long long ret=0;
for(int i=1;i<=N;i++){
    long long a,b,c;
    cin>>a>>b>>c;
    ret+=min(a*f[i],c+b*f[i]);
}
cout<<ret<<endl;
return 0;
}
```
## 同向双指针
```c
//UVA11572 唯一的雪花 Unique Snowflakes
#include <bits/stdc++.h>
using namespace std;
int main(){
    int t,n;
    cin>>t;

    while(t--){
   cin>>n;
    vector<int> a(n);
   for(int i=0;i<n;i++){
    cin>>a[i];
   }
   int l=0,r=0;
   int result=0;
   unordered_map<int,int>mp;
    while(r<n){
        mp[a[r]]++;
    while(mp[a[r]]>1){
        mp[a[l]]--;
        l++;
    }
    result=max(result,r-l+1);
    r++;
    }
    cout<<result<<endl;
   }
   return 0;
    }

```

## 二分算法
### 二分查找
- 区间左端点
```c
int a[N];
int n=nums.size();
int l=0,r=n;
while(l<r){
int m=l+(r-l)/2;
if(nums[m]>=target){
r=m;
}
else{
l=m+1;
}
//结束后检查是否存在结果
```
- 区间右端点
```c
int a[N];
int n=a.size();
int l=0,r=n;
while(l<r){
   int m=l+(r-l+1)/2;//防止溢出
    if(a[m]<=target){
       r=m-1;
    }else{
        l=m;
    }
    //检查结果是否存在
}
```
- STL中的二分查找
```c
#include <iostream>
#include <algorithm>
using namespace std;
int main(){
    int a[]={1,2,2,2,3,3,4,5,5,6,8};
    int target=5;
    auto low=lower_bound(a,a+11,target);
    auto upper=upper_bound(a,a+11,target);
    cout<<*low<<endl;
    cout<<*upper<<endl;
    return 0;
}
5
6
```
### 二分答案
```c
//P2440 木材加工
#include <bits/stdc++.h>
using namespace std;
const int N=1e6;
int a[N];
long long n;
long long cal(long long mid){
    long long count=0;
    for(int i=0;i<n;i++){
        count+=a[i]/mid;
    }
    return count;
}
int main(){
    int k;
    cin>>n>>k;
   for(int i=0;i<n;i++){
    cin>>a[i];
   }
       long long total = 0;
    for (int i = 0; i < n; i++) total += a[i];
    if (total < k) {
        cout << 0 << endl;
        return 0;
    }

    long long left=1;
     long long right = *max_element(a, a + n);  
    while(left<right){
        long long mid = left + (right - left + 1) / 2; 
        if (cal(mid) >= k) {
            left = mid;        
        } else {
            right = mid - 1;   
        }
    }
   cout<<left<<endl;
   return 0;
}
```

## 贪心算法
- 简单贪心
```c
//P10452 货仓选址
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
const int N=1e5;
int a[N];
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    sort(a,a+n);
    int ret=0;
    for(int i=0;i<n;i++){
     ret+=abs(a[i]-a[n/2]);
    }
    cout<<ret<<endl;
    return 0;
}
```
原理|a-x|+|b-x|>=|a-b|
- 最大子段和
```c
#include <bits/stdc++.h>

using namespace std;

int main(){

int n;

cin>>n;

vector<int> a(n+1,0);

for(int i=1;i<=n;i++){

cin>>a[i];

}

vector<int>f(n+1,0);

for(int i=1;i<=n;i++){

f[i]=f[i-1]+a[i];

}

int ret=-1e9;

int prev=0;

for(int i=1;i<=n;i++){

ret=max(ret,f[i]-prev);

prev=min(prev,f[i]);

}

cout<<ret<<endl;

}
```