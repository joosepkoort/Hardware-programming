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
#include "../lib/helius_microrl/microrl.h"
#include "cli_microrl.h"
#include <util/atomic.h>
#include "../lib/matejx_avr_lib/mfrc522.h"
#include "rfid.h"

#define UART_STATUS_MASK 0x00FF
#define BAUD 9600


volatile uint32_t time;

int in_list;
int done;

//microrl object and pointer creation
microrl_t rl;
microrl_t *prl = &rl;

static inline void init_rfid_reader(void)
{
    /* Init RFID-RC522 */
    MFRC522_init();
    PCD_Init();
}


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
    DDRA |= _BV(DDA1);
    // Init UART3
    uart3_init(UART_BAUD_SELECT(BAUD, F_CPU));
    stderr = &uart3_out;
    // init UART0
    uart0_init(UART_BAUD_SELECT(BAUD, F_CPU));
    clock();
    //interrupts
    sei();
    stdout = &uart0_io;
    stdin = &uart0_io;
        fprintf_P(stdout,
              PSTR(STUD_NAME"\n"));
    fprintf_P(stdout,
              PSTR(CONSOLE_HELP1));
    fprintf_P(stdout, PSTR(CONSOLE_HELP2));
    //init lcd
    lcd_init();
    //clears lcd screen
    lcd_clrscr();
    //init cli
    microrl_init(prl, cli_print);
    microrl_set_execute_callback (prl, cli_execute);
}


static inline void print_version()
{
    fprintf_P(stderr, PSTR(VER_FW1 GIT_DESCR VER_FW2 __DATE__ " " __TIME__ "\n"));
    fprintf_P(stderr, PSTR(VER_LIBC __AVR_LIBC_VERSION_STRING__ " " VER_GCC
                           __VERSION__ "\n"));
}


static inline void print_startup()
{
    lcd_home();
    lcd_puts_P(PSTR(STUD_NAME));
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


//checks if rfid card is in contact
void check(void)
{   
    //known card contact var
    static uint32_t since_allowed;
    
    //unknown card contact var
    static uint32_t since_blocked;
    
    //card contact var
    if(PICC_IsNewCardPresent()) {
        
        /* Kind of a same as in_list, but with smaller scope (needed, when illegit card is in contact while door is open */
        int found = 0;
        
        /* In case we have cards in list */
        if (head != NULL) {
        
            card_t *current;
            current = head;
            
            
            /* Iteration through the list */
            while (current != NULL) {
            
                Uid card_uid;
                Uid *uid_ptra = &card_uid;
                PICC_ReadCardSerial(uid_ptra);
                
                /* In case the card in list examined is the same in contact. */
                if(!memcmp(card_uid.uidByte, current->uid, card_uid.size)){
                    
                    in_list = 1;
                    PORTA |= _BV(PORTA1);
                    since_allowed = time;
                    lcd_clrscr();
                    lcd_puts_P(PSTR(STUD_NAME));
                    lcd_goto(0x40);
                    lcd_puts(current->name);
                    done = 0;
                    found = 1;
                }
                current = current->next;
            }
        }
        
        /* In case we have no cards in list or we have no match */
        if (head == NULL || found == 0) {
            in_list = 0;
            PORTA &= ~_BV(PORTA1);
            since_blocked = time;
            lcd_clrscr();
            lcd_puts_P(PSTR(STUD_NAME));
            lcd_goto(0x40);
            lcd_puts_P(PSTR(ACCESS));
            done = 0;
        }
        
        /* Extending a local scope variable to global scope variable */
        in_list = found;
    }
    
    if(in_list == 1 && (time-since_allowed)<3) {
        PORTA |= _BV(PORTA1);
    } else {
        PORTA &= ~_BV(PORTA1);
    }        
    
    if (((time-since_blocked)>=7) && ((time-since_allowed)>=7) && done == 0) {
        lcd_clrscr();
        lcd_puts_P(PSTR(STUD_NAME));
        done = 1;
    }
}

//main method
int main (void)
{
    init_rfid_reader();
    hw_init();
    print_startup();
    print_version();
    done = 1;
    while (1) {
        heartbeat();
        microrl_insert_char(prl, (uart0_getc() & UART_STATUS_MASK));
         check();
    }
}

//System clock
ISR(TIMER1_COMPA_vect)
{
    time++;
}
