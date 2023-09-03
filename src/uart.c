
#include "type.h"
#include "defs.h"
#define UART0 0x10000000L //uart regesters address

/*MemoryMap:
0x00001000 -- boot ROM, provided by qemu
0x02000000 -- CLINT
0x0C000000 -- PLIC
0x10000000 -- UART0
0x10001000 -- virtio disk
0x80000000 -- boot ROM jumps here in machine mode, where we load our kernel
*/

#define REG(reg) ((volatile uint8_t *)(UART0 + reg))

#define ReadReg(reg) (*(REG(reg)))
#define WriteReg(reg, v) (*(REG(reg)) = (v))


#define RHR 0	// Receive Holding Register (read mode)
#define THR 0	// Transmit Holding Register (write mode)
#define DLL 0	// LSB of Divisor Latch (write mode)
#define IER 1	// Interrupt Enable Register (write mode)
#define DLM 1	// MSB of Divisor Latch (write mode)
#define FCR 2	// FIFO Control Register (write mode)
#define ISR 2	// Interrupt Status Register (read mode)
#define LCR 3	// Line Control Register
#define MCR 4	// Modem Control Register
#define LSR 5	// Line Status Register
#define MSR 6	// Modem Status Register
#define SPR 7	// ScratchPad Register

/*
LSR : we can receive data when bit0 is 1, and send data when bit5 is 1.

bit0: 0 = no data in receive holding register or FIFO.
      1 = data has been receive and saved in the receive holding register or FIFO.
bit5: 0 = transmit holding register is full. 16550 will not accept any data for transmission.
      1 = transmitter hold register (or FIFO) is empty. CPU can load the next character.
*/

#define LSR_RX_READY (1 << 0)
#define LSR_TX_IDLE  (1 << 5) 

void uart_init()
{
    //disable Interrupt
    WriteReg(IER, 0X00);

    /*To set registers DLL and DLM, we need to set LCR's bit7 to 1*/
    uint8_t lcr = ReadReg(LCR);
    WriteReg(LCR, lcr | (1 << 7));
    /* Set baud rate. Here we set value to 3, which means 38.4K when 1.8432 MHZ crystal.
       We respectively set registers DLL(low) and DLM(high) because the divisor register is 16 bits.
    This step is necessary.
    */
    
    WriteReg(DLL, 0x03);
    WriteReg(DLM, 0x00);


    lcr = 0;
    WriteReg(LCR, lcr | (3 << 0));
}


int uart_putc(char ch)
{
    while((ReadReg(LSR) & LSR_TX_IDLE) == 0);
    /*THR(write mode) and RHR(read mode) are same register.
      Datas are stored here.*/
    return WriteReg(THR, ch);
}

void uart_puts(const char *s)
{
	while (*s) {
		uart_putc(*s++);
	}
}
void uart_input()
{
    while(1)
    {
        while((ReadReg(LSR) & LSR_RX_READY)==0);
        char ch = ReadReg(RHR);
        if(ch == '\r')
            ch = '\n';
        while ((ReadReg(LSR) & LSR_TX_IDLE) == 0);
        WriteReg(THR, ch);
        //uart_write_reg(THR, '\n');
    }
}
