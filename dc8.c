#include <lpc17xx.h>
int main()
{
	LPC_GPIO2->FIODIR = (1<<8); //Configure the PORT2 pins as OUTPUT
	LPC_GPIO4->FIODIR = (1<<28)|(1<<29); //configure port4 pins p4.28,p4.29 as output
	while(1)
	{
		LPC_GPIO2->FIOSET=(1<<8); //enable DC motor by making P2.8=1
		LPC_GPIO4->FIOCLR = (1<<28); // P4.28 =1
		LPC_GPIO4->FIOSET = (1<<29); // P4.29 = 0 Anti Clockwise rotation
	}
}
