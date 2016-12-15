#ifndef _RFID_H_
#define _RFID_H_
#include <inttypes.h>

#ifndef NULL
#define NULL ((void *)0)
#endif

typedef struct card {
    uint8_t size;
    uint8_t uid[10];
    char *name;
    struct card *next;
} card_t;

extern card_t *head;

void check(void);

#endif
