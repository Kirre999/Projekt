
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */



char map[4][17] = {	  {' ',' ',' ','@',' ',' ',' ','@',' ',' ',' ','@',' ',' ',' ','@','t'}
					, {' ',' ',' ','@',' ',' ',' ','@',' ',' ',' ','@',' ',' ',' ','@','t'}
					, {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','@','t'}
					, {' ',' ',' ','@',' ',' ',' ','@',' ',' ',' ','@',' ',' ',' ','@','t'}};
int alive = 1;

int timeoutcount = 0;




void user_isr( void ) {
	/* (btn 3 == 1 ){
		alive = 1
	}*/
	int i;
	int j;
	//x 0x78, 120
	int xlocation = 3;

	while (alive == 1){
		if(IFS(0) & 0x100){
			IFS(0) = 0;
			timeoutcount++;
		}

		if(timeoutcount == 10){

			for(i = 0; i < 16; i++){

				if(i == 0){
					map[0][16] = map[0][0];
					map[1][16] = map[1][0];
					map[2][16] = map[2][0];
					map[3][16] = map[3][0];
				}

				for(j = 0; j < 4; j++){
					if(!(j == xlocation && i == 0)){
						map[j][i] = map[j][i+1];}
						
						//map[j][i] = map[j][i];
						//if(map[j][i+1] == '@'){
							//alive = 0;
						//}
					
					
				}
			}
			if (xlocation > 0)
			{
				//xlocation = xlocation - 1;
			}
			map[xlocation][1] = 'x';

			display_update();
			display_string(0, map[0]);
			display_string(1, map[1]);
			display_string(2, map[2]);
			display_string(3, map[3]);

			PORTE++;
			IFS(0) = 0;
			timeoutcount = 0;
		}
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
}
