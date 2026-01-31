.section .text
.globl _start
_start:
  mov $1, %rcx        # i = 1
  xor %rax, %rax      # sum = 0

loop_start:
  add %rcx, %rax      # sum += i
  inc %rcx
  cmp $11, %rcx       # while i < 11
  jne loop_start

  mov %rax, %rdi      # exit with sum (low byte)
  mov $60, %rax       # sys_exit
  syscall
