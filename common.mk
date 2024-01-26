CROSS_COMPILE = riscv64-unknown-elf-
INC_DIR = $(OS_HOME)/include
SRC_DIR = $(OS_HOME)/src
BUILD_DIR = $(OS_HOME)/build
CFLAGS = -nostdlib -fno-builtin -march=rv64imac_zicsr_zifencei -mabi=lp64 -g -Wall -mcmodel=medany  -I$(INC_DIR)

QEMU = qemu-system-riscv64
QFLAGS = -nographic -smp 1 -machine virt -bios none

GDB = gdb-multiarch
CC = ${CROSS_COMPILE}gcc
OBJCOPY = ${CROSS_COMPILE}objcopy
OBJDUMP = ${CROSS_COMPILE}objdump
