#ifndef _HMI_MSG_H_
#define _HMI_MSG_H_
#include <avr/pgmspace.h>


const char VER_FW[]  PROGMEM = "Version: %s built on: %s %s\n";
const char VER_LIBC[]  PROGMEM = "avr-libc version: %s\n";
const char STUD_NAME[]     PROGMEM = "Joosep Koort";
const char tervitustekst[] PROGMEM = "Enter Month name first letter >";
const char kuud[6][10] PROGMEM = {"January","February","March","April","May","June"};
#endif /* _HMI_MSG_H */

