#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

#include "../lib/hd44780_111/hd44780.h"
#include "hmi_msg.h"
#include "../lib/andygock_avr-uart/uart.h"
#include "print_helper.h"
#include "cli_microrl.h"
#include "../lib/matejx_avr_lib/mfrc522.h"
#include "rfid.h"

#define NUM_ELEMS(x) (sizeof(x) / sizeof((x)[0]))

void cli_print(const char * str);
void cli_print_help(const char *const *argv);
void cli_print_ver(const char *const *argv);
void cli_print_ascii_tbls(const char *const *argv);
void cli_handle_month(const char *const *argv);
void cli_print_cmd_error(void);
void cli_print_cmd_arg_error(void);
int cli_execute(int argc, const char *const *argv);

typedef struct cli_cmd {
    PGM_P cmd;
    PGM_P help;
    void (*func_p)();
    const uint8_t func_argc;
} cli_cmd_t;

const char help_cmd[]   PROGMEM = "help";
const char help_help[]  PROGMEM = "Get help";
const char ver_cmd[]    PROGMEM = "version";
const char ver_help[]   PROGMEM = "Print FW version";
const char ascii_cmd[]  PROGMEM = "ascii";
const char ascii_help[] PROGMEM = "print ASCII tables";
const char month_cmd[]  PROGMEM = "month";
const char month_help[] PROGMEM =
    "Find month by it's first character. Usage: month <character>";
const char read_cmd[] PROGMEM = "read";
const char read_help[] PROGMEM = "Read UID from RFID card";
const char add_cmd[] PROGMEM = "add";
const char add_help[] PROGMEM =
    "Add card to memory by name (card needs to be in contact)";
const char remove_cmd[] PROGMEM = "remove";
const char remove_help[] PROGMEM = "Remove card from memory by name";
const char list_cmd[] PROGMEM = "list";
const char list_help[] PROGMEM = "List all valid cards";


const cli_cmd_t cli_cmds[] = {
    {help_cmd, help_help, cli_print_help, 0},
    {ver_cmd, ver_help, cli_print_ver, 0},
    {ascii_cmd, ascii_help, cli_print_ascii_tbls, 0},
    {month_cmd, month_help, cli_handle_month, 1},
    {read_cmd, read_help, read_card, 0},
    {add_cmd, add_help, add_card, 1},
    {remove_cmd, remove_help, remove_card, 1},
    {list_cmd, list_help, list_cards, 0}
};


void cli_print(const char * str)
{
    fprintf(stdout, "%s", str);
}

void read_card(void)
{
    Uid uid;
    Uid *uid_ptr = &uid;
    printf_P(PSTR("\n"));

    if (PICC_IsNewCardPresent()) {
        printf("Card selected!\n");
        PICC_ReadCardSerial(uid_ptr);
        printf("UID size: 0x%02X\n", uid.size);
        printf("UID sak: 0x%02X\n", uid.sak);
        printf("Card UID: ");

        for (byte i = 0; i < uid.size; i++) {
            printf("%02X", uid.uidByte[i]);
        }

        printf_P(PSTR("\n"));
    } else {
        printf_P((PSTR("No card detected!\n")));
    }
}

void add_card(const char *const *argv)
{
    int is_found = 0;

    if (PICC_IsNewCardPresent()) {
        if (head != NULL) {
            card_t *current;
            current = head;
            int number = 1;

            while (current != NULL && is_found == 0) {
                uint8_t *uid = current->uid;
                Uid card_uid;
                Uid *uid_ptra = &card_uid;
                PICC_ReadCardSerial(uid_ptra);

                if (!memcmp(current->name, argv[1], (strlen(current->name) + 1)) ||
                        !memcmp(card_uid.uidByte, current->uid, card_uid.size)) {
                    is_found = 1;
                    printf("%d. ", number);

                    for (byte i = 0; i < current->size; i++) {
                        printf("%02X", uid[i]);
                    }

                    printf(" %s", current->name);
                }

                current = current->next;
                number++;
            }
        }

        if (is_found == 0) {
            card_t *new_card;
            Uid uid;
            Uid *uid_ptr = &uid;
            new_card = malloc(sizeof(card_t));
            PICC_ReadCardSerial(uid_ptr);
            memcpy(&(new_card->size), &(uid.size), 1);
            memcpy(new_card->uid, uid.uidByte, uid.size);
            new_card->name = malloc(strlen(argv[1]) + 1);

            if (new_card == NULL || new_card->uid == NULL || new_card->name == NULL) {
                printf_P(PSTR("Not enough memory. Please remove any of the cards added."));
            }

            strcpy(new_card->name, argv[1]);
            new_card->next = NULL;

            if (head != NULL) {
                card_t *current;
                current = head;

                while (current->next != NULL) {
                    current = current->next;
                }

                current->next = new_card;
            } else {
                head = new_card;
            }
        }
    } else if (is_found == 0) {
        printf_P(PSTR("No card detected!"));
    }

    printf_P(PSTR("\n"));
}

void remove_card(const char *const *argv)
{
    card_t *current;
    card_t *previous;
    current = head;
    previous = head;
    int in_list = 0;

    while (current != NULL) {
        if (current == head && current->next == NULL &&
                !memcmp(current->name, argv[1], (strlen(current->name) + 1))) {
            head = NULL;
            free(current->name);
            free(current);
            current = NULL;
            previous = NULL;
            in_list = 1;
        } else if (current == head && current->next != NULL &&
                   !memcmp(current->name, argv[1], (strlen(current->name) + 1))) {
            head = current-> next;
            free(current->name);
            free(current);
            current = head;
            previous = head;
            in_list = 1;
        } else if (current->next != NULL &&
                   !memcmp(current->name, argv[1], (strlen(current->name) + 1))) {
            previous->next = current->next;
            free(current->name);
            free(current);
            current = previous->next;
            in_list = 1;
        } else if (current->next == NULL  &&
                   !memcmp(current->name, argv[1], (strlen(current->name) + 1))) {
            previous->next = NULL;
            free(current->name);
            free(current);
            current = NULL;
            in_list = 1;
        } else if (current->next != NULL) {
            previous = current;
            current = current->next;
        } else {
            previous = current;
            current = NULL;
        }
    }

    if (in_list == 0) {
        printf("No card with that name!");
    }

    printf_P(PSTR("\n"));
}

void list_cards(void)
{
    if (head == NULL) {
        printf_P(PSTR("No cards added to the list!"));
    } else {
        int number = 1;
        card_t *current;
        current = head;

        while (current->next != NULL) {
            printf("%d. ", number);
            uint8_t *uid = current->uid;

            for (byte i = 0; i < current->size; i++) {
                printf("%02X", uid[i]);
            }

            printf(" %s", current->name);
            current = current->next;
            number++;
            printf_P(PSTR("\n"));
        }

        printf("%d. ", number);
        uint8_t *uid = current->uid;

        for (byte i = 0; i < current->size; i++) {
            printf("%02X", uid[i]);
        }

        printf(" %s", current->name);
    }

    printf_P(PSTR("\n"));
}


void cli_print_help(const char *const *argv)
{
    (void) argv;
    printf_P(PSTR("\n"));
    printf_P(PSTR(CON_CMD_IMPL));

    for (uint8_t i = 0; i < NUM_ELEMS(cli_cmds); i++) {
        printf_P(cli_cmds[i].cmd);
        printf_P(PSTR(" : "));
        printf_P(cli_cmds[i].help);
        printf_P(PSTR("\n"));
    }
}


void cli_print_ver(const char *const *argv)
{
    (void)argv;
    printf_P(PSTR("\n"));
    printf_P(PSTR(VER_FW1 GIT_DESCR VER_FW2 __DATE__ " " __TIME__ "\n"));
    printf_P(PSTR(VER_LIBC __AVR_LIBC_VERSION_STRING__ " " VER_GCC __VERSION__
                  "\n"));
}

/* Print ascii table */
void cli_print_ascii_tbls(const char *const *argv)
{
    (void)argv;
    print_ascii_tbl(stdout);
    unsigned char asciitable [128] = {0};

    for (unsigned char i = 0; i < 128; i++) {
        asciitable[i] = i;
    }

    print_for_human(stdout, asciitable, 128);
}
/* End print ascii table */
/* Scan and print months and display name of month on LCD second row */
void cli_handle_month(const char *const *argv)
{
    (void) argv;
    printf("\n\r");
    lcd_clr(LCD2ROW, 16);
    lcd_goto(LCD2ROW);

    for (int i = 0; i < 6; i++) {
        if (!strncmp_P(argv[1], (PGM_P)pgm_read_word(&months[i]),
                       strlen(argv[1]))) {
            fprintf_P(stdout, (PGM_P)pgm_read_word(&months[i]));
            printf("\n\r");
            lcd_puts_P((PGM_P)pgm_read_word(&months[i]));
            lcd_goto(0x48);
        }
    }
}
/* End scan and print months and display name of month on LCD second row */
/*  */
void cli_print_cmd_error(void)
{
    printf_P(PSTR("\n"));
    printf_P(PSTR(CON_IMPLEMENTED));
}
/*  */
/*  */
void cli_print_cmd_arg_error(void)
{
    printf_P(PSTR("\n"));
    printf_P(PSTR(CON_ARGUMENTS));
}
/*  */
/* Execute callback */
int cli_execute(int argc, const char *const *argv)
{
    for (uint8_t i = 0; i < NUM_ELEMS(cli_cmds); i++) {
        if (!strcmp_P(argv[0], cli_cmds[i].cmd)) {
            // Test do we have correct arguments to run command
            // Function arguments count shall be defined in struct
            if ((argc - 1) != cli_cmds[i].func_argc) {
                cli_print_cmd_arg_error();
                return 0;
            }

            // Hand argv over to function pointer,
            // cross fingers and hope that funcion handles it properly
            cli_cmds[i].func_p (argv);
            return 0;
        }
    }

    cli_print_cmd_error();
    return 0;
}

