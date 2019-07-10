#include <stdio.h>

int main(){
    float x = 1;
    for (int i = 0; i < 10;i++){
        x -= 1.0 / 3.0;
        if(x < 0){
            break;
        }

        printf("%.20f\n", x);
    }

    return 0;
}