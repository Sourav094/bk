#include <LPC17xx.h> 
int main() 
{ 
	LPC_GPIO3->FIODIR = 1<< 25; 					// port 3.25 pin (buzzer) is configured as o/p 
	LPC_GPIO1->FIODIR &=~(1<< 21); 					// port p1.21 pin (switch) is configured as i/p 
	while(1) 
	{ 
		if (! (LPC_GPIO1->FIOPIN & (1<< 21)))			 // if switch P.21 pressed 
		{ 
			LPC_GPIO3->FIOSET = (1<< 25); 			// Port 3.25 pin is set [ High] 
		} 
		else 
		{ 
			LPC_GPIO3->FIOCLR = (1<< 25); 			// Port 3.25 pin is Clear [Low] 
		} 
	} 
}
