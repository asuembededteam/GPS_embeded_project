#include "tm4c123gh6pm.h"
#define entter 0x0D
#include <stdio.h>
#include <string.h>

void init_uart(){
SYSCTL_RCGCUART_R |= 0x01; // activate clock of uart
while((SYSCTL_RCGCUART_R & 0x01 )==0); // wait
UART0_CTL_R &= ~0x01; //disable for configuration
UART0_IBRD_R=520;
UART0_FBRD_R=53; // baud rate = 9600
UART0_LCRH_R=0x070;// 8 bit word length and enable fifo
UART0_CTL_R=0x301;//enable rxe , txe and uart
}

char read(){
while (((UART0_FR_R) & 0x010) != 0);
return (char)(UART0_DR_R & 0x0FF);
}

void getstring(char *Command ,int len){
int i=0;
char ch=0;
for (i=0;i<len;i++){
	ch=read();
if(ch != entter){
	Command[i]=ch;
}
else if (ch == entter){
		break;
}
}

}

//Diaa Ashraf Diaa El-Deen 2100578 
