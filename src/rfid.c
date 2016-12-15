#include "rfid.h"
#include "../lib/matejx_avr_lib/mfrc522.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

card_t *head = NULL;
