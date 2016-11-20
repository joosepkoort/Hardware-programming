#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "hmi_msg.h"
#include "uart_wrapper.h"
#include "print_helper.h"
#include "../lib/hd44780_111/hd44780.h"
#include "../lib/andygock_avr-uart/uart.h"
#include <util/atomic.h>

#define UART_STATUS_MASK 0x00FF
#define BAUD 9600

volatile uint32_t time;

static inline void clock(void)
{
    TCCR1A = 0;  //timer/counter 1 control register A
    TCCR1B = 0;  //timer/counter 1 control register B
    TCCR1B |= _BV(WGM12); // Turn on CTC (Clear Timer on Compare)
    TCCR1B |= _BV(CS12); // fCPU/256. cs11 faster, cs10 even more faster
    OCR1A = 62549; //1 second
    TIMSK1 |= _BV(OCIE1A); // Output Compare A Match Interrupt Enable
}

static inline void hw_init()
{
    //pin3 PORTA väljund
    DDRA |= _BV(DDA3);
    // Init UART3
    uart3_init(UART_BAUD_SELECT(BAUD, F_CPU));
    stderr = &uart3_out;
    // init UART0
    uart0_init(UART_BAUD_SELECT(BAUD, F_CPU));
    clock();
    sei();
    stdout = &uart0_io;
    stdin = &uart0_io;
    //init lcd
    lcd_init();
    //clears lcd screen
    lcd_clrscr();
}

static inline void print_version()
{
    fprintf_P(stderr, PSTR(VER_FW1  GIT_DESCR VER_FW2 __DATE__ " " __TIME__ "\n"));
    fprintf_P(stderr, PSTR(VER_LIBC __AVR_LIBC_VERSION_STRING__ "\n"));
}

static inline void print_startup()
{
    //prints student name
    fprintf_P(stdout, PSTR(STUD_NAME));
    fprintf_P(stdout, PSTR("\n"));
    lcd_home();
    lcd_puts_P(PSTR(STUD_NAME));
    //prints lab03.1 ascii table
    print_ascii_tbl(stdout);
    unsigned char asciitable [128] = {0};

    for (unsigned char i = 0; i < 128; i++) {
        asciitable[i] = i;
    }

    print_for_human(stdout, asciitable, 128);
    //asks user for letter
    fprintf_P(stdout, PSTR(WELCOME_MONTH));
}

static inline void search_month()
{
    //ask user to input first letter of month name
    char inBuf = 0;
    fscanf(stdin, "%c", &inBuf);
    fprintf(stdout, "%c\n", inBuf);
    //tries to find months
    //goes to second lcd row
    lcd_goto(LCD2ROW);

    if (uart0_peek() != UART_NO_DATA) {
        inBuf = uart0_getc() & UART_STATUS_MASK;
        printf("%c\n", inBuf);
    }

    for (int i = 0; i < 6; i++) {
        if (!strncmp_P(&inBuf, (PGM_P)pgm_read_word(&months[i]), 1)) {
            fprintf_P(stdout, (PGM_P)pgm_read_word(&months[i]));
            //goes to next line
            fputc('\n', stdout);
            lcd_puts_P((PGM_P)pgm_read_word(&months[i]));
            //prints space between months on lcd
            lcd_putc(LCDSPACE);
        }
    }

    //prints welcome message
    fprintf_P(stdout, PSTR(WELCOME_MONTH));
    //prints empty line
    lcd_puts_P(PSTR(EMPTYLCDLINE));
}

static inline void heartbeat()
{
    static uint32_t previous_time;
    uint32_t current_time = time;
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        current_time = time;
    }

    if (current_time != previous_time) {
        PORTA ^= _BV(PORTA3);
        fprintf_P(stderr, PSTR(MESSAGE_UPTIME "\n"), current_time);
        previous_time = current_time;
    }
}
//main method
int main (void)
{
    hw_init();
    print_version();
    print_startup();

    while (1) {
        heartbeat();

        if (uart0_available()) {
            search_month();
        }
    }
}

//System clock
ISR(TIMER1_COMPA_vect)
{
    time++;
}
