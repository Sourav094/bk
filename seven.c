#include <lpc17xx.h>
unsigned char dat7seg[] = {0x88,0xeb,0x4c,0x49,0x2b,0x19,0x18,0xcb,0x8,0x9,0xa,0x38,0x98,0x68,0x1c,0x1e};
int main(void)
{
unsigned int i,j;
unsigned int count = 0;

LPC_GPIO2->FIODIR = 0x000000FF;
LPC_GPIO2->FIOPIN = 0x000000FF;

LPC_GPIO1->FIODIR  |= 0x3C000000;
LPC_GPIO1->FIOPIN &= ~(0x3C000000);
while(1)
{
	if(count>9) count =0;
for(i=0;i<20000;i++)
{
LPC_GPIO2->FIOPIN = dat7seg[count];
LPC_GPIO1->FIOSET = (1<<29)|(1<<26);
for(j=0;j<1000;j++);
LPC_GPIO1->FIOCLR = (1<<29)|(1<<26);
}
count++;
}
}

