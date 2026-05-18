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

//hardware specifics
#include "hdw.h"

#include "icarutypes.h"
void dispatch_start_event();


#include "ram.h"
#include "disk.h"
#include "net.h"
#include "stack.h"
#include "instset.h"
#include "fbs.h"
#include "hdwfbs.h"





//Perform conversion for CCS C Compiler float format
//sign bit is BIT 24, while IEEE is BIT 31
//#define CCS_FLOATPOINT 1

#define FB_MAX_QUEUE 15
icr_uint16 FB_QUEUE[FB_MAX_QUEUE];
icr_uint16 FB_QUEUE_EXTRA[FB_MAX_QUEUE];
icr_uint8 FB_QUEUE_COUNT,FB_QUEUE_COUNT_EXTRA,FB_QUEUE_PROCESSED;
icr_uint16 CONN_QUEUE[15];
icr_uint8 CONN_QUEUE_COUNT,CONN_QUEUE_PROCESSED;

void appendConn(icr_uint16 p){
	CONN_QUEUE[CONN_QUEUE_COUNT] = p;
	CONN_QUEUE_COUNT++;
}
void appendFBExtra(icr_uint16 p){
	//printf("append %Lu\r\n",p);
	FB_QUEUE_EXTRA[FB_QUEUE_COUNT_EXTRA] = p;
	FB_QUEUE_COUNT_EXTRA++;
	//if(FB_)
}

void copyFromExtra(){
	icr_uint8 i;
	for(i=0;i<FB_QUEUE_COUNT_EXTRA;i++){
		FB_QUEUE[i] = FB_QUEUE_EXTRA[i];
	}
	FB_QUEUE_COUNT = FB_QUEUE_COUNT_EXTRA;
	FB_QUEUE_COUNT_EXTRA = 0;
}

void procces_connections(icr_uint16 mem_index){
	icr_uint16 index, conn_from, conn_to, conn_size, conn_pointer;
	icr_uint8 i,size;
	icr_uint8 ei,eo;
	//FB_QUEUE_COUNT = 0;
	index = mem_index;
	//printf("CONN: %Lu...", index);
	if(index == 0) return;
	
	while(TRUE){
		
		conn_from = (((icr_uint16)(ram_read(index))) << 8) | (ram_read(index+1));
		if(conn_from==0) break;
		if(conn_from!=1) { 
			
			conn_to = (((icr_uint16)(ram_read(index+2))) << 8) | (ram_read(index+3));
			//if(conn_to == 1506){
			//	printf("CONN to 1506 from %Lu, %Lu\r\n", conn_from, mem_index);
			//}
			conn_size = ram_read(index+4);
			conn_pointer = (((icr_uint16)(ram_read(index+5))) << 8) | (ram_read(index+6));
			size = conn_size & 0x7F;
			if(size == 0){
				eo = ram_read(conn_from);
				
				if(eo>0){
					FB_QUEUE[FB_QUEUE_COUNT] = conn_pointer;
					FB_QUEUE_COUNT++;
					
					ei = ram_read(conn_to);
					ram_write(conn_to, ei+1);
					ram_write(conn_from, eo-1);
				}
				
			}else{
				for(i=0; i<size; i++){
					ram_write(conn_to+i, ram_read(conn_from+i));
				}
			}
		}
		index= index + 7;
		
	}
	//printf("OK\r\n");
}



void copyDiskToRam(){
	icr_uint16 i;
	for(i=0;i<RAMSIZE;i++){
		ram_write(i, disk_read(i));
	}
}

#define TY_INT  1
#define TY_BYTE 2
#define TY_REAL 3

typedef union _operand
{
    icr_float f;
    icr_uint8 bytes[4];
    icr_uint32 i;
} Operand;

#ifdef CCS_FLOATPOINT
//thanks to: https://www.ccsinfo.com/forum/viewtopic.php?t=18460 (plehman)
void convert_ieee_to_microchip(icr_uint8 *Value) 
{ 
   icr_int1   Temp; 

   Temp = shift_left(&Value[1], 1, 0); 
   Temp = shift_left(&Value[0], 1, Temp); 
   shift_right(&Value[1], 1, Temp); 
} 

void convert_microchip_to_ieee(icr_uint8 *Value) 
{ 
   icr_int1   Temp; 
    
   Temp = shift_left(&Value[1], 1, 0); 
   Temp = shift_right(&Value[0], 1, Temp); 
   shift_right(&Value[1], 1, Temp); 
}
#endif

void res_popO(STACK *st, icr_uint8 *bytes, icr_uint8 o)
{
    bytes[0] = 0;
    bytes[1] = 0;
    bytes[2] = 0;
    bytes[3] = 0;
    switch(o)
    {
    case TY_BYTE:
        stk_pop(st, &bytes[0]);
        break;
    case TY_INT:
        stk_pop(st, &bytes[0]);
        stk_pop(st, &bytes[1]);
        break;
    case TY_REAL:
		stk_pop(st, &bytes[0]);
        stk_pop(st, &bytes[1]);
        stk_pop(st, &bytes[2]);
        stk_pop(st, &bytes[3]);
		#ifdef CCS_FLOATPOINT
		convert_ieee_to_microchip(bytes);
		#endif
        break;
    }
}

#define CONV_INT2BYTE (TY_INT<<4) | TY_BYTE
#define CONV_INT2REAL (TY_INT<<4) | TY_REAL
#define CONV_REAL2INT (TY_REAL<<4) | TY_INT
#define CONV_BYTE2INT (TY_BYTE<<4) | TY_INT

/**
conv [0:top, 1:second][conv]
*/

int8 convertOperand(Operand *o, icr_uint8 type)
{
    switch(type)
    {
    case CONV_INT2REAL:
        (*o).f = (float)(*o).i;
        return TY_REAL;
        break;
    case CONV_REAL2INT:
        (*o).i = (int32)(*o).f;
        return TY_INT;
        break;
    case CONV_INT2BYTE:
        (*o).i = (*o).i&0xFF;
        return TY_BYTE;
        break;

    }
    return type;
}

void performOperation(STACK * st, icr_uint8 conv, icr_uint8 types, icr_uint8 op)
{
    Operand o1, o2, r;
    icr_uint8 rtype;

    res_popO(st, o2.bytes, types & 0x0F);
    res_popO(st, o1.bytes, types >> 4);
    /*
    printf("operands %f[%02X%02X%02X%02X], %f = ",
               o1.f,o1.bytes[0],o1.bytes[1],o1.bytes[2],o1.bytes[3],
               o2.f);
*/
    rtype= types&0xF;
    if(conv)
    {
        if(conv >> 7)
        {
            rtype=convertOperand(&o1, conv&0x7F);
        }
        else
        {
            rtype=convertOperand(&o2, conv&0x7F);
        }
    }

    if( (types>>4)==TY_REAL || (types&0xF) == TY_REAL)
    {
        /*
        printf("operands %f[%02X%02X%02X%02X], %f = ",
               o1.f,o1.bytes[0],o1.bytes[1],o1.bytes[2],o1.bytes[3],
               o2.f);
               */
        switch(op)
        {
        case I_ADD:
            r.f = o1.f + o2.f;
            //printf("%f + %f = %f\n", o1.f,o2.f,r.f);
            break;
        case I_SUB:
            r.f = o1.f - o2.f;
            //printf("%f - %f = %f\n", o1.f,o2.f,r.f);
            break;
        case I_MUL:
            r.f = o1.f * o2.f;
            //printf("%f * %f = %f\n", o1.f,o2.f,r.f);
            break;
        case I_DIV:
            r.f = o1.f / o2.f;
            //printf("%f / %f = %f\n", o1.f,o2.f,r.f);
            break;
        case I_GT:
            rtype=TY_BYTE;
            r.i = o1.f > o2.f;
            //printf("%f > %f = %d\n", o1.f,o2.f,r.i);
            break;
        }
        //printf("Result=%f\n", r.f);
    }
    else
    {
        //printf("operands %Ld, %Ld = ", o1.i, o2.i);
        switch(op)
        {
        case I_ADD:
            r.i = o1.i + o2.i;
            break;
        case I_SUB:
            r.i = o1.i - o2.i;
            break;
        case I_MUL:
            r.i = o1.i * o2.i;
            break;
        case I_DIV:
            r.i = o1.i / o2.i;
            break;
		case I_GT:
            rtype=TY_BYTE;
            r.i = o1.i > o2.i;
			break;
        }
       // printf("Result=%d\n", r.i);
    }
    switch(rtype){
		case TY_REAL:
			#ifdef CCS_FLOATPOINT
			convert_microchip_to_ieee(r.bytes);
			#endif
			stk_push(st,r.bytes[3]);
			stk_push(st,r.bytes[2]);
			stk_push(st,r.bytes[1]);
			stk_push(st,r.bytes[0]);
		  //  printf("empilhado f: %f\n", r.f);
			break;
		case TY_INT:
			stk_push(st, r.bytes[2]);
			stk_push(st, r.bytes[3]);
		  //  printf("empilhado i: %d\n", r.i);
			break;
		case TY_BYTE:
			stk_push(st, r.bytes[0]);
		  //  printf("empilhado b: %d\n", r.bytes[0]);
			break;
    }

}

icr_uint8 procces_fb(icr_uint16 mem_index){
	icr_uint8 ret_var;
	icr_int1 repeat;
	icr_int1 noret;
	icr_char instr[8];
	STACK st;
	Operand val;
	icr_uint8 instruction[3];
	icr_uint16 code_pc,pc, code_pointer;
	icr_uint8 p1, p2, i;
	noret = 1;
	repeat=0;
	//printf("FB AT %Lu\r\n", mem_index);
	
	if (mem_index == 0) return 0;
	//code_pointer = ((icr_uint16)(ram_read(mem_index))<<8) | (ram_read(mem_index+1));
	code_pointer = (((icr_uint16)ram_read(mem_index))<<8) | (ram_read(mem_index+1));
	
	if(code_pointer < 65500){
		code_pc=0;
		if(ram_read(code_pointer+3) != 0){
			//code_pointer0 = code_pointer;
			//code_pointer = code_pointer+3;
			code_pc = 1;
			repeat=1;
		}
		stk_init(&st);
		while(noret){
			pc = (code_pc)*3;
			instruction[0] = ram_read(code_pointer+pc);
			instruction[1] = ram_read(code_pointer+pc+1);
			instruction[2] = ram_read(code_pointer+pc+2);
			//printf("Ins %4Lu: '%6s' %2X %2X (%5Lu)\n", code_pc, instText(instruction[0],instr), instruction[1], instruction[2], ((int16)instruction[1]<<8) | instruction[2]);
			code_pc++;
			switch(instruction[0]){
				case I_GOTO:
					code_pc = ((icr_uint16)instruction[1]<<8) | instruction[2];
					break;
				case I_CONST:
					stk_push(&st, instruction[2]);
					break;
				case I_CONST2:
					stk_push(&st, instruction[1]);
					stk_push(&st, instruction[2]);
					break;
				case I_STORE:
					if(instruction[1] == 0 || instruction[1] == 1)
					{
						stk_pop(&st, &p1);
						ram_write(instruction[2]+mem_index+4, p1);
					}
					else
					{
						for(i = 0; i < instruction[1]; i++)
						{							
							stk_pop(&st, &p1);
							ram_write(instruction[2]+instruction[1]-i-1+mem_index+4, p1);
						}
					}
					break;
				case I_RET:
					if(stk_pop(&st, &p2))
					{
						stk_pop(&st, &p1);
						code_pc = (icr_uint16)((icr_uint16)p1)<<8 | p2;
					}
					else
					{
						if(repeat){
							//code_pointer = code_pointer0;
							ram_write(code_pointer+3, 0);
							code_pc = 0;
							repeat=0;
						}else
						noret = 0;
					}
					break;
				 case I_CALL:
					//code_pc++;
					stk_push(&st, code_pc>>8);
					stk_push(&st, (int8)code_pc);
					code_pc = ((icr_uint16)instruction[1]<<8) | instruction[2];
					break;
				case I_LOAD:
					if(instruction[1] == 0 || instruction[1] == 1)
					{
						p1 = ram_read(instruction[2]+mem_index+4);
						stk_push(&st, p1);
					}
					else
					{
						
						p1 = instruction[1];
						for(i = 0; i < p1; i++){
							p2 = ram_read(instruction[2]+i+mem_index+4);
							stk_push(&st, p2);
						}
						/*
						fsr_seek(&fb->ram_data, data[2]);
						p1 = data[1];
						fsr_read(&fb->ram_data, data, p1);
						for(i = 0; i < p1; i++)
						{
							stk_push(&st, data[i]);
						}
						*/
					}
					break;
				case I_IF:
					stk_pop(&st, &p1);
					if(p1 != 0)
					{
						code_pc = ((icr_uint16)instruction[1]<<8) | instruction[2];
					}
					break;
				case I_IFEQ:
					stk_pop(&st, &p1);
					stk_pop(&st, &p2);
					if(p1 == p2)
					{
						code_pc = ((icr_uint16)instruction[1]<<8) | instruction[2];
					}
					break;
				case I_IFGT:
					stk_pop(&st, &p1);
					stk_pop(&st, &p2);
					if(p1 > p2)
					{
						code_pc = ((icr_uint16)instruction[1]<<8) | instruction[2];
					}
					break;
				case I_IFLT:
					stk_pop(&st, &p1);
					stk_pop(&st, &p2);
					if(p1 < p2)
					{
						code_pc = ((icr_uint16)instruction[1]<<8) | instruction[2];
					}
					break;
				case I_IFGE:
					stk_pop(&st, &p1);
					stk_pop(&st, &p2);
					if(p1 >= p2)
					{
						code_pc = ((icr_uint16)instruction[1]<<8) | instruction[2];
					}
					break;
				case I_IFLE:
					stk_pop(&st, &p1);
					stk_pop(&st, &p2);
					if(p1 <= p2)
					{
						code_pc = ((icr_uint16)instruction[1]<<8) | instruction[2];
					}
					break;
				case I_IFNE:
					stk_pop(&st, &p1);
					stk_pop(&st, &p2);
					if(p1 != p2)
					{
						code_pc = ((icr_uint16)instruction[1]<<8) | instruction[2];
					}
					break;
				case I_AND:
					stk_pop(&st, &p1);
					stk_pop(&st, &p2);
					if(p1 && p2)
					{
						stk_push(&st, 1);
					}
					else
					{
						stk_push(&st, 0);
					}
					break;
				case I_OR:
					stk_pop(&st, &p1);
					stk_pop(&st, &p2);
					if(p1 || p2)
					{
						stk_push(&st, 1);
					}
					else
					{
						stk_push(&st, 0);
					}
					break;
				case I_ADD:
					performOperation(&st,instruction[1], instruction[2], I_ADD);
					break;
				case I_SUB:
					performOperation(&st,instruction[1], instruction[2], I_SUB);
					break;
				case I_MUL:
					performOperation(&st,instruction[1], instruction[2], I_MUL);
					break;
				case I_DIV:
					performOperation(&st,instruction[1], instruction[2], I_DIV);
					break;
				case I_GT:
					performOperation(&st,instruction[1], instruction[2], I_GT);
					
				case I_ALLOC:
					break;
				/*
				case I_ARLOAD:
					break;
				case I_ARSTORE:
					break;
				case I_NISND:
					break;
				case I_NIRCV:
					break;
				*/
				case I_GE:
					stk_pop(&st, &p1);
					stk_pop(&st, &p2);
					if(p2 >= p1)
					{
						stk_push(&st, 1);
					}
					else
					{
						stk_push(&st, 0);
					}
					break;
				case I_LT:
					stk_pop(&st, &p1);
					stk_pop(&st, &p2);
					if(p2 < p1)
					{
						stk_push(&st, 1);
					}
					else
					{
						stk_push(&st, 0);
					}
					break;
				case I_LE:
					stk_pop(&st, &p1);
					stk_pop(&st, &p2);
					if(p2 <= p1)
					{
						stk_push(&st, 1);
					}
					else
					{
						stk_push(&st, 0);
					}
					break;
				case I_EQ:
					stk_pop(&st, &p1);
					stk_pop(&st, &p2);
					if(p1 == p2)
					{
						stk_push(&st, 1);
					}
					else
					{
						stk_push(&st, 0);
					}
					break;
				case I_NOT:
					stk_pop(&st, &p1);
					stk_push(&st, !p1);
					break;
				case I_NE:
					stk_pop(&st, &p1);
					stk_pop(&st, &p2);
					if(p1 != p2)
					{
						stk_push(&st, 1);
					}
					else
					{
						stk_push(&st, 0);
					}
					break;
				case I_CONV:
					if(instruction[1] == TY_REAL && instruction[2] == TY_BYTE){
						res_popO(&st, val.bytes, TY_REAL);
						p1 = val.f;
						stk_push(&st, p1);
						//printf("conv %f = %d\n", val.f, p1);
					}else{
						//printf("Warn: Can not perform a CONV.\n");
					}
					break;
				default:
					//printf("Unrecognized instruction (%u) '%s' at %Lu (%LX)\n", instruction[0], instText(instruction[0],instr), code_pc, code_pc);
					while(TRUE);
					//exit(0);
					break;
			}
		}
		
	}else{
		switch(code_pointer){
			case 65504:
				FB_E_SPLIT(mem_index+4);
				break;
			case 65503:
				FB_E_MERGE(mem_index+4);
				break;
			case 65502:
				FB_DIGITAL_WRITE(mem_index+4);
				break;
			case 65501:
				FB_DIGITAL_READ(mem_index+4);
				break;
			case 65506:
				FB_E_DELAY(mem_index+4);
				break;
			case 65507:
				FB_E_PERMIT(mem_index+4);
				break;
			case 65505:
				FB_SUBL_5(mem_index+4);
				break;
			case 65508:
				FB_PUBL_5(mem_index+4);
				break;
		}
		
	}
	CONN_QUEUE[CONN_QUEUE_COUNT] = ((icr_uint16)(ram_read(mem_index+2)) << 8) | (ram_read(mem_index+3));
	CONN_QUEUE_COUNT++;
	return 0;
}

int testeq = 0;
void dispatch_start_event(){
	ram_write(4,1);  //START.COLD event
	ram_write(5,0);   //START.WARM
	ram_write(6,0);   //START.STOP
	
	CONN_QUEUE_COUNT=0;
	CONN_QUEUE_PROCESSED=0;
	FB_QUEUE_COUNT=0;
	FB_QUEUE_PROCESSED=0;
	
	CONN_QUEUE[0] = ((icr_uint16)(ram_read(2)) << 8) | (ram_read(3)); //connections from START
	CONN_QUEUE_COUNT=1;
	//printf("DISPATCH START EVENT (%Lu)\r\n", CONN_QUEUE[0]);
	testeq=1;
}

#ifdef ARDUINO_MODE
icr_int1 state;
void icaru_init(){
	//init hardware specifics
	hdw_init();
	ram_init();
	disk_init();
	net_init();
	
	copyDiskToRam();
	
	CONN_QUEUE_COUNT=0;
	CONN_QUEUE_PROCESSED=0;
	FB_QUEUE_COUNT=0;
	FB_QUEUE_PROCESSED=0;
	
	state = 1;
	
	
}

void icaru_loop(){
		if(state){
			//proccess conn if there  are no fb to proccess
			
			if(CONN_QUEUE_PROCESSED == CONN_QUEUE_COUNT){
				CONN_QUEUE_PROCESSED=0;
				CONN_QUEUE_COUNT = 0;
				state = !state;
			}else{
				//printf("PROCESSING CONN %Lu...", CONN_QUEUE[CONN_QUEUE_PROCESSED]);
				procces_connections(CONN_QUEUE[CONN_QUEUE_PROCESSED]);
				//printf("OK\r\n");
				CONN_QUEUE_PROCESSED++;
			}
		}else{
			//procces FBs on queue
			
			if(FB_QUEUE_PROCESSED == FB_QUEUE_COUNT){
				FB_QUEUE_PROCESSED = 0;
				FB_QUEUE_COUNT=0;
				state = !state;
				copyFromExtra();
			}else{
				//printf("PROCESSING FB %Lu...", FB_QUEUE[FB_QUEUE_PROCESSED]);
				procces_fb(FB_QUEUE[FB_QUEUE_PROCESSED]);
				//printf("OK\r\n");
				FB_QUEUE_PROCESSED++;
			}
		}
		/*
		if((CONN_QUEUE_PROCESSED == CONN_QUEUE_COUNT) && (FB_QUEUE_PROCESSED == FB_QUEUE_COUNT) && testeq){
			printf("EQUALS...\r\n");
			while(TRUE){
				hdw_run();
			}
		}
		*/
		/*
		if(ram_read(4) == 2){
			CONN_QUEUE[0] = ((icr_uint16)(ram_read(2)) << 8) | (ram_read(3)); //connections from START
			CONN_QUEUE_COUNT=1;			
		}
		*/
		//proccess network
		net_run();
		hdw_run();
}

/*
void main(){
	icaru_init();
	while(TRUE){
		icaru_loop();
	}
}
*/

#else





void main(){
	icr_int1 state;
	//init hardware specifics
	hdw_init();
	ram_init();
	disk_init();
	net_init();
	
	//printf("STARTING\r\n");
	//printf("Copying Disk...");
	//delay_ms(3);
	
	copyDiskToRam();
	
	//printf("OK\r\n");
	//delay_ms(3);
	
	CONN_QUEUE_COUNT=0;
	CONN_QUEUE_PROCESSED=0;
	FB_QUEUE_COUNT=0;
	FB_QUEUE_PROCESSED=0;
		
	state = 1;
	
	//gen start event
//	ram_write(0,0);
//	ram_write(1,0);
//	ram_write(2,0);
//	ram_write(3,0);

	//ram_write(4,1);  //START.COLD event
	//ram_write(5,0);   //START.WARM
	//ram_write(6,0);   //START.STOP
	//CONN_QUEUE[0] = ((icr_uint16)(ram_read(2)) << 8) | (ram_read(3)); //connections from START
	//CONN_QUEUE_COUNT=1;
	
	//dispatch_start_event();
	
	
	//ICARU_VM loop
	while(TRUE){
		if(state){
			//proccess conn if there  are no fb to proccess
			
			if(CONN_QUEUE_PROCESSED == CONN_QUEUE_COUNT){
				CONN_QUEUE_PROCESSED=0;
				CONN_QUEUE_COUNT = 0;
				state = !state;
			}else{
				//printf("PROCESSING CONN %Lu...", CONN_QUEUE[CONN_QUEUE_PROCESSED]);
				procces_connections(CONN_QUEUE[CONN_QUEUE_PROCESSED]);
				//printf("OK\r\n");
				CONN_QUEUE_PROCESSED++;
			}
		}else{
			//procces FBs on queue
			
			if(FB_QUEUE_PROCESSED == FB_QUEUE_COUNT){
				FB_QUEUE_PROCESSED = 0;
				FB_QUEUE_COUNT=0;
				state = !state;
				copyFromExtra();
			}else{
				//printf("PROCESSING FB %Lu...", FB_QUEUE[FB_QUEUE_PROCESSED]);
				procces_fb(FB_QUEUE[FB_QUEUE_PROCESSED]);
				//printf("OK\r\n");
				FB_QUEUE_PROCESSED++;
			}
		}
		
		//proccess network
		net_run();
		hdw_run();
		
	}
}
#endif

//Why? Read inside of the file "includeallc.h"
#include "includeallc.h"

