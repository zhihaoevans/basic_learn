.section .data
arr:
  .quad 1, 2, 3, 4, 5
arr_len = 5

.section .text
.globl _start
_start:
  xor %rax, %rax      # sum
  xor %rcx, %rcx      # index

loop_arr:
  add arr(,%rcx,8), %rax
  inc %rcx
  cmp $arr_len, %rcx
  jne loop_arr

  mov $60, %rbx
  mov %rax, %rdi
  mov %rbx, %rax
  syscall
