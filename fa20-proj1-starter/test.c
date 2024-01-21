#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main(void){

    struct Color {
        uint8_t R;
        uint8_t G;
        uint8_t B;
    } color;

    color.R = 10;
    color.G = 52;
    color.B = 93;

    uint8_t array[3];
    array[0] = color.R;
    array[1] = color.G;
    array[2] = color.B;

    uint32_t test = (uint32_t) color;

    if (test & 10)
        printf("true\n");
    else 
        printf("false\n");

}

