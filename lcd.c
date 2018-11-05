/*
 * File:   lcd.c
 * Author: evohc
 *
 * Created on October 30, 2018, 6:14 PM
 */


#include "lcd.h"

void LCD_Init ( void )  {
PORTD = 0;
TRISD = 0x00;
delay__ (); /* wait enough time after Vdd rise */
delay__ ();
delay__ ();
delay__ ();
 LCD_RS =0 ;
 PORTD = 0x03;
LCD_PulseEnable();
delay__ ();
 LCD_PulseEnable();
delay__ ();
 LCD_PulseEnable();
 PORTD = 0x02 ; /* set 4-bit interface */
 LCD_PulseEnable();
 LCD_PutCmd ( 0x2C ); /* function set (all lines, 5x7 characters) */
 LCD_PutCmd ( 0x0C ); /* display ON, cursor off, no blink */
 LCD_PutCmd ( 0x01 ); /* clear display */
 LCD_PutCmd ( 0x06 ); /* entry mode set, increment & scroll left */
 }


void delay__(void)
{
for(count = 1; count < 10000; count++);
}


void upper (unsigned int c)
{
if(c & 0x80) LCD_D7=1; else LCD_D7=0;
if(c & 0x40) LCD_D6=1; else LCD_D6=0;
if(c & 0x20) LCD_D5=1; else LCD_D5=0;
if(c & 0x10) LCD_D4=1; else LCD_D4=0;
}


void lower(unsigned int c)
{
if(c & 0x08) LCD_D7=1; else LCD_D7=0;
if(c & 0x04) LCD_D6=1; else LCD_D6=0;
if(c & 0x02) LCD_D5=1; else LCD_D5=0;
if(c & 0x01) LCD_D4=1; else LCD_D4=0;
}


void LCD_PutChar ( unsigned int c )
 {
 /* this subroutine works specifically for 4-bit Port A */

 LCD_RS =1;
 upper ( c ); /* send high nibble */
 LCD_PulseEnable();
 lower ( c ); /* send low nibble */
 LCD_PulseEnable();
 LCD_RS =0;

 }



void LCD_SetPosition ( unsigned int c )
 {
 /* this subroutine works specifically for 4-bit Port A */
 upper ( c | 0x08 ); 
 LCD_PulseEnable();
 lower ( c );
 LCD_PulseEnable();
 }
void LCD_PutCmd ( unsigned int c )
 {
 /* this subroutine works specifically for 4-bit Port A */
 upper ( c ); /* send high nibble */
 LCD_PulseEnable();
 lower ( c ); /* send low nibble */
 LCD_PulseEnable();
 }
void LCD_PulseEnable ( void )
 {
 LCD_EN = 1;
 delay__(); // was 10
 LCD_EN =0;
 delay__(); // was 5
 }