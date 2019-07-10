#include <stdio.h>

#define M 3
#define N 4

int main(){
    int a[M][N];
    printf("Matrix a is\n");
    for (int i = 0; i < M;i++){
        for (int j = 0; j < N;j++){
            a[i][j] = 10 * i + j;
            printf("%2d ", a[i][j]);
        }
        printf("\n");
    }
    /*printf("%d", a) ではaのアドレス値が返されるのか*/
    return 0;
}