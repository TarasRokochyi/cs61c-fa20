.globl matmul

.text
# =======================================================
# FUNCTION: Matrix Multiplication of 2 integer matrices
# 	d = matmul(m0, m1)
# Arguments:
# 	a0 (int*)  is the pointer to the start of m0 
#	a1 (int)   is the # of rows (height) of m0
#	a2 (int)   is the # of columns (width) of m0
#	a3 (int*)  is the pointer to the start of m1
# 	a4 (int)   is the # of rows (height) of m1
#	a5 (int)   is the # of columns (width) of m1
#	a6 (int*)  is the pointer to the the start of d
# Returns:
#	None (void), sets d = matmul(m0, m1)
# Exceptions:
#   Make sure to check in top to bottom order!
#   - If the dimensions of m0 do not make sense,
#     this function terminates the program with exit code 72.
#   - If the dimensions of m1 do not make sense,
#     this function terminates the program with exit code 73.
#   - If the dimensions of m0 and m1 don't match,
#     this function terminates the program with exit code 74.
# =======================================================
matmul:

    # Error checks
    bge x0, a1, exep72
    bge x0, a2, exep72

    bge x0, a4, exep73
    bge x0, a5, exep73

    bne a1, a5, exep74

    # Prologue
    addi sp, sp, -32
    sw s0, 0(sp)
    sw s1, 4(sp)
    sw s2, 8(sp)
    sw s3, 12(sp)
    sw s4, 16(sp)
    sw s5, 20(sp)
    sw s6, 24(sp)
    sw ra, 28(sp)

    add s0, a0, x0
    add s1, a1, x0
    add s2, a2, x0
    add s3, a3, x0
    add s4, a4, x0
    add s5, a5, x0
    add s6, a6, x0


    add t0, x0, x0 # counter
outer_loop_start:

    # while counter less than rows in v1
    bge t0, s1, outer_loop_end

    add t2, s3, x0 # pointer to v2
    add t1, x0, x0 # second counter
inner_loop_start:

    # while counter less than cols in v2
    bge t1, s5, inner_loop_end 

    # set up for calling procedure
    add a0, s0, x0 # vector 1
    add a1, t2, x0 # vector 2
    add a2, s2, x0 # length of vectors
    addi a3, x0, 1 # stride for v1
    add a4, s5, x0 # stride for v2

    addi sp, sp, -12
    sw t0, 0(sp)
    sw t1, 4(sp)
    sw t2, 8(sp)
    jal ra, dot   # jump to dot procedure
    lw t2, 8(sp)
    lw t1, 4(sp)
    lw t0, 0(sp)
    addi sp, sp, 12

    sw a0, 0(s6) # save return value in result array

    # increment pointers and counter
    addi s6, s6, 4
    addi t2, t2, 4
    addi t1, t1, 1

    j inner_loop_start

inner_loop_end:

    # increment pointers and counter
    slli t4, s2, 2 # multiply by 4
    add s0, s0, t4
    addi t0, t0, 1

    j outer_loop_start

outer_loop_end:

    # Epilogue
    lw ra, 28(sp)
    lw s6, 24(sp)
    lw s5, 20(sp)
    lw s4, 16(sp)
    lw s3, 12(sp)
    lw s2, 8(sp)
    lw s1, 4(sp)
    lw s0, 0(sp)
    addi sp, sp, 32
    
    ret


    
exep72: 
    addi a1, x0, 72
    j exit2

exep73: 
    addi a1, x0, 73
    j exit2

exep74: 
    addi a1, x0, 74
    j exit2
