include $(OS_HOME)/common.mk

SRCS_ASM = entry.S
SRCS_C   = start.c

OBJS =  $(SRCS_C:.c=.o)
OBJS += $(SRCS_ASM:.S=.o)



.DEFAULT_GOAL := all

all : os.elf

os.elf : $(OBJS)
	$(CC) $(CFLAGS) -T os.ld -o $@ $^
	${OBJCOPY} -O binary $@ kernel

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o : %.S
	
	$(CC) $(CFLAGS) -c -o $@ $<

run : all
	@${QEMU} -M ? | grep virt >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit QEMU"
	@echo "------------------------------------"
	@${QEMU} ${QFLAGS} -kernel os.elf

clean :
	rm -rf *.o *.bin *.elf
