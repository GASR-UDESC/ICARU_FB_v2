

#ifndef _NET_H_
#define _NET_H_ 1

#include "icarutypes.h"

void net_init();
void net_snd(icr_uint8 *data, icr_uint8 *t);
icr_uint8 net_rcv(icr_uint8 *data);

void net_run();

#endif

