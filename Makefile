include $(OS_HOME)/common.mk

SRCS_ASM := $(wildcard $(SRC_DIR)/*.S)
SRCS_C   := $(wildcard $(SRC_DIR)/*.c)

OBJS = $(SRCS_ASM:.S=.o)
OBJS += $(SRCS_C:.c=.o)

# OBJS = $(subst $(SRC_DIR),$(BUILD_DIR),$(OBJS))

OBJS =  $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS_C))
OBJS += $(patsubst $(SRC_DIR)/%.S,$(BUILD_DIR)/%.o,$(SRCS_ASM))


TARGET_ELF = $(BUILD_DIR)/kernel.elf
TARGET_BIN = $(BUILD_DIR)/kernel.bin



.DEFAULT_GOAL := all

all : $(TARGET_ELF)

$(TARGET_ELF) : $(OBJS)
	echo $(OBJS)
	$(CC) $(CFLAGS) -T $(SRC_DIR)/os.ld -o $@ $^
	${OBJCOPY} -O binary $@ $(TARGET_BIN)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.S
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

run : all
	@${QEMU} -M ? | grep virt >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit QEMU"
	@echo "------------------------------------"
	@${QEMU} ${QFLAGS} -kernel $(TARGET_ELF)

clean :
	rm -rf *.o *.bin *.elf
