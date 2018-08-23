/*
 * GccApplication15.c
 *
 * Created: 7/27/2018 10:30:47 PM
 * Author : HP
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "USART_8.h"
#define BAUD 9600
#include <avr/interrupt.h>
#define F_CPU 1000000UL
#include <util/delay.h>
int ratio;

#include <avr/sfr_defs.h>


#include "ps2.h"

//#define BAUD 12				//set after at commands mode
//#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)


enum {select, leftStick, rightStick, start, up, right, down, left}; //3rd byte from ps2 controller
enum {leftFront2, rightFront2, leftFront1, rightFront1, triangle_up, circle_right, cross_down, square_left}; // 4th byte from ps2 controller

enum left;

uint8_t x,y,j,b,c,d;
uint8_t l,m,n,o;
int isAnalogOn(uint8_t);
/*void pwm1_init()
{
	TCCR1A|=(1<<WGM11 | 1<<COM1A1 | 1<<COM1B1);
	TCCR1B|=(1<<WGM13 | 1<<WGM12 | 1<<CS10);
	DDRD|=(1<<PIND5 | 1<<PIND4);
	ICR1=1000;
}
*/

int isAnalogOn(uint8_t v)
{
	if(v==127)
	{
		return(0);
	}
	else
	{
		return(1);
	}
}

int isPressed(uint8_t dataByte, uint8_t dataBit)
 {
	return ((dataByte & (1 << dataBit)) ? 1 : 0);
}




int main(void)
{
    USART_Init(51);
	//pwm1_init();
	//USART_Transmitchar('A');
	//USART_Transmitchar(0x0D);
	_delay_us(50);
	init_PS2();				//function to initialize spi
	_delay_us(2000);
	//initialise usart
    DDRB|=(1<<PINB1)|(1<<PINB2);
	
	
	//USART_Transmitchar('M');
	//USART_Receive();
	while (1)
	{//USART_Transmitchar('U');
		//USART_Transmitchar('B');
		//USART_Receive();
		//	USART_Transmitchar(0x0D);
		scan_PS2();
		//_delay_us(500);
		PORTD=0x00;
		x=~data_array[3];
		y=~data_array[4];
		j=~data_array[5];
		b=~data_array[6];
		c=~data_array[7];
		d=~data_array[8];
		
		l=j;
		m=b;
		n=c;
		o=d;
		//USART_Transmitchar('A');
		//USART_TransmitBinary(x);
		//USART_TransmitNumber(b);
		//_delay_ms(3000);
		//USART_TransmitNumber(d);
		
		//_delay_ms(3000);
		/*if (isPressed(x,up))	//x refers to the array which will be in terms of 000x 0000 if switch corresponding to up is pressed and up refers to enum
		{
			
            USART_Transmitchar('u');
            PORTD|=(1<<PIND7);
			
			//USART_Transmitchar(0x0D);
			//USART_Receive();
			//PORTC|=(1<<PINC1);
			_delay_ms(10);
		}
		/*else if(d<127)
		{
				PORTB|(1<<PINB1);
		}
			
		else if(d>127)
		{
			PORTB|(1<<PINB2);
		}
		
		else
		{PORTD&=~(1<<PIND7);
		}
		*/
		/*
		if(isAnalogOn(b))
		{	USART_TransmitNumber(b);
			_delay_ms(6);
			ratio=(((128-m)*999)/128);
			//ratio=ratio-%*ratio;
			//OCR1A=(ratio);
			_delay_ms(1);
			if(m<128)
			{
				PORTD|=(1<<PIND0);
			}
			else
			{
				PORTD&=~(1<<PIND0);
			}
			if(m>128)
			{
				PORTD|=(1<<PIND1);
			}
			else
			{
				PORTD&=~(1<<PIND1);
			}
		}	
		
		else if(isAnalogOn(o))
		{
			ratio=(((128-o)*999)/128);
		    
			OCR1B=(ratio);
			_delay_ms(1);
			if(o<128)
			{
				PORTD|=(1<<PIND2);
			}
			else
			{
				PORTD&=~(1<<PIND2);
			}
			if(o>128)
			{
				PORTD|=(1<<PIND3);
			}
			else
			{
				PORTD&=~(1<<PIND3);
			}
		}
		*/
		
		/*else if (isPressed(x,right))	//x refers to the array which will be in terms of 000x 0000 if switch corresponding to up is pressed and up refers to enum
		{
			
			USART_Transmitchar('R');
			//_delay_us(50);
			//USART_Transmitchar(0x0D);
			//USART_Receive();
		}
		else if (isPressed(x,left))	//x refers to the array which will be in terms of 000x 0000 if switch corresponding to up is pressed and up refers to enum
		{
			
			USART_Transmitchar('L');
			//_delay_us(50);
			//USART_Transmitchar(0x0D);
			//USART_Receive();
		}
		*/
		 /*if (isPressed(x,down))	//x refers to the array which will be in terms of 000x 0000 if switch corresponding to up is pressed and up refers to enum
		{
			
			USART_Transmitchar('D');
			//_delay_us(50);
			//USART_Transmitchar(0x0D);
			//USART_Receive();
			PORTD|=(1<<PIND6);
		}
		else
		{
			PORTD&=~(1<<PIND6);
		}
		*/
		//USART_Transmitchar('A');
		
		if(d<127)
		{
			USART_TransmitString("LB");
			PORTD|=(1<<PIND6);
			PORTD&=~(1<<PIND7);
		}
		else if (d>127)
		{
			USART_TransmitString("LF");
			PORTD|=(1<<PIND7);
			PORTD&=~(1<<PIND6);
		}
		else if (d==127)
		{
			USART_TransmitString("LC");
			PORTD&=~(1<<PIND7);
			PORTD&=~(1<<PIND6);
			
		}
		
		if(b<127)
		{
			USART_TransmitString("RB");
			PORTD|=(1<<PIND5);
			PORTD&=~(1<<PIND4);
		}
		else if (b>127)
		{
			USART_TransmitString("RF");
			PORTD|=(1<<PIND4);
			PORTD&=~(1<<PIND5);
		}
		else if (b==127)
		{
			USART_TransmitString("RC");
			PORTD&=~(1<<PIND4);
			PORTD&=~(1<<PIND5);
			
		}
		
		
		/*
		if (isPressed(y,triangle_up))
		{
			USART_Transmitchar('T');
			//_delay_us(50);
			//USART_Transmitchar(0x0D);
		}
		else if (isPressed(y,circle_right))
		{
			USART_Transmitchar('C');
			//_delay_us(50);
			//USART_Transmitchar(0x0D);
		}
		else if (isPressed(y,cross_down))
		{
			USART_Transmitchar('X');
			//_delay_us(50);
			//USART_Transmitchar(0x0D);
		}
		else if (isPressed(y,square_left))
		{
			USART_Transmitchar('S');
			//_delay_us(50);
			//USART_Transmitchar(0x0D);
		}
		/*else
		{
			USART_Transmitchar('e');
			_delay_us(50);
			//USART_Transmitchar(0x0D);
		}*/
		}
}
