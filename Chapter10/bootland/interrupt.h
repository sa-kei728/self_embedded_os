#ifndef _INTERRUPT_H_INCLUDED_
#define _INTERRUPT_H_INCLUDED_

/* linker script symbol */
extern char softvec;
#define SOFRVEC_ADDR (&softvec)

typedef short softvec_type_t;

typedef void (*softvec_handler_t)(softvec_type_t type, unsigned long sp);

#define SOFTVECS ((softvec_handler_t *)SOFRVEC_ADDR)

#define INTR_ENABLE     asm volatile ("andc.b #0x3f,ccr")
#define INTR_DISABLE    asm volatile ("orc.b  #0xc0,ccr")

/* initialize SW interrupt vector */
int softvec_init(void);

/* Setting of SW interrupt vector */
int softvec_setintr(softvec_type_t type, softvec_handler_t handler);

/* common interrupt handler */
void interrupt(softvec_type_t type, unsigned long sp);

#endif /* _INTERRUPT_H_INCLUDED_ */