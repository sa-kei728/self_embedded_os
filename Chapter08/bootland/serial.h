#ifndef _SERIAL_H_INCLUDED_
#define _SERIAL_H_INCLUDED_

int serial_init(int index);                         /* intialize device */
int serial_is_send_enable(int index);               /* check to be able to send */
int serial_send_byte(int index, unsigned char b);   /* send 1 char */
int serial_is_recv_enable(int index);               /* check to be able to recv */
unsigned char serial_recv_byte(int index);          /* recv 1 char */

#endif /* _SERIAL_H_INCLUDED_ */
