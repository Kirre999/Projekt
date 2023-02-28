
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

/* Interrupt Service Routine */

int mytime = 0x5957;

int prime = 1234567;

char textstring[] = "text, more text, and even more text!";

int timeoutcount = 0;


char test[] =  {0, 7, 7, 7, 
				0, 0, 0, 0,
  				0, 0, 0, 0,  
  				0, 0, 0, 0,  };
int i;
const uint8_t const pipe_mid[] = {
  255, 255, 255, 255, 
  15, 15, 15, 15, 
  240, 240, 240, 240, //erik
  255, 255, 255, 255
};

const uint8_t const pipe_midhigh[] = {
  255, 255, 255, 255, 
  0, 0, 0, 0, 
  255, 255, 255, 255, 
  255, 255, 255, 255,//erik
};

const uint8_t const pipe_high[] = {
  15, 15, 15, 15, 
  240, 240, 240, 240, //erik
  255, 255, 255, 255, 
  255, 255, 255, 255
};

const uint8_t const pipe_midlow[] = {
  255, 255, 255, 255, 
  255, 255, 255, 255, //erik
  0, 0, 0, 0, 
  255, 255, 255, 255, 
};

const uint8_t const pipe_low[] = {
  255, 255, 255, 255, 
  255, 255, 255, 255, 
  15, 15, 15, 15, 
  240, 240, 240, 240,//erik
};

const uint8_t const mordin[] = {0,0,0,0
,0,0,0,0
,0,0,0,0
,0,0,0,0};
int test2 = 64;

void user_isr( void ) {
	
	if(IFS(0) & 0x100){
    IFS(0) = 0;
    timeoutcount++;
  }
	
  while(timeoutcount == 1 && test2 >= 0){
	display_update();
	display_image(test2,pipe_midhigh);
	
	test2 = test2-0x10;
	//display_image(test2+4, mordin);

	IFS(0) = 0;
    timeoutcount = 0;
}
}



void labinit (void){
	//initialisera knapp 2,4 och ledlampor
	//initalisera timer och interrupts??
	 volatile int* trise = 0xbf886100;
  volatile int* porte = 0xbf886110;
  (*trise) = 0XFF00;
  TRISD = 0xFFE0;

	
	
	T2CON = 0x0;
	T2CONSET = 0x70;
	TMR2 = 0;
	PR2 = (80000000/10)/256;
	T2CONSET = 0x8000;

	IEC(0) |= 0x100;
  	IPC(2) |= 0x1C;

	enable_interrupt();

	return;
}




void labwork (void){

	//display_image(16, test);
  	//display_image(32, pipe_mid);
	//display_image(80,pipe_midlow);
	//display_image(96,pipe_high);
	//display_image(112,pipe_low);


}
