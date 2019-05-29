#include <LPC17xx.H>
unsigned char dat7seg[] = {0x88,0xeb,0x4c,0x49,0x2b,0x19,0x18,0xcb,0x8,0x9,0xa,0x38,0x9C,0x68,
0x1c,0x1e};
int main (void)
{
	unsigned int i, j;
	unsigned int count=0; 												// initially count=0;
	LPC_GPIO2->FIODIR = 0x000000FF;									 // PORT2 p2.0 to p2.7 are output
	LPC_GPIO1->FIODIR = (1<<26)|(1<<27)|(1<<28)|(1<<29); 								//Dig control on PORT1 p1.26-.29 are output
	while(1)
	{
		if (count > 0xF) 
			count = 0;										 // if count Greater than F, re initialize to 0
			for (i=0; i < 20000; i++) 									//change to inc/dec speed of count
			{
				LPC_GPIO2->FIOPIN = dat7seg[count];								 // & 0x000F];
				LPC_GPIO1->FIOSET = (1<<26)|(1<<27)|(1<<28)|(1<<29); // 26 for first Sev segment , 27 for second
				for (j=0; j<1000; j++); 								//change to inc/dec brightness of display
				LPC_GPIO1->FIOCLR = (1<<26)|(1<<27)|(1<<28)|(1<<29);
			}
		count++;													 //count = count+1
	}
}
