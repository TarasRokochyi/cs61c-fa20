#include <stdio.h>
#include "bit_ops.h"

// Return the nth bit of x.
// Assume 0 <= n <= 31
unsigned get_bit(unsigned x, unsigned n) {
    // YOUR CODE HERE
    // Returning -1 is a placeholder (it makes
    // no sense, because get_bit only returns 
    // 0 or 1)
    return (x >> n) & 1;
}
// Set the nth bit of the value of x to v.
// Assume 0 <= n <= 31, and v is 0 or 1
void set_bit(unsigned * x, unsigned n, unsigned v) {
    // YOUR CODE HERE
    unsigned nth_bit = 1 << n;

    if (v)
        *x = *x | nth_bit;
    else{
        nth_bit = ~nth_bit;
        *x = *x & nth_bit;
    }
}
// Flip the nth bit of the value of x.
// Assume 0 <= n <= 31
void flip_bit(unsigned * x, unsigned n) {
    // YOUR CODE HERE

    unsigned nth_bit = 1 << n;
    
    if ((*x >> n) & 1){
        nth_bit = ~nth_bit;
        *x = *x & nth_bit;
    }
    else
        *x = *x | nth_bit;

}

