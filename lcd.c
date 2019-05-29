
#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
#include "lcd.h"

/****************************************************************************
  Function Name : delay()		(software)
  Description :
  Input :  
  Output : void
********************************************************************************/
void delay(unsigned int count)
{
  unsigned int j=0,i=0;

  for(j=0;j<count;j++)
  {
    for(i=0;i<12000;i++);
  }
}

/********************************************************************************************
  Function Name :	lcd_command_write()
  Description   :	
  Input         :	
  Output        :	Void
*********************************************************************************************/
void lcd_command_write( unsigned char command )
{
 
  //LCD_DATA_SET |= (command & LCD_DATA_MASK);
	LCD_DATA_SET = command;
	
	LCD_CTRL_CLR |= LCDRS;
	LCD_CTRL_SET |= LCDEN;
  delay(1);
  LCD_CTRL_CLR |= LCDEN;
  delay(1);
}

/**********************************************************************************************
  Function Name :	lcd_data_write()
  Description   :	
  Input         :	
  Output        :	Void
*********************************************************************************************/
void lcd_data_write( unsigned char data )
{
	//LCD_DATA_SET = (data & LCD_DATA_MASK);
  LCD_DATA_SET = data;
	
  LCD_CTRL_SET |= LCDRS;
	LCD_CTRL_SET |= LCDEN;
  delay(1);
  LCD_CTRL_CLR |= LCDEN;
  delay(1);
}

/**********************************************************************************************
  Function Name :	lcd_clear()
  Description   :	
  Input         :	
  Output        :	Void
*********************************************************************************************/
void lcd_clear( void)
{
  lcd_command_write( 0x01 );
}

/**********************************************************************************************
  Function Name :	lcd_gotoxy()
  Description   :	
  Input         :	
  Output        :	Void
*********************************************************************************************/
int lcd_gotoxy( unsigned char x, unsigned char y)
{
  unsigned char retval = TRUE;
  
  if( (x > 1) && (y > 15) )
   {
     retval = FALSE;
   } 
  else
   {
     if( x == 0 ) lcd_command_write( 0x80 + y );		
  	 else if( x==1 ) lcd_command_write( 0xC0 + y );
   }
   return retval;
}

/**********************************************************************************************
  Function Name :	lcd_putchar()
  Description   :	
  Input         :	
  Output        :	Void
*********************************************************************************************/
void lcd_putchar( unsigned char c )
{
  lcd_data_write( c );
}

/**********************************************************************************************
  Function Name :	lcd_putstring()
  Description   :	
  Input         :	
  Output        :	Void
*********************************************************************************************/
void lcd_putstring( char *string )
{
   while(*string != '\0')
  {
    lcd_putchar( *string );
    string++;
  }
}

/**********************************************************************************************
  Function Name :	lcd_putstring16()
  Description   :	
  Input         :	
  Output        :	Void
*********************************************************************************************/
void lcd_putstring16( unsigned char line, char *string )
{
  unsigned char len = 16;

  lcd_gotoxy( line, 0 );
  while(*string != '\0' && len--)
  {
    lcd_putchar( *string );
    string++;
  }
}

/**********************************************************************************************
  Function Name :	init_lcd()
  Description   :	
  Input         :	
  Output        :	Void
*********************************************************************************************/
void init_lcd( void )
{
	SEG_CTRL_DIR |= SEG_DIG_MASK;		//switch off 7-seg
	SEG_CTRL_SET &= ~SEG_DIG_MASK;	//switch off 7-seg
	
	LPC_GPIO0->FIODIR |= 0x00000FF0;           /* LEDs on PORT0 are output      */
	LPC_GPIO0->FIOPIN &= ~0x00000FF0;           /* LEDs off      */
	
	LCD_CTRL_DIR |= ( LCDEN | LCDRS );
  LCD_DATA_DIR = LCD_DATA_MASK;

  delay(1000);
  lcd_command_write(0x38);     /*   8-bit interface, two line, 5X7 dots.        */
  lcd_command_write(0x38);     
  lcd_command_write(0x38);     
  lcd_command_write(0x10);     /*     display shift       */
  lcd_command_write(0x0C);     /*     display on          */
  lcd_command_write(0x06) ;    /*   cursor move direction */
  lcd_command_write(0x01) ;    /*   cursor home      */
  delay(1000);
}
