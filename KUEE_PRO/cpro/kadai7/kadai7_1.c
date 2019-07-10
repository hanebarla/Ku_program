#include <stdio.h>

int main(){
    char input[128];
    int i = 0;
    printf("Input a word: ");
    scanf("%s", input);

    while(input[i]){

        if(input[i] == 'z'){
            input[i] = 'a';
        }else if(input[i] == 'Z'){
            input[i] = 'A';
        }else if(input[i] == '\0'){
            continue;
        }else{
            input[i] += 1;
        }
        i++;
    }
    printf("%s", input);

    return 0;
}