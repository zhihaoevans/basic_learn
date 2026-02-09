.section .text
.globl _start
_start:
  rdtsc
  shl $32, %rdx
  or %rdx, %rax
  mov %rax, %rdi
  mov $60, %rax
  syscall
