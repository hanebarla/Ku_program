#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void initialize(int *array, int size){
    srand(time(NULL));
    printf("Data: ");
    for (int i = 0; i < size;i++){
        array[i] = rand();
        printf("%d ", array[i]);
    }
    printf("\nN: %d\n", size);
}

void swap(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void b_sort(int *array, int size)
{
    for (int i = 0; i < size;i++){
        printf("loop %d ", i + 1);
        for (int j = 0; j < size - 1 ;j++){
            if(array[j]>array[j+1]){
                swap(&array[j], &array[j + 1]);
            }
            printf("%d ", array[j]);
        }
        printf("\n");
    }
}

int main(){
    int num;
    printf("Please type a positive integeer: ");
    scanf("%d", &num);
    int array[num];
    initialize(array, num);
    b_sort(array, num);

    return 0;
}