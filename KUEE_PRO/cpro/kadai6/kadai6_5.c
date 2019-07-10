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

void init(int size_y, float ini_fl,float *y){
    for (int i = 0; i < size_y;i++){
        y[i] = ini_fl;
    }
}

int main(){
    float y[6] = {1, 1, 2, 3, 5, 8};
    int size_y = sizeof(y) / sizeof(y[0]);
    print_oct(2, 3, size_y, y, 'y');
    init(size_y, 7, y);
    print_oct(2, 3, size_y, y, 'y');

    return 0;
}