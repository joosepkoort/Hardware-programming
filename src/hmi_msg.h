#ifndef _HMI_MSG_H_
#define _HMI_MSG_H_

#define ERROR_LED PORTA1
#define HEARTBEAT_LED PORTA3
#define emptyLCDline "               "
#define STUD_NAME "Joosep Koort"
#define tervitustekst "Enter Month name first letter >"
#define VER_FW "Version: %S built on: %S %S\n"
#define VER_LIBC "avr-libc version: %S\n"

const char january[] PROGMEM = "January";
const char february[] PROGMEM = "February";
const char march[] PROGMEM = "March";
const char april[] PROGMEM = "April";
const char may[] PROGMEM = "May";
const char june[] PROGMEM = "June";

PGM_P const kuud[] PROGMEM = {january,february,march,april,may,june};

#endif /* _HMI_MSG_H */


