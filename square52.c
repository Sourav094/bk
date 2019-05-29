#include <LPC17xx.H>
int main (void)
{
	int i;
	LPC_PINCON->PINSEL1 = (1<<21) ; //Select AOUT function for P0.26
	while (1)
	{
	LPC_DAC -> DACR = (1024 << 6); // 10bit = 1024 Vmax = 3.3 V
	for (i = 120000; i > 1; i--); // maintain this value for some delay
	LPC_DAC -> DACR = (512 << 6); // for Vmax/2 = 1.74V
	for (i = 120000; i > 1; i--); // delay
	}
}
