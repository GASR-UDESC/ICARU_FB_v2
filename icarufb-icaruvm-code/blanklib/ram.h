
#ifndef _RAM_H_
#define _RAM_H_

#include <icarutypes.h>

void ram_init();
icr_int1 ram_write(icr_int16 address, icr_int8 val);
icr_int8 ram_read(icr_int16 address);

#endif