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
// LCD module connections
#define LCD_D4 PORTDbits.RD4
#define LCD_D5 PORTDbits.RD5
#define LCD_D6 PORTDbits.RD6
#define LCD_D7 PORTDbits.RD7
#define LCD_EN PORTEbits.RE2
#define LCD_RS PORTEbits.RE0
// End LCD module connections
#pragma config WDT=OFF
long int count;
char c; //Character to be printed to LCD



void LCD_Init ( void );
void LCD_SetPosition ( unsigned int c );
void LCD_PutCmd ( unsigned int c );
void LCD_PulseEnable ( void );
void delay__(void);
void upper (unsigned int c);
void lower(unsigned int c);
void LCD_PutChar ( unsigned int c );

#endif	/* LCD_H */

