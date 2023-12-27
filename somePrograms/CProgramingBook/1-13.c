#include <stdio.h>

#define OUT 0
#define IN  1
#define SIZE 10

int main(void){
    
    int c, count_word;

    count_word = 0;

    int lengths[SIZE];
    for (int i = 0; i < SIZE; ++i){
        lengths[i] = 0;
    }

    int state = OUT;
    while ((c = getchar()) != EOF){
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT){
            ++count_word;
            state = IN;
        }


        if (state == IN)
            ++lengths[count_word-1];
    }

    int biggest = lengths[0];
    for (int i = 1; i < SIZE; ++i){
        if (lengths[i] > biggest)
            biggest = lengths[i];
    }

    // to not lose the biggest value
    int pivot = biggest;
    while(pivot >= 0){
        for (int i = 0; i < SIZE; ++i){
            if (pivot < 0)
                break;

            if ((lengths[i] - pivot) == 0)
                printf("__");
            else
                printf("  ");
        }
        --pivot;
        printf("\n");
    }
}
