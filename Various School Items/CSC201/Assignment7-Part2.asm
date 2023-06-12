.include "examples/IO_macros.asm"
.data
.text

addi $t5, $t0, 3
sw $t5, 12($sp)

START:

print_str("Enter hours worked: ")
read_int 
move $t0, $v0 # $t0 hours worked      # save $v0 to t$t0 

print_str("Enter wage rate: ") 
read_int 
move $t7, $v0 # $t7 wage      # save $v0 to $t7 

#addi $t0, $0, 40 # hours
#addi $t7, $0, 20 # wage
#                                                                         _____________
#                                                              0($sp)    | hours       |
# Call CalcOvertimeHours subroutine                            4($sp)    | wage        |
addi $sp, $sp, -4   # Push $t0 to stack                        8($sp)    | return OT   |
sw $t0, 0($sp)      # save                                     12($sp)   | loop count  | start at 3, then decrement. 
addi $sp, $sp, -4   # Push $t7 to stack
sw $t7, 0($sp)      # save
addi $sp, $sp, -4   # Make space for return value
jal CalcOvertimeHours  
lw $t1, 0($sp)      # Pop OT wage value to $t1
addi $sp, $sp, 4  
lw $t2, 0($sp)      # pop wage to $t2
addi $sp, $sp, 4    # Pop argument from stack
lw $t3, 0($sp)      # pop worked hours to $t3 
addi $sp, $sp, 4    # Pop argument from stack
mul $t6, $t3, $t2
add $t6, $t6, $t1
print_str("Total wage: ")
print_int($t6)
j Done

CalcOvertimeHours:
  lw $t1, 8($sp)       # Load hours argument from stack 
  addi $t2, $zero, 40  # set standard hours to 40
  slt $t3, $t1, $t2 
  bne $t3, $zero, NoOvertime
  sw $t2, 8($sp)      # since there is OT hours, save standard 40 hours to the stack
  sub $t4, $t1, $t2 
  lw $t5, 4($sp)       # load wage to $t5
  mul $t4, $t4, $t5
  addi $t5, $0, 2
  mul $t4, $t4, $t5
  j ReturnOvertime
NoOvertime:
  addi $t4, $zero, 0
ReturnOvertime:
  sw $t4, 0($sp)   # Copy return value to stack: 0($sp)= ot hours * wage * 2
  jr $ra 

Done:
lw $t5, 12($sp)     # temporarily load the loop count from the stack
addi $t5, $t5, -1   # decrement the loop count
sw $t5, 12($sp)     # save new loop count
bne $t5, $0, START  # jump to the start if the loop count has not been decremented to 0

done
