//Diaa Ashraf Diaa Eldeen 2100578
#include "tm.h"
#define star 0x2A //* in ascii
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <net_config.h>
#include "sysctl.h"
#include "eeprom.h"

#define lengtharr 200 // no of points taken
#define lengtharrgps 100 // size of gps module output
#define PI 3.141592653589793238462643383279502884197
#define EARTH_RADIUS 6371
#define rec 0x55 //u in ascii

//Global variables
int flagsend;
int distance_sent;
int flag ;
int t;
int temp;
int z ;// flag to compare each character recieced with gpslogname
int flg ;//flag to determine if log name is the required one or not
int fillcount ;//index to fill gpsmoduleoutput
int i; //flag for sending each of latitude and longtitude
int flagg;
int lat_int[lengtharr];// Latitude in char that would be sent to the python code in order to be drawn
int lon_int[lengtharr];//  Longitude in char that would be sent to the python code in order to be drawn
float lat [lengtharr];// Latitude in float
float lon [lengtharr];//  Longitude in float
float distance;//distance calculatd from function getdistance
float speed;//speed that was determined by gps module
float tempfloat;//the float part of latitude and longtitude
double distance_acc ;//total distance at the end
char gpsmoduleoutput[lengtharrgps];//total output from gps module after removing log name
char gpslogname[]="$GPRMC,";//logname required to get from distance from
char Gps_field [12][20];//2d array required to divide gps module into fields to easily modify them
char recieved;//each character received from gps module
char ur;//character received from the pc
char str[9]; // Assuming a maximum of 20 characters for the string representation
char strs[5];
unsigned long xv;
#include "Initializations.c"
#include "UART0 PC_2_TIVA.c"
#include "EEPROM_INIT.c"
#include "Distance_Manipulation.c"
#include "dividing_Field_gps.c"



//-----------------------------------------------------------------------------------
		
void sev_segment(){
int distancedisp=(int)distance_acc;
int h=distancedisp/100;//hundredth
int t=(distancedisp-h*100)/10;//tenth
int u = distancedisp-h*100-t*10;//units
GPIO_PORTA_DATA_R|=(h<<2);
GPIO_PORTB_DATA_R|=t;
GPIO_PORTB_DATA_R|=(u<<4);
}

int main(){
//calling initialization functions
PORTD_Init();
PORTB_Init();
PORTF_Init();
init_uart0();
//SW_Init();
SYSTIC_TIMER_Init();
init_portA_pin01();
//infinite loop to keep the function going
while(1){
	if(flagg==0){
xv = switch_interface();//get value from switch
gpsread();//read output from gps module
dividing_field_gps();//divide output from gps module into fields
getdistance();//update the value of latitude and longtitude and calculate the distance
if ( xv==0x01)// if distance exceeds 100 or switch is pushed
{
eeprom_initialization();
updateled(GREEN);
 break;
//updateled(GREEN);
//sev_segment();
}
else if(xv==0x11)
updateled(RED);
}
ur=read_char();
if (flagsend==1){
	
if (ur==rec )
{	
memset(lat_int,0,sizeof(lat_int));
memset(lon_int,0,sizeof(lon_int));
eeprom_read();
EEPROMMassErase();
SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN);
SysCtlPeripheralDisable(SYSCTL_PERIPH_EEPROM0);
init_uart0();
updateled(BLUE);
send_coordinates();
//sev_segment();
 break;
}
}
}
}





