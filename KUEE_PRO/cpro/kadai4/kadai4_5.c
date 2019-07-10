#include <stdio.h>

int n;

int my_input(){
    int r = 0;
    while (r == 0){
        while (r != 1){
            printf("Please enter a positive integer\n");
            r = scanf("%d", &n);
            if (r!=1){
                printf("You enter an invalid number\n");
                scanf("%*s");
            }else{
                if(n>0){
                    break;
                }else{
                    printf("You enter an invalid number\n");
                }
            }
        }
    }

    return n;
}

int fact(int a){
    int all = 1;
    while (a>0)
    {
        all *= a;
        a--;
    }
    
    
    return all;
}

int perm(int n, int r){
    if(n >= r){
        return fact(n) / fact(n - r);
    }else{
        printf("ERROR");
        return 0;
    }
}

int main(){
    n = my_input();
    for (int i = 0; i < n+1; i++){
        int ans = perm(n, i);
        printf("P(%d,%d) = %d\n", n, i,ans);
    }
    return 0;
}