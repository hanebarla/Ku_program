#include <stdio.h>
#include <math.h>

typedef struct
{
    double axis_x;
    double axis_y;
}Vector2d;

double GetLength(Vector2d vec){
    double xx = vec.axis_x * vec.axis_x;
    double yy = vec.axis_y * vec.axis_y;
    return sqrt(xx + yy);
}

int main(){
    Vector2d vector;
    double length;
    printf("Please input 2 param: ");
    scanf("%lf %lf", &vector.axis_x, &vector.axis_y);
    length = GetLength(vector);
    printf("%lf", length);

    return 0;
}
