#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

void init(int size_y, float ini_fl, float *y){
    for (int i = 0; i < size_y;i++){
        y[i] = ini_fl;
    }
}

void print(int n, int retu, float *y){
    if (n % retu == 0 && n/retu !=1){
        for (int i = 0; i < (n / retu);i++){
            for (int j = 0; j < retu;j++){
                printf("%5.3lf ", y[i*j + j]);
            }
            printf("\n");
        }
    }else{
        for (int i = 0; i < n; i++)
        {
            printf("%.5lf ", y[i]);
        }
    }
}

void save(const char *filename, int m, int n, float *A, float *b){
    FILE *fp;
    fp = fopen(filename , "wb");
    for (int i = 0; i < m;i++){
        for (int j = 0; j < n;j++){
            fwrite(&A[i*j+j], sizeof(float), 1, fp);
        }
    }
    for (int j = 0; j < n; j++){
        fprintf(&b[j], sizeof(float), 1, fp);
    }
    fclose(fp);
}

int main(int argc, char *argv[]){
    int gyou = 0;
    int retu = 0;
    if(argc >1){
        gyou = atoi(argv[1]);
        retu = atoi(argv[2]);
    }
    int matrix_size = gyou * retu;
    float *A = malloc(sizeof(float) * matrix_size);
    float *b = malloc(sizeof(float) * retu);
    init(matrix_size, 1, A);
    init(retu, 2, b);
    printf("INITIALIZE :\n");
    print(matrix_size, retu, A);
    print(retu, retu, b);

    save("test.bat", gyou, retu, A, b);

    return 0;
}