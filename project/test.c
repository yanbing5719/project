#include <stdio.h>
#include <float.h>

int main() {
    float max_val = FLT_MAX;  // float 类型的最大值
    float overflow = max_val * 2.0f;
    
    printf("最大值: %e\n", max_val);
    printf("上溢结果: %f\n", overflow);  // 输出: inf 或 infinity
    
    return 0;
}