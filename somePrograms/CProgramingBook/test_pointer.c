#include <stdio.h>


void IncrementPtr(int **p);

int main(void){

    int A[3] = {50, 60, 70};

    int* q = A;

    IncrementPtr(&q);

    int x = 3;

    int* y = &x;

    printf("%d\n", *y);

    //int* ptr = &x;
    //printf("ptr = %d\n", *ptr);

    //printf("q: %p\n", q);
    //printf("A: %p\n", A);
    //printf("q: %d\n", *q);
}


void IncrementPtr(int **p){
    printf("before %p\n", *p);
    *p = *p + 1;
    printf("after %p\n", *p);
    printf("%d\n", **p);
    p = 234;
}
