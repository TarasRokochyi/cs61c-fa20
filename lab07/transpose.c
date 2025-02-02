#include "transpose.h"

/* The naive transpose function as a reference. */
void transpose_naive(int n, int blocksize, int *dst, int *src) {
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            dst[y + x * n] = src[x + y * n];
        }
    }
}

/* Implement cache blocking below. You should NOT assume that n is a
 * multiple of the block size. */
void transpose_blocking(int n, int blocksize, int *dst, int *src) {
    // YOUR CODE HERE

    //int rep = up(n / blocksize);
    int remainder = n % blocksize;

    int block_x = 0, block_y = 0;

    for (int i = 0; i < n; i += blocksize){
        block_x = blocksize;
        if (i + blocksize > n)
            block_x = remainder;

        for (int j = 0; j < n; j += blocksize){
            block_y = blocksize;
            if (j + blocksize > n)
                block_y = remainder;

            for (int y = 0; y < block_y; y++){
                for (int x = 0; x < block_x; x++){
                    dst[(j+y) + (i+x) * n] = src[(i+x) + (j+y) * n];
                }
            }
        }
    }

}
