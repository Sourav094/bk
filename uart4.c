#include "LPC17xx.h" 
void UART0_Init (void) 
{ 
	LPC_PINCON->PINSEL0 |= (1 << 4)| (1 << 6);			 //Pin P0.2 used as TXD0 & Pin P0.3 used as RXD0 
	LPC_UART0->LCR = 0x83;								 /* 8 bits, no polarity, 1stop bit */ 
	LPC_UART0->DLM = 0; 
	LPC_UART0->DLL = 9; 						// 115200 baus rate @25MHz clk 
	LPC_UART0->LCR = 0x03; 						/* Lock the baud rate */ 
	LPC_UART0->FDR = 0x21; 							//MULVAL=2,DIVADDval=1 
} 
int UART0_SendChar (int Data) 
{ 
	while (!(LPC_UART0->LSR & 0x20)); 					//if LSR.5th bit =0 wait for valid data. 
	return (LPC_UART0->THR = Data); 					// LSR.5th bit =1 ,THR has valid data 
}
int UART0_GetChar(void)
{
	while(!(LPC_UART0->LSR & 0x01));
	return(LPC_UART0->RBR);
}
void UART0_SendString (unsigned char *s) 
{ 
	while (*s != 0)									 // if content of string is not 0 
	UART0_SendChar(*s++); 						//send char and auto increment i.e 
	s=s+1;
} 
int main(void) 
{ 
	char ch; 
	UART0_Init( ); 									//initialize UART0 
	UART0_SendString( " hello world! "); 				//send to uart terminal 
	while(1)
	{
		ch=UART0_GetChar();
		UART0_SendChar(ch);
	}
}

