#ifndef _HMI_MSG_H_
#define _HMI_MSG_H_
#include <avr/pgmspace.h>


#define ERROR_LED PORTA1
#define HEARTBEAT_LED PORTA3
#define emptyLCDline "               "

const char  PROGMEM  VER_FW[] = "Version: %s built on: %s %s\n";
const char  PROGMEM  VER_LIBC[] = "avr-libc version: %s\n";
const char  PROGMEM  STUD_NAME[] = "Joosep Koort";
const char  PROGMEM  tervitustekst[] = "Enter Month name first letter >";
const char  PROGMEM  kuud[6][10]= {"January","February","March","April","May","June"};
#endif /* _HMI_MSG_H */

