
#include "spi.h"

void SPISlaveInit(void)
{
	//set MISO as output

	DDRB=(1<<MISO);
	PORTB|=(1<<SS); //pulls up the ss pin

	SPCR = (1<<SPE);			//|(1<<CPOL)|(1<<CPHA); //enable SPI and enable SPI interrupt

	DDRA=0xff;
	//PORTA=0xff; //PORTA as o/p for blinking leds
}


void spi_init_master (void)
{
	DDRB=(1<<MOSI)|(1<<SCK)|(1<<SS);  //Set MOSI, SCK as Output and others as i/p

	PORTB|=(1<<SS);
	_delay_ms(5);



	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);//|(1<<CPOL)|(1<<CPHA); //Enable SPI, Set as Master,&//Prescaler: Fosc/16, Enable Interrupts

	DDRA=0xff;
	//PORTA=0xff;
}

//Function to send and receive data
unsigned char spi_tranceiver (unsigned char data)
{
	_delay_us(5);
	SPDR = data;                   //Load data into the buffer
	while(!(SPSR & (1<<SPIF) ));       //Wait until transmission complete

	return(SPDR);                      //Return received data
}

//Function to blink LED
void led_blink (unsigned char pin,unsigned char i)
{
	//Blink LED "i" number of times
	for (; i>0; --i)
	{
		PORTA&=~(1<<pin);
		_delay_ms(500);
		PORTA|=(1<<pin);
		_delay_ms(500);
	}
}

