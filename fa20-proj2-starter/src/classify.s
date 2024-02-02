.globl classify

.text
classify:
    # =====================================
    # COMMAND LINE ARGUMENTS
    # =====================================
    # Args:
    #   a0 (int)    argc
    #   a1 (char**) argv
    #   a2 (int)    print_classification, if this is zero, 
    #               you should print the classification. Otherwise,
    #               this function should not print ANYTHING.
    # Returns:
    #   a0 (int)    Classification
    # Exceptions:
    # - If there are an incorrect number of command line args,
    #   this function terminates the program with exit code 89.
    # - If malloc fails, this function terminats the program with exit code 88.
    #
    # Usage:
    #   main.s <M0_PATH> <M1_PATH> <INPUT_PATH> <OUTPUT_PATH>

    
    addi t0, x0, 5
    bne a0, t0, exep89

	# =====================================
    # LOAD MATRICES
    # =====================================


    addi sp, sp, -36
    sw ra, 0(sp)
    sw s0, 4(sp)
    sw s1, 8(sp)
    sw s2, 12(sp)
    sw s3, 16(sp)
    sw s4, 20(sp)
    sw s5, 24(sp)
    sw s6, 28(sp)
    sw s7, 32(sp)

    add s0, a0, x0
    add s1, a1, x0
    add s2, a2, x0


    # allocate memory for rows and cols
    addi a0, x0, 24
    jal malloc
    beq a0, x0, exep88
    add s3, a0, x0

    # Load pretrained m0
    lw a0, 4(s1)
    addi a1, s3, 0 # pointers to integers
    addi a2, s3, 4 #
    jal read_matrix
    add s4, a0, x0

    # Load pretrained m1
    lw a0, 8(s1)
    addi a1, s3, 8  # pointers to integers
    addi a2, s3, 12 #
    jal read_matrix
    add s5, a0, x0

    # Load input matrix
    lw a0, 12(s1)
    addi a1, s3, 16  # pointers to integers
    addi a2, s3, 20  #
    jal read_matrix
    add s6, a0, x0




    # =====================================
    # RUN LAYERS
    # =====================================
    # 1. LINEAR LAYER:    m0 * input
    # 2. NONLINEAR LAYER: ReLU(m0 * input)
    # 3. LINEAR LAYER:    m1 * ReLU(m0 * input)

    # 1
    addi t3, x0, 4 # amount of bytes per element
    lw t0, 0(s3)
    lw t1, 20(s3)
    mul a0, t0, t1
    mul a0, a0, t3
    jal malloc
    beq a0, x0, exep88
    add s7, a0, x0


    add a0, s4, x0
    lw a1, 0(s3)
    lw a2, 4(s3)
    add a3, s6, x0
    lw a4, 16(s3)
    lw a5, 20(s3)
    add a6, s7, x0

    jal matmul

    # free s4 and s6
    add a0, s4, x0
    jal free
    add a0, s6, x0
    jal free


    # 2
    lw t0, 0(s3)
    lw t1, 20(s3)

    add a0, s7, x0
    mul a1, t0, t1
    jal relu

    # 3
    addi t3, x0, 4 # amount of bytes per element
    lw t0, 8(s3)
    lw t1, 20(s3)
    mul a0, t0, t1
    mul a0, a0, t3
    jal malloc
    beq a0, x0, exep88
    add s6, a0, x0

    add a0, s5, x0
    lw a1, 8(s3)
    lw a2, 12(s3)
    add a3, s7, x0
    lw a4, 0(s3)
    lw a5, 20(s3)
    add a6, s6, x0 
    jal matmul


    # =====================================
    # WRITE OUTPUT
    # =====================================
    # Write output matrix

    lw a0, 16(s1)
    add a1, s6, x0 
    lw a2, 8(s3)
    lw a3, 20(s3)
    jal write_matrix


    # =====================================
    # CALCULATE CLASSIFICATION/LABEL
    # =====================================

    bne s2, x0, end
    # Call argmax

    lw t0, 8(s3)
    lw t1, 20(s3)

    add a0, s6, x0
    mul a1, t0, t1
    jal argmax
    add s5, a0, x0

    # Print classification
    
    add a1, s5, x0
    jal print_int

    # Print newline afterwards for clarity

    addi a1, x0, 10
    jal print_char

    # free all the memory alocation left
    add a0, s7, x0
    jal free
    add a0, s6, x0
    jal free
    add a0, s5, x0
    jal free
    add a0, s3, x0
    jal free


end:
    lw s7, 32(sp)
    lw s6, 28(sp)
    lw s5, 24(sp)
    lw s4, 20(sp)
    lw s3, 16(sp)
    lw s2, 12(sp)
    lw s1, 8(sp)
    lw s0, 4(sp)
    lw ra, 0(sp)
    addi sp, sp, 36

    ret


exep88:
    addi a1, x0, 88
    j exit2

exep89:
    addi a1, x0, 89
    j exit2

exep44:
    addi a1, x0, 44
    j exit2
