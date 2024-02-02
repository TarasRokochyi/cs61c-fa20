.globl write_matrix

.text
# ==============================================================================
# FUNCTION: Writes a matrix of integers into a binary file
# FILE FORMAT:
#   The first 8 bytes of the file will be two 4 byte ints representing the
#   numbers of rows and columns respectively. Every 4 bytes thereafter is an
#   element of the matrix in row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is the pointer to the start of the matrix in memory
#   a2 (int)   is the number of rows in the matrix
#   a3 (int)   is the number of columns in the matrix
# Returns:
#   None
# Exceptions:
# - If you receive an fopen error or eof,
#   this function terminates the program with error code 93.
# - If you receive an fwrite error or eof,
#   this function terminates the program with error code 94.
# - If you receive an fclose error or eof,
#   this function terminates the program with error code 95.
# ==============================================================================
write_matrix:

    # Prologue
    addi sp, sp, -28
    sw ra, 0(sp)
    sw s0, 4(sp)
    sw s1, 8(sp)
    sw s2, 12(sp)
    sw s3, 16(sp)
    sw s4, 20(sp)
    sw s5, 24(sp) # reg for malloc

    add s0, a0, x0
    add s1, a1, x0
    add s2, a2, x0
    add s3, a3, x0

    add a1, s0, x0 # file name
    addi a2, x0, 1 # permission
    jal fopen
    blt a0, x0, exep93
    add s4, a0, x0 # returned file descriptor

    # writing rows and cols to buffer
    addi a0, x0, 8
    jal malloc
    beq a0, x0, exep88 
    add s5, a0, x0 # pointer to memory from malloc
    sw s2, 0(s5)
    sw s3, 4(s5)

    add a1, s4, x0
    add a2, s5, x0
    addi a3, x0, 2
    addi a4, x0, 4
    jal fwrite
    addi t0, x0, 2
    blt a0, t0, exep94

    # free malloc
    add a0, s5, x0
    jal free

    mul t0, s2, s3 

    add a1, s4, x0
    add a2, s1, x0
    add a3, t0, x0
    addi a4, x0, 4
    addi sp, sp, -4
    sw t0, 0(sp)
    jal fwrite
    lw t0, 0(sp)
    addi sp, sp, 4
    blt a0, t0, exep94

    add a1, s4, x0
    jal fclose
    blt a0, x0, exep95

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

exep93: 
    addi a1, x0, 93
    j exit2

exep94: 
    addi a1, x0, 94
    j exit2

exep95:
    addi a1, x0, 95
    j exit2
