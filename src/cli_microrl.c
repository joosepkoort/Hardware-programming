#include <stdio.h>
#include <string.h>
#include <avr/pgmspace.h>
#include "hmi_msg.h"
#include "print_helper.h"
#include "../lib/hd44780_111/hd44780.h"

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

const cli_cmd_t cli_cmds[] = {
    {help_cmd, help_help, cli_print_help, 0},
    {ver_cmd, ver_help, cli_print_ver, 0},
    {ascii_cmd, ascii_help, cli_print_ascii_tbls, 0},
    {month_cmd, month_help, cli_handle_month, 1}
};


void cli_print(const char * str)
{
    fprintf(stdout, "%s", str);
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

