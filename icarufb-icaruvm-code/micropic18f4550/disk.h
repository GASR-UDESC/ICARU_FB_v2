
#ifndef _DISK_H_
#define _DISK_H_

#include "icarutypes.h"

void disk_init();
icr_int1 disk_write(icr_uint16 address, icr_uint8 val);
icr_uint8 disk_read(icr_uint16 address);

#endif