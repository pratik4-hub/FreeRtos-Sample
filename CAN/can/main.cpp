#include<stdio.h>
#include<avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

//#include "lcd.h"
#include "mcp_can.h"
#include "spi.h"
#include "uart.h"

#define PRESCALAR 1024
MCP_CAN can;

void lm35_init(void);
int lm35_read(int channel);
char* itoa(int num, char* str, int base);
int mystrcmp(char *s1,char *s2);


ISR(INT0_vect)
{
	INT32U length = 8;
	INT8U exFlag = 0;
	INT8U can_ID = 1;

	char *str= "STOP";
	uart_puts("Interrupt Arrived\r\n");

	int res = can.sendMsgBuf(can_ID,exFlag,length,(unsigned char*)str);
	if(res == CAN_OK)
		uart_puts("sendMsgBuf successful\r\n");
	else
		uart_puts("sendMsgBuf unsuccessful\r\n");
		return;
		_delay_ms(10);
	return;
}

ISR (INT1_vect)        //External interrupt_one ISR for VEHICLE START/STOP
{
	INT8U can_ID = 3;
	INT32U length = 8;
	INT8U exFlag = 0;

	char *str= "START";
	uart_puts("Interrupt Arrived\r\n");

	int res = can.sendMsgBuf(can_ID,exFlag,length,(unsigned char*)str);
	if(res == CAN_OK)
		uart_puts("START VEHICLE \r\n");
	else
		uart_puts("Button Press unsuccessful\r\n");
		return;
	_delay_ms(10);
	return;

}

int main()
{
	int temp = 0;
	char *str;
	char *str1 = "Temperature";

	lm35_init();
	uart_init(9600);
	spi_init_master();

	PORTB=(1<<SS);
	DDRD=0;
	PORTD=0xFF;

	GICR = 1<<INT0| 1<<INT1;
	MCUCR = 1<<ISC01 | 1<<ISC00 | 1<<ISC10 | 1<< ISC11;

	sei();
	//while(1);

	uart_puts("CAN begin \r\n");
	unsigned int res =can.begin(CAN_100KBPS,MCP_8MHz);
	if(res == CAN_OK)
	{
		uart_puts("init : Successful\r\n");
		_delay_ms(100);
	}
	else if(res == CAN_FAILINIT)
	{
		uart_puts("init : unSuccessfull\r\n");
		_delay_ms(100);
		return -1;
	}
	uart_puts("CAN begin ended \r\n");

	// transmitter code
	while(1)
	{
		can.clearMsg();
		INT8U exFlag = 0;
		INT8U can_ID = 2;
		INT32U length = 8;

		temp = lm35_read(1);

		str = itoa(temp,str,10);
		uart_puts(str);

		res = can.sendMsgBuf(can_ID,exFlag,length,(unsigned char*)str);
		if(res == CAN_OK)
			uart_puts("\r\ntemp sendMsgBuf successful\r\n");
		else
			uart_puts("sendMsgBuf unsuccessful \r\n");

		uart_puts("\r\n");



		_delay_ms(1000);

	}

	while(1);
	return 0;

}


void lm35_init(void)
{
	DDRA=0x0;
	ADCSRA = 0x87;
	ADMUX = 0x40;

}

int lm35_read(int channel)
{
	char *str;
	int Ain,AinLow,celsius;

	ADMUX=ADMUX|(channel & 0x07);

	ADCSRA |= (1<<ADSC);
	while((ADCSRA&(1<<ADIF))==0);
	_delay_us(100);
	AinLow = (int)ADCL;
	Ain = (int)ADCH*256;
	Ain = Ain + AinLow;
	celsius = (Ain*5);
	celsius = (celsius/10);
	return (celsius);
}

char* itoa(int num, char* str, int base)
{
	int i = 0;
	int isNegative = 0;

	// Handle 0 explicitely, otherwise empty string is printed for 0
	if(num == 0)
	{
		str[i++] = '0';
		str[i] = '\0';
		return str;
	}
	// base 10. Otherwise numbers are considered unsigned.
	if (num < 0 && base == 10)
	{
		isNegative = 1;
		num = -num;
	}
	// Process individual digits
	while (num != 0)
	{
		int rem = num % base;
		str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
		num = num/base;
	}
	// If number is negative, append '-'
	if (isNegative)
		str[i++] = '-';
	str[i] = '\0'; // Append string terminator

	// Reverse the string
	int n = i;
	for(i=0; i<n/2; i++)
	{
		char tmp=str[i];
		str[i]=str[n-1-i];
		str[n-1-i]=tmp;
	}
	str[n] = '\0';
	return str;
}

int mystrcmp(char *s1,char *s2)
{
	int i=0;
	while(*(s1+i)==*(s2+i))
	{
		if(*(s1+i)=='\0' || *(s2+i)=='\0')
			break;
		i++;
		if(*(s1+i)!='\0' && *(s2+i)=='\0')
			   return -1;
		else if(*(s1+i)=='\0' && *(s2+i)=='\0')
			   return 0;
		else if(*(s1+i)=='\0' && *(s2+i)!='\0')
			 return 1;
	}
	return -2;

}
