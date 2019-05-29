#include <LPC17xx.H>
int main (void)
{
	unsigned int i,k, z;
	LPC_GPIO1->FIODIR = (1<< 22)|(1<< 23)|(1<< 24)|(1<< 25);
	while (1)
	{
		k = 0x00400000; 						//initially P.25 =1 [ 1000 ]
		for(z=0; z<4; z++)						 // four coils to be made high one by one
		{
			LPC_GPIO1->FIOPIN =k; 				//Port1 pins assigned with Ka value
			for ( i=120000; i >0 ; i-- ) ;		 // Delay
			k = k<<1;							 // k content rotate right
		}
	}
}
