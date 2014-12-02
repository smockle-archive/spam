## Daniel J. Ellard -- 02/21/94
## palindrome.asm -- read a line of text and test if it is a palindrome.
##
## A palindrome is a string that is exactly the same when read backwards
## as when it is read forward (e.g. anna).
##
## Whitespace is considered significant in this version, so "ahahaha"
## is a palindrome while "aha haha" is not.
##
## Register usage:
## $t1 - A - initially, the address of the first character in the string S.
## $t2 - B - initially, the address of the the last character in S.
## $t3 - the character at address A.
## $t4 - the character at address B.
## $v0 - syscall parameter / return values.
## $a0 - syscall parameters.
## $a1 - syscall parameters.

## Jake and Clay -- 10/03/14
## Rewrite Danny's work, swapping register names for numbers representing
## our setup in our Registry object.
## 00-03: $t1-$t4
## 29:    $v0
## 30-31: $a0-$a1
## 04-28: misc.


.text
main:
	
## read the string S:
	la 30, string_space
	li 31, 1024
	li 29, 8		# load "read_string" code into $v0.
    nop
	syscall

	la 0, string_space
	la 1, string_space

length_loop:			
	lb 2, 0, 1
	beqz 2, end_length_loop # if $t3 == 0, branch out of loop.

	addi 1, 1, 1	# otherwise, increment B,
	b length_loop

end_length_loop:
	subi 1, 1, 1	# subtract 1 to move B back past \0

test_loop:
	bge 0, 1, is_palin
	lb 2, 0, 0		# load the byte at addr A into $t3,
	lb 3, 0, 1		# load the byte at addr B into $t4.
	bne 2, 3, not_palin

# Otherwise,

	addi 0, 0, 1	# increment A,
	subi 1, 1, 1	# decrement B,
	b test_loop

is_palin:
	la 30, is_palin_msg
	li 29, 4
    nop
	syscall
	b exit

not_palin:
	la 30, not_palin_msg 
	li 29, 4
    nop
	syscall
	b exit

exit:				
	li 29, 10		# load "exit" code into $v0.
    nop
	syscall			# make the system call.
    end

.data
is_palin_msg: The string is a palindrome.
not_palin_msg: The string is not a palindrome.
string_space: ""
