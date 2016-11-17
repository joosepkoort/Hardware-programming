#ifndef _UART_WRAPPER_H_
#define _UART_WRAPPER_H_

int uart0_putchar_w(char c, FILE *stream);
int uart0_getchar_w(FILE *stream);
int uart3_putchar_w(char c, FILE *stream);

/* http://www.ermicro.com/blog/?p=325 */

extern FILE uart0_io;
extern FILE uart3_out;

#endif /* _UART_WRAPPER_H_ header guard */
