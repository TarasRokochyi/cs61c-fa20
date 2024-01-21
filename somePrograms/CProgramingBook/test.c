#include <stdio.h>

char *month(int num);

int main(void){

    int num = 2;

    printf("%s\n", month(num));
}



char *month(int num){

    char *name[] = { "Illegal month", "January", "February", "March", "April"};

    return (num < 1 || num > 12) ? name[0] : name[num];
}
