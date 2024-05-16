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

//reading the output of gps and putting it in gpsmoduleoutput array
void gpsread()
	{
	do {//loop until logname = logname
	flg=1;
		for(z=0;z<7;z++){
			recieved = read();
	if(recieved!=gpslogname[z]){
		flg=0;
		break;
	}
	}
}while(flg==0);
memset(gpsmoduleoutput,0,lengtharrgps);
fillcount=0;
do{
recieved = read();
gpsmoduleoutput[fillcount++]=recieved;
}while(recieved !=star);
}
// Hassan Ramadan Zaref 2101364	
