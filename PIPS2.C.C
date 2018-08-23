#include "wiringPi"
#define F_CPU 8000000UL
#include <util/delay.h>
#include "PS2.h"
#include "bcm2835_new.h"



void init_PS2()
{
	bcm2835_spi_begin();


	/*SPI_DDR |= (_BV(MOSI_PIN)) | _BV(SCK_PIN) | _BV(SS_PIN);
	SPI_DDR &= ~(_BV(MISO_PIN));
	SPI_PORT |= _BV(MISO_PIN);

	SPCR= 0b01111101;
    */

	char  PS2_CONFIGMODE[5]= {0x01, 0x43, 0x00, 0x01, 0x00};
	char  PS2_ANALOGMODE[9]= {0x01, 0x44, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00};
	char  PS2_EXITCONFIG[9]= {0x01, 0x43, 0x00, 0x00, 0x5a, 0x5a, 0x5a, 0x5a, 0x5a};

    void bcm2835_spi_transfer_array(PS2_CONFIGMODE,5);
	/*SPI_PORT &= ~(_BV(SS_PIN));
	SPI_send_array(PS2_CONFIGMODE,5);
	SPI_PORT |= _BV(SS_PIN);
	_delay_ms(1);
    */
    void bcm2835_spi_transfer_array(PS2_ANALOGMODE,9);
    void bcm2835_spi_transfer_array(PS2_EXITCONFIG,9);
    /*
	SPI_PORT &= ~(_BV(SS_PIN));
	SPI_send_array(PS2_ANALOGMODE,9);
	SPI_PORT |= _BV(SS_PIN);
	_delay_ms(1);


	SPI_PORT &= ~(_BV(SS_PIN));
	SPI_send_array(PS2_EXITCONFIG,9);
	SPI_PORT |= _BV(SS_PIN);
	_delay_ms(1);
	*/
	volatile char ps2_init_array[9]= {0x01, 0x42, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00};
	volatile int ps2_init_i;
	for(ps2_init_i=0; ps2_init_i<10; ps2_init_i++)
	{
		PS2_POLLBUTTON[ps2_init_i] = ps2_init_array[ps2_init_i];
	}
}

void scan_PS2()
{
    void bcm2835_spi_transfer_array(PS2_POLLBUTTON,9);
    /*
	SPI_PORT &= ~(_BV(SS_PIN));
	void bcm2835_spi_transfer_array(PS2_POLLBUTTON,9);
	SPI_PORT |= _BV(SS_PIN);
	_delay_ms(2);
    */
}

