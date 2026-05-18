
#ifndef _HARDWARE_H_
#define _HARDWARE_H_ 1

#include <18F4550.H>
#DEVICE ADC=10
//#fuses HS,NOWDT,PROTECT,NOWDT
//#fuses HS,NOWDT,PROTECT,NOUSBDIV,NOLVP
#fuses HSPLL,NOWDT,PROTECT,NOUSBDIV,NOLVP,PLL5,CPUDIV1

#use delay(clock=48000000, RESTART_WDT)
#use standard_io(c)
#use standard_io(d)
#use standard_io(e)
#use standard_io(a)
#use standard_io(b)
#use rs232(baud=38400, xmit=PIN_C6, rcv=PIN_C7, ERRORS)

/***************** Bootloader ********************/
//#include <leboot.h>

#define EEPROM_SDA  PIN_B0
#define EEPROM_SCL  PIN_B1
#use i2c(master, sda=EEPROM_SDA, scl=EEPROM_SCL)


/********************** EEPROM *******************/

#rom int8 0xF00000 ={	0,0,0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,0,0}
				

//int32 getTime();
//int32 time_var;
#define getTime() time_sec_div_100

#define CCS_FLOATPOINT 1

void hdw_init();
void hdw_run();

#endif


