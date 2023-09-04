include $(OS_HOME)/common.mk

SRCS_ASM := $(wildcard $(SRC_DIR)/*.S)
SRCS_C   := $(wildcard $(SRC_DIR)/*.c)
SRCS_CPP := $(wildcard $(SRC_DIR)/*.cpp)
#OBJS = $(SRCS_ASM:.S=.o)
#OBJS += $(SRCS_C:.c=.o)

# OBJS = $(subst $(SRC_DIR),$(BUILD_DIR),$(OBJS))
OBJS = $(patsubst $(SRC_DIR)/%.S,$(BUILD_DIR)/%.o,$(SRCS_ASM))
OBJS +=  $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS_C))
OBJS +=  $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS_CPP))


TARGET_ELF = $(BUILD_DIR)/kernel.elf
TARGET_BIN = $(BUILD_DIR)/kernel.bin



.DEFAULT_GOAL := all

all : $(TARGET_ELF)

$(TARGET_ELF) : $(OBJS)
	echo $(OBJS)
	$(CPP) $(CFLAGS) -T $(SRC_DIR)/os.ld -o $@ $^
	${OBJCOPY} -O binary $@ $(TARGET_BIN)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.S
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CPP) $(CFLAGS) -c -o $@ $< 

run : all
	@${QEMU} -M ? | grep virt >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit QEMU"
	@echo "------------------------------------"
	@${QEMU} ${QFLAGS} -kernel $(TARGET_ELF)

.PHONY : debug
debug: all
	@echo "Press Ctrl-C and then input 'quit' to exit GDB and QEMU"
	@echo "-------------------------------------------------------"
	@${QEMU} ${QFLAGS} -kernel $(TARGET_ELF) -s -S &
	@${GDB} $(TARGET_ELF) -q -x gdbinit


clean :
	rm -rf $(BUILD_DIR)

once : clean run
	


