CROSS_COMPILE = riscv64-unknown-elf-
INC_DIR = $(OS_HOME)/include
SRC_DIR = $(OS_HOME)/src
BUILD_DIR = $(OS_HOME)/build
CFLAGS = -nostdlib -fno-builtin -march=rv64ima -mabi=lp64 -g -Wall -mcmodel=medany -I$(INC_DIR)
CPPFLAGS = $(CFLAG) -std=c++17
QEMU = qemu-system-riscv64
QFLAGS = -nographic -smp 1 -machine virt -bios none

GDB = gdb-multiarch
CC  = ${CROSS_COMPILE}gcc
CPP = ${CROSS_COMPILE}g++
OBJCOPY = ${CROSS_COMPILE}objcopy
OBJDUMP = ${CROSS_COMPILE}objdump
