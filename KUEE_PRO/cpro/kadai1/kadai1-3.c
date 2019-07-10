#include <stdio.h>
#include <math.h>

int main(){
    double a, b, c, x1, x2;
    printf("Please type three numbers\n");
    scanf("%lf %lf %lf", &a, &b, &c);
    x1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
    x2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);

    printf("%f\n%f", x1,x2);

    return 0;
}