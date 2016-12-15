#ifndef _CLI_MICROCL_H_
#define _CLI_MICROCL_H_

void cli_print(const char * str);
int cli_execute(int argc, const char *const *argv);
void read(void);
void add(const char *const *argv);
void remove(const char *const *argv);
void list(void);
#endif /* End _CLI_MICROCL_H_ header guard */
