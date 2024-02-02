.globl read_matrix

.text
# ==============================================================================
# FUNCTION: Allocates memory and reads in a binary file as a matrix of integers
#
# FILE FORMAT:
#   The first 8 bytes are two 4 byte ints representing the # of rows and columns
#   in the matrix. Every 4 bytes afterwards is an element of the matrix in
#   row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is a pointer to an integer, we will set it to the number of rows
#   a2 (int*)  is a pointer to an integer, we will set it to the number of columns
# Returns:
#   a0 (int*)  is the pointer to the matrix in memory
# Exceptions:
# - If malloc returns an error,
#   this function terminates the program with error code 88.
# - If you receive an fopen error or eof, 
#   this function terminates the program with error code 90.
# - If you receive an fread error or eof,
#   this function terminates the program with error code 91.
# - If you receive an fclose error or eof,
#   this function terminates the program with error code 92.
# ==============================================================================
read_matrix:

    # Prologue
    addi sp, sp, -28 
    sw ra, 0(sp)
    sw s0, 4(sp)
    sw s1, 8(sp)
    sw s2, 12(sp)
    sw s3, 16(sp)
    sw s4, 20(sp)
    sw s5, 24(sp)

    # save arguments a0, a1, a2
    add s0, a0, x0
    add s1, a1, x0
    add s2, a2, x0

    add a1, s0, x0 # filename
    add a2, x0, x0 # permission
    jal fopen
    blt a0, x0, exep90

    # save returned file descriptor
    add s3, a0, x0


    addi a0, x0, 8
    jal malloc
    beq a0, x0, exep88
    add s5, a0, x0 # pointer to memory

    addi t0, x0, 8 # numb of bytes to read

    add a1, s3, x0 # file descriptor
    add a2, s5, x0 # buffer
    add a3, x0, t0 # num of bytes to read
    addi sp, sp, -4
    sw t0, 0(sp)
    jal fread
    lw t0, 0(sp)
    addi sp, sp, 4
    blt a0, t0, exep91

    lw t0, 0(s5) # rows
    lw t1, 4(s5) # cols

    # free memory from malloc
    add a0, s5, x0
    addi sp, sp, -8
    sw t0, 0(sp)
    sw t1, 4(sp)
    jal free
    lw t1, 4(sp)
    lw t0, 0(sp)
    addi sp, sp, 8

    # save rows and cols to pointers
    sw t0, 0(s1)  
    sw t1, 0(s2)

    mul s4, t0, t1 # number of elements
    slli s4, s4, 2 # multiply by 4, numb of bytes

    add a0, s4, x0
    jal malloc
    beq a0, x0, exep88
    add s5, a0, x0 # pointer to memory from malloc

    add a1, s3, x0 # file descriptor
    add a2, s5, x0 # buffer to write
    add a3, x0, s4 # numb of bytes to read
    jal fread
    blt a0, s4, exep91

    
    add a1, s3, x0
    jal fclose
    blt a0, x0, exep92

    add a0, s5, x0 # return value 
    # Epilogue
    lw s5, 24(sp)
    lw s4, 20(sp)
    lw s3, 16(sp)
    lw s2, 12(sp)
    lw s1, 8(sp)
    lw s0, 4(sp)
    lw ra, 0(sp)
    addi sp, sp, 28

    ret


exep88: 
    addi a1, x0, 88
    j exit2

exep90: 
    addi a1, x0, 90
    j exit2

exep91: 
    addi a1, x0, 91
    j exit2

exep92:
    addi a1, x0, 92
    j exit2
    
