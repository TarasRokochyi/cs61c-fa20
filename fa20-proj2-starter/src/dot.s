.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int vectors
# Arguments:
#   a0 (int*) is the pointer to the start of v0
#   a1 (int*) is the pointer to the start of v1
#   a2 (int)  is the length of the vectors
#   a3 (int)  is the stride of v0
#   a4 (int)  is the stride of v1
# Returns:
#   a0 (int)  is the dot product of v0 and v1
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 75.
# - If the stride of either vector is less than 1,
#   this function terminates the program with error code 76.
# =======================================================
dot:

    # exeptions
    bge x0, a2, exep1

    bge x0, a3, exep2

    bge x0, a4, exep2

    # Prologue
    addi sp, sp, -12
    sw s0, 0(sp)
    sw s1, 4(sp)
    sw s2, 8(sp)

    # pointers to arrays
    add s0, a0, x0
    add s1, a1, x0

    # counter
    add s2, x0, x0

    # return value (sum)
    add a0, x0, x0

    # strides in bytes
    addi t0, x0, 4
    mul t3, a3, t0
    mul t4, a4, t0
    ebreak

loop_start:

    bge s2, a2 loop_end
    
    lw t0, 0(s0)
    lw t1, 0(s1)

    mul t0, t0, t1
    add a0, a0, t0

    # increment pointers to next elements
    add s0, s0, t3
    add s1, s1, t4

    # increment counter
    addi s2, s2, 1
    j loop_start

loop_end:

    # Epilogue
    lw s2, 8(sp)
    lw s1, 4(sp)
    lw s0, 0(sp)
    addi sp, sp, 12
    
    ret



exep1: 
    addi a1, x0, 75
    j exit2

exep2: 
    addi a1, x0, 76
    j exit2
