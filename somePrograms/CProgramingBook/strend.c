#include <stdio.h>


int strend(char *s, char * t);

int main(void){

    char string[] = "hello, world";

    char string2[] = "world";

    printf("%d\n", strend(string, string2));
}



int strend(char *s, char *t){

    int s_len = 0;
    while (*s != '\0'){
        s++;
        s_len++;
    }

    int t_len = 0;
    while (*t != '\0'){
        t++;
        t_len++;
    }

    if (s_len < t_len)
        return 0;

    for (int i = 0; (i < t_len); i++)
        if (*--s != *--t){
            return 0;
        }

    return 1;
}
