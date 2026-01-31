.section .data
path:
  .asciz "input.txt"

buf:
  .space 64

.section .text
.globl _start
_start:
  mov $2, %rax        # sys_open
  lea path(%rip), %rdi
  xor %rsi, %rsi      # O_RDONLY
  xor %rdx, %rdx
  syscall

  mov %rax, %r12      # fd
  mov $0, %rax        # sys_read
  mov %r12, %rdi
  lea buf(%rip), %rsi
  mov $64, %rdx
  syscall

  mov %rax, %r13      # bytes read
  mov $1, %rax        # sys_write
  mov $1, %rdi
  lea buf(%rip), %rsi
  mov %r13, %rdx
  syscall

  mov $3, %rax        # sys_close
  mov %r12, %rdi
  syscall

  mov $60, %rax
  xor %rdi, %rdi
  syscall
