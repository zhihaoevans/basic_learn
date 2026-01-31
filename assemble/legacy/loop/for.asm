
for.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <f>:
   0:	31 c0                	xor    %eax,%eax
   2:	85 ff                	test   %edi,%edi
   4:	7e 15                	jle    1b <f+0x1b>
   6:	31 d2                	xor    %edx,%edx
   8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
   f:	00 
  10:	01 d0                	add    %edx,%eax
  12:	83 c2 01             	add    $0x1,%edx
  15:	39 fa                	cmp    %edi,%edx
  17:	75 f7                	jne    10 <f+0x10>
  19:	f3 c3                	repz retq 
  1b:	f3 c3                	repz retq 

Disassembly of section .comment:

0000000000000000 <.comment>:
   0:	00 47 43             	add    %al,0x43(%rdi)
   3:	43 3a 20             	rex.XB cmp (%r8),%spl
   6:	28 47 4e             	sub    %al,0x4e(%rdi)
   9:	55                   	push   %rbp
   a:	29 20                	sub    %esp,(%rax)
   c:	34 2e                	xor    $0x2e,%al
   e:	38 2e                	cmp    %ch,(%rsi)
  10:	35 20 32 30 31       	xor    $0x31303220,%eax
  15:	35 30 36 32 33       	xor    $0x33323630,%eax
  1a:	20 28                	and    %ch,(%rax)
  1c:	52                   	push   %rdx
  1d:	65 64 20 48 61       	gs and %cl,%fs:0x61(%rax)
  22:	74 20                	je     44 <f+0x44>
  24:	34 2e                	xor    $0x2e,%al
  26:	38 2e                	cmp    %ch,(%rsi)
  28:	35 2d 34 34 29       	xor    $0x2934342d,%eax
	...

Disassembly of section .eh_frame:

0000000000000000 <.eh_frame>:
   0:	14 00                	adc    $0x0,%al
   2:	00 00                	add    %al,(%rax)
   4:	00 00                	add    %al,(%rax)
   6:	00 00                	add    %al,(%rax)
   8:	01 7a 52             	add    %edi,0x52(%rdx)
   b:	00 01                	add    %al,(%rcx)
   d:	78 10                	js     1f <.eh_frame+0x1f>
   f:	01 1b                	add    %ebx,(%rbx)
  11:	0c 07                	or     $0x7,%al
  13:	08 90 01 00 00 14    	or     %dl,0x14000001(%rax)
  19:	00 00                	add    %al,(%rax)
  1b:	00 1c 00             	add    %bl,(%rax,%rax,1)
  1e:	00 00                	add    %al,(%rax)
  20:	00 00                	add    %al,(%rax)
  22:	00 00                	add    %al,(%rax)
  24:	1d 00 00 00 00       	sbb    $0x0,%eax
  29:	00 00                	add    %al,(%rax)
  2b:	00 00                	add    %al,(%rax)
  2d:	00 00                	add    %al,(%rax)
	...
