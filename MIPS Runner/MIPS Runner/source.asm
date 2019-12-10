.data
x: .space 10
.text
la $a0,x
addi $v0,$0,8
addi $a1,$zero,10
syscall
add $t1, $0, $a0
syscall