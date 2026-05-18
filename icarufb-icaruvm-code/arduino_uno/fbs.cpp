

#include "icarutypes.h"
#include "fbs.h"
#include "ram.h"
#include "hdw.h"
#include "icaru.h"


/**
0: ei: input event
1: number of event
2: eo1: output event
3: eo2:
...

*/
void FB_E_SPLIT(icr_uint16 mem_index){
	icr_uint8 i, ne, a;
	a = ram_read(mem_index);
	if(a > 0){
		ram_write(mem_index,a-1);
		ne = ram_read(mem_index+1);
		for(i=0;i<ne;i++){
			a = ram_read(mem_index+2+i);
			ram_write(mem_index+2+i,a+1);
		}
	}else{
	//printf("NO EVNT");
	}	
}

/**
0: ne: number input event
1: eo: output event
2: ei1: input event
3: ei2
...

*/
void FB_E_MERGE(icr_uint16 mem_index){
	icr_uint8 i, ne, a;
	i=0;
	ne = ram_read(mem_index);
	while(i < ne){
		a = ram_read(mem_index+2+i);
		if(a > 0){			
			ram_write(mem_index+2+i, a-1);
			a = ram_read(mem_index+1);
			ram_write(mem_index+1, a+1);
			return;
		}
		i++;
	}
}


/**
0: INIT
1: INITO:
2: IND
3: ID
4: RD_1
5: RD_2
6: RD_3
7: RD_4
8: RD_5
*/
void FB_SUBL_5(icr_uint16 mem_index){
	icr_uint8 a;
	a = ram_read(mem_index);
	ram_write(mem_index, a-1);
	a = ram_read(mem_index+1);
	ram_write(mem_index+1, a+1);
}

/**
0: START
1: STOP
2: EO
3,4,5,6: DT (32 bit)
7,8,9,10: CT (32 bit)   
11: started
12: told
*/
void FB_E_DELAY(icr_uint16 mem_index){
	icr_uint32 dt;
	icr_uint8 clocks, oc, a, ot;
	if(ram_read(mem_index+1)>0){
		ram_write(mem_index+11, 0);
		return;
	}
	if(ram_read(mem_index+11)==0){
		a = ram_read(mem_index);
		if(a>0){
			ram_write(mem_index, a-1);
			dt = ((icr_uint32)ram_read(mem_index+3))<<24 | ((icr_uint32)ram_read(mem_index+4))<<16 | ((icr_uint32)ram_read(mem_index+5))<<8 | ((icr_uint32)ram_read(mem_index+6));
			dt = dt/10;
			//printf("SET DT: %Lu\r\n", dt);
			ram_write(mem_index+7, (icr_uint8)(dt>>24));
			ram_write(mem_index+8, (icr_uint8)(dt>>16));
			ram_write(mem_index+9, (icr_uint8)(dt>>8));
			ram_write(mem_index+10, (icr_uint8)(dt));
			ram_write(mem_index+11,1);
			ram_write(mem_index+12,getTime());
			appendFBExtra(mem_index-4);
		}
		
	}else{
		oc = getTime();
		ot = ram_read(mem_index+12);
		if(ot <= oc){
			clocks = oc - ot;
		}else{
			clocks = 100 - ot-oc;
		}
		
		
		/*
		if(clocks > oc){
			clocks = clocks + 0xFF;
		}
		*/
		if(clocks > 0){
			//printf("CLOCK = %u, oc= %u, ot=%u\r\n",clocks,oc, ot);
			ram_write(mem_index+12,getTime());
			dt = ((icr_uint32)ram_read(mem_index+7))<<24 | ((icr_uint32)ram_read(mem_index+8))<<16 | ((icr_uint32)ram_read(mem_index+9))<<8 | ((icr_uint32)ram_read(mem_index+10));
			if(dt >= clocks)
				dt = dt - clocks;
			else
				dt = 0;
			ram_write(mem_index+7, (icr_uint8)(dt>>24));
			ram_write(mem_index+8, (icr_uint8)(dt>>16));
			ram_write(mem_index+9, (icr_uint8)(dt>>8));
			ram_write(mem_index+10, (icr_uint8)(dt));
			//printf("NEW SET DT: %Lu\r\n", dt);
			if(dt == 0){
				a = ram_read(mem_index+2);
				ram_write(mem_index+2, a+1);
				ram_write(mem_index+11, 0);
				return;
			}	
		}
		appendFBExtra(mem_index-4);
	}
}




