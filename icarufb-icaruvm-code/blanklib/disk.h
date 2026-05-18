
#ifndef _DISK_H_
#define _DISK_H_

#include "icarutypes.h"

void disk_init();
icr_int1 disk_write(icr_int16 address, icr_int8 val);
icr_int8 disk_read(icr_int16 address);

#endif