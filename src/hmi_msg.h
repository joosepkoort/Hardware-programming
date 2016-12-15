#include <avr/pgmspace.h>
#ifndef _HMI_MSG_H_
#define _HMI_MSG_H_

#define EMPTYLCDLINE    "               "
#define STUD_NAME       "Joosep Koort"
#define WELCOME_MONTH   "Enter Month name first letter >"
#define VER_FW1         "Version: "
#define VER_FW2         " built on: "
#define VER_LIBC        "avr-libc version: "
#define VER_GCC         "avr-gcc version: "
#define MESSAGE_UPTIME  "Uptime: %lu s"
#define LCD2ROW         0x40
#define CONSOLE_HELP1   "Use backspace to delete entry and enter to confirm.\n\r"
#define CONSOLE_HELP2   "Arrow key's and del do not work currently.\n\r"
#define CON_IMPLEMENTED "Command not implemented.\n Use <help> to get help.\n"
#define CON_ARGUMENTS   "To few or to many arguments for this command\nUse <help>\n"
#define CON_CMD_IMPL    "Implemented commands:\n"
#define ACCESS          "ACCESS DENIED!"

extern PGM_P const months[];

#endif /* _HMI_MSG_H_ */


