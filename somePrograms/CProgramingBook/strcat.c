#include <stdio.h>

#define MAX_LEN 1000

void strcat(char *s, char *t);

int main(void){
    char string [MAX_LEN];

    int i = 0;
    for (; i < 4; i++){
        string[i] = 'h';
    }
    string[i] = '\0'; 

    char string2[] = "taras";

    strcat(string, string2);

    printf("%s\n", string);

    return 0;

}


void strcat(char *s, char *t){

    while(*s != '\0')
        s++;


    while((*s++ = *t++) != '\0')
        ;
}
