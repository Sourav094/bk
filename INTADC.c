//Program display Internal ADC value on 16x2 lcd
                  
#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
//#include <stdio.h>
#include "lcd.h"

#define ADC_DONE            0x80000000
#define ADC_OVERRUN         0x40000000

#define ADC_CLK			1000000		/* set to 1Mhz */

volatile int ADCValue;


void ADCInit( int Clk )
{
  int pclk;

  
  LPC_SC->PCONP |= (1 << 12);   				/* Enable CLOCK into ADC controller */

  //LPC_PINCON->PINSEL1 &= ~0x0000C000;		/* P0.23 AD0 function 01 Input */
  LPC_PINCON->PINSEL1 |= 0x00004000;
  //LPC_PINCON->PINMODE1 &= ~0x0000C000;	/* P0.23 AD0 function 10 No pull-up no pull-down */
  LPC_PINCON->PINMODE1 |= 0x00008000;
	
	pclk = SystemCoreClock/4;

  LPC_ADC->ADCR = ( 0x01 << 0 ) |  /* SEL=1,select channel 0~7 on ADC0 */
		( ( pclk  / Clk - 1 ) << 8 ) |  /* CLKDIV = Fpclk / ADC_Clk - 1 */ 
		( 0 << 16 ) | 		/* BURST = 0, no BURST, software controlled */
		( 0 << 17 ) |  		/* CLKS = 0, 11 clocks/10 bits */
		( 1 << 21 ) |  		/* PDN = 1, normal operation */
		( 0 << 24 ) |  		/* START = 0 A/D conversion stops */
		( 0 << 27 );		/* EDGE = 0 (CAP/MAT singal falling,trigger A/D conversion) */ 

  return;
}


uint32_t ADCRead( )
{
  int regVal, ADC_Data;
  LPC_ADC->ADCR &= 0xFFFFFF00;
  LPC_ADC->ADCR |= (1 << 24) | 1;	
	/* switch channel,start A/D convert */

  while ( 1 )							/* wait until end of A/D convert */
  {
		regVal = LPC_ADC->ADDR0;
		
		if ( regVal & ADC_DONE ) break;        /* read result of A/D conversion */
  }	
        
  LPC_ADC->ADCR &= 0xF8FFFFFF;						/* stop ADC now */    
  
	if ( regVal & ADC_OVERRUN )	return ( 0 ); /* save data when it's not overrun, otherwise, return zero */
  
  ADC_Data = ( regVal >> 4 ) & 0xFFF;
  return ( ADC_Data );											/* return A/D conversion value */
}


int main (void) 
{
	char lstr[10];
	double volt;
	
	
  ADCInit( ADC_CLK );

  init_lcd();

	lcd_putstring16(0,"ADC Val = 00  ");
	lcd_putstring16(1,"VOLTAGE = 0.00v ");
	
  while(1)
  {
		ADCValue = ADCRead();
		sprintf (lstr, "%4u", ADCValue);
		lcd_gotoxy(0,10);
		lcd_putstring(lstr);
		
		volt = ADCValue * 3.3/4096;				//temp = ((ADCValue * 3.3) / 4096) ;
		sprintf (lstr, "%0.2f", volt);
		lcd_gotoxy(1,10);
		lcd_putstring(lstr);
		delay(500);
	}
}
