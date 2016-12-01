#ifndef _HMI_MSG_H_
#define _HMI_MSG_H_

#define EMPTYLCDLINE    "               "
#define STUD_NAME       "Joosep Koort"
#define WELCOME_MONTH   "Enter Month name first letter >"
#define VER_FW1         "Version: "
#define VER_FW2         " built on: "
#define VER_LIBC        "avr-libc version: "
#define MESSAGE_UPTIME  "Uptime: %lu s"
#define LCD2ROW         0x40
#define LCDSPACE        ' '

extern PGM_P const months[];

#endif /* _HMI_MSG_H_ */


