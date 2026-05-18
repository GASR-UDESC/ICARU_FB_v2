
#include "deviceconfig.h"


#include <LiquidCrystal.h>

#ifdef ICARU_MEGA2560
#include <SPI.h>
#include <SD.h>
#endif

#include "hdwfbs.h"
#include "ram.h"
#include "icarutypes.h"



#ifdef ICARU_MEGA2560
int CS_PIN = 10;
File file;
#endif


/**
PINS:

X0...X100
Y0...Y100
A0...A100

*/
icr_uint16 toPicPin(icr_uint8 n){
	return n;
}
/*
icr_uint16 toPicPin(icr_uint8 n){
	switch(n){
			case 100:
				return 22;
				break;
			case 101:
				return 23;
				break;
			case 102:
				return 24;
				break;
			case 103:
				return 25;
				break;
				
			case 200:
				return 26;
				break;
			case 201:
				return 27;
				break;
			case 202:
				return 28;
				break;
			case 203:
				return 29;
				break;
	}
	return 0;
}
*/

/**
	Vars map:
	0: REQ IN
	1: PIN IN
	2: CNF OUT
	3: VAL OUT
*/
void FB_DIGITAL_READ(icr_uint16 mem_index){
	icr_uint8 a;
	a = ram_read(mem_index);
	ram_write(mem_index,a-1);
	a = ram_read(mem_index+2);
	ram_write(mem_index+2,a+1);
	
	ram_write(mem_index+3, digitalRead(toPicPin(ram_read(mem_index+1))));
	//printf("WR (%u): %u\r\n",ram_read(mem_index+1), input(toPicPin(ram_read(mem_index+1))));
	//ram_write(mem_index+2,1);
}

/**
	Vars map:
	0: REQ IN
	1: PIN IN
	2: CNF OUT
	3: VAL IN
*/
void FB_DIGITAL_WRITE(icr_uint16 mem_index){
	icr_uint8 a;
	a = ram_read(mem_index);
	ram_write(mem_index,a-1);
	a = ram_read(mem_index+2);
	ram_write(mem_index+2,a+1);
	
	digitalWrite(toPicPin(ram_read(mem_index+1)), (ram_read(mem_index+3)>0) );
}

/**
	Vars map:
	0: REQ IN
	1: PIN IN
	2: CNF OUT
	3: VAL OUT 16
*/
void FB_ANALOG_READ(icr_uint16 mem_index){
	icr_uint16 v;
 //Doesn
 v = analogRead(ram_read(mem_index+1));
 ram_write(mem_index+3, (icr_uint8) (v>>8) );
 ram_write(mem_index+4, (icr_uint8) v );

 ram_write(mem_index+2,ram_read(mem_index+2)+1);
 /*
	set_adc_channel(ram_read(mem_index+1));
	ram_write(mem_index+2,1);
	delay_us(20);
	v = read_adc();
	ram_write(mem_index+3, (icr_uint8) (v>>8) );
	ram_write(mem_index+3, (icr_uint8) v );
 */
}



/**
  Vars map:
  0: REQ IN
  1: PIN1 IN
  2: CNF OUT
  3: VAL1 OUT 16
  5: PIN2 OUT
  6: VAL2 OUT 16
*/
void FB_ANALOG_READ_2(icr_uint16 mem_index){
  icr_uint16 v;
 //Doesn
 v = analogRead(ram_read(mem_index+1));
 ram_write(mem_index+3, (icr_uint8) (v>>8) );
 ram_write(mem_index+4, (icr_uint8) v );
 v = analogRead(ram_read(mem_index+5));
 ram_write(mem_index+6, (icr_uint8) (v>>8) );
 ram_write(mem_index+7, (icr_uint8) v );

 ram_write(mem_index+2,ram_read(mem_index+2)+1);
}


/**
  Vars map:
  0: REQ IN
  1: CNF OUT
  2: MS OUT 16
*/
void FB_MILLIS(icr_uint16 mem_index){
  icr_uint32 v;
  ram_write(mem_index,ram_read(mem_index)-1);
  ram_write(mem_index+1,ram_read(mem_index+1)+1);
  v = millis();
  ram_write(mem_index+2,v>>2);
  ram_write(mem_index+3,v & 0xFF);
}

/**
  Vars map
  0: INIT
  1: REQ
  2: INITO
  3: CNF
  4: MSG
  5: VAR1
  7: VAR2
  9: VAR3
  11: VAR4
  */
LiquidCrystal lcd(8, 9, 5, 7, 3, 2);
int lcdcount = 0;
void FB_LCD_MSG(icr_uint16 mem_index){
  float aux;
  icr_uint8 a;
  a = ram_read(mem_index);
  if(a){
    ram_write(mem_index,a-1);
    lcd.begin(16, 2);  
    lcd.print(" ");   
    ram_write(mem_index+2,a+1);
  }
  a = ram_read(mem_index+1);
  if(a){
    ram_write(mem_index+1,a-1);
    switch(ram_read(mem_index+4)){
      case 0:
		lcd.clear();
        lcd.setCursor(0, 0);
        //lcd.print("HELLO..."); 
        lcd.clear();
        
        aux = (float)(((int)ram_read(mem_index+5) << 8) | ram_read(mem_index+6))/10;        
        lcd.print(aux);

        lcd.print("V  ");
        aux = (float)(((int)ram_read(mem_index+7) << 8) | ram_read(mem_index+8))/10;  
            
        lcd.print(aux);
        lcd.print("A");  
        
        lcd.setCursor(0, 1);

        aux = (float)(((int)ram_read(mem_index+9) << 8) | ram_read(mem_index+10));        
        lcd.print(aux);

        lcd.print("W Fp:");
        aux = (float)(((int)ram_read(mem_index+11) << 8) | ram_read(mem_index+12))/10;        
        lcd.print(aux);
        /*
        lcd.print(ram_read(mem_index+4));
        lcd.print(" ");
        lcd.print(ram_read(mem_index+5));
        lcd.print(" ");
        lcd.print(ram_read(mem_index+6));
        lcd.print(" ");
        lcd.print(ram_read(mem_index+7));
        lcd.print(" ");
        lcd.print(ram_read(mem_index+8));
        lcd.print(" ");
        lcd.print(ram_read(mem_index+9));
        lcd.print(" ");
        lcd.print(ram_read(mem_index+10));
        lcd.print(" ");
        lcd.print(lcdcount);
        lcdcount++;
        */
        
        break;
    }
    a = ram_read(mem_index+3);
    ram_write(mem_index+3,a+1);
  }
}




/**
  Vars map
  0: INIT
  1: REQ
  2: INITO
  3: CNF
  4: MSG
  5: VAR1
  7: VAR2
  9: VAR3
  11: VAR4
  */
void FB_SD_CARD_WRITE(icr_uint16 mem_index){
  #ifdef ICARU_MEGA2560
  float aux;
  char sep;
  icr_uint8 a;
  a = ram_read(mem_index);
  if(a){
    ram_write(mem_index,a-1);
    pinMode(CS_PIN, OUTPUT);
    SD.begin();
    
    /*
    if (SD.begin())
    {
     
    } else
    {
      
      return;
    }  */
    ram_write(mem_index+2,a+1);
  }
  a = ram_read(mem_index+1);
  if(a){
    ram_write(mem_index+1,a-1);
    sep = ram_read(mem_index+4);
        file = SD.open("datalog.txt", FILE_WRITE); 
        aux = (float)(((int)ram_read(mem_index+5) << 8) | ram_read(mem_index+6))/10;        
        file.print(aux);
        file.print(";");

        aux = (float)(((int)ram_read(mem_index+7) << 8) | ram_read(mem_index+8))/10;  
            
        file.print(aux);
        file.print(";"); 
        
        aux = (float)(((int)ram_read(mem_index+9) << 8) | ram_read(mem_index+10));        
        file.print(aux);
        file.print(";");

        
        aux = (float)(((int)ram_read(mem_index+11) << 8) | ram_read(mem_index+12))/10;        
        file.println(aux);
        
        file.close();
    a = ram_read(mem_index+3);
    ram_write(mem_index+3,a+1);
  }
  #endif
}


/**
	Vars map
	0: INIT
	1: REQ
	2: INITO
	3: CNF
	4: QI
	5: PARAMS
	6: SD_1
	7: SD_2
	8: QO
	9: STATUS
	10: RD_1
*/
void FB_IO_WRITE(icr_uint16 mem_index){

}

void FB_IO_READ(icr_uint16 mem_index){
}
/*
void FB_E_DELAY(icr_uint16 mem_index){
}
*/

