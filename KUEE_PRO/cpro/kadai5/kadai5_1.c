#include <stdio.h>

int conv(int n, int r){
    if(n==r || r==0){
        return 1;
    }else if(r == 1){
        return n;
    }else{
        return conv(n - 1, r - 1) + conv(n - 1, r);
    }
}

void swap(int* a, int* b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int main(){
    int x, y;
    printf("Please enter two integers: ");
    scanf("%d %d", &x, &y);
    if(x < y){
        swap(&x, &y);
    }

    printf("C(%d, %d) = %d", x, y, conv(x , y));

    return 0;
}