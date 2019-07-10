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

void ReLU(int n, float *y, float *x){
    for (int i = 0; i < n;i++){
        if(y[i] <0){
            x[i] = 0;
        }else{
            x[i] = y[i];
        }
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
    ReLU(n, y, x);
    printf("\nReLU :\n");
    print(n, x);

    return 0;
}