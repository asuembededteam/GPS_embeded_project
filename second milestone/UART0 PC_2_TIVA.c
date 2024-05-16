//DIAA ASHRAF DIAA ElDeen 2100578
//Abdelaziz Mohamed Ahmed 
//UART PC TO TIVA Interface --> UART0
//GPS TO UART --> UART2

//read and write from uart0
void WRITE_int (int data)
{ // Split the 32-bit integer into four bytes
    
	  while((UART0_FR_R & 0X20) !=0) {};
	  UART0_DR_R=(char)data;
}

void WRITE_char (char data)
{
	while((UART0_FR_R & 0X20) !=0) {};
	UART0_DR_R = data;
		
}

char read_char(){
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
void UART_WRITE (char data)
{
	while((UART2_FR_R & 0X20) !=0) {};
	UART2_DR_R = data;
}

char read(){
while (((UART2_FR_R) & 0x010) != 0);
return (char)(UART2_DR_R & 0x0FF);
}
