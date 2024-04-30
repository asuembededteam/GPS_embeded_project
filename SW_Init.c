#include "tm4c123gh6pm.h"
void SW_Init(){
GPIO_PORTF_CR_R|= PF04_mask ; //allow changes to pf 4,0
GPIO_PORTF_AMSEL_R &= ~ PF04_mask ;//disable analog
GPIO_PORTF_DEN_R|=PF04_mask ;//make pins 4,0 digital
GPIO_PORTF_DIR_R &= ~ PF04_mask ;//make pins 4,0 inputs
GPIO_PORTF_DATA_R &= ~ PF04_mask ;//make switch  off
GPIO_PORTF_AFSEL_R &=~PF04_mask ;//disable alternate functions
GPIO_PORTF_PCTL_R&=~0x000F000F;// clear pctl for 4,0
GPIO_PORTF_PUR_R|= PF04_mask ;//initialize pur for pins 4,0
}
//Ahmed Hany Mostafa Ahmed 
//id 2100741 
