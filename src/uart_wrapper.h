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

#ifndef _UART_WRAPPER_H_
#define _UART_WRAPPER_H_

int uart0_putchar(char c, FILE *stream);
int uart0_getchar(FILE *stream);
int uart3_putchar(char c, FILE *stream);
char cli_get_char(void);
/* http://www.ermicro.com/blog/?p=325 */

extern FILE uart0_io;
extern FILE uart3_out;

#endif /* _UART_WRAPPER_H_ header guard */
