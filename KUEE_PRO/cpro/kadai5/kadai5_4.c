#include <stdio.h>

int input(){
    int x;
    int r = 0;
    while (r==0)
    {
        while (r!=1)
        {
            printf("please enter an intergeer: ");
            r = scanf("%d", &x);
            if(r!=1){
                scanf("%*s");
            }else{
                break;
            }
        }
    }
    return x;
}

void pr_bit(int inp){
    for (int i = 31; i >= 0;i--){
        printf("%d (10) = %d (2)",inp, (inp >> i) & 1);
    }
}

int main(){
    int inp;
    inp = input();
    pr_bit(inp);

    return 0;
}