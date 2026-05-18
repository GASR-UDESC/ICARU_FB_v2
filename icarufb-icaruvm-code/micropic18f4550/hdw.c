
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

#int_rtcc
void trata_t0()
{
    set_timer0(60+get_timer0());
    time_sec_div_100++;
    /* ==100 para 1 segundo */
    if(time_sec_div_100==100)
    {
        time_sec_div_100=0;
        time_sec++;

        //output_toggle(pin_e1);

		mywdt_count++;
		if(mywdt_count > 10){
			reset_cpu();
		}
    }
	//time_var++;
}
/*
int32 getTime(){
	return time_var;
}
*/
void hdw_init(){
	mywdt_reset();
    setup_counters( RTCC_INTERNAL, RTCC_DIV_256 | RTCC_8_BIT);
    enable_interrupts(INT_RTCC);
    set_timer0(60);
    enable_interrupts(GLOBAL);

    setup_adc_ports(AN0_TO_AN1);
    //setup_adc_ports(AN0_AN1_AN2_AN3_AN4);
    setup_adc(ADC_CLOCK_DIV_2);
    setup_vref(false);
    setup_comparator(NC_NC_NC_NC);
	
}

void hdw_run(){
	mywdt_reset();
}