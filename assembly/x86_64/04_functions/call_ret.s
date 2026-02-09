.section .text
.globl _start
_start:
  mov $5, %rdi
  mov $7, %rsi
  call add_two
  mov %rax, %rdi
  mov $60, %rax
  syscall

add_two:
  mov %rdi, %rax
  add %rsi, %rax
  ret
