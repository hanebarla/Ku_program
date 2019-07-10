#include <stdio.h>
#include <math.h>

typedef struct
{
    double axis_x;
    double axis_y;
    double length;
}Vector2d;

double GetLength(Vector2d vec){
    double xx = vec.axis_x * vec.axis_x;
    double yy = vec.axis_y * vec.axis_y;
    vec.length = sqrt(xx + yy);
    return vec.length;
}

void ScaleVector(Vector2d *vec, double scale){
    vec->axis_x *= scale;
    vec->axis_y *= scale;
    vec->length = GetLength(*vec);
}

int main(){
    Vector2d vec;
    double scale;
    printf("Please input 2 param: ");
    scanf("%lf %lf", &vec.axis_x, &vec.axis_y);
    printf("Please input a large-scale number: ");
    scanf("%lf", &scale);
    ScaleVector(&vec, scale);
    printf("Result: (%lf, %lf)\n", vec.axis_x, vec.axis_y);
    printf("Length: %lf", vec.length);

    return 0;
}