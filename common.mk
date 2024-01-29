CROSS_COMPILE = riscv64-unknown-elf-
INC_DIR = $(OS_HOME)/kernel/include
SRC_DIR = $(OS_HOME)/kernel/src
BUILD_DIR = $(OS_HOME)/build
CFLAGS = -nostdlib -fno-builtin -march=rv64imac_zicsr_zifencei -mabi=lp64 -g -Wall -mcmodel=medany  -I$(INC_DIR)

QEMU = qemu-system-riscv64
QFLAGS = -nographic -smp 3 -machine virt -bios none
QFLAGS += -global virtio-mmio.force-legacy=false

GDB = gdb-multiarch
CC = ${CROSS_COMPILE}gcc
OBJCOPY = ${CROSS_COMPILE}objcopy
OBJDUMP = ${CROSS_COMPILE}objdump
