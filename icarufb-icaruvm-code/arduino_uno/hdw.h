
#ifndef _HARDWARE_H_
#define _HARDWARE_H_ 1


#define ARDUINO_MODE 1

#include "icarutypes.h"				

icr_uint8 getTime();
//int32 time_var;
//#define getTime() time_sec_div_100

void hdw_init();
void hdw_run();

#endif


