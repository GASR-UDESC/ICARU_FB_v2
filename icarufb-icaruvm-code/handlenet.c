


//NET COMMANDS
/*

BIT 7 6 5 4 3 2 1 0
7 6 5: 11 - FB Communication

BITs b7 b6 b5 ID_4 ID_3 ...
001: Enter programming mode 
010: Write
011: Write with size
100: Exit programming
101: Read Memory
 





-------- OLD ----------
10: Enter programming mode
12: Write on memory
	[12 data...]
13: Write on Memory with size
	[13 size data...]
14: Exit programming mode

200 - 249: For subscribers


*/

#include "deviceconfig.h"
#include "net.h"
#include "icaru.h"

#define ENTER_PROGRAMMING (0x20 | DEVICE_ID)
#define EXIT_PROGRAMMING (0x40 | DEVICE_ID)
#define WRITE_MEMORY (0x60 | DEVICE_ID)
#define WRITE_MEMORY_SIZE (0x80 | DEVICE_ID)
#define READ_MEMORY (0xA0 | DEVICE_ID)
#define WRITE_CHECK (0xC0 | DEVICE_ID)

icr_uint8 hnet_state=0;
icr_uint16 hnet_memp;
icr_uint16 hnet_checksum;

void icaru_subl(icr_uint8 id, icr_uint8 *data){
	icr_uint16 subp,dp;
	icr_uint8 ids,i;
	subp = (((icr_uint16)(ram_read(7)))<<8) | (ram_read(8));
//	printf("SUBP: %Lu\r\n", subp);
	if(subp == 0) return;
	ids = ram_read(subp);
	while(ids != 0){
		if(ids!=1){
			if(ids == id){
				// [id MSB LSB]
				dp = (((icr_uint16)(ram_read(subp+1)))<<8) | (ram_read(subp+2));
				if(ram_read(dp) > 0){ //check if block is initialized
					dp = dp + 4; 
					for(i=0;i<5;i++){
						ram_write(dp+i+4, data[i+1]);
					}
					ram_write(dp+2,1);
					dp = dp - 2;
					dp = (((icr_uint16)(ram_read(dp)))<<8) | (ram_read(dp+1)); 
					appendConn(dp);
	//				printf("APPCON: %Lu\r\n", dp);
				}
			}			
		}
		subp = subp + 3;
		ids = ram_read(subp);
	}
}

void icaru_handle_netdata(icr_uint8 *data){
	icr_uint8 id;
	icr_uint8 msg[9];
	int1 w=0;
//	printf("HANDLE: %X\r\n",data[0]);
	if(data[0] >= 200 && data[0] < 250){
		icaru_subl(data[0], data);
	}else
	if(data[0] == ENTER_PROGRAMMING){
		hnet_state = EXIT_PROGRAMMING;
		id = (((icr_uint16)data[1])<<8) | data[2];
		if(id == DEVICE_ID){
			hnet_state = ENTER_PROGRAMMING;
			hnet_memp = (((icr_uint16)data[3])<<8) | data[4];
			hnet_checksum = 0;
		//	printf("ENTER_PROGRAMMING %Lu\r\n", hnet_memp);
		}
	}else
	if(data[0] == WRITE_MEMORY && hnet_state == ENTER_PROGRAMMING){
		//if(hnet_state == ENTER_PROGRAMMING){
			for(id=0;id<5;id++){
				ram_write(hnet_memp, data[id+1]);
				hnet_checksum = hnet_checksum + data[id+1];
				hnet_memp++;
			}
		//}
		if(ram_read(4) == 1){
			
			dispatch_start_event();		
		}
	}
	else
	if(data[0] == WRITE_MEMORY_SIZE && hnet_state == ENTER_PROGRAMMING){
		//if(hnet_state == ENTER_PROGRAMMING){
		//	if(hnet_memp==4){
		//		printf("WRITE: ");
		//		w=1;
		//	}
			for(id=0;id<data[1];id++){
				ram_write(hnet_memp, data[id+2]);
				hnet_checksum = hnet_checksum + data[id+2];
		//		if(w)
		//			printf("[%X]", ram_read(hnet_memp));
				hnet_memp++;
				
			}
		//	if(w)
		//	printf("\r\n");
		//}
		if(ram_read(4) == 1){
			
			dispatch_start_event();		
		}
	}else
	if(data[0] == EXIT_PROGRAMMING){
		//id = (((icr_uint16)data[2])<<8) | data[3];
		//if(id == DEVICE_ID){
			hnet_state = EXIT_PROGRAMMING;
			msg[0] = WRITE_CHECK;
			msg[1] = hnet_checksum>>8;
			msg[2] = (icr_uint8) hnet_checksum;
			msg[3]=0;
			msg[4]=0;
			msg[5]=0;
			net_snd_force(msg,6);
		//	printf("EXIT_PROGRAMMING\r\n");
		//}
	}
	
	
}

