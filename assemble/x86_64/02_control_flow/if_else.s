.section .text
.globl _start
_start:
  mov $7, %rax
  cmp $10, %rax
  jl less
  mov $1, %rdi        # return 1 if >= 10
  jmp done
less:
  mov $0, %rdi        # return 0 otherwise
done:
  mov $60, %rax
  syscall
