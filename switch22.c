#include <LPC17xx.h> 
int main() 
{ 
	LPC_GPIO0->FIODIR = 1<< 25; 						// port 0.25 pin (relay) is configured as o/p 
	LPC_GPIO1->FIODIR &=~ (1<< 21); 					// port p1.21 pin is configured as i/p 
	while(1) 
	{ 
		if (! (LPC_GPIO1->FIOPIN & (1<< 21))) 				// if switch P.21 pressed 
		{ 
			LPC_GPIO0->FIOSET = (1<< 25);					 // Port 0.25 pin is set [ High] 
		} 
		else 
		{ 
			LPC_GPIO0->FIOCLR = (1<< 25);				 // Port 0.25 pin is Clear [Low] 
		} 
	} 
}
