#include <stdio.h>

int main(){
    int fahr, celsius;
    int  limit, step;

    limit = 0;
    step = 20;

    for(fahr = 300; fahr >= limit; fahr = fahr - step){
        celsius = 5 * (fahr - 32) / 9;
        printf("%d\t%d\n", fahr, celsius);
    }
    
   // while(fahr < upper){
   //     celsius = 5 * (fahr - 32) / 9;
   //     printf("%d\t%d\n", fahr, celsius);
   //     fahr = fahr + step;
   // }
}
