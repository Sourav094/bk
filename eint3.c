#include <lpc17xx.h> 
void EINT1_IRQHandler(void) 
{ 
	LPC_SC->EXTINT = 2; /* Clear Interrupt Flag ext int 0 */ 
	LPC_GPIO0->FIOPIN ^= (1<<11); /* Toggle the LED1 everytime INTR0 is generated */ 
} 
int main( ) 
{ 
	LPC_SC->EXTINT = 2; /* Clear Pending interrupts */ 
	LPC_PINCON->PINSEL4 = (1<< 22); /* Configure P2_10 as EINT0 */ 
	LPC_GPIO0->FIODIR = (1<<11); /*configure LED pins as OUTPUT */ 
	NVIC_EnableIRQ(EINT1_IRQn); /* Enable the EINT0 interrupts */ 
	while(1) 
	{ // any main program running 
	} 
}