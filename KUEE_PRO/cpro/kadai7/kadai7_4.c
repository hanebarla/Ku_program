#include <stdio.h>

void maxmin(int array[], int *max, int *min){
    for (int i = 0; i < 3;i++){
        if(*max < array[i]){
            *max = array[i];
        }
        if(*min > array[i]){
            *min = array[i];
        }
    }

}

int main(){
    int inp[3];
    for (int i = 0; i < 3; i++){
        printf("Please enter [%d] numbers :", i);
        scanf("%d", &inp[i]);
    }
    int max = inp[0];
    int min = inp[0];

    maxmin(inp, &max, &min);

    printf("Max is %d\n", max);
    printf("Min is %d\n", min);

    return 0;
}