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

//tramsfering the field of latitude and longtitude into float and storing it in lat[float],lon[float] and copying this field into lat_har and lon_char
void getdistance(){
if(flag==0)
{
	if((strcmp(Gps_field[1],"A")) ==0){
		  temp=(atoi(Gps_field[4]))/100;
		  tempfloat=((atof(Gps_field[4])/100.0)-temp)*(100.0/60.0);//transfering from minute to float
		  tempfloat=temp+tempfloat;	  
		  lon[flag]=tempfloat*1.0000;
			//strcpy(lon_char[flag],Gps_field[4]);
		  lon_int[flag]=(atof(Gps_field[4]))*100000;
			temp=(atoi(Gps_field[2]))/100;
		  tempfloat=((atof(Gps_field[2])/100.0)-temp)*(100.0/60.0);//transfering from minute to float
		  tempfloat=temp+tempfloat;
		  lat[flag]=tempfloat*1.0000;
			//strcpy(lat_char[flag],Gps_field[2]);
		  lat_int[flag]=(atof(Gps_field[2]))*100000;
		  flag++;
	}
} else
{
      if((strcmp(Gps_field[1],"A")) ==0){
		  temp=(atoi(Gps_field[4]))/100;
		  tempfloat=((atof(Gps_field[4])/100.0)-temp)*(100.0/60.0);//transfering from minute to float
		  tempfloat=temp+tempfloat;	  
		  lon[flag]=tempfloat*1.0000;
			//strcpy(lon_char[flag],Gps_field[4]);
		  lon_int[flag]=(atof(Gps_field[4]))*100000;
			temp=(atoi(Gps_field[2]))/100;
		  tempfloat=((atof(Gps_field[2])/100.0)-temp)*(100.0/60.0);//transfering from minute to float
		  tempfloat=temp+tempfloat;
		  lat[flag]=tempfloat*1.0000;
			//strcpy(lat_char[flag],Gps_field[2]);
		  lat_int[flag]=(atof(Gps_field[2]))*100000;
			speed=atof(Gps_field[6]);
			if(speed>1.1){//if the speed is more than this donot update the distance or change the flag this was written because of error in the begining of operation
			distance=(GPS_getDistance())*1000;
			if(distance<10.0){//if the distance is more than this donot update the distance or change the flag this was written because of error in the begining of operation
			distance_acc=distance_acc+(distance);
			distance_sent=(int)(distance_acc*100.0);
		  flag++;
			}
			}
	}
}
}