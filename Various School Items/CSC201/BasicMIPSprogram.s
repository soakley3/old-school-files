.data

.text

addi 	$s0, $zero, 200    	# $s0 = 0 + 20 = 20, can write $0 instead of $zero
addi    $s1, $0, 100 


add    $s3, $s0, $s1

#sw      $s1, 268501000($0)
#lw      $t1, 268501000($0)
	
# the following 2-line instructions are needed for the program to exit properly
li    $v0, 10               # 10 is the exit program syscall
syscall                     # exit program

