

#include "hdwfbs.h"
#include "ram.h"

/**
PINS:

X0...X100
Y0...Y100
A0...A100

*/
icr_uint16 toPicPin(icr_uint8 n){
	switch(n){
			case 100:
				return PIN_D4;
				break;
			case 101:
				return PIN_D5;
				break;
			case 102:
				return PIN_D6;
				break;
			case 103:
				return PIN_D7;
				break;
				
			case 200:
				return PIN_D0;
				break;
			case 201:
				return PIN_D1;
				break;
			case 202:
				return PIN_D2;
				break;
			case 203:
				return PIN_D3;
				break;
	}
	return 0;
}


/**
	Vars map:
	0: REQ IN
	1: PIN IN
	2: CNF OUT
	3: VAL OUT
*/
void FB_DIGITAL_READ(icr_uint16 mem_index){
	int8 a;
	a = ram_read(mem_index);
	ram_write(mem_index,a-1);
	a = ram_read(mem_index+2);
	ram_write(mem_index+2,a+1);
	
	ram_write(mem_index+3, !input(toPicPin(ram_read(mem_index+1))));
	//printf("WR (%u): %u\r\n",ram_read(mem_index+1), input(toPicPin(ram_read(mem_index+1))));
	//ram_write(mem_index+2,1);
}

/**
	Vars map:
	0: REQ IN
	1: PIN IN
	2: CNF OUT
	3: VAL IN
*/
void FB_DIGITAL_WRITE(icr_uint16 mem_index){
	int8 a;
	a = ram_read(mem_index);
	ram_write(mem_index,a-1);
	a = ram_read(mem_index+2);
	ram_write(mem_index+2,a+1);
	
	output_bit(toPicPin(ram_read(mem_index+1)), ram_read(mem_index+3)>0);
}

/**
	Vars map:
	0: REQ IN
	1: CHANNEL IN
	2: CNF OUT
	3: VAL OUT 16
*/
void FB_ANALOG_READ(icr_uint16 mem_index){
	icr_uint16 v;
	set_adc_channel(ram_read(mem_index+1));
	ram_write(mem_index+2,1);
	delay_us(20);
	v = read_adc();
	ram_write(mem_index+3, (icr_uint8) (v>>8) );
	ram_write(mem_index+3, (icr_uint8) v );
}


/**
	Vars map
	0: INIT
	1: REQ
	2: INITO
	3: CNF
	4: QI
	5: PARAMS
	6: SD_1
	7: SD_2
	8: QO
	9: STATUS
	10: RD_1
*/
void FB_IO_WRITE(icr_uint16 mem_index){

}

void FB_IO_READ(icr_uint16 mem_index){
}
/*
void FB_E_DELAY(icr_uint16 mem_index){
}
*/

