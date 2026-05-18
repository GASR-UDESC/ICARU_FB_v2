
#ifndef _RAM_H_
#define _RAM_H_

#include "deviceconfig.h"
#include "icarutypes.h"

#ifdef ICARU_MEGA2560
#define RAMSIZE 4000
#endif

#ifdef ICARU_UNO
#define RAMSIZE 1000
#endif

void ram_init();
icr_int1 ram_write(icr_uint16 address, icr_uint8 val);
icr_uint8 ram_read(icr_uint16 address);

#endif
