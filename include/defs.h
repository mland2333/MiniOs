//uart.c
#pragma once


#ifdef __cplusplus
extern "C" {
#endif


    void uart_init();
    int uart_putc(char ch);
    void uart_puts(const char* s);
    void uart_input();

#ifdef __cplusplus
}
#endif



