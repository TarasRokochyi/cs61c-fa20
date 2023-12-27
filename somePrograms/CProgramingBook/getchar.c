#include <stdio.h>

int main(){

    int c;

    while (c != EOF){
        if ((c = getchar()) == EOF){
            putchar(c);
        }
        
        putchar(c);
    }
}
