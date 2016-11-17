#include <avr/io.h>
#include <stdio.h>
#include "uart_wrapper.h"
#include "../lib/andygock_avr-uart/uart.h"

#define UART_STATUS_MASK 0x00FF

FILE uart0_io = FDEV_SETUP_STREAM(uart0_putchar_w, uart0_getchar_w,
                                  _FDEV_SETUP_RW);
FILE uart3_out = FDEV_SETUP_STREAM(uart3_putchar_w, NULL, _FDEV_SETUP_WRITE);

/* Character input for uart0 */
int uart0_getchar_w(FILE *stream)
{
    (void) stream;

    while (uart0_peek() == UART_NO_DATA)
        ;

    return (uart0_getc() & UART_STATUS_MASK);
}
/* End character input for uart0 */
/* Character output for uart0 */
int uart0_putchar_w(char c, FILE *stream)
{
    (void) stream;

    if (c == '\n') {
        uart0_putc('\r');
        uart0_putc('\n');
        return 0;
    }

    uart0_putc((uint8_t) c);
    return 0;
}
/* End character output for uart0 */
/* Character output for uart3 */
int uart3_putchar_w(char c, FILE *stream)
{
    (void) stream;

    if (c == '\n') {
        uart3_putc('\r');
        uart3_putc('\n');
        return 0;
    }

    uart3_putc((uint8_t) c);
    return 0;
}
/* End character output for uart3 */

