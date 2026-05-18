/************************************************************************
    Copyright 2015 Leandro Israel Pinto
	
	This file is part of ICARU_FB.

    ICARU_FB is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ICARU_FB is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ICARU_FB.  If not, see <http://www.gnu.org/licenses/>.
************************************************************************/

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
	//ram_write(mem_index, a-1);
	ram_write(mem_index, 1);

	a = ram_read(mem_index+1);
	ram_write(mem_index+1, a+1);
}


/**
0: EI
1: EO
2: PERMIT
*/
void FB_E_PERMIT(icr_uint16 mem_index){
	icr_uint8 a,b;
	a = ram_read(mem_index);
	ram_write(mem_index, a-1);	
	b = ram_read(mem_index+2);
	if(a>0 && b>0){	
		a = ram_read(mem_index+1);
		ram_write(mem_index+1, a+1);
	}
}


/**
0: INIT
1: INITO
2: REQ
3: CNF
4: ID
5: SD_1
6: SD_2
7: SD_3
8: SD_4
9: SD_5
10: resend
*/
void FB_PUBL_5(icr_uint16 mem_index){
	icr_uint8 msg[6];
	icr_uint8 a;
	a = ram_read(mem_index);
	if(a>0){
		ram_write(mem_index, a-1);
		a = ram_read(mem_index+1);
		ram_write(mem_index+1, a+1);
	}
	
	a = ram_read(mem_index+2);
	if(a>0){
		ram_write(mem_index+2, a-1);
		msg[0] = ram_read(mem_index+4);
		msg[1] = ram_read(mem_index+5);
		msg[2] = ram_read(mem_index+6);
		msg[3] = ram_read(mem_index+7);
		msg[4] = ram_read(mem_index+8);
		msg[5] = ram_read(mem_index+9);
		if(!net_snd(msg,6)){
			appendFBExtra(mem_index-4);
			ram_write(mem_index+10, 1);
		}else{
			a=ram_read(mem_index+3);
			ram_write(mem_index+3,a+1);
		}
	}else{
		a = ram_read(mem_index+10);
		if(a==1){
			msg[0] = ram_read(mem_index+4);
			msg[1] = ram_read(mem_index+5);
			msg[2] = ram_read(mem_index+6);
			msg[3] = ram_read(mem_index+7);
			msg[4] = ram_read(mem_index+8);
			msg[5] = ram_read(mem_index+9);
			if(!net_snd(msg,6)){
				appendFBExtra(mem_index-4);
			}else{
				ram_write(mem_index+10, 0);
				a=ram_read(mem_index+3);
				ram_write(mem_index+3,a+1);
			}
		}
	}
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




