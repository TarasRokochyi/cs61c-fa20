#include <stdio.h>


void IncrementPtr(int **p);

int main(void){

    int A[3] = {50, 60, 70};

    int *q = A;

    IncrementPtr(&q);

    printf("q: %p\n", q);
    printf("A: %p\n", A);
}


void IncrementPtr(int **p){
    printf("before %p\n", *p);
    *p = *p + 1;
    printf("after %p\n", *p);
}
