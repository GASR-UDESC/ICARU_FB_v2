

#ifndef _NET_H_
#define _NET_H_ 1

#include "icarutypes.h"
#include "deviceconfig.h"
#define NET_MASTER 1
#define LP_ADDRESS DEVICE_ID
#define RSCONTROL 50//PIN_E1 //pin_e2
#include "leprotocol2.h"

void net_init();
void net_snd(icr_uint8 *data, icr_uint8 *t);
void net_snd_force(icr_uint8 *data, icr_uint8 t);
icr_uint8 net_rcv(icr_uint8 *data);

void net_run();

void icaru_handle_netdata(icr_uint8 *data);

#endif

