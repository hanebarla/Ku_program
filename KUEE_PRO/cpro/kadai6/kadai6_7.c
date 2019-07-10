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

void mul(int m, int n, int size_y, int size_x, int size_o, float *y, float *x,float *o){
    if(m * n == size_y && n == size_x && m == size_o){
        for (int i = 0; i < m;i++){
            for (int j = 0; j < n;j++){
                o[i] += y[i * n + j] * x[j];
            }
        }
    }else{
        printf("Matrix size error\n");
    }
}

int main(){
    float y[6] = {1, 2, 3, 4, 5, 6};
    float x[3] = {2,3,5};
    float o[2] = {};

    int size_y = sizeof(y) / sizeof(y[0]);
    int size_x = sizeof(x) / sizeof(x[0]);
    int size_o = sizeof(o) / sizeof(o[0]);

    mul(2, 3, size_y, size_x, size_o, y, x, o);

    print_oct(2, 3, size_y, y, 'y');
    print_oct(3, 1, size_x, x, 'x');
    print_oct(2, 1, size_o, o, 'o');

    return 0;
}