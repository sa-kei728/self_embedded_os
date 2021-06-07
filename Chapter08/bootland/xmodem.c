#include "defines.h"
#include "serial.h"
#include "lib.h"
#include "xmodem.h"

#define XMODEM_SOH  0x01
#define XMODEM_STX  0x02
#define XMODEM_EOT  0x04
#define XMODEM_ACK  0x06
#define XMODEM_NAK  0x15
#define XMODEM_CAN  0x18
#define XMODEM_EOF  0x1a    /* ctrl + z */

#define XMODEM_BLOCK_SIZE   128

/* return send request until starting receive */
static int xmodem_wait(void)
{
    long cnt = 0;

    while(!serial_is_recv_enable(SERIAL_DEFAULT_DEVICE)){
        if( ++cnt >= 2000000 ){
            cnt = 0;
            serial_send_byte(SERIAL_DEFAULT_DEVICE, XMODEM_NAK);
        }
    }

    return 0;
}

/* receive by block size */
static int xmodem_read_block(unsigned char block_number, char* buf)
{
    unsigned char data, block_num, check_sum;
    int idx;
    /*
     *  [block format]
     *  |block_num(1Byte)|inv_block_num(1Byte)|data(128Byte)|check_sum(1Byte)|
     */

    block_num = serial_recv_byte(SERIAL_DEFAULT_DEVICE);
    if(block_num != block_number)   return -1;

    block_num ^= serial_recv_byte(SERIAL_DEFAULT_DEVICE);
    if(block_num != 0xff)   return -1;

    check_sum = 0;
    for(idx = 0; idx < XMODEM_BLOCK_SIZE; idx++){
        data = serial_recv_byte(SERIAL_DEFAULT_DEVICE);
        *(buf++) = data;
        check_sum += data;
    }

    check_sum ^= serial_recv_byte(SERIAL_DEFAULT_DEVICE);
    if(check_sum)   return -1;

    return idx;
}

long xmodem_recv(char* buf)
{
    int r, receiving = 0;
    long size = 0;
    unsigned char c, block_number = 1;

    while(1){
        if(!receiving)  xmodem_wait();

        c = serial_recv_byte(SERIAL_DEFAULT_DEVICE);

        if(c == XMODEM_EOT){            /* finish Receive */
            serial_send_byte(SERIAL_DEFAULT_DEVICE, XMODEM_ACK);
            break;
        } else if (c == XMODEM_CAN){    /* suspend Receive */
            return -1;
        } else if (c == XMODEM_SOH){    /* start Receive */
            receiving++;
            r = xmodem_read_block(block_number, buf);
            if(r < 0){  /* receive error */
                serial_send_byte(SERIAL_DEFAULT_DEVICE, XMODEM_NAK);
            } else {
                block_number++;
                size += r;
                buf  += r;
                serial_send_byte(SERIAL_DEFAULT_DEVICE, XMODEM_ACK);
            }
        } else {
            if(receiving)   return -1;
        }
    }

    return size;
}
