
#ifndef _LEPROTOCOL_H_
#define _LEPROTOCOL_H_ 1

#ifndef RSCONTROL
#define RSCONTROL 50
#endif

#ifndef LP_BUF_SIZE
#define LP_BUF_SIZE 6
#endif

#ifndef LP_ADDRESS
#define LP_ADDRESS 0x04
#endif

#define LP_TOKEN 0
#define LP_NOTOKEN 1

#include "icarutypes.h"

void lp_init();

icr_int1 lp_istoken();


//char timed_getc();


icr_int1 lp_recv();

icr_int1 lp_recvtk();

void lp_send(icr_uint8 *msg, icr_int1 token);

icr_uint8 * lp_stc2msg(icr_uint8 *st, icr_uint8 *msg, icr_uint8 t);
icr_uint8 * lp_msg2stc(icr_uint8 *msg, icr_uint8 *st, icr_uint8 t);

void lp_sendTokenTo(icr_uint8 addr);

icr_uint8 * lp_getBuffer();



#endif
