#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#define __ASSERT_USE_STDERR
#include <assert.h>
#include "uart.h"
#include "print_helper.h"
#include "hmi_msg.h"
#include <string.h>
#define BLINK_DELAY_MS 200
#include "../lib/hd44780_111/hd44780.h"
#include <avr/pgmspace.h>


#define CONSOLE_START "console started"
//#define VER_LIBC "avr version: " __AVR_LIBC_VERSION_STRING__"\n"
//#define VER_FW "Version: " GIT_DESCR "Date" __DATE__ "Time" __TIME__

//#define VER_FW ("Version %s", GIT_DESCR )


int main (void)
{
    /*SAMM1 set pin 3 of PORTA for output*/
    DDRA |= _BV(DDA3);
    /* Init error console as stderr in UART3 and print libc info */
    uart3_init();
    stderr = &uart3_out;
    /* INIT CLI  (STDIN AND STDOUT) in urt0 and print student name*/
    uart0_init();
    stdout = &uart0_io;
    stdin = &uart0_io;
    lcd_init();
    lcd_clrscr();
    lcd_puts(STUD_NAME);
    //
    fprintf_P(stdout, VER_LIBC,  GIT_DESCR, __DATE__, __TIME__);
    fprintf_P(stdout,VER_FW, __AVR_LIBC_VERSION_STRING__);
    /*PRINT STUDENT NAME */
    fprintf_P(stdout, STUD_NAME);
    print_ascii_tbl(stdout);
    //LAB03.1 print ASCII maps to CLI
    unsigned char test2 [128] = {0};

    for (unsigned char i = 0; i < 128; i++) {
        test2[i] = i;
    }

    print_for_human(stdout, test2, 128);
    char inBuf = 0;
    //init lcd and display student name

    while (1) {
        //set blinK LED ON
        PORTA |= _BV(PORTA3);
        _delay_ms(BLINK_DELAY_MS);
        //ask user to input first letter of month name
        fprintf(stdout, tervitustekst);
        fscanf(stdin,    "%c",    &inBuf);
        fprintf(stdout,    "%c\n",    inBuf);
        //try to find month beginning with letter from list

        for    (int    i    =    0;    i    <    6;    i++)    {
            if    (!strncmp(&inBuf,    kuud[i],    1))    {
                //kui leiab vaste siis:
                //prindib konsooli
                fprintf(stdout,    "%s\n",    kuud[i]);
                //ja LCD teisele reale
                lcd_goto(0x40);
                lcd_puts("              ");
                lcd_goto(0x40);
                lcd_puts(kuud[i]);
  


            

            
            } else if  (strncmp(&inBuf,    kuud[i],    1)) {
                //teeb LCD teise rea tühjaks
                //
                lcd_goto(0x40);
                lcd_puts("               ");
            }

            //lülitab LEDi välja
            PORTA &= ~_BV(PORTA3);
            _delay_ms(BLINK_DELAY_MS);
        }
    }
}


