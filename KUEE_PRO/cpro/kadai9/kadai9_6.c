#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

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
            printf("%5.3lf ", y[i]);
        }
    }
}

void load(const char *filename, int m, int n, float *A, float *b){
    FILE *fp;
    fp = fopen(filename, "rb");
    if(!fp){
        printf("FILE CANNOT OPEN");
    }
    for (int i = 0; i < m;i++){
        for (int j = 0; j < n;j++){
            fread(&A[i*j+j], sizeof(float), 1, fp);
        }
    }
    for (int j = 0; j < n; j++){
        fread(&b[j], sizeof(float), 1, fp);
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
    load("test.bat", gyou, retu, A, b);
    printf("LOAD :\n");
    print(matrix_size, retu, A);
    print(retu, retu, b);

    return 0;
}