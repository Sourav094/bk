#include <LPC17xx.H>
#include "lcd.h"
void col_write(unsigned char data)
{
	LPC_GPIO1->FIOSET|=(data<<14);
}
int main (void)
{
	unsigned char key,i;
	unsigned char rval[]={0x7,0xB,0xD,0xE};
	unsigned char keyPadMatrix[ ]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	init_lcd();
	LPC_GPIO1->FIODIR=(1<<14|1<<15|1<<16|1<<17);
	lcd_putstring16(0,"Press HEX_KeyBoard..");
	lcd_putstring16(1,"Key Pressed=");
	
	while(1)
	{
		key=0;
		for(i=0;i<4;i++)
		{
			LPC_GPIO1->FIOCLR|=(1<<14|1<<15|1<<16|1<<17);
			col_write(rval[i]);
			if(!(LPC_GPIO1->FIOPIN & 1<<21))
				break;
			  key++;
			if(!(LPC_GPIO1->FIOPIN & 1<<20))
				break;
			  key++;
			if(!(LPC_GPIO1->FIOPIN & 1<<19))
				break;
			  key++;
			if(!(LPC_GPIO1->FIOPIN & 1<<18))
				break;
			  key++;
		}
		if(key==0x10)
			lcd_putstring16(1,"Key Pressed= ");
		else
		{
			lcd_gotoxy(1,14);
			lcd_putchar(keyPadMatrix[key]);
		}
	}
}