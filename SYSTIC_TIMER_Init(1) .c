#include "tm4c123gh6pm.h"
void SYSTIC_TIMER_Init(){
NVIC_ST_CTRL_R = 0; // 1) disable SysTick during setup
NVIC_ST_RELOAD_R = 0x00FFFFFF; // 2) maximum reload value
NVIC_ST_CURRENT_R = 0; // 3) any write to CURRENT clears it
NVIC_ST_CTRL_R = 0x00000005; // 4) enable SysTick with core clock
}
void wait_1ms(){
NVIC_ST_RELOAD_R=16000;
NVIC_ST_CURRENT_R = 0;
while((NVIC_ST_CTRL_R & 0x00010000)==0);
}
void wait(int delay){
	int i;
	for(i=0;i<delay;i++)
	wait_1ms();
}
//abdelaziz 2100420 and youssef waleed