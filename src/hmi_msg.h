#ifndef _HMI_MSG_H_
#define _HMI_MSG_H_
#include <avr/pgmspace.h>

#define LDC_NOT_OP "LCD not operational"
#define STUD_NAME "Joosep Koort"
#define VERSIOON = "Version: %s built on: %s %s\n"
#define LIBC "avr-libc version: %s\n"
#define HEX "\"0x%02x\""
#define CHAR "%c"
#define TYHIK "\n"
#define ERR "Error"
#define ERR_GEN "Program error"

#define tervitustekst "Enter    Month    name    first    letter    >"
//const char *kuud[6] = {"January", "February", "March", "April" , "May", "June"  };
const char kuud[6][10] PROGMEM = {"January", "February", "March", "April" , "May", "June"  };
const char VER_FW[]  PROGMEM = "Version: %s built on: %s %s\n";
const char VER_LIBC[]  PROGMEM = "avr-libc version: %s\n";



#endif /* _HMI_MSG_H */

