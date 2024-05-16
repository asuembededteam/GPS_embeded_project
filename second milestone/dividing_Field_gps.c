//Omar mohamed araby shamandy 2100550
/////// dividing gps module output into fields
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
void dividing_field_gps(){
char* token;
t=0;
memset(Gps_field,0,sizeof(Gps_field));
token=strtok(gpsmoduleoutput,",");
do 
{
	strcpy(Gps_field[t],token);
	token=strtok(NULL,",");
	t++;
} while (token!=NULL);
}
