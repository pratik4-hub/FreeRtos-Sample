
#ifndef __SPI_H_
#define __SPI_H_

#include <avr/io.h>
#include <util/delay.h>

#define MISO 6
#define MOSI 5
#define SCK 7
#define SS 4

void SPISlaveInit(void);
unsigned char spi_tranceiver(unsigned char);
void led_blink (unsigned char ,unsigned char );
void spi_init_master(void);










#endif /* SPI_H_ */




