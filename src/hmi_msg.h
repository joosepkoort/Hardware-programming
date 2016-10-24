#ifndef _HMI_MSG_H_
#define _HMI_MSG_H_

#define ERROR_LED PORTA1
#define HEARTBEAT_LED PORTA3
#define emptyLCDline "               "

const char  PROGMEM  VER_FW[] = "Version: %s built on: %s %s\n";
const char  PROGMEM  VER_LIBC[] = "avr-libc version: %s\n";
const char  PROGMEM  STUD_NAME[] = "Joosep Koort";
const char  PROGMEM  tervitustekst[] = "Enter Month name first letter >";

const char PROGMEM  j1[]   = "January";
const char PROGMEM  f[]   = "February";
const char PROGMEM  m1[]  = "March";
const char PROGMEM  a[]   = "April";
const char PROGMEM  m2[]  = "May";
const char PROGMEM  j2[]   = "June";

PGM_P const kuud[] PROGMEM = {j1,f,m1,a,m2,j2};
#endif /* _HMI_MSG_H */

