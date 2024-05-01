#include "tm4c123gh6pm.h"
void init_portA_pin01(){
SYSCTL_RCGCGPIO_R |=0x01 ; //PORT A clock enable
while((SYSCTL_PRGPIO_R & 0x01 )==0); //make sure that clock  of port A is enabled  
GPIO_PORTA_LOCK_R= GPIO_LOCK_KEY;
GPIO_PORTA_CR_R |=0x03; // allow changes to pins 0,1 for port A 
GPIO_PORTA_AMSEL_R &= ~ 0x03; // disable anlog 	
GPIO_PORTA_AFSEL_R |= 0x03; //alternating function on
GPIO_PORTA_PCTL_R |= 0x00000011; // pin0(RX),1(TX)
GPIO_PORTA_DIR_R |= 0x02; // enable pin0 input,1 output 
GPIO_PORTA_DEN_R |= 0x03; // enable pin0,1 to be digital 
GPIO_PORTA_DATA_R &= ~ 0x02;// make leds off
}
// Hassan Ramadan Zaref
// 2101364
