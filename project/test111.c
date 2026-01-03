#include <stdio.h>
double fact(int n) {
    if (n <= 1) return 1;
    return n * fact(n - 1);
}
double cheng(int n) {
    if (n == 3) return 3.0;
    return n * cheng(n - 2);
}
int main() {
    double eps;
    scanf("%le", &eps);
    double result = 1.0;
    int i = 0;
    double point = 1.0;
    while (point>=eps){
        point = point * (2.0 * i + 1) / (2.0 * i + 3) / (2.0 * i + 2);
        result += point;
        i++;
    }
    printf("PI = %.5f", 2*result);
    return 0;
}