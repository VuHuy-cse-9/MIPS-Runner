.data
	prompt1: .asciiz "Input first real number: \n"
	prompt2: .asciiz "Input second real number: \n"
	prompt3: .asciiz "Sum: "
	prompt4: .asciiz "Sub: "
.text
main:
	# Input the data
	la	$a0, prompt1
	li	$v0, 4
	syscall
	li	$v0, 6
	syscall
	
	mfc1 	$t0, $f0	# t0 contain the bits of first number
	
	la	$a0, prompt2
	li	$v0, 4
	syscall
	li	$v0, 6
	syscall
	
	mfc1 	$t1, $f0	# t1 contains the bits of second number
	
	
	# Add number in t0, t1 in IEEE standard
	
	# Get the sign of those float
	F_SIGN_CHECKING:
		bgez	$t0, F_GREATER_ZERO
		addi	$t2, $zero, 1
		sll	$t2, $t2, 31
		j	END_F_SIGN_CHECKING
	F_GREATER_ZERO:
		add	$t2, $zero, $zero	
	END_F_SIGN_CHECKING:			# t2 contain the sign of the first number
	S_SIGN_CHECKING:
		bgez	$t1, S_GREATER_ZERO
		addi	$t3, $zero, 1
		sll	$t3, $t3, 31
		j	END_S_SIGN_CHECKING
	S_GREATER_ZERO:
		add	$t3, $zero, $zero
	END_S_SIGN_CHECKING:			# t3 contain the sign of the second number
	
	# Split into two part, exponent and significand
	
	# Get exponent
	F_GET_EXP:
		sll	$t4, $t0, 1
		srl	$t4, $t4, 24		# t4 contains exponent of first number
	S_GET_EXP:
		sll	$t5, $t1, 1
		srl	$t5, $t5, 24		# t5 contains exponent of second number
	
	# Get significand
	F_GET_SIG:
		ori	$s0, $t0, 0x00800000
		sll	$s0, $s0, 8
		srl	$s0, $s0, 7			# Add 1 to cal
	S_GET_SIG:
		ori	$s1, $t1, 0x00800000
		sll	$s1, $s1, 8
		srl	$s1, $s1, 7			# Add 1 one cal
		
	# Set signed for SIG
		#beqz	$t2, NEXT_NUM
		#not	$s0, $s0
		#addiu	$s0, $s0, 1			# 2-complement binary
	#NEXT_NUM:
		#beqz	$t3, WHICH_GREATER
		#not	$s1, $s1
		#addiu	$s1, $s1, 1			# 2-complement binary
	
	# Increase the exponent
	WHICH_GREATER:
		bgt	$t4, $t5, A_GREATER_B
		j	B_GREATER_A
	A_GREATER_B:
		beq	$t5, $t4, END_A_GREATER_B
		addi	$t5, $t5, 1
		sra	$s1, $s1, 1
		j	A_GREATER_B
	END_A_GREATER_B:
		j	CAL
	B_GREATER_A:
		beq	$t5, $t4, END_B_GREATER_A
		addi	$t4, $t4, 1
		sra	$s0, $s0, 1
		j	B_GREATER_A
	END_B_GREATER_A:
	CAL:
	# Combine those part of float
	bne	$t2, $t3, DIFF_SIGN
	SAME_SIGN:
		addu	$t8, $s0, $s1		# t8 is sum
		subu	$t9, $s0, $s1		# t9 is sub
		# same signed -> signed of sum is signed of operand
		# same signed -> signed of sub is signed of operand xor with signed of operand
		srl	$t7, $t9, 31
		sll	$t7, $t7, 31
		xor	$t3, $t7, $t3		# 0 , 0 -> 0; 1, 1 -> 0; 1, 0 -> 1; 0, 1 -> 1
		j	END_CAL
		#addi	$t4, $t4, 1
		#sll	$t8, $t8, 1		# Change the to type 0.xxxxx
		#subi	$t5, $t5, 1
		#sll	$t9, $t9, 1		# Change the to type 0.xxxxx
	DIFF_SIGN:
		subu	$t8, $s0, $s1		# t8 is sum
		addu	$t9, $s0, $s1		# t9 is sub
		# diff signed -> signed of sub is signed of first operand
		add	$t3, $zero, $t2
		# diff signed -> signed of sum is signed of t8
		srl	$t7, $t8, 31
		sll	$t7, $t7, 31
		xor	$t2, $t7, $t2
		#addi	$t5, $t5, 1
		#sll	$t9, $t9, 1		# Change the to type 0.xxxxx
		#subi	$t4, $t4, 1
		#srl	$t8, $t8, 1		# Change the to type 0.xxxxx
	END_CAL:
		srl	$t6, $t8, 31
		beqz	$t6, SUM_NOT_NEG
		not	$t8, $t8
		addi	$t8, $t8, 1
	SUM_NOT_NEG:
		srl	$t7, $t9, 31
		beqz	$t7, SUB_NOT_NEG
		not	$t9, $t9
		addi	$t9, $t9, 1
	SUB_NOT_NEG:
	# Sum > 0x01000000
	# Check Overflow
	add	$v0, $zero, $t8
	add	$s3, $zero, $t4
	jal	STANDARDIZED
	add	$t8, $zero, $v0
	add	$t4, $zero, $s3
	
	add	$v0, $zero, $t9
	add	$s3, $zero, $t5
	jal	STANDARDIZED
	add	$t9, $zero, $v0
	add	$t5, $zero, $s3
	
	COMBINE:
	SHIFT_POS_EXP:
	sll	$t4, $t4, 23
	sll	$t5, $t5, 23
	
	SHIFT_POS_SIG:
	sll	$t8, $t8, 8
	srl	$t8, $t8, 9
	sll	$t9, $t9, 8
	srl	$t9, $t9, 9
	
	# srl	$t2, $t8, 31
	# sll	$t2, $t2, 31			# get signed of sum
	# srl	$t3, $t9, 31
	# sll	$t3, $t3, 31			# get signed of sub
	
	ADD_SIGNED:
	or	$t0, $t2, $t4
	or	$t0, $t0, $t8
	or	$t1, $t3, $t5
	or	$t1, $t1, $t9
	
	mtc1	$t0, $f12
	la	$a0, prompt3
	li	$v0, 4
	syscall
	li	$v0, 2
	syscall
	
	mtc1	$t1, $f12
	la	$a0, prompt4
	li	$v0, 4
	syscall
	li	$v0, 2
	syscall
	j END
	
	STANDARDIZED:
		blt	$v0, 0x01000000, LESS_THAN
		GREATER_THAN:
			subi	$v1, $v0, 0x01000000
			blt	$v1, 0x01000000, END_STANDARDIZED
			srl	$v0, $v0, 1
			addi	$s3, $s3, 1
			j	GREATER_THAN
		LESS_THAN:
			subi	$v1, $v0, 0x01000000
			bge	$v1, $zero, END_STANDARDIZED
			sll	$v0, $v0, 1
			subi	$s3, $s3, 1
			j	LESS_THAN
	END_STANDARDIZED:
	jr	$ra
	
	END: