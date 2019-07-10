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

void print(int n, float *y){
    printf("INITIALIZED: \n");
    for (int i = 0; i < n;i++){
        printf("%.3lf ", y[i]);
    }
}

void SoftMax(int n, float *y, float *x){
    float sum = 0;
    for (int i = 0; i < n;i++){
        sum += exp(y[i]);
    }
    for (int j = 0; j < n;j++){
        x[j] = exp(y[j]) / sum;
    }
}

int main(int argc, char *argv[]){
    int n = 0;
    if(argc >1){
        n = atoi(argv[1]);
    }
    float *y = malloc(sizeof(float) * n);
    float *x = malloc(sizeof(float) * n);
    rand_init(n, y);
    printf("INITIALIZE :\n");
    print(n, y);
    SoftMax(n, y, x);
    printf("\nSoftMax :\n");
    print(n, x);

    return 0;
}