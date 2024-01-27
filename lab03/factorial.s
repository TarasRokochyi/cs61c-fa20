.globl factorial

.data
n: .word 8

.text
main:
    la t0, n
    lw a0, 0(t0)
    jal ra, factorial

    addi a1, a0, 0
    addi a0, x0, 1
    ecall # Print Result

    addi a1, x0, '\n'
    addi a0, x0, 11
    ecall # Print newline

    addi a0, x0, 10
    ecall # Exit

factorial:
    # YOUR CODE HERE

    addi sp, sp, -8   # allocate memory for ra and current argument (a0)
    sw ra, 0(sp)
    sw a0, 4(sp)

    addi a0, a0, -1    

    bne a0, x0, calc   # if n is 0, return 1
    lw a0, 4(sp)      # recover a0
    addi sp, sp, 8
    ret

calc:

    jal factorial    # call another factorial

    lw t0, 4(sp)     # recover saved registers
    lw ra, 0(sp)
    addi sp, sp, 8

    mul a0, a0, t0   # multiply return value with current argument

    ret
