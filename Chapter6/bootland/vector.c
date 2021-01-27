#include "defines.h"

extern void start(void);

/*
 * Setting of Interrupt Vector
 * It is placed at the beginning address according to the definition of the linker script.
 */
void (*vectors[]) (void) = {
    start,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,
     NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,
     NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,
     NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,
     NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,
     NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,
     NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,
     NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,
};
