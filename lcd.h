/* 
 * File:   lcd.h
 * Author: evohc
 *
 * Created on October 30, 2018, 6:12 PM
 */

#ifndef LCD_H
#define	LCD_H
#include <xc.h>
//#include <pic18f4520.h>
#include <string.h>
#include <stdio.h>

#define _XTAL_FREQ 4000000// LCD module connections

#define RS PORTEbits.RE0
#define EN PORTEbits.RE1

#define D4 PORTCbits.RC1
#define D5 PORTCbits.RC2

#define D6 PORTCbits.RC3
#define D7 PORTCbits.RC4

// End LCD module connections


  
void Lcd_Port(char a);
void Lcd_Cmd(char a);
void Lcd_Clear();
void  Lcd_Set_Cursor(char a, char b);
void Lcd_Init();
void Lcd_Write_String(char *a);
void Lcd_Write_Char( char a);
void Lcd_Shift_Right();
void Lcd_Shift_Left();


#endif	/* LCD_H */
