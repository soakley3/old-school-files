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

mul $t2, $t1, $t0 # $t2 <-- multiply the hourly wage and hours worked, to receive salary
          
print_str("Total wage: ")

print_int($t2)
          
done