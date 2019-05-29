#include <lpc17xx.h> 
int main(void) 
{ 
	int x, y, z; 
	LPC_GPIO0->FIODIR = 0x0FF0;					 // Configure P0.4 to p0.11 as Output 
	while(1) 										//infinite loop 
	{ 
		z = 0x0800; 								// initialize with 1000 0000 0000; 
		for (x=8; x > 0; x-- ) 
		{ 
			LPC_GPIO0-> FIOPIN = z; 				// Initially P0.11 to turn LED ON 
			for (y=1000000; y > 0; y--); 			// delay 
			z = z >> 1; 							// right shift Z content by 1 time 
		} 
	} 
}
