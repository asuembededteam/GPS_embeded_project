//Youssef Waleed Hussien: 2101023
#include "Variables &Functions Prototypes.c"
#include "Distance_Manipulation.c"
#include "dividing_Field_gps.c"
#include "EEPROM.c"
#include "GetDistance.c"
#include "GPS_READ.c"
#include "Initializations.c"
#include "Input_output.c"
#include "Send_Coodinates.c"
#include "Systick_functions.c"
#include "UART0 PC_2_TIVA.c"

// send an array of char to uart 0
void printstring(char *p){
	while(*p)
	{
		WRITE_char(*p);
		p++;
	}
}
// getting value from switch and updating the led

unsigned long switch_interface(){
return (GPIO_PORTF_DATA_R & 0x11);
}

void updateled(unsigned int led){
	GPIO_PORTF_DATA_R=led;
}

