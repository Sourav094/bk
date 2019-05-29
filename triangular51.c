#include <LPC17xx.H>
int main (void) 
{ 
	int i, m; 
	LPC_PINCON->PINSEL1 = (1<< 21); //Select AOUT function for P0.26 
	while(1) 
	{ 
		for (i = 0; i <= 1023; i++) //send value start from 0 to 1023 insteps of 1 
		{ 
			LPC_DAC->DACR = (i << 6); // DACR register value should placed in 15:6 
			for(m = 15; m >=1; m--); //delay to vary freq 
		} 
		for (i = 1023 ; i > 0; i--) //once reaches max of 3.3v starts decreasing 
		{ 
			LPC_DAC->DACR = (i << 6); 
			for(m = 15; m > 1; m--); 
		} 
	} 
}
