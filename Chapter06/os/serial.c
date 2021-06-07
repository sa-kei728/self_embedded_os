#include "defines.h"
#include "serial.h"

#define SERIAL_SCI_NUM  3

#define H8_3069F_SCI0   ((volatile struct h8_3069_sci *) 0xffffb0)
#define H8_3069F_SCI1   ((volatile struct h8_3069_sci *) 0xffffb8)
#define H8_3069F_SCI2   ((volatile struct h8_3069_sci *) 0xffffc0)

struct h8_3069f_sci {
    volatile uint8  smr;    /* Setting Serial Connection Mode*/
    volatile uint8  brr;    /* Setting Baudrate */
    volatile uint8  scr;    /* recv/trans enable/disable etc...*/
    volatile uint8  tdr;    /* write charactor */
    volatile uint8  ssr;    /* finish recv/trans */
    volatile uint8  rdr;    /* read charactor */
    volatile uint8  scmr;
};

#define H8_3069F_SCI_SMR_CKS_PER1   (0<<0)  /* Clock Select */
#define H8_3069F_SCI_SMR_CKS_PER4   (1<<0)
#define H8_3069F_SCI_SMR_CKS_PER16  (2<<0)
#define H8_3069F_SCI_SMR_CKS_PER64  (3<<0)
#define H8_3069F_SCI_SMR_MP         (1<<2)  /* Multi Processor */
#define H8_3069F_SCI_SMR_STOP       (1<<3)  /* Stop Bit length */
#define H8_3069F_SCI_SMR_OE         (1<<4)  /* Parity Category 0: Even 1: Odd */
#define H8_3069F_SCI_SMR_PE         (1<<5)  /* Parity Enabler */
#define H8_3069F_SCI_SMR_CHR        (1<<6)  /* Charactor Length (Data bits) 0: 8bit 1: 7bit*/
#define H8_3069F_SCI_SMR_CA         (1<<7)  /* Communication Mode 0: start-stop synchronous 1: clock synchronous*/

#define H8_3069F_SCI_SCR_CKS0       (1<<0)  /* Clock Enable 0 */
#define H8_3069F_SCI_SCR_CKS1       (1<<1)  /* Clock Enable 1 */
#define H8_3069F_SCI_SCR_TEIE       (1<<2)  /* Transmit Endpoint Interrupt Enable */
#define H8_3069F_SCI_SCR_MPIE       (1<<3)  /* Multi Processor Interrupt Enable */
#define H8_3069F_SCI_SCR_RE         (1<<4)  /* Enable Receive */
#define H8_3069F_SCI_SCR_TE         (1<<5)  /* Enable Transmit */
#define H8_3069F_SCI_SCR_RIE        (1<<6)  /* Enable Interrupt Receive */
#define H8_3069F_SCI_SCR_TIE        (1<<7)  /* Enable Interrupt Transmit */

#define H8_3069F_SCI_SSR_MPBT       (1<<0)  /* Multi Processor Bit Transfer */
#define H8_3069F_SCI_SSR_MPB        (1<<1)  /* Multi Processor Bit */
#define H8_3069F_SCI_SSR_TEND       (1<<2)  /* Transmit End */
#define H8_3069F_SCI_SSR_PER        (1<<3)  /* Parity Error */
#define H8_3069F_SCI_SSR_FERERS     (1<<4)  /* Framing Error / Error Signal Status*/
#define H8_3069F_SCI_SSR_OPER       (1<<5)  /* Overrun Error */
#define H8_3069F_SCI_SSR_RDRF       (1<<6)  /* Receive Data Register Full */
#define H8_3069F_SCI_SSR_TDRE       (1<<7)  /* Transmit Data Register Empty */

static struct {
    volatile struct h8_3069f_sci    *sci;
} regs[SERIAL_SCI_NUM] = {
    { H8_3069F_SCI0 },
    { H8_3069F_SCI1 },
    { H8_3069F_SCI2 },
};

/* Initialize Device */
int serial_init(int index)
{
    volatile struct h8_3069f_sci    *sci = regs[index].sci;

    sci->scr = 0;
    sci->smr = 0;
    /*
     *  [start-stop synchronous]
     *  N = (Frequency / (64 * 2^(2n - 1) * Baudrate)) * 10^6 - 1
     *  
     *  [clock synchronous]
     *  N = (Frequency / (8 * 2^(2n - 1) * Baudrate)) * 10^6 - 1
     */
    sci->brr = 64; /* generate 9600bps from 20MHz clk (if 25MHz clk, trans from 64 to 80) */
    sci->scr = H8_3069F_SCI_SCR_RE | H8_3069F_SCI_SCR_TE;   /* enable Recieve and Transmit */
    sci->ssr = 0;

    return 0;
}

/* check to be able to send */
int serial_is_send_enable(int index)
{
    volatile struct h8_3069f_sci    *sci = regs[index].sci;
    return (sci->ssr & H8_3069F_SCI_SSR_TDRE);
}

/* send 1 char */
int serial_send_byte(int index, unsigned char c)
{
    volatile struct h8_3069f_sci    *sci = regs[index].sci;

    /* wait to be able to send */
    while (!serial_is_send_enable(index));
    sci->tdr = c;
    sci->ssr &= ~H8_3069F_SCI_SSR_TDRE; /* start to Transmit */

    return 0;
}

/* check to be able to recv */
int serial_is_recv_enable(int index)
{
    volatile struct h8_3069f_sci* sci = regs[index].sci;
    return (sci->ssr & H8_3069F_SCI_SSR_RDRF);
}

/* recv 1 char */
unsigned char serial_recv_byte(int index)
{
    volatile struct h8_3069f_sci* sci = regs[index].sci;
    unsigned char c;

    /* wait for recv char*/
    while(!serial_is_recv_enable(index));
    c = sci->rdr;
    sci->ssr &= ~H8_3069F_SCI_SSR_RDRF; /* finish to receive */

    return c;
}
