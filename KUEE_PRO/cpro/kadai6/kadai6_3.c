#include <stdio.h>

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

void add(int size_x, int size_y, float *x, float *y){
    if(size_x == size_y){
        for (int i = 0; i < size_x;i++){
            y[i] += x[i];
        }
    }else{
        printf("Matrix's sizes are not equal\n");
    }
}

int main(){
    float x[6] = {0, 1, 2, 3, 4, 5};
    float y[6] = {1, 1, 2, 3, 5, 8};
    int size_x = sizeof(x) / sizeof(x[0]);
    int size_y = sizeof(y) / sizeof(y[0]);
    print_oct(2, 3, size_x ,x, 'x');
    print_oct(2, 3, size_y, y, 'y');
    add(size_x, size_y, x, y);

    print_oct(2, 3,size_y, y, 'y');

    return 0;
}