//Hussien Mohamed Hussien 2100274
//Ahmed Ibrahim 2101038
//Salma mostafa 2100470
#include "tm.h"
#define star 0x2A //* in ascii
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <net_config.h>
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
static float ToRad(float angle){
	return angle*PI/180;
}

// get the distance between two suessive points

static float GPS_getDistance () {
float long1 =ToRad ((lon[flag]));
float lat1 = ToRad ((lat[flag])); 
float long2 = ToRad ((lon[flag-1]));
float lat2 = ToRad ((lat[flag-1]));
// Get Difference
float dlong = -(long2 - long1);
float dlat = -(lat2 - lat1);
// Calculate Distance
float a = pow(sin(dlat / 2), 2)+cos(lat1)*cos(lat2)*pow(sin(dlong / 2), 2); // Haversine formula: a sin" (?f/2) + cos 1 cos 20 sin (?1/2)
double c = 2 * atan2(sqrt(a), sqrt(1 - a));
return EARTH_RADIUS*c;
}
static void getdistance(){
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
