


#include "ram.h"



icr_uint8 RAMMEMORY[RAMSIZE];

void ram_init(){
	
}

icr_int1 ram_write(icr_uint16 address, icr_uint8 val){
	RAMMEMORY[address] = val;
	return 1;
}

icr_uint8 ram_read(icr_uint16 address){
	return RAMMEMORY[address];
}

