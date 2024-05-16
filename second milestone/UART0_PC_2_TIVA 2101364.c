//Abdelaziz Mohamed Ahmed 2100420
//Hassan Ramadan Zaref 2101364
//Youssef Waleed Hussien 2101023
//Ahmed Hany Mostafa 2100741
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
extern int flagsend;
extern int distance_sent;
extern int flag ;
extern int t;
extern int temp;
extern int z ;// flag to compare each character recieced with gpslogname
extern int flg ;//flag to determine if log name is the required one or not
extern int fillcount ;//index to fill gpsmoduleoutput
extern int i; //flag for sending each of latitude and longtitude
extern int flagg;
extern int lat_int[lengtharr];// Latitude in char that would be sent to the python code in order to be drawn
extern int lon_int[lengtharr];//  Longitude in char that would be sent to the python code in order to be drawn

extern float lat [lengtharr];// Latitude in float
extern float lon [lengtharr];//  Longitude in float
extern float distance;//distance calculatd from function getdistance
extern float speed;//speed that was determined by gps module
extern float tempfloat;//the float part of latitude and longtitude
extern double distance_acc ;//total distance at the end
extern char gpsmoduleoutput[lengtharrgps];//total output from gps module after removing log name
extern char gpslogname[];//logname required to get from distance from
extern char Gps_field [12][20];//2d array required to divide gps module into fields to easily modify them
extern char recieved;//each character received from gps module
extern char ur;//character received from the pc
extern char str[9]; // Assuming a maximum of 20 characters for the string representation
extern char strs[5];
extern unsigned long xv;

//Global variables
extern int flagsend;
static void wait_1ms(){ 
NVIC_ST_RELOAD_R=16000;
NVIC_ST_CURRENT_R = 0;
while((NVIC_ST_CTRL_R & 0x00010000)==0); 
}

// wait for a time of delay*1ms*1000=delay*1sec

static void wait(int delay){ 
	int i;
	int data=delay*1000;
	for(i=0;i<data;i++){
	wait_1ms();
}
}
//Abdelaziz Mohamed Ahmed & DIAA ASHRAF DIAA 
//UART PC TO TIVA Interface --> UART0
//GPS TO UART --> UART2
//read and write from uart0
static void WRITE_int (int data)
{ // Split the 32-bit integer into four bytes
    
	  while((UART0_FR_R & 0X20) !=0) {};
	  UART0_DR_R=(char)data;
}

static void WRITE_char (char data)
{
	while((UART0_FR_R & 0X20) !=0) {};
	UART0_DR_R = data;
		
}

static char read_char(){
while (((UART0_FR_R) & 0x010) != 0){
	flagsend=0;
	wait(1);
	break;
}
flagsend=1;
return (char)(UART0_DR_R & 0x0FF);
}

//---------------------------------------------------------
 //read and write from uart2
static void UART_WRITE (char data)
{
	while((UART2_FR_R & 0X20) !=0) {};
	UART2_DR_R = data;
}

static char read(){
while (((UART2_FR_R) & 0x010) != 0);
return (char)(UART2_DR_R & 0x0FF);
}

static void gpsread()
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
static void printstring(char *p){
	while(*p)
	{
		WRITE_char(*p);
		p++;
	}	
}
// getting value from switch and updating the led

static unsigned long switch_interface(){
return (GPIO_PORTF_DATA_R & 0x11);
}

static void updateled(unsigned int led){
	GPIO_PORTF_DATA_R=led;
}
static void send_coordinates(){
	i=0;
while(1){
	if(lat_int[i]==0)
		break;
	sprintf(str, "%d", lat_int[i]);
	printstring(str);
	i++;
printstring("\n");
}
printstring("latdone\n\n");
i=0;
while(1){
		if(lon_int[i]==0)
		break;
sprintf(str, "%d", lon_int[i]);
	printstring(str);
	i++;
printstring("\n");
}
printstring("logdone\n\n");

sprintf(strs, "%d", distance_sent);
printstring(strs);
printstring("\n");
printstring("done\n\n");
}
