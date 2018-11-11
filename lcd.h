/* 
 * File:   lcd.h
 * Author: evohc
 *
 * Created on October 30, 2018, 6:12 PM
 */

#ifndef LCD_H
#define	LCD_H
#include <xc.h>
#include <string.h>
#include <stdio.h>
#define _XTAL_FREQ 4000000// LCD module connections
/*
#define RS PORTEbits.RE0
#define EN PORTEbits.RE2

#define D4 PORTBbits.RB1
#define D5 PORTBbits.RB2
#define D6 PORTBbits.RB3
#define D7 PORTBbits.RB4

 */
 // End LCD module connections
#define RS PORTDbits.RD2
#define EN PORTDbits.RD3
#define D4 PORTDbits.RD4
#define D5 PORTDbits.RD5
#define D6 PORTDbits.RD6
#define D7 PORTDbits.RD7

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
