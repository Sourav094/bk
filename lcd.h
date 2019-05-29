#ifndef _LCD_H
#define _LCD_H

#define TRUE 1
#define FALSE 0

#define LINE1 0x80
#define LINE2 0xC0

#define CONTROL_REG 0x00
#define DATA_REG    0x01

#define LCD_DATA_DIR	   LPC_GPIO2->FIODIR0
#define LCD_DATA_SET	   LPC_GPIO2->FIOPIN0
#define LCD_CTRL_DIR	   LPC_GPIO0->FIODIR
#define LCD_CTRL_SET	   LPC_GPIO0->FIOSET
#define LCD_CTRL_CLR	   LPC_GPIO0->FIOCLR

#define SEG_DATA_DIR	   LPC_GPIO2->FIODIR
#define SEG_DATA_SET	   LPC_GPIO1->FIOPIN
#define SEG_CTRL_DIR	   LPC_GPIO1->FIODIR
#define SEG_CTRL_SET	   LPC_GPIO1->FIOPIN

#define LCDEN	           (1 << 27)
#define LCDRS	           (1 << 28)

//scale 31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,09,08,07,06,05,04,03,02,01,00
#define LCD_DATA_MASK		0x000000FF
#define SEG_DIG_MASK		0x0F000000

void delay(unsigned int count);
void init_lcd(void);
void lcd_putstring(char *string);
void lcd_putstring16(unsigned char line, char *string);
void lcd_clear(void);
int lcd_gotoxy(unsigned char x, unsigned char y);
void lcd_putchar(unsigned char c);

#endif
