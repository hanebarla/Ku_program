#include <stdio.h>

int main(){
    int a;
    printf("Please type an integeer: ");
    scanf("%d", &a);

    if(a % 3 == 0){
        printf("Yes");
    }else if (a % 5 == 0){
        printf("Yes");
    }else{
        printf("No");
    }

    return 0;
}