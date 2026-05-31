# 89路径之谜
```c
#include <bits/stdc++.h>

using namespace std;

int n;

vector<int>path;

//记录每一个方格是否走过

bool vis[25][25];

//是否找到正确答案

bool finish=false;

//坐标 上下左右

int dx[4]={1,-1,0,0};

int dy[4]={0,0,-1,1};

//每一个靶子的箭数

int north[25];

int west[25];

void dfs(int x,int y)

{

if(finish)return ;

north[y]--;

west[x]--;

if(north[y]<0||west[x]<0)

{

north[y]++;

west[x]++;

return ;

}

vis[x][y]=true;

path.push_back(x*n+y);

//检查每一个靶子上面箭的数量是不是归零

bool ok=true;

for(int i=0;i<n;i++)

{

if(north[i]!=0)ok=false;

}

for(int i=0;i<n;i++)

{

if(west[i]!=0) ok=false;

}

//判断是否走到右下角

if(x==n-1&&y==n-1&&ok){

finish=true;

return;

}

//更新新的坐标

int nx,ny;

for(int i=0;i<4;i++)

{

nx=x+dx[i];

ny=y+dy[i];

//检查根新后的坐标是否符合题目

if(nx>=0&&nx<n&&ny>=0&&ny<n&&!vis[nx][ny])

{

dfs(nx,ny);

if(finish)return ;

}

}

//如果循环结束后还是没有找到结果,退回到上一步

path.pop_back();

vis[x][y]=false;

north[y]++;

west[x]++;

  

}

int main()

{

cin>>n;

for(int i=0;i<n;i++)

{

cin>>north[i];

}

for(int i=0;i<n;i++)

{

cin>>west[i];

}

dfs(0,0);

for(int i=0;i<path.size();i++)

{

cout<<path[i]<<" ";

}

return 0;

}
```
尝试每一步是不是符合题意，注意要判断符合的条件，一个也不能少，遇到这种坐标问题要学会怎么更新坐标，重点要学会如何回溯