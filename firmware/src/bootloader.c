/******************************************************************************
* ACNodeReader Bootloader                                                     *
*                                                                             *
* (c) 2020 London Hackspace                                                   *
* Released under a 3-clause BSD license. See included LICENSE file.           *
*                                                                             *
******************************************************************************/

#include "target.h"
#include "commsprotocol.h"
#include "serial.h"
#include "tickcounter.h"
#include "lights.h"

#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>

comms_context_t comms;

int main()
{
    wdt_disable();

    unsigned char temp;
    temp = MCUCR;
    MCUCR = temp|(1<<IVCE);
    MCUCR = temp|(1<<IVSEL);

    cli();

    lights_init();

    lights_set(255,0,0);
    _delay_ms(500);
    lights_set(0,255,0);
	_delay_ms(500);
    lights_set(0,0,255);
    _delay_ms(500);
    lights_set(0,0,0);

    tickcounter_init();
    sei();

    lights_set(255,0,0);
	unsigned int start = tickcounter_get();
	lights_set(0,0,255);
	while(tickcounter_get()-start < 500)
	{
		
		wdt_reset();
	}

	lights_set(0,255,0);

	cli();
	wdt_disable();
    MCUCR = temp|(1<<IVCE);
    MCUCR = temp;

#if defined(__AVR_ATmega88PA__) || defined(__AVR_ATmega88PB__)
    void (*go)() = 0x00;
    go();
#else
	asm("jmp 0000");
#endif
}

/*int main()
{
	// disable the watchdog timer so it doesn't interrupt us until we are ready
    MCUSR = 0;
    wdt_disable();

    cli();

    lights_init();

    // make interrupts work in bootloader space
    MCUCR = (1<<IVCE);
    MCUCR = (1<<IVSEL);

    serial_init(115200);
    comms_init(&comms);
    sei();
    comms_set_handlers(&comms, serial_put, serial_get);

    tickcounter_init();

    wdt_reset();
    //wdt_enable(WDTO_500MS);

	while(0)
	{
		wdt_reset();
        comms_poll(&comms);
	}

	lights_set(255,0,0);
	//unsigned int start = tickcounter_get();
	while(1)//tickcounter_get()-start < 10000)
	{
		//wdt_reset();
	}

	//lights_set(255,127,0);

	// run main code
	wdt_disable();
	cli();

	// Put interrupts back in app land
	MCUCR = (1<<IVCE);
	MCUCR = 0;
	//asm("jmp 0000");
	while(1);
}*/