.data
x: .word 1, 2, 3
.text
j lab
addi $s0, $0, 1
lab:
li $t0, 10