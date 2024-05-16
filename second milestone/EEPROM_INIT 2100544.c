//Abdelrahman Mohamed Ragab 2100544
#include "tm4c123gh6pm.h"
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

static void eeprom_initialization(){
// Enable the EEPROM peripheral\
	
SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
SysCtlDelay(20000000);
SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);
EEPROMInit();
EEPROMMassErase();
EEPROMProgram((uint32_t*)&lat_int,0x0000,sizeof(lat_int));
EEPROMProgram((uint32_t*)&lon_int,0x200,sizeof(lon_int));
EEPROMProgram((uint32_t*)&distance_sent,0x400,sizeof(distance_sent));
}

static void eeprom_read(){
SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
SysCtlDelay(20000000);
SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);
EEPROMInit();	
EEPROMRead((uint32_t*)&lat_int,0x0000,sizeof(lat_int));
EEPROMRead((uint32_t*)&lon_int,0x200,sizeof(lon_int));
EEPROMRead((uint32_t*)&distance_sent,0x400,sizeof(distance_sent));
}