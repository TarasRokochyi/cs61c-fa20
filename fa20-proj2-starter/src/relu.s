.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
# 	a0 (int*) is the pointer to the array
#	a1 (int)  is the # of elements in the array
# Returns:
#	None
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 78.
# ==============================================================================
relu:
    # if a1 is less than 1, exit with 78
    bge x0, a1, exep

prologue:
    # Prologue
    addi sp, sp, -8
    sw s0, 0(sp)
    sw s1, 4(sp)

    add s0, a0, x0
    # clear counter s1
    add s1, x0, x0

loop_start:
    bge s1, a1, loop_end

    lw t0, 0(s0) 
    # if value < 0, change it to 0 
    bge t0, x0, loop_continue
    sw x0, 0(s0)

loop_continue:
    # increment pointer and counter
    addi s0, s0, 4
    addi s1, s1, 1
    j loop_start

loop_end:

    # Epilogue
    lw s0, 0(sp)
    lw s1, 4(sp)
    addi sp, sp, 8
	ret


exep:
    addi a1, x0, 78
    j exit2
