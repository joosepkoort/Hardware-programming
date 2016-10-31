#ifndef _HMI_MSG_H_
#define _HMI_MSG_H_

#define HEARTBEAT_LED   PORTA3
#define emptyLCDline    "               "
#define STUD_NAME       "Joosep Koort"
#define tervitustekst   "Enter Month name first letter >"
#define VER_FW          "Version: %S built on: %S %S\n"
#define VER_LIBC        "avr-libc version: %S\n"

const char jan[] PROGMEM = "January";
const char feb[] PROGMEM = "February";
const char mar[] PROGMEM = "March";
const char apr[] PROGMEM = "April";
const char may[] PROGMEM = "May";
const char jun[] PROGMEM = "June";

PGM_P const kuud[] PROGMEM = {jan,feb,mar,apr,may,jun};

#endif /* _HMI_MSG_H */


