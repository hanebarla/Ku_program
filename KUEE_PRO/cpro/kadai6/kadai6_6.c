#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void print_oct(int m, int n, int size, float *x, char name){
    if(size == m*n){
        printf("%c = [", name);
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if(i != 0 && j == 0){
                    printf("    "); //0 margin
                }else if(i !=0 ){
                    printf(" ");
                }

                printf("%6.2lf", *x);
                ++x;
            }
            printf(" ;\n");
        }
            printf("];\n");
    }else{
        printf("Matrix size error\n");
    }
}

void rand_init(int size_y, float *y){
    srand(time(NULL));
    for (int i = 0; i < size_y;i++){
        int np = (rand() % 2) + 1;
        y[i] = pow(-1, np) * (rand() % 100 ) / 100;
    }
}

int main(){
    float y[6] = {1, 1, 2, 3, 5, 8};
    int size_y = sizeof(y) / sizeof(y[0]);
    print_oct(2, 3, size_y, y, 'y');
    rand_init(size_y, y);
    print_oct(2, 3, size_y, y, 'y');

    return 0;
}