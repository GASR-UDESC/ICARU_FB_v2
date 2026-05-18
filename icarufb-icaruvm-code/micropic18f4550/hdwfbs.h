

#ifndef _HDWFBS_H_
#define _HDWFBS_H_ 1

void FB_DIGITAL_READ(icr_uint16 mem_index);
void FB_DIGITAL_WRITE(icr_uint16 mem_index);
void FB_ANALOG_READ(icr_uint16 mem_index);
void FB_IO_WRITE(icr_uint16 mem_index);
void FB_IO_READ(icr_uint16 mem_index);

//void FB_E_DELAY(icr_uint16 mem_index);

#endif

