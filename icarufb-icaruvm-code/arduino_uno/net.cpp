/**
    Copyright 2014 Leandro Israel Pinto
	
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

*/

#include "net.h"
#include "hdw.h"



icr_uint8 net_buffer_out[LP_BUF_SIZE];
//icr_uint8 net_buffer_in[LP_BUF_SIZE];
icr_uint8 net_oldt, net_i, net_tk;


void net_init(){
	//net_tokens[0] = 10;
	//net_tokens[1] = 20;
	//net_tokens[2] = 30;
	//net_tokens[3] = 40;
	//net_tokens[4] = 50;
	//output_high(RSCONTROL);
	lp_init();
}

icr_uint8 net_snd(icr_uint8 *data, icr_uint8 t){
	icr_uint8 i;
	if(net_buffer_out[0] != 0){
		printf("(net_snd) E2\r\n");
		return FALSE;
	}
	if(t <= LP_BUF_SIZE){
		for(i=0;i<t;i++){
			net_buffer_out[i] = data[i];
			//return TRUE;
		}
		return TRUE;
	}else{
		printf("(net_snd) E1\r\n");
	}
	return FALSE;
}

void net_snd_force(icr_uint8 *data, icr_uint8 t){
	#ifdef NET_MASTER
	lp_send(data,LP_NOTOKEN);
	#else
	lp_send(data,LP_TOKEN);
	#endif
}


icr_uint8 net_rcv(icr_uint8 *data){
	return 0;
}





void net_run(){
	//icr_uint8 i;
	#ifdef NET_MASTER
	//manage tokens
	if(net_tk > LP_ADDRESS){
		net_tk = 1;
	}	
	if(net_oldt != getTime()){
		net_oldt = getTime();
		if(net_i > 5){
			net_i = 0;
			if(net_tk == LP_ADDRESS){
				net_tk++;
				//send my buffer;
				if(net_buffer_out[0] != 0){
					lp_send(net_buffer_out, LP_NOTOKEN);
					net_buffer_out[0] = 0;
				}				
			}else{
				//lp_sendTokenTo(net_tokens[net_tk]);
				lp_sendTokenTo(net_tk);
				net_tk++;
			}
		}
		net_i++;	
	}
	if(lp_recv()){
		icaru_handle_netdata(lp_getBuffer());
		/*
		for(i=0;i<LP_BUF_SIZE;i++){
			net_buffer_in[i] = lp_buffer[i];
		}
		*/
	}
	#else
	if(lp_recv()){
		if(lp_istoken()){
			//send my buffer;
			if(net_buffer_out[0] != 0){
				lp_send(net_buffer_out, LP_NOTOKEN);
				net_buffer_out[0] = 0;
			}	
		}else{
		
		}
	}	
	#endif
}

