.text
    .globl  main

# INPUT
main:
        li 	$v0, 4
        la 	$a0, input
        syscall
        
        li 	$v0, 5
        syscall
        move 	$s0, $v0        # $s0 = input

# CHECK IF INPUT > 1 (TODO: fill this procedure as an exercise)
L1:
	bgt	$s0, 1, L2	# if $s0 > 1 then jump to L2
	j	L3
# FOR LOOP INPUT > 1 (TODO: fill this procedure as an exercise)
L2:
	move	$t0, $0		# initialize $t0
	addi	$t0, 2		# set $t0 to 2 and use it as loop index
Check:	
	move	$t1, $s0	# $t1 = $ts0
	beq	$t1, 2, L4	# deal with if input is 2
	beq	$t0, $s0, L4	# if index reach $s0 then end loop
	divu	$t1, $t0	# do mod
	mfhi	$t2		# get the remainder
	beq	$t2, $0, L3	# if remainder = 0 then jump to L3
	addi	$t0, 1		# index add 1
	j	Check		# loop
#PRINT OUTPUT (FALSE)
L3:
        li      $v0, 4
        la      $a0, false
        syscall

        j Exit

#PRINT OUTPUT (TRUE)
L4:
        li      $v0, 4
        la      $a0, true
        syscall

        j Exit

#EXIT
Exit:
        li      $v0, 10
        syscall	

        .data
input:	.asciiz "Input: "
true: 	.asciiz "True\n"
false:  .asciiz "False\n"
