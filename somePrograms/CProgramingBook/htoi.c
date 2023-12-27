#include <stdio.h>
#define MAX 10
 
int htoi(char[]);
int charToLow(char);

int main(void){
    
    char hex_string[MAX];

    char c;

    for(int i = 0;i < MAX && (c = getchar()) != EOF && c != '\n'; ++i){
        hex_string[i] = c;
    }

    int decimal = htoi(hex_string);

    printf("%d\n", decimal);
}



int htoi(char hex[]){
    int result = 0;

    // int length = sizeof(hex) / sizeof(hex[0]);

    int i = 0;
    if (charToLow(hex[1]) == 'x')
        i = 2;

    char lower;
    for(;((lower = charToLow(hex[i])) >= 'a' && lower <= 'f') || (lower >= '0' && lower <= '9'); ++i){
        // printf("%c\n", lower);
        if (lower >= 'a' && lower <= 'f')
            result = (result * 16) + ( lower - 'a' + 10);
        else 
            result = (result * 16) + (hex[i] - '0');
        printf("\n%d\n", result);
    }

    return result;
}


int charToLow(char c){
    if (c >= 'A' && c <= 'Z')
        return c + 'a' - 'A';
    else 
        return c;
}

