#include <avr/pgmspace.h>
#include "hmi_msg.h"
const char jan[] PROGMEM = "January";
const char feb[] PROGMEM = "February";
const char mar[] PROGMEM = "March";
const char apr[] PROGMEM = "April";
const char may[] PROGMEM = "May";
const char jun[] PROGMEM = "June";

PGM_P const months[] PROGMEM = {jan, feb, mar, apr, may, jun};
