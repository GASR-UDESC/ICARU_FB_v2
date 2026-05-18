

#ifndef _DEVICECONFIG_H_
#define _DEVICECONFIG_H_ 1



/** The network device address */
#define DEVICE_ID 0x05


#if defined(__AVR_ATmega2560__)
#define ICARU_MEGA2560 1
#elif defined(__AVR_ATmega328P__)
#define ICARU_UNO 1
#else
#define ICARU_UNO 1
#endif

#endif
