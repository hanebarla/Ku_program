#include <stdio.h>

void print(int m, int n, int size, float *x){
    if(size == m*n){
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

int main(){
    float m[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    int size = sizeof(m) / sizeof(m[0]);
    print(3, 4, size ,&m);

    return 0;
}