.data

.text

addi $t1, $0, 100 # register A 
addi $t2, $0, 200 # register B 

addi $t4, $0, 2 # set the multiplier to multiply A. 

mul $t3, $t4, $t1   # store '2A' into register C - $t4(2) * $t1(100) = 200
add $t3, $t3, $t2 # C = C + B

addi $t5, $0, 268500992 # set memory address to write the value of register C

sw, $t3, 0($t5) # save the value within register C to the memory location 268500992

	
# the following 2-line instructions are needed for the program to exit properly
li    $v0, 10               # 10 is the exit program syscall
syscall                     # exit program



