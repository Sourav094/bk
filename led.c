#include <LPC17xx.h> 
int main() 
{ 
	LPC_GPIO0- >FIODIR = 0x0FF0; 				// P0.4-P0.11 pins as o/p. 
	while(1) 									//infinite loop 
	{
		int i; 
		LPC_GPIO0 - >FIOSET = 0x0FF0; 			// SET po.4 to p0.11 LEDS Turns ON 
		for (i=2000000; i >0; i- -);			 // delay 
		LPC_GPIO0 - >FIOCLR = 0x0FF0; 			//clear P0.4 to P.11 LEDS Turns OFF 
		for (i=2000000;i>0; i--); 					//delay 
	} 
}
