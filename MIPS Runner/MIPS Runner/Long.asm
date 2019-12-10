.data
	array: .word 5, 1, 50, 26, 17, 20, 9, 12, 42, 85, 99, 33, 46, 75, 80, 19, 55, 56, 57, 60, 42, 53, 44, 11, 98, 97, 69, 96, 2, 77, 66, 32, 13, 91, 89, 30, 50, 51, 76, 40, 3, 4, 6, 7, 8, 9, 10, 82, 81, 71
	size: .word 50
	spaceSymb: .asciiz " "
.text
	.globl _main
	
_main:
	la $a0, array
	add $a1, $0, $0
	lw $a2, size
	subi $a2, $a2, 1
	
	jal _quicksort
	
	li $v0, 10
	syscall
# func swap(x: int*, y: int*) {
#	(*x, *y) = (*y, *x)
# }
_swap:
	lw $t0, 0($a0)
	lw $t1, 0($a1)
	sw $t0, 0($a1)
	sw $t1, 0($a0)
	
	jr $ra
	
# func quicksort(array: int*, start: int, end: int) {
# 	guard start < end
#	let position = partition(array, start, end)
#	quicksort(array, start, position - 1)
#	quicksort(array, position + 1, end)
# }
_quicksort: # array, start, end = a0, a1, a2, resp.
	bge $a1, $a2, quicksort_returning # guard a1 < a2

	subi $sp, $sp, 20 # we need to save ra, array, start, end, position
	sw $ra, 0($sp) # push ra
	sw $a0, 4($sp) # push array
	sw $a1, 8($sp) # push start
	sw $a2, 12($sp) # push end
	
	jal print
	
	
	jal _partition # call partition, return to v0
	sw $v0, 16($sp) # push position
	
	lw $a1, 8($sp) # a1 = start
	lw $a2, 16($sp) # a2 = position
	subi $a2, $a2, 1 # a2 = position - 1
	jal _quicksort # call quicksort
	
	lw $a1, 16($sp) # a1 = position
	addi $a1, $a1, 1 # a1 = position + 1
	lw $a2, 12($sp) # a2 = end
	jal _quicksort # call quicksort
	
	lw $a2, 12($sp) # pop end
	lw $a1, 8($sp) # pop start
	lw $a0, 4($sp) # pop array
	lw $ra, 0($sp) # pop ra
	addi $sp, $sp, 20 # re-align the stack
	
	quicksort_returning:
		jr $ra

# func partition(array: int*, start: int, end: int) -> int {
# 	let pivot = array[end]
#	var left = start
#	var right = end - 1
#	while true {
#		while left <= right and array[left] <= pivot { left += 1 }
#		while left <= right and array[right] > pivot { right -= 1 }
#		if left >= right { break }
#		swap(array + left, array + right)
#		left += 1
#		right -= 1
#	}
#	swap(array + left, array + end)
#	return left
# }	

_partition: # array, start, end = a0, a1, a2, resp.
	subi $sp, $sp, 16 # we need to save ra, array, start, end
	sw $ra, 0($sp) # push ra
	sw $a0, 4($sp) # push rray
	sw $a1, 8($sp) # push start
	sw $a2, 12($sp) # push end
	
	# pivot, left, right = s0, s1, s2, resp.
	
	lw $s0, 12($sp) # s0 = end
	sll $s0, $s0, 2 # s0 = 4.end
	lw $t0, 4($sp) # t0 = array
	add $s0, $s0, $t0 # s0 = array + 4.end
	lw $s0, 0($s0) # pivot = s0 = array[end]
	
	lw $s1, 8($sp) # left = s1 = start
	lw $s2, 12($sp) # right = s2 = end
	subi $s2, $s2, 1 # right = end - 1
	
	loop1:
		lw $a0, 4($sp) # load array from stack
		loop2:
			bgt $s1, $s2, end_loop2 # if left > right then break
			
			sll $t0, $s1, 2 # t0 = 4.left
			add $t0, $t0, $a0 # t0 = array + 4.left
			lw $t0, 0($t0) # t0 = array[left]
			
			bgt $t0, $s0, end_loop2 # if array[left] > pivot then break
			
			addi $s1, $s1, 1 # left += 1
			
			j loop2
		end_loop2:
		
		loop3:
			bgt $s1, $s2, end_loop3 # if left > right then break
			
			sll $t0, $s2, 2 # t0 = 4.right
			add $t0, $t0, $a0 # t0 = array + 4.right
			lw $t0, 0($t0) # t0 = array[right]
			
			ble $t0, $s0, end_loop3 # if array[right] <= pivot then break
			
			subi $s2, $s2, 1 # right -= 1
			
			j loop3
		end_loop3:
		
		bge $s1, $s2, end_loop1 # if left >= right then break
		
		sll $t0, $s1, 2 # t0 = 4.left
		add $a0, $a0, $t0 # a0 = array + 4.left
		
		lw $a1, 4($sp) # a1 = array
		sll $t0, $s2, 2 # t0 = 4.right
		add $a1, $a1, $t0 # a1 = array + 4.right
		
		jal _swap # call swap
		
		addi $s1, $s1, 1 # left += 1
		subi $s2, $s2, 1 # right -= 1
	
		j loop1
	end_loop1:
	
	lw $a0, 4($sp) # a0 = array
	sll $t0, $s1, 2 # t0 = 4.left
	add $a0, $a0, $t0 # a0 = array + 4.left
	
	lw $a1, 4($sp) # a1 = array
	lw $t0, 12($sp) # t0 = end
	sll $t0, $t0, 2 # t0 = 4.end
	add $a1, $a1, $t0 # a1 = array = 4.end
	
	jal _swap # call swap
	
	add $v0, $s1, $0 # return left
	
	lw $a2, 12($sp) # pop end
	lw $a1, 8($sp) # pop start
	lw $a0, 4($sp) # pop array
	lw $ra, 0($sp) # pop ra
	addi $sp, $sp, 16 # re-align the stack
	
	partition_returning:
		jr $ra
		
print:

	subi $sp, $sp, 4
	sw $a0, 0($sp)
	
	la $t0, array
	add $t1, $0, $0
	for:
		bge $t1, 50, end_for
		li $v0, 1
		lw $a0, 0($t0)
		syscall
		
		la $a0, spaceSymb
		li $v0, 4
		syscall
		
		addi $t0, $t0, 4
		addi $t1, $t1, 1
		j for
		
	end_for:
		addi $a0, $0, 10
		li $v0, 11
		syscall
		
		lw $a0, 0($sp)
		addi $sp, $sp, 4
		
		jr $ra