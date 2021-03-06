.data
	textA: .asciiz "+ Nhap so a = "
	textB: .asciiz "+ Nhap so b = "
	soA: .float 0
	soB: .float 0
	kq1: 	.asciiz " \n+ Ket qua : \n\t a + b = "
	kq2: 	.asciiz " \n\t a - b = "
.text
     #Nhap so thu nhat
	la $a0,textA 
	li $v0,4
	syscall
	li $v0,6
	syscall 
	swc1 $f0,soA	
    #Nhap so thu 2
	la $a0,textB 
	li $v0,4
	syscall
	li $v0,6
	syscall
	swc1 $f0,soB
    #Chuyen du lieu sang ma nhi phan
	lw $a1,soA
	lw $a2,soB		
    #Tach cac truong cua ma nhi phan 32 bit
    	srl $t1,$a1,31			#truong sign cua so A = $t1
    	srl $t2,$a2,31			#truong sign cua so B = $t2
    	move 	$t8,$t1
	move 	$t9,$t2
     	sll $t3,$a1,1 			#Tim truong Exponent cua so A
	srl $t3,$t3,24
	subi $t3,$t3,127#Exponent A = t3
	sll $t4,$a2,1 			#Tim truong Exponent cua so B
	srl $t4,$t4,24
	subi $t4,$t4,127#Exponent B = t4 	
	sll $t5,$a1,9			#Tim truong fraction cua so A
	srl $t5,$t5,9
	ori $t5,$t5,0x00800000# t5 = 1bit + fraction A 
	sll $t6,$a2,9			#Tim truong fraction cua so B
	srl $t6,$t6,9
	ori $t6,$t6,0x00800000# t6 = 1bit + fraction B
	
###### BUOC 1: So sanh cac truong va chon dau cho phep (+) va (-)
	slt	$s0,$t3,$t4		#So sanh Exponent A va Exponent B
    	beq 	$s0,1,A_N_B# A<B
  	j A_LB_B# A >= B
A_LB_B:	bne $t3,$t4,A_L_B# A > B
	slt $s0,$t5,$t6 		#So sanh fraction A va fraction B
	beq $s0,1,A_N_B #  A < B
	beq $t5,$t6,SSExp # A == B
	j A_L_B #A>B
A_L_B:	addi $s6,$t1,0 			#s6 = bit dau cua phep +
	addi $s7,$t1,0			#s7 = bit dau cua phep -
	j ThucThi
A_N_B:
	addi $s6,$t2,0 		
	xor $s7,$t2,1			
	j ThucThi
SSExp:	beq	$t3,-127,man0		
	beq $t1,$t2,A_B_B		#So sanh Sign A va sign B
	addi $s6,$0,0 #A = - B
	addi $s7,$t1,0			
	j ThucThi	
A_B_B:	addi $s6,$t1,1 		
	xor $s7,$0,0			
	j ThucThi
man0:	beq	$t5,0x00800000,result0 #Truong hop 2 so deu bang 0

###### BUOC 2: Thuc hien phep (+),(-) tren truong Exponent, fraction cua so A va B
ThucThi:
	slt	$s1,$t3,$t4   		#So sanh Exponent A va Exponent B
	beq	$s1,0,NoSwap		
	#Doi cho Sign giua A va B
	move	$s0,$t3			
	move	$t3,$t4
	move	$t4,$s0
	#Doi cho Exponent giua A va B
	move	$s0,$t5
	move	$t5,$t6
	move	$t6,$s0
	#Doi cho fraction giua A va B
	move	$s0,$t1
	move	$t1,$t2
	move	$t2,$s0
NoSwap:
	sub	$s1,$t3,$t4	
	move	$t4,$t3			# copy t3 vao t4 de tinh toan cho phep "-"
			
dich:	addi	$s0,$0,0		# t2 la bo dem so mu
loop:	slt 	$s2,$s0,$s1
	beq	$s2,0,Add
	srl	$t6,$t6,1		# Dich sang phai truong Fraction cua so B (EA-EB) bit
	addi	$s0,$s0,1
	j loop
     #Thuc hien phep + truong fraction giua so A va V
Add:	add	$s3,$t5,$t6		
	addi	$s0,$0,0x01000000	
LoopB1:	slt	$s5,$s3,$s0		# so sanh s3 co lon hon 23 bit khong ?
	beq	$s5,1,Sub		
	srl	$s3,$s3,1		# Neu co thi Dich truong Fraction sang phai 1bit
	addi	$t3,$t3,1		# Neu co thi Tang truong Exponent them 1
	j	LoopB1
	
     #Thuc hien phep - truong fraction giua so A va V
Sub:	beq	$s1,0,A_BF_B		# Fraction A = Fraction B
A_K_B:	sub	$s4,$t5,$t6		
	abs	$s4,$s4
	addi	$s0,$0,0x007fffff	
LoopB2:	slt	$s5,$s0,$s4		#So sanh s5 co nho hon 23 bit khong ?
	beq	$s5,1,IEEE		
	sll	$s4,$s4,1		# Neu co thi Dich truong Fraction sang trai 1bit
	subi	$t4,$t4,1		# Neu co thi giam truong Exponent bot 1
	j	LoopB2
A_BF_B:	bne	$t5,$t6,A_K_B
	addi	$s4,$0,-1		# Exponent A = Exponent B => Ket qua phep (-) = 0 
###### BUOC 3: Chuan hoa cac truong fraction v� exponent cua ket qua phep (+),(-)
IEEE:		
	# Ket qua cua phep (+)
	sll	$s6,$s6,31		# Chuyen bit Sign cua phep (+) vao dung vi tri
	addi	$s1,$t3,127		# s1 la 8-bit E
	sll	$s1,$s1,23		# chuyen bit E vao dung vi tri
	sll	$s3,$s3,9		
	srl	$s3,$s3,9		# loai bo so 1 ==> s3 la truong fraction cua phep (+)
	or	$s2,$s1,$s3		# dua truong exponent va fraction vao ket qua phep (+)

	# Ket qua cua phep (-)
	sll	$s7,$s7,31		# Chuyen bit Sign cua phep (-) vao dung vi tri
	beq	$s4,-1,Bang0		# Neu s4 = -1, tra ket qua phep (-) = 0
	addi	$s1,$t4,127		# s1 la 8-bit E
	sll	$s1,$s1,23		# -chuyen bit E vao dung vi tri
	sll	$s4,$s4,9		
	srl	$s4,$s4,9		# loai bo so 1 ==> s3 la truong fraction cua phep (-)
	or	$s4,$s1,$s4		# dua truong exponent va fraction vao ket qua phep (-)
	j	Sign			
Bang0:	addi	$s4,$0,0		# tra ket qua phep (-) = 0
##### Luu truong Sign va chon ket qua cua phep (+) va (-)
Sign:	beq	$t8,$t9,A_cd_B		
	j 	A_kd_B
	A_cd_B:				# A va B cung dau
		or	$v0,$s6,$s2	# |a+b| = |a| + |b|	
		or	$v1,$s7,$s4	# |a-b| = ||a| - |b||
		j trans			# A va B khac dau 
	A_kd_B:	or	$v0,$s6,$s4	# |a+b| = ||a| - |b||
		or	$v1,$s7,$s2	# |a-b| = |a| + |b|
		j trans
result0:# truong hop hai so deu bang 0
	li	$v0,0	
	li	$v1,0
trans:	
	mtc1	$v0,$f1			# v0 la gia tri phep + theo chuan IEEE 754
	mtc1	$v1,$f2			# v1 la gia tri phep - theo chuan IEEE 754
	
###### xuat kq ra man hinh  
    #In ket qua phep (+)
	li	$v0,4
	la	$a0,kq1
	syscall
	mov.s	$f12,$f1
	li $v0,2
	syscall
    #In ket qua phep (-)	
	li	$v0,4
	la	$a0,kq2
	syscall
	mov.s	$f12,$f2
	li $v0,2
	syscall
	mfc1	$v0,$f1		
	li $v0,10		#Ket thuc chuong trinh
	syscall
