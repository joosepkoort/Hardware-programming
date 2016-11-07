#ifndef _HMI_MSG_H_
#define _HMI_MSG_H_

#define HEARTBEAT_LED   PORTA3
#define EMPTYLCDLINE    "               "
#define STUD_NAME       "Joosep Koort"
#define TERVITUSTEKST   "Enter Month name first letter >"
#define VER_FW1         "Version: "
#define VER_FW2         " built on: "
#define VER_LIBC        "avr-libc version: "
#define UPTIME          "Uptime: %lu s"

const char jan[] PROGMEM = "January";
const char feb[] PROGMEM = "February";
const char mar[] PROGMEM = "March";
const char apr[] PROGMEM = "April";
const char may[] PROGMEM = "May";
const char jun[] PROGMEM = "June";

PGM_P const kuud[] PROGMEM = {jan,feb,mar,apr,may,jun};

#endif /* _HMI_MSG_H */


