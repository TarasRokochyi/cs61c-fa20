#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LIM 4

int setbits(int x, int p, int n, int y);
void printBinary(int decimal);
int getNumber();

int main(void){
    char c;

    printf("enter decimal number\n");
    int16_t x = getNumber();

    printf("enter p\n");
    int16_t p = getNumber();

    printf("enter n\n");
    int16_t n = getNumber();

    printf("enter y\n");
    int16_t y = getNumber();

    printBinary(x);
    printBinary(y);

    int16_t result = setbits(x, p, n, y);

    printBinary(result);
}


int setbits(int x, int p, int n, int y){

    return (x & ~(~(~0 << n) << (p-n+1))) | ((y & ~(1 << n)) << (p-n+1));
}

void printBinary(int decimal){
    int bit;
    for (int i = 15; i >= 0; i--){
        printf("%d", (decimal >> i) & 1);
    }
    printf("\n");
}

int getNumber(){

    char c;
    char s[LIM];
    for(int i = 0; i < LIM+1 && (c = getchar()) != '\n'; i++){
        s[i] = c;
    }

    return atoi(s);
}
