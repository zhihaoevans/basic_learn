AS=as
LD=ld
ASFLAGS=
LDFLAGS=

EXAMPLES := \
  01_basics/hello_write \
  01_basics/exit_code \
  02_control_flow/loop_sum \
  02_control_flow/if_else \
  03_data/strings \
  03_data/arrays \
  04_functions/call_ret \
  05_stack/stack_frame \
  06_syscalls/syscall_table \
  07_files/open_read_write \
  08_misc/rdtsc

all: $(EXAMPLES)

%: %.o
	$(LD) $(LDFLAGS) -o $@ $<

%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

.SUFFIXES:

clean:
	rm -f $(EXAMPLES) $(addsuffix .o,$(EXAMPLES))

.PHONY: all clean
