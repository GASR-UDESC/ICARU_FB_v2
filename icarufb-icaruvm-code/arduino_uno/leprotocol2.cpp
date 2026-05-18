

#include "leprotocol2.h"

icr_uint8 lp_buffer[LP_BUF_SIZE];

icr_uint8 * lp_getBuffer(){
  return lp_buffer;
}


void lp_init(){
  pinMode(RSCONTROL, OUTPUT);
  digitalWrite(RSCONTROL,0);
  Serial.begin(38400);
  //Serial.setTimeout(5);
}

icr_int1 lp_istoken(){
	
	if(lp_buffer[0] == LP_ADDRESS){
		if(lp_buffer[1] == 0xF1 && lp_buffer[2] == 0xF1){
			lp_buffer[0] = 0;
			return 1;
		}
	}
	return 0;
}

icr_int1 timeout_error;
icr_uint8 timed_getc() {
   icr_uint16 timeout;
   timeout_error=FALSE;
   timeout=0;
   while(!Serial.available()&&(++timeout<1000))   // 1/2 second
      delayMicroseconds(10);
   if(Serial.available()){
     return Serial.read();
   }else {
     timeout_error=TRUE;
     return(0);
   }
}


icr_int1 lp_recv(){
	icr_uint8 i;
	if(Serial.available()){
		if(timed_getc() != 0xAA) return 0;
		if(timeout_error) return 0;
		if(timed_getc() != 0x55) return 0;
		if(timeout_error) return 0;
		for(i=0;i<LP_BUF_SIZE;i++){
			lp_buffer[i] = timed_getc();
			if(timeout_error) return 0;
		}		
		if(timed_getc() != 0x55) return 0;
		if(timeout_error) return 0;
		return 1;
	}
	return 0;
}

icr_int1 lp_recvtk(){
	if(lp_recv())
		if(lp_istoken()) 
			return 1;
	return 0;
}

void lp_send(icr_uint8 *msg, icr_int1 token){
	icr_uint8 i;
	if(!token){
		while(!lp_istoken()){
			lp_recv();
		}
	}
	digitalWrite(RSCONTROL,1);
    delayMicroseconds(800);
	Serial.write(0xAA);
	Serial.write(0x55);
	for(i=0;i<LP_BUF_SIZE;i++){
		Serial.write(msg[i]);
	}
	Serial.write(0x55);
	delayMicroseconds(700);
    digitalWrite(RSCONTROL,0);
}

icr_uint8 * lp_stc2msg(icr_uint8 *st, icr_uint8 *msg, icr_uint8 t){
	icr_uint8 i;
	for(i=0;i<t;i++){
		msg[i] = st[i];
	}
	return msg;
}
icr_uint8 * lp_msg2stc(icr_uint8 *msg, icr_uint8 *st, icr_uint8 t){
	icr_uint8 i;
	for(i=0;i<t;i++){
		st[i] = msg[i];
	}
	return st;
}

void lp_sendTokenTo(icr_uint8 addr){
	icr_uint8 msg[LP_BUF_SIZE];
	msg[0]=addr;
	msg[1]=0xF1;
	msg[2]=0xF1;
	lp_send(msg,1);
}

