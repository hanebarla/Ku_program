#include <stdio.h>
#include <string.h>

int main(){

    char str[] = "hane";
    int length = strlen(str);

    int n[] = {20, 1, 49};
    int intlength = sizeof(n) / sizeof(n[0]);

    double m[] = {2.0, 60.3, 5.9};
    int doublelength = sizeof(m) / sizeof(m[0]);

    for (int i = 0; i < length;i++){
        printf("value : %c, adress : %p\n", str[i], &str[i]);
    }
    for (int i = 0; i < intlength;i++){
        printf("value : %d, adress : %p\n", n[i], &n[i]);
    }
    for (int i = 0; i < doublelength;i++){
        printf("value : %lf, adress : %p\n", m[i], &m[i]);
    }

        return 0;
}