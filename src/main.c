#include <avr/pgmspace.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "print_helper.h"
#include "hmi_msg.h"
#include "../lib/hd44780_111/hd44780.h"
#include <string.h>

#define  BLINK_DELAY_MS 100


int main (void)
{
    //pin3 PORTA väljund
    DDRA |= _BV(DDA3);
    // Init veakonsooli UART3 and prindib libc info
    uart3_init();
    stderr = &uart3_out;
    // init cli (stdin and stdout)
    uart0_init();
    stdout = &uart0_io;
    stdin = &uart0_io;
    //init lcd ja prindib õpilase nime
    lcd_init();
    lcd_clrscr();
    lcd_puts_P(PSTR(STUD_NAME));
    fprintf_P(stderr, PSTR(VER_FW), PSTR(GIT_DESCR), PSTR(__DATE__),
              PSTR(__TIME__));
    fprintf_P(stderr, PSTR(VER_LIBC), PSTR(__AVR_LIBC_VERSION_STRING__));
    //prindib õpilase nime
    fprintf_P(stdout, PSTR(STUD_NAME));
    fprintf_P(stdout, PSTR("\n"));
    //prindib lab03.1 ascii käsureale
    print_ascii_tbl(stdout);
    unsigned char asciitabel [128] = {0};

    for (unsigned char i = 0; i < 128; i++) {
        asciitabel[i] = i;
    }

    print_for_human(stdout, asciitabel, 128);

    while (1) {
        //vaste staatuse boolean. 1 = pole olemas. 0 = olemas
        int x = 1;
        //set blink led on
        PORTA |= _BV(HEARTBEAT_LED);
        _delay_ms(BLINK_DELAY_MS);
        //ask user to input first letter of month name
        char inBuf = 0;
        fprintf_P(stdout, PSTR(tervitustekst));
        fscanf(stdin, "%c", &inBuf);
        fprintf(stdout, "%c\n", inBuf);

        //üritab kuu nime leida
        for    (int i = 0; i < 6; i++) {
            if (!strncmp_P(&inBuf, (PGM_P)pgm_read_word(&kuud[i]), 1)) {
                x = 0;
                //kui leiab vaste, siis:
                //prindib konsooli
                fprintf_P(stdout, (PGM_P)pgm_read_word(&kuud[i]));
                fputc('\n', stdout);

                //kontrollib, et kuvataks tervitusteksti ainult üks kord
                if (x != 0) {
                    fprintf_P(stdout, PSTR(tervitustekst));
                }

                //ja lcd teisele reale
                //viga seisnes antud ülesandes selles, et kui leiti mitu kuud, prinditi need üksteisest üle.
                //Üks võimalus oleks eraldada kuud ja minna käsuga lcd_goto(0x46) nt teise rea keskele, et kirjutada teine väärtus esimese taha.
                //mina olen aga printinud mõlemad kuud samma kohta väikese vahega.
                lcd_goto(0x40);
                //tühik on vajalik kustutamiseks esimene väärtus
                lcd_puts_P(PSTR(emptyLCDline));
                lcd_goto(0x40);
                lcd_puts_P((PGM_P)pgm_read_word(&kuud[i]));
            }

            //kui
            if (x != 0) {
                //teeb teise rea tühjaks kui ei leia vastet
                lcd_goto(0x40);
                lcd_puts_P(PSTR(emptyLCDline));
            }

            //ootab natuke, enne teise kuu printimist
            _delay_ms(BLINK_DELAY_MS);
            _delay_ms(BLINK_DELAY_MS);
        }

        //Lülitab ledi välja, siis kui rohkem iteratsioone pole. Praegusel juhul while (1) ei lõppe ära
        PORTA &= ~_BV(HEARTBEAT_LED);
        _delay_ms(BLINK_DELAY_MS);
    }
}



