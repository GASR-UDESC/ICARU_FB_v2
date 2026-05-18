
#ifndef _RAM_H_
#define _RAM_H_

#include <icarutypes.h>

#define RAMSIZE 1500

void ram_init();
icr_int1 ram_write(icr_uint16 address, icr_uint8 val);
icr_uint8 ram_read(icr_uint16 address);

#endif