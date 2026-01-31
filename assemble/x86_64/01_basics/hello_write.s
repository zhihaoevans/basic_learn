.section .data
msg:
  .ascii "Hello, x86_64!\n"
len = . - msg

.section .text
.globl _start
_start:
  mov $1, %rax        # sys_write
  mov $1, %rdi        # fd = stdout
  lea msg(%rip), %rsi # buf
  mov $len, %rdx      # count
  syscall

  mov $60, %rax       # sys_exit
  xor %rdi, %rdi
  syscall
