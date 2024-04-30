#include "tm4c123gh6pm.h"
void PORTB_Init(){
SYSCTL_RCGCGPIO_R |=0x02 ; //PORT b clock enable
while((SYSCTL_PRGPIO_R & 0x02 )==0); //make sure that clock  of port b is enabled  
GPIO_PORTB_LOCK_R= GPIO_LOCK_KEY;
GPIO_PORTB_CR_R |=0x0FF; // allow changes to all pins for port b 
GPIO_PORTB_AMSEL_R &= ~ 0x0FF; // disable anlog 	
GPIO_PORTB_AFSEL_R &= ~ 0x0FF; //alternating function off
GPIO_PORTB_PCTL_R &= ~0xFFFFFFFF; // all pins are cleared 
GPIO_PORTB_DIR_R |= 0x0FF; // enable all pins to be output 
GPIO_PORTB_DEN_R |= 0x0FF; // enable all pins to be digital 
GPIO_PORTB_DATA_R &= ~ 0x0FF;// make all pins off
}
//abdelrahman/2100544
