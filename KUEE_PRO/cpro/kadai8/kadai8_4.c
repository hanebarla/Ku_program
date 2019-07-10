#include <stdio.h>

int main(){
    FILE *fp1 = NULL;
    FILE *fp2 = NULL;
    char str[128];

    fp1 = fopen("test.txt", "r");
    fp2 = fopen("test.bak", "w");
    if(!fp1){
        printf("File cannot open");
        return 0;
    }
    while (fgets(str,128,fp1))
    fprintf(fp2, "%s", str);
    fclose(fp1);
    fclose(fp2);
}