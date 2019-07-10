#include <stdio.h>

int main(){
    int n, sum;
    sum = 1;
    printf("Prease enter an integeer: ");
    scanf("%d", &n);
    for (; n > 0;){
        sum *= n;
        n--;
    }
    printf("%d", sum);

    return 0;
}