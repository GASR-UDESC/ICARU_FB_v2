
#include "hdw.h"

/********************** Soft WDT *****************/
int mywdt_count;
void mywdt_reset(){
	mywdt_count = 0;
}


/************************* Timer 0 ***************/
int time_sec_div_100;
int time_sec;
//int32 time_var;
boolean toggle1 = 0;
ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
  if (toggle1){
    digitalWrite(13,HIGH);
    toggle1 = 0;
  }
  else{
    digitalWrite(13,LOW);
    toggle1 = 1;
  }
  time_sec_div_100++;
    /* ==100 para 1 segundo */
    if(time_sec_div_100==100)
    {
        time_sec_div_100=0;
        time_sec++;

        //output_toggle(pin_e1);

    mywdt_count++;
    if(mywdt_count > 10){
      //reset_cpu();
    }
    }
    
}

icr_uint8 getTime(){
  return time_sec_div_100;
}


/*
int32 getTime(){
	return time_var;
}
*/
void hdw_init(){
	mywdt_reset();
  
  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  //OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  //OCR1A = 230;
  OCR1A = 157;
  
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  
  

  pinMode(22, INPUT);
  pinMode(23, INPUT);
  pinMode(24, INPUT);
  pinMode(25, INPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(29, OUTPUT);
	pinMode(13, OUTPUT);

  digitalWrite(26,1);
  digitalWrite(27,1);
  digitalWrite(28,1);
  digitalWrite(29,1);
}

void hdw_run(){
	mywdt_reset();
}

