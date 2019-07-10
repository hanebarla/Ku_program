#include <stdio.h>

int main(){
    int x[5] = {4, 1, 8, 2, 9};
    int range;
    range = x[0];
    for (int i = 0; i < sizeof(x) / sizeof(int);i++){
        if(range < x[i]){
            range = x[i];
        }
    }
    printf("Max number is %d", range);

    return 0;
}