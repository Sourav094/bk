#include <lpc17xx.h>

int main(void)
{
	SystemInit();
	LPC_GPIO4->FIODIR = 0x30000000;
	LPC_GPIO1->FIODIR = ~(1<<21);
	LPC_GPIO1->FIODIR = ~(1<<20);
	LPC_GPIO1->FIODIR = ~(1<<19);
	while(1)
	{
		if(!(LPC_GPIO1->FIOPIN &(1<<21)))
		{
			LPC_GPIO4->FIOPIN = 0x10000000;
			LPC_GPIO2->FIOPIN = 0x00000100;
		}
		else if(!(LPC_GPIO1->FIOPIN &(1<<20)))
		{
			LPC_GPIO4->FIOPIN = 0x20000000;
			LPC_GPIO2->FIOPIN = 0x00000100;
		}
		else if(!(LPC_GPIO1->FIOPIN &(1<<19)))
		{
			LPC_GPIO4->FIOPIN = 0x00000000;
			LPC_GPIO2->FIOPIN = 0x00000100;
		}
	}
}

