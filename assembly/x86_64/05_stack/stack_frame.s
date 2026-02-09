.section .text
.globl _start
_start:
  mov $3, %rdi
  call fact
  mov %rax, %rdi
  mov $60, %rax
  syscall

fact:
  push %rbp
  mov %rsp, %rbp
  sub $16, %rsp
  mov %rdi, -8(%rbp)
  cmp $1, %rdi
  jle .base
  dec %rdi
  call fact
  mov -8(%rbp), %rcx
  imul %rcx, %rax
  jmp .done
.base:
  mov $1, %rax
.done:
  mov %rbp, %rsp
  pop %rbp
  ret
