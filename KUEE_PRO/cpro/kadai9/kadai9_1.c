#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void rand_init(int size_y, float *y){
    srand(time(NULL));
    for (int i = 0; i < size_y;i++){
        int np = (rand() % 2) + 1;
        y[i] = pow(-1, np) * (rand() % 100 ) / 100;
    }
}

int matrix_size(int n){
    int gyou = 1;
    for (int i = n - 1; n > 0;i--){
        if(n % i == 0){
            gyou = i;
            break;
        }
    }
    return gyou;
}

void print(int m, int n, int size, float *x){
    if(size == m * n){
    for (int i = 0; i < m;i++){
        for (int j = 0; j < n;j++){
            printf("%6.2lf", *x);
            ++x;
        }
        printf("\n");
    }
    }else{
        printf("Matrix size error");
    }
}

void swap(float *a, float *b){
    float temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void b_sort(float *array, int size)
{
    for (int i = 0; i < size;i++){
        for (int j = 0; j < size - 1 ;j++){
            if(array[j]>array[j+1]){
                swap(&array[j], &array[j + 1]);
            }
        }
    }
}

int main(int argc, char *argv[]){
    int n = 0;
    int gyou = 0;
    if(argc >1){
        n = atoi(argv[1]);
    }
    float *y = malloc(sizeof(float) * n);
    rand_init(n, y);
    gyou = matrix_size(n);
    int retu = n / gyou;
    printf("INITIALIZE :\n");
    print(gyou, retu, n, y);
    b_sort(y, n);
    printf("\nSORTED :\n");
    print(gyou, retu, n, y);

    return 0;
}