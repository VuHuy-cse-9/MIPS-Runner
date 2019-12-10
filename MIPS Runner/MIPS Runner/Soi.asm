.data
iArray: .word 45, 89, 50, 60, 84, 1, 53, -54, 71, 72, 80, 43, 30, 31, 12, 56, 90, 60, 102, 92
input: .asciiz "=== iArray ======================================================================\n\n"
output: .asciiz "=== Quick Sort ==================================================================\n\n"
lurid: .asciiz "\n=================================================================================\n"
vertical_bar: .asciiz "|"
asterisk: .asciiz "*"
space: .asciiz " "
enter: .asciiz "\n"

.text
	li $v0, 4				# print input
	la $a0, input				# print input
	syscall					# print input
	
	la $a0, iArray				# int* array = iArray
	li $a1, 20				# int size = 20
	li $a2, 20				# int swap1 = 20
	li $a3, 20				# int swap2 = 20
	jal printArray				# call function printArray
	
	li $v0, 4				# print lurid
	la $a0, lurid				# print lurid
	syscall					# print lurid
	
	la $a0, iArray				# int* array = iArray
	li $a1, 0				# int low = 0
	li $a2, 19				# int high = 0
	jal quickSort				# call function quickSort
	
	li $v0, 4				# print output
	la $a0, output				# print output
	syscall					# print output
	
	la $a0, iArray				# int* array = iArray
	li $a1, 20				# int size = 20
	li $a2, 20				# int swap1 = 20
	li $a3, 20				# int swap2 = 20
	jal printArray				# call function printArray
	
	li $v0, 4				# print lurid
	la $a0, lurid				# print lurid
	syscall					# print lurid
	
	j exit
	
#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#

# function printPivot(int* array, int size, int pivot, int swap) print array with pivot
printPivot:
	addi $sp, $sp, -20					# decrease stack pointer 20 bytes
	sw $a0, 16($sp)						# 16($sp) store addr of array
	sw $a1, 12($sp)						# 12($sp) store size of array
	sw $a2, 8($sp)						# 8($sp) store index of pivot
	sw $a3, 4($sp)						# 4($sp) store index of swap
	sw $zero, 0($sp)					# 0($sp) count
	
	compare_printPivot:					# for (int count = 0; count < size; count ++)
		lw $v0, 0($sp)				 	# $v0 = count
		lw $v1, 12($sp)					# $v1 = size 
		slt $v0, $v0, $v1				# $v0 = (count < size ? 1 : 0)
		beq $v0, $zero, out_loop_printPivot		# if ($v0 == 0) -> branch
								# if ($v0 != 0) -> continue
		
			lw $v0, 0($sp)				# $v0 = count
			lw $v1, 8($sp)				# $v1 = index of pivot
			addi $v1, $v1, 1			# $v1 = index of pivot + 1
			bne $v0, $v1, printPivot_pivot		# if (count != index of pivot + 1) -> branch
								# if (count == index of pivot + 1) -> continue
			
			lw $v0, 0($sp)				# $v0 = count
			sll $v0, $v0, 2				# $v0 = count * 4
			lw $v1, 16($sp)				# $v1 = addr of array
			add $v1, $v1, $v0			# $v1 = addr of array[count]
			lw $v0, ($v1)				# $v0 = array[count]
			add $a0, $zero, $v0			# print array[count]
			li $v0, 1				# print array[count]
			syscall					# print array[count]
			
			li $v0, 4				# print space
			la $a0, space				# print space
			syscall					# print space
			
			j loop_printPivot
		
		printPivot_pivot:
			lw $v0, 0($sp)				# $v0 = count
			lw $v1, 8($sp)				# $v1 = index of pivot
			bne $v0, $v1, printPivot_swap		# if (count != index of pivot) -> branch
								# if (count == index of pivot) -> continue
			
			li $v0, 4				# print vertical bar
			la $a0, vertical_bar			# print vertical bar
			syscall					# print vertical bar
			
			lw $v0, 0($sp)				# $v0 = count
			sll $v0, $v0, 2				# $v0 = count * 4
			lw $v1, 16($sp)				# $v1 = addr of array
			add $v1, $v1, $v0			# $v1 = addr of array[count]
			lw $v0, ($v1)				# $v0 = array[count]
			add $a0, $zero, $v0			# print array[count]
			li $v0, 1				# print array[count]
			syscall					# print array[count]
			
			li $v0, 4				# print asterisk
			la $a0, asterisk			# print asterisk
			syscall					# print asterisk
						
			li $v0, 4				# print vertical bar
			la $a0, vertical_bar			# print vertical bar
			syscall					# print vertical bar
			
			j loop_printPivot
			
		printPivot_swap:
			lw $v0, 0($sp)				# $v0 = count
			lw $v1, 4($sp)				# $v1 = index of swap
			bne $v0, $v1, printPivot_no_swap	# if (count != index of swap) -> branch
								# if (count == index of swap) -> continue
								
			li $v0, 4				# print vertical bar
			la $a0, vertical_bar			# print vertical bar
			syscall					# print vertical bar
			
			lw $v0, 0($sp)				# $v0 = count
			sll $v0, $v0, 2				# $v0 = count * 4
			lw $v1, 16($sp)				# $v1 = addr of array
			add $v1, $v1, $v0			# $v1 = addr of array[count]
			lw $v0, ($v1)				# $v0 = array[count]
			add $a0, $zero, $v0			# print array[count]
			li $v0, 1				# print array[count]
			syscall					# print array[count]
						
			li $v0, 4				# print vertical bar
			la $a0, vertical_bar			# print vertical bar
			syscall					# print vertical bar
			
			j loop_printPivot
			
		printPivot_no_swap:
			li $v0, 4				# print space
			la $a0, space	   			# print space
			syscall					# print space
	
			lw $v0, 0($sp)				# $v0 = count
			sll $v0, $v0, 2				# $v0 = count * 4
			lw $v1, 16($sp)				# $v1 = addr of array
			add $v1, $v1, $v0			# $v1 = addr of array[count]
			lw $v0, ($v1)				# $v0 = array[count]
			add $a0, $zero, $v0			# print array[count]
			li $v0, 1				# print array[count]
			syscall					# print array[count]

			li $v0, 4				# print space
			la $a0, space				# print space
			syscall
			
	loop_printPivot:
		lw $v0, 0($sp)					# $v0 = count
		addi $v0, $v0, 1				# $v0 = count + 1
		sw $v0, 0($sp)					# 0($sp) store count = count + 1
		
		j compare_printPivot					
		
	out_loop_printPivot:
		li $v0, 4					# print enter
		la $a0, enter					# print enter
		syscall						# print enter
		
	out_printPivot:
		addi $sp, $sp, 20				# increase stack pointer 20 bytes
		jr $ra						# jump back addr call function printPiovt
		
# function printArray(int* array, int size, int swap1, int swap2) print array
printArray:
	addi $sp, $sp, -20					# decrease stack pointer 20 bytes
	sw $a0, 16($sp)						# 16($sp) store addr of array
	sw $a1, 12($sp)						# 12($sp) store size of array
	sw $a2, 8($sp)						# 8($sp) store index of swap 1
	sw $a3, 4($sp)						# 4($sp) store index of swap 2
	sw $zero, 0($sp)					# 0($sp) count
	
	compare_printArray:					# for (int count = 0; count < size; count++)
		lw $v0, 0($sp)					# $v0 = count
		lw $v1, 12($sp)					# $v1 = size of array
		slt $v0, $v0, $v1				# $v0 = (count < size of array ? 1 : 0)
		beq $v0, $zero, out_loop_printArray		# if ($v0 == 0) -> branch
								# if ($v0 != 0) -> continue
		
		# if (count == swap1 || count == swap 2) -> branch printArray_swap
		
			lw $v0, 0($sp)				# $v0 = count
			lw $v1, 8($sp)				# $v1 = index of swap1
			beq $v0, $v1, printArray_swap		# if (count == index of swap1) -> branch
								# if (count != index of swap1) -> continue
			
			lw $v0, 0($sp)				# $v0 = count
			lw $v1, 4($sp)				# $v1 = index of swap2
			bne $v0, $v1, printArray_no_swap	# if (count != index of swap) -> branch
								# if (count == index of swap) -> continues
		
		printArray_swap:
			li $v0, 4				# print vertical bar
			la $a0, vertical_bar			# print vertical bar
			syscall					# print vertical bar
			
			lw $v0, 0($sp)				# $v0 = count
			sll $v0, $v0, 2				# $v0 = count * 4
			lw $v1, 16($sp)				# $v1 = addr of array
			add $v1, $v1, $v0			# $v1 = addr of array[count]
			lw $v0, ($v1)				# $v0 = array[count]
			add $a0, $zero, $v0			# print array[count]
			li $v0, 1				# print array[count]
			syscall					# print array[count]	
			
			li $v0, 4				# print vertical_bar	
			la $a0, vertical_bar			# print vertical_bar
			syscall					# print vertival_bar
			
			j loop_printArray
			
		printArray_no_swap:
			li $v0, 4				# print space
			la $a0, space				# print space
			syscall					# print space
			
			lw $v0, 0($sp)				# $v0 = count
			sll $v0, $v0, 2				# $v0 = count * 4
			lw $v1, 16($sp)				# $v1 = addr of array
			add $v1, $v1, $v0			# $v1 = addr of array[count]
			lw $v0, ($v1)				# $v0 = array[count]
			add $a0, $zero, $v0			# print array[count]
			li $v0, 1				# print array[count]
			syscall					# print array[count]
			
			li $v0, 4				# print space
			la $a0, space				# print space
			syscall					# print space
			
	loop_printArray:
		lw $v0, 0($sp)					# $v0 = count
		addi $v0, $v0, 1				# $v0 = count + 1
		sw $v0, 0($sp)					#  0($sp) store count = count + 1
 		
		j compare_printArray
		
	out_loop_printArray:
		li $v0, 4					# print enter
		la $a0, enter					# print enter
		syscall						# print enter
		
	out_printArray:
		addi $sp, $sp, 20				# increase stack pointer 20 bytes
		jr $ra						# jump back addr call function printArray
		
# function swap(int* array, int swap1, int swap2) swap iArray[swap1] iArray[swap2]
swap:
	addi $sp, $sp, -24
	sw $a0, 20($sp)						# 20($sp) store addr of array
	sw $a1, 16($sp)						# 16($sp) store index of swap1
	sw $a2, 12($sp)						# 12($sp) store index of swap2
								# 8($sp) store addr of array[swap1]
								# 4($sp) store addr of array[swap2]
	 							# 0($sp) temp
	
	lw $v0, 16($sp)						# $v0 = index of swap1
	sll $v0, $v0, 2						# $v0 = index * 4
	lw $v1, 20($sp)						# $v1 = addr of array
	add $v0, $v0, $v1					# $v0 = addr of array[swap1]
	sw $v0, 8($sp)						# 8($sp) store addr of array[swap1]
	
	lw $v0, 12($sp)						# $v0 = index of swap2		
	sll $v0, $v0, 2						# $v0 = index * 4
	lw $v1, 20($sp)						# $v1 = addr of array
	add $v0, $v0, $v1					# $v0 = addr of array[swap2]
	sw $v0, 4($sp)						# 4($sp) store addr of array[swap2]
	
	lw $v0, 8($sp)						# $v0 = addr of array[swap1]
	lw $v1, ($v0)						# $v1 = array[swap1]
	sw $v1, 0($sp)						# temp = array[swap1]
	
	lw $v0, 4($sp)						# $v0 = addr of array[swap2]
	lw $v1, ($v0)						# $v1 = array[swap2]
	lw $v0, 8($sp)						# $v0 = addr of array[swap1]
	sw $v1, ($v0)						# array[swap 1] = array[swap2]
	
	lw $v0, 0($sp)						# $v0 = temp
	lw $v1, 4($sp)						# $v1 = addr of array[swap2]
	sw $v0, ($v1)						# array[swap2] = temp
	
	addi $sp, $sp, 24					# increase stack pointer 24 bytes
	jr $ra							# jump back addr call function swap
	
# function partition(int* array, int low, int high) return index of partion
partition:
	addi $sp, $sp, -28
	sw $ra, 24($sp)						# 24($sp) store $ra
	sw $a0, 20($sp)						# 20($sp) store address of array
	sw $a1, 16($sp)						# 16($sp) store low
	sw $a2, 12($sp)						# 12($sp) store high
								# 8($sp) store pivot
								# 4($sp) store i
								# 0($sp) store j
	
	lw $v0, 16($sp)						# $v0 = low
	sll $v0, $v0, 2						# $v0 = low * 4
	lw $v1, 20($sp)						# $v1 = addr of array
	add $v1, $v1, $v0					# $v1 = addr of array[low]
	lw $v0, ($v1)						# $v0 = array[low]
	sw $v0, 8($sp)						# 8$(sp) store pivot = array[low] + 1
	
	lw $v0, 16($sp)						# $v0 = low
	sw $v0, 4($sp)						# 4($sp) store i = low
	
	lw $v0, 16($sp)						# $v0 = low
	addi $v0, $v0, 1					# $v0 = low + 1
	sw $v0, 0($sp)						# 0($sp) store j = low + 1
	
	compare_partition:
		lw $v0, 0($sp)					# $v0 = j
		lw $v1, 12($sp)					# $v1 = high
		slt $v0, $v1, $v0				# $v0 = (high < j ? 1 : 0)
		bne $v0, $zero, out_loop_partition		# if ($v0 != 0) -> branch
								# if ($v0 == 0) -> continue
			
			lw $v0, 0($sp)				# $v0 = j
			sll $v0, $v0, 2				# $v0 = j * 4
			lw $v1, 20($sp)				# $v1 = addr of array
			add $v1, $v1, $v0			# $v1 = addr of array[j]
			lw $v0, ($v1)				# $v0 = iArray[j]
			lw $v1, 8($sp) 				# $v1 = pivot
			
			slt $v0, $v1, $v0			# $v0 = (pivot < iArray[j] ? 1 : 0)
			bne $v0, $zero, loop_partition		# if ($v0 != 0) -> branch
								# if ($v0 == 0) -> oontinue
				
				lw $v0, 4($sp)			# $v0 = i
				addi $v0, $v0, 1		# $v0 = i + 1
				sw $v0, 4($sp)			# 4($sp) store i = i + 1
				
				#lw $v0, 4($sp)			# $v0 = i
				#lw $v1, 0($sp)			# $v1 = j
				#beq $v0, $v1, loop_partition	# if (i == j) -> branch
								# if (i != j) -> continue
				
				lw $a0, 20($sp)			# int* array = addr of array
				lw $v0, 4($sp)			# $v0 = i
				add $a1, $zero, $v0		# int swap1 = i
				lw $v0, 0($sp)			# $v0 = j
				add $a2, $zero, $v0		# int swap2 = j
				jal swap			# call function swap
				
				lw $a0, 20($sp)			# int* array = addr of array
				li $a1, 20			# int size = 20
				lw $a2, 4($sp)			# int swap1 = i
				lw $a3, 0($sp)			# int swap2 = j
				jal printArray			# call function printArray
				
	loop_partition:
		lw $v0, 0($sp)					# $v0 = j
		addi $v0, $v0, 1				# $v0 = j + 1
		sw $v0, 0($sp)					# 0($sp) store j = j + 1
		
		j compare_partition
		
	out_loop_partition:
		#lw $v0, 4($sp)					# $v0 = i
		#lw $v1, 16($sp)					# $v1 = low
		#beq $v0, $v1, out_partition			# if (i == low) -> branch
								# if (i != low) -> continue
		
		lw $a0, 20($sp)					# int* array = addr of array
		lw $v0, 4($sp)					# $v0 = i
		add $a1, $zero, $v0				# int swap1 = i
		lw $v0, 16($sp)					# $v0 = low
		add $a2, $zero, $v0				# int swap2 = low
		jal swap					# call function swap
		
		lw $a0, 20($sp)					# int* array = addr of array
		li $a1, 20					# int size = 20
		lw $a2, 4($sp)					# int swap1 = i
		lw $a3, 16($sp)					# int swap2 = low
		jal printPivot					# call function printPivot
		
	out_partition:					
		lw $v0, 4($sp)					# $v0 = i (return index of pivot)
		
		lw $ra, 24($sp)					# $ra = addr call function partition
		addi $sp, $sp, 28				# increase stack pointer 28 bytes
		
		jr $ra						# jump back addr call function partition
		
# funnction quickSort(int* iArray, int low, int high)
quickSort:
	addi $sp, $sp, -20
	sw $ra, 16($sp)						# 16($sp) store addr call function quickSort
	sw $a0, 12($sp)						# 12($sp) store addr of array
	sw $a1, 8($sp)						# 8($sp) store low
	sw $a2, 4($sp)		 				# 4($sp) store high
								# 0($sp) store index of pivot
	
	lw $v0, 8($sp)						# $v0 = low
	lw $v1, 4($sp)						# $v1 = high
	slt $v0, $v0, $v1					# $v0 - ($v0 < $v1 ? 1 : 0)
	beq $v0, $zero, end_quickSort				# if ($v0 == 0) -> branch
								# if ($v0 != 0) -> continue
	
	lw $a0, 12($sp)						# load address of array
	lw $a1, 8($sp)						# load low
	lw $a2, 4($sp)						# load high
	jal partition
	
	sw $v0, 0($sp)						# 0($sp) store index of pivot
	
	lw $a0, 12($sp)						# int* array = addr of array
	lw $a1, 8($sp)						# int low = low
	lw $v0, 0($sp)						# $v0 = index of pivot
	addi $v0, $v0, -1					# $v0 = index of pivot - 1
	add $a2, $zero, $v0					# int high = index of pivot -1
	jal quickSort						# call function quickSort
	
	lw $a0, 12($sp)						# int* array = addr of array
	lw $v0, 0($sp)						# $v0 = index of pivot
	addi $v0, $v0, 1					# $v0 = index of pivot + 1
	add $a1, $zero, $v0					# int low = index of pivot + 1
	lw $a2, 4($sp)						# int high = high
	jal quickSort						# call function quickSort
	
	end_quickSort:
		lw $ra, 16($sp)					# $ra = addr call function quickSort
		addi $sp, $sp, 20				# increase stack pointer 20 bytes
		jr $ra						# jump back addr call function quickSort
		
exit:
