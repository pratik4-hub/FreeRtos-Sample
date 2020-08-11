/*
 * lcd.h
 *
 *  Created on: 19-Jan-2020
 *      Author: ranveer
 */

#ifndef LCD_H_
#define LCD_H_

#define F_CPU 8000000UL					/* Define CPU Frequency e.g. here its 8MHz */
#include <avr/io.h>						/* Include AVR std. library file */
#include <util/delay.h>					/* Include Delay header file */

#define LCD_Data_Dir DDRC				/* Define LCD data port direction */
#define LCD_Command_Dir DDRD			/* Define LCD command port direction register */
#define LCD_Data_Port PORTC				/* Define LCD data port */
#define LCD_Command_Port PORTD			/* Define LCD data port */
#define RS PD5							/* Define Register Select (data reg./command reg.) signal pin */
#define RW PD6							/* Define Read/Write signal pin */
#define EN PD7							/* Define Enable signal pin */

void LCD_Command (char);				/* LCD command write function */
void LCD_Char (char);					/* LCD data write function */
void LCD_Init (void);					/* LCD Initialize function */
void LCD_String (char*);				/* Send string to LCD function */
void LCD_String_xy (char,char,char*);	/* Send row, position and string to LCD function */
void LCD_Clear (void);					/* LCD clear function */




#endif /* LCD_H_ */
