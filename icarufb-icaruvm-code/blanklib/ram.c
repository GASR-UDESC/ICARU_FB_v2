


#include "ram.h"

#define RAMSIZE 2000

icr_int8 RAMMEMORY[RAMSIZE]

void ram_init(){
	
}

icr_int1 ram_write(icr_int16 address, icr_int8 val){
	RAMMEMORY[address] = val;
	return 1;
}

icr_int8 ram_read(icr_int16 address){
	return RAMMEMORY[address];
}

