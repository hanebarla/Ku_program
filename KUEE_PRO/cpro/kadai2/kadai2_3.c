#include <stdio.h>
#include <math.h>

int main(){
    double a, b, c, root, front;
    printf("Please type three coefficients: \n");
    scanf("%lf %lf %lf", &a, &b, &c);
    printf("%f x^2 + %f x + %f = 0\n", a, b, c);

    front = -b / (2 * a);
    root = b * b - 4 * a * c;

    printf("Answer :");
    if (root > 0.0){
        root = sqrt(root) / (2 * a);
        printf("%f , %f", front + root, front - root);
    }else if(root < 0.0){
        root = sqrt(-root) / (2 * a);
        printf("%f + i*%f , %f - i*%f", front, root, front, root);
    }else{
        printf("%f", front); //root = 0
    }

    return 0;
}