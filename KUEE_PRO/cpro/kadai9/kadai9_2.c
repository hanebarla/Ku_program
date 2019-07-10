#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

void rand_init(int size_y, float *y){
    srand(time(NULL));
    for (int i = 0; i < size_y;i++){
        int np = (rand() % 2) + 1;
        y[i] = pow(-1, np) * (rand() % 100 ) / 100;
    }
}

void int_swap(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void float_swap(float *a, float *b){
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
                float_swap(&array[j], &array[j + 1]);
            }
        }
    }
}

void print(int n, float *y){
    printf("INITIALIZED: \n");
    for (int i = 0; i < n;i++){
        printf("%.3lf ", y[i]);
    }
}

void shuffle(int n, int *x){
    int temp;
    for (int i = 0; i < n;i++){
        temp = rand() % n;
        int_swap(&x[i], &x[temp]);
    }
}

int main(int argc, char *argv[]){
    int n = 0;
    if(argc >1){
        n = atoi(argv[1]);
    }
    float *y = malloc(sizeof(float) * n);
    rand_init(n, y);
    printf("INITIALIZE :\n");
    print(n, y);
    b_sort(y, n);
    printf("\nSORTED :\n");
    print(n, y);

    int *index = malloc(sizeof(int) * n);
    for (int i = 0; i < n;i++){
        index[i] = i;
    }
    shuffle(n, index);
    printf("\nUSED INDEX\n");
    for (int i = 0; i < n;i++){
        printf("%.3lf ", y[index[i]]);
    }

    return 0;
}