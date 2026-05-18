
#ifndef _LEPROTOCOL_H_
#define _LEPROTOCOL_H_ 1

#ifndef RSCONTROL
#define RSCONTROL PIN_E0
#endif

#ifndef LP_BUF_SIZE
#define LP_BUF_SIZE 6
#endif

#ifndef LP_ADDRESS
#define LP_ADDRESS 0x05
#endif

#define LP_TOKEN 0
#define LP_NOTOKEN 1

int lp_buffer[LP_BUF_SIZE];

void lp_init(){
	output_low(RSCONTROL);
}

int1 lp_istoken(){
	
	if(lp_buffer[0] == LP_ADDRESS){
		if(lp_buffer[1] == 0xF1 && lp_buffer[2] == 0xF1){
			lp_buffer[0] = 0;
			return 1;
		}
	}
	return 0;
}

short timeout_error;
char timed_getc() {
   long timeout;
   timeout_error=FALSE;
   timeout=0;
   while(!kbhit()&&(++timeout<500))   // 1/2 second
      delay_us(10);
   if(kbhit())
     return(getc());
   else {
     timeout_error=TRUE;
     return(0);
   }
}


int1 lp_recv(){
	int i;
	if(kbhit()){
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

int1 lp_recvtk(){
	if(lp_recv())
		if(lp_istoken()) 
			return 1;
	return 0;
}

void lp_send(int *msg, int1 token){
	int i;
	if(!token){
		while(!lp_istoken()){
			lp_recv();
		}
	}
	output_high(RSCONTROL);
    delay_us(800);
	putc(0xAA);
	putc(0x55);
	for(i=0;i<LP_BUF_SIZE;i++){
		putc(msg[i]);
	}
	putc(0x55);
	delay_us(700);
    output_low(RSCONTROL);
}

int * lp_stc2msg(void *st, int *msg, int t){
	int i;
	for(i=0;i<t;i++){
		msg[i] = st[i];
	}
	return msg;
}
void * lp_msg2stc(int *msg, void *st, int t){
	int i;
	for(i=0;i<t;i++){
		st[i] = msg[i];
	}
	return st;
}

void lp_sendTokenTo(int addr){
	int msg[LP_BUF_SIZE];
	msg[0]=addr;
	msg[1]=0xF1;
	msg[2]=0xF1;
	lp_send(msg,1);
}



#endif
