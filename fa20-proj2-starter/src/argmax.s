.globl argmax

.text
# =================================================================
# FUNCTION: Given a int vector, return the index of the largest
#	element. If there are multiple, return the one
#	with the smallest index.
# Arguments:
# 	a0 (int*) is the pointer to the start of the vector
#	a1 (int)  is the # of elements in the vector
# Returns:
#	a0 (int)  is the first index of the largest element
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 77.
# =================================================================
argmax:

    # exeption
    bge x0, a1, exep


    # Prologue
    addi sp, sp, -8
    sw s0, 0(sp)
    sw s1, 4(sp)

    add s0, a0, x0 # pointer to array
    add s1, x0, x0 # counter

    add t1, x0, x0 # biggest value 

loop_start:
    bge s1, a1, loop_end

    lw t0, 0(s0)
    bge t1, t0, loop_continue
    add a0, s1, x0 # set index of big value
    add t1, t0, x0 # set curr val to big val


loop_continue:
    addi s0, s0, 4
    addi s1, s1, 1

    j loop_start


loop_end:
    
    # Epilogue
    lw s1, 4(sp)
    lw s0, 0(sp)
    addi sp, sp, 8

    ret


exep:
    addi a1, x0, 77
    j exit2
