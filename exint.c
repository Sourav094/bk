#include <lpc17xx.h>
void EINT1_IRQHandler(void)
{
	LPC_SC->EXTINT =2;
	LPC_GPIO0->FIOPIN ^= (1<<4);
}
void EINT0_IRQHandler(void)
{
	LPC_SC->EXTINT =1;
	LPC_GPIO0->FIOPIN ^= (1<<11);
}
int main()
{
	LPC_SC->EXTINT = 3;
	LPC_PINCON->PINSEL4 = (1<<22)|(1<<20);
	LPC_SC->EXTMODE = 1;
	LPC_SC->EXTPOLAR = 1;
	LPC_GPIO0->FIODIR = (0xFF<<4);
	LPC_GPIO0->FIOPIN = 0x00;
	NVIC_EnableIRQ(EINT1_IRQn);
	NVIC_EnableIRQ(EINT0_IRQn);
	while(1)
	{
		LPC_GPIO3->FIODIR = (1<<27);
	}
}
