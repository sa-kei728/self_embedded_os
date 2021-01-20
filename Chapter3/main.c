#include "defines.h"
#include "serial.h"
#include "lib.h"

static int init(void)
{
    /* linker script symbol*/
    extern int erodata, data_start, edata, bss_start, ebss;

    /* initialize data and bss area */
    memcpy(&data_start, &erodata, (long)&edata - (long)&data_start);
    memset(&bss_start, 0, (long)&ebss - (long)&bss_start);

    /* initialize serial */
    serial_init(SERIAL_DEFAULT_DEVICE);

    return 0;
}

int global_data = 0x10;         // .data section
int global_bss;                 // .bss  section
static int static_data = 0x20;  // .data section
static int static_bss;          // .bss  section

static void printval(void)
{
    puts("global_data = "); putxval(global_data, 0); puts("\n");
    puts("global_bss  = "); putxval(global_bss,  0); puts("\n");
    puts("static_data = "); putxval(static_data, 0); puts("\n");
    puts("static_bss  = "); putxval(static_bss,  0); puts("\n");
}

int main(void)
{
    init();

    puts("Hello World!\n");

    printval();
    puts("overwrite variables.\n");
    global_data = 0x20;
    global_bss  = 0x30;
    static_data = 0x40;
    static_bss  = 0x50;
    printval();

    while(1);

    return 0;
}
