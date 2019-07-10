#include <stdio.h>

int main(){
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10 - i; j++){
            printf("%d ", i + j);
        }
        printf("\n");
    }

    return 0;
}