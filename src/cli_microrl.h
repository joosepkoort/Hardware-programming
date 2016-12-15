#ifndef _CLI_MICROCL_H_
#define _CLI_MICROCL_H_

void read_card(void);
void add_card(const char *const *argv);
void remove_card(const char *const *argv);
void list_cards(void);
void cli_print(const char * str);
int cli_execute(int argc, const char *const *argv);
#endif /* End _CLI_MICROCL_H_ header guard */
