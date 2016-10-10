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
    fprintf(stdout, "%s \n", STUD_NAME);
    print_ascii_tbl(stdout);
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

