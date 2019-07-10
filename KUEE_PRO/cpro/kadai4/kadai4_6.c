#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void hist(int n){
    printf("n = %8d: ", n);
    int ran;
    int num[10] = {};
    double hist[10] = {};
    for (int i = 0; i < n; i++){
        ran = rand() % 10;
        switch (ran)
        {
        case 0:
            num[0] += 1;
            break;
        case 1:
            num[1] += 1;
            break;
        case 2:
            num[2] += 1;
            break;
        case 3:
            num[3] += 1;
            break;
        case 4:
            num[4] += 1;
            break;
        case 5:
            num[5] += 1;
            break;
        case 6:
            num[6] += 1;
            break;
        case 7:
            num[7] += 1;
            break;
        case 8:
            num[8] += 1;
            break;
        case 9:
            num[9] += 1;
            break;
        default:
            break;
        }
    }
    for (int i = 0; i < 10;i++){
        hist[i] = (double)num[i] * 100.0 / (double)n;
        printf("%4.1lf ", hist[i]);
    }
    printf("\n");
}

int main(){
    hist(100);
    hist(1000);
    hist(10000);
    hist(100000);
    hist(1000000);

    return 0;
}