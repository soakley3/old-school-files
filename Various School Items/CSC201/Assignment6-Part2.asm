# import helper functions

.include "examples/IO_macros.asm"


.data
           
.text
          
print_str("Enter hours worked: ")

read_int
          
move $t0, $v0 # $t0 hours worked

print_str("Enter wage rate: ")

read_int
          
move $t1, $v0 # $t1 wage rate per hour

addi $t3, $zero, 40 # Set the hours of a standard work week. 

addi $t4, $zero, 0 # initialize $t4 with 0, Overtime wage will be added later if applicable.

bgt $t3, $t0, CALC # if (40 > hours worked), branch to calculate. Skips calculating overtime.

addi $t4, $t0, -40 # calculate only the overtime hours and assign to $t4

sub $t0, $t0, $t4 # remove the overtime hours from the hours worked

# overtime = wage*2*hours. This could also be overtime = 2*hours*wage

addi $t5, $zero, 2 # set overtime wage

mul $t4, $t4, $t5 # overtime hours = overtime hours * overtime rate
mul $t4, $t4, $t1 # overtime hours rate = overtime hours rate * actual rate


CALC:

mul $t2, $t1, $t0 # $t2 <-- multiply the hourly wage and hours worked, to receive non-overtime salary

add $t2, $t2, $t4 # add overtime wage, or add zero
          
print_str("Total wage: ")

print_int($t2)
          
done