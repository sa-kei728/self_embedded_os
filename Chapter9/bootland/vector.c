#include "defines.h"

extern void start(void);
extern void intr_softerr(void);
extern void intr_syscall(void);
extern void intr_serintr(void);

/*
 * Setting of Interrupt Vector
 * It is placed at the beginning address according to the definition of the linker script.
 */
void (*vectors[]) (void) = {
    start,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,
    intr_syscall,  intr_softerr,  intr_softerr,  intr_softerr,
     NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,
     NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,
     NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,
     NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,
     NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,
    intr_serintr,  intr_serintr,  intr_serintr,  intr_serintr,  /* SCI0 */
    intr_serintr,  intr_serintr,  intr_serintr,  intr_serintr,  /* SCI1 */
    intr_serintr,  intr_serintr,  intr_serintr,  intr_serintr,  /* SCI2 */
};
