#include "tm4c123gh6pm.h"
void PORTF_Init(){
SYSCTL_RCGCGPIO_R |=PF_mask ; //PORT f clock enable
while((SYSCTL_PRGPIO_R & PF_mask )==0); //make sure that clock  of port f is enabled  
GPIO_PORTF_LOCK_R= GPIO_LOCK_KEY;
GPIO_PORTF_CR_R |=PF123_mask; // allow changes to pins  1,2,3 for port f 
GPIO_PORTF_AMSEL_R &= ~ PF123_mask; // disable anlog 	
GPIO_PORTF_AFSEL_R &= ~ PF123_mask; //alternating function off
GPIO_PORTF_PCTL_R &= ~0x0000FFF0; // pin1,2,3 are cleared 
GPIO_PORTF_DIR_R |= PF123_mask; // enable pins 1,2,3 to be output 
GPIO_PORTF_DEN_R |= PF123_mask; // enable pins 1,2,3 to be digital 
GPIO_PORTF_DATA_R &= ~ PF123_mask;// make leds off
}
//hussien