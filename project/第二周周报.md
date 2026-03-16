# XiyouLinux Group 周报 郭晏华
## Github : yanbing5719
## 第二周
本周学习内容
- 数据结构学习
仓库链接：https://github.com/yanbing5719/cpp

**关键 commit**:

1.[57e108b]:https://github.com/yanbing5719/cpp/commit/57e108bbb8ced7d3d05be665bc6282490ad985b3

41c4469: https://github.com/yanbing5719/cpp/commit/41c4469c321a6791df4f029105a99b1110ebf110

2.[6c32375]:https://github.com/yanbing5719/cpp/commit/6c32375b2bc75c9d8f869e2c3aadcc0503e8c4fe

**commit简介**：

1.图的学习，掌握如何构建无向图，邻接表的构建以及DFS+邻接表，DFS+连通块
2.堆的学习，知晓堆一般用来解决找最值的问题，构建大根堆和小根堆，实现寻找第几大的值

- 算法的学习

1.[3fbdc4e]:https://github.com/yanbing5719/cpp/commit/3fbdc4edf7059de3ec5f13a6555c92ac6ab48303

2.[41c4469]:https://github.com/yanbing5719/cpp/commit/41c4469c321a6791df4f029105a99b1110ebf110

47bc3d7: https://github.com/yanbing5719/cpp/commit/47bc3d7c6830317c475af0f8e15acbaa180a008b

3.[c55fe09]:https://github.com/yanbing5719/project/commit/c55fe09c02b78124df8cb0ef4aa60a5ba0b36ca6

**commit简介**：

1.模拟算法的几道经典题目，学会矩阵填数类型的题目
2.高精度的加减乘除法
3.根据网课以及ai学习枚举算法，着重理解并掌握二进制枚举
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
