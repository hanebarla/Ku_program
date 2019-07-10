#include <stdio.h>

#define M 3
#define N 4

int a[M][N];

void substitute(int arr[M][N]){
    for (int i = 0; i < M; i++){
        for (int j = 0; j < N; j++){
            arr[i][j] = 10 * i + j;
        }
    }
}

void display(int arr[M][N]){
    for (int i = 0; i < M;i++){
        for (int j = 0; j < N;j++){
            printf("%2d ", arr[i][j]);
        }
        printf("\n");
    }
}

int main(){
    substitute(a);
    display(a);

    return 0;
}