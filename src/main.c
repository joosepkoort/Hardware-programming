#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#define __ASSERT_USE_STDERR
#include <assert.h>
#include "uart.h"
#include "print_helper.h"
#include "hmi_msg.h"
#include <string.h>
#define BLINK_DELAY_MS 100

int main (void)
{
    /* set pin 3 of PORTA for output*/
    DDRA |= _BV(DDA3);
    /* Init error console as stderr in UART3 and print user code info */
    uart3_init();
    stderr = &uart3_out;
    uart0_init();
    stdout = &uart0_io;
    stdin = &uart0_io;
    fprintf(stderr, "Version: %s built on: %s %s\n",
            GIT_DESCR, __DATE__, __TIME__);
    fprintf(stderr, "avr-libc version: %s\n", __AVR_LIBC_VERSION_STRING__);
    /*End UART3 init and info print */
    print_ascii_tbl(stderr);
    const unsigned char test[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    print_for_human(stderr, test, 10);
    fprintf(stdout, "%s \n", STUD_NAME);
    print_ascii_tbl(stdout);
    /*unsigned char test[128] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18 , 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72,73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85 ,86, 87, 88, 89, 90, 91, 92, 93, 94 , 95 ,96 ,97, 98, 99, 100, 101,102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128};
    */
    unsigned char test2 [128] = {0};

    for (unsigned char i = 0; i < 128; i++) {
        test2[i] = i;
    }

    print_for_human(stdout, test2, 128);
    char inBuf = 0;

    while (1) {

        fprintf(stdout,    "Enter    Month    name    first    letter    >");
        fscanf(stdin,    "%c",    &inBuf);
        fprintf(stdout,    "%c\n",    inBuf);

        for    (int    i    =    0;    i    <    6;    i++)    {
            if    (!strncmp(strupr(&inBuf),    kuud[i],    1))    {
                fprintf(stdout,    "%s\n",    kuud[i]);
            }
        }
    }
}

