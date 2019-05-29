#include <lpc17xx.h>
int main(void)
{
	int j,DutyCycle;
	LPC_PINCON->PINSEL7 = 3 << 20; /* Cofigure pin P3.20 for PWM mode. */
	LPC_PWM1->TCR = (1<< 0) | (1<< 2); //enable counter and PWM
	LPC_PWM1->MCR = (1<< 1);						 /*Reset on PWMMR0, reset TC if it matches MR0 */
	LPC_PWM1->MR0 = 100; 								/* set PWM cycle(Ton+Toff)=100) */
	LPC_PWM1->PCR = 1 << 11; /* Enable the PWM output pin for PWM_3 */
	while(1)
	{
		for(DutyCycle=0; DutyCycle < 100; DutyCycle++)
		{
			LPC_PWM1->MR3 = DutyCycle; /* Increase the DutyCycle from 0-100 */
			for(j=0;j<1000000;j++);
		}
	}
}
