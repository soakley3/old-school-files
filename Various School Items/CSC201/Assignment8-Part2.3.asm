# Assignment 8.
# Create a program that performs conversions of a series of temperature values from the unit of Celsius (C) to Fahrenheit (F) using the formula F = C X 1.8 + 32. 
# The program must have a loop which on each iteration must ask the user for a temperature value in Celsius, and print the converted value in Fahrenheit.


.include "examples/IO_macros.asm"

.data

CtoF_Coefficient: .float 1.8
CtoF_Addition: .float 32

.text

# ESTABLISH VARIABLES
addi $t2, $zero, 0 # should we continue? 
addi $t3, $zero, 1 # yes if $t2 == $t3, then continue, else branch to End
# $f0 for celcius
# $f1 for farenheit 
l.s $f2, CtoF_Coefficient # contains 1.8
l.s $f3, CtoF_Addition    # contains 32

# VISUAL
#             _____________
#  0($sp)    | Celcius     | parameter
# -4($sp)    | Farenheit   | return value
# -8($sp)    | Empty       |
# -12($sp)   | Empty       | 

While: 
  print_str("\nWould you like to convert a temperature from Celcius to Farenheit? Enter 1 for yes, 0 for no.\n")

  read_int 
  move $t2, $v0 

  bne $t2, $t3, End # $t2 continue? ...if $t2 == 1 then continue, if no then jump to the end.    

  print_str("Please enter a temperature in Celcis to convert to Farenheit.\n")
  # read_float
  li $v0, 6
  syscall # $f0 now contains the Celcius temp.
                          
  # mov.s $f1, $f0          # $f1 now contains the Celcius temp.
  addi $sp, $sp, -4         # push $f0 to the stack  
  swc1 $f0, 0($sp)            # save

  j CtoF

CtoF:
  lwc1 $f1, 0($sp) # pop Celcius parameter from the stack
  #addi $sp, $sp, 4  
  mul.s $f1, $f1, $f2 # multiply by the celcius coefficient
  add.s $f1, $f1, $f3 # add 32

  #mov.s $f12, $f1 # prepare the farenheit value for printing from $f12
  addi $sp, $sp, -4
  swc1 $f1, 0($sp) # save $f1 to the stack
  j Print
  
Print:
  lwc1 $f5, 0($sp)
  addi $sp, $sp 4 # pop farenheit value from the stack.
  mov.s $f12, $f5 # prepare the farenheit value for printing from $f12
  print_str("The Farenheit temperature is: ")
  li $v0, 2
  syscall
  addi $sp, $sp, 4 # pop once more, thus resetting stack pointer position
  j While

End:

          
done
