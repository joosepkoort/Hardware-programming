/*
    Copyright 2016 Joosep Koort

    This file is part of lab06_Joosep_Koort.

    lab06_Joosep_Koort is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    lab06_Joosep_Koort is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with lab06_Joosep_Koort.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <avr/io.h>
#include <stdio.h>
#include "uart_wrapper.h"
#include "../lib/andygock_avr-uart/uart.h"

#define UART_STATUS_MASK 0x00FF //255

FILE uart0_io = FDEV_SETUP_STREAM(uart0_putchar, uart0_getchar, _FDEV_SETUP_RW);
FILE uart3_out = FDEV_SETUP_STREAM(uart3_putchar, NULL, _FDEV_SETUP_WRITE);

/* Character input for uart0 */
int uart0_getchar(FILE *stream)
{
    (void) stream;

    while (uart0_peek() == UART_NO_DATA)
        ;

    return (uart0_getc() & UART_STATUS_MASK);
}
/* End character input for uart0 */
/* Character output for uart0 */
int uart0_putchar(char c, FILE *stream)
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
int uart3_putchar(char c, FILE *stream)
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

