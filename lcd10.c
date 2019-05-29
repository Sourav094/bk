#include <LPC17xx.h>
#define LCD_RS (1<<28)
#define LCD_EN (1<<27)
void LCD_Command(unsigned char cmd)
{
	LPC_GPIO2->FIOPIN = cmd ;
	LPC_GPIO0->FIOCLR |= LCD_RS; 			// RS=0
	LPC_GPIO0->FIOSET |= LCD_EN; 			// EN=1
	for(int k=0;k<100000;k++); 				// delay
	LPC_GPIO0->FIOCLR |= LCD_EN;			 //EN=0
}
void LCD_Data(unsigned char data)
{
	LPC_GPIO2->FIOPIN = data;
	LPC_GPIO0->FIOSET |= LCD_RS;			 // RS=1
	LPC_GPIO0->FIOSET |= LCD_EN; 			//EN=1
	for(int j=0;j<100000;j++); 				// delay
	LPC_GPIO0->FIOCLR |= LCD_EN; 			// EN=0
}
void LCD_Init(void)
{
	LPC_GPIO0->FIODIR |= (LCD_RS | LCD_EN);
	LPC_GPIO2->FIODIR0 = 0x00FF; 					// Config P2.0 to P2.7 as o/p pins
	LCD_Command(0x38); 							// 8 bits, 2 lines, 5x7 Dots
	LCD_Command(0x01);							 // Clear Display screen
	LCD_Command(0x0e); 							// Display on & cursor On
}
int main()
{
	unsigned char str[]={"Acharya "};
	unsigned int x=0; 				// initialize x=0
	LCD_Init();
	LCD_Command(0x80); 				// Force cursor to beginging of I row, [ 0xc0 for II row]
	while(str[x] != '\0')			 // if content of str in not a null char
	{
		LCD_Data(str[x]);			 // send to LCD as Data
		x++; 						//increment x
	}
}
