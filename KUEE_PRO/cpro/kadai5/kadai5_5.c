#include <stdio.h>

int main(){
    float a, b;
    double c, d;

    a = 0;
    b = 0;
    c = 0;
    d = 0;

    for (int i = 0; i < 1e+8;i++){
        a += 1e-8;
        c += 1e-8;
    }
    b = 1e-8 * 1e+8;
    d = 1e-8 * 1e+8;

    printf("a = %.20f\nb = %.20f\nc = %.20lf\nd = %.20lf", a, b, c, d);

    return 0;
}