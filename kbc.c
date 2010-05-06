#include "kbc.h"

int DEBUG = 0;


/** Initializes the KeyBoard Controller. If 'debug' is not 0 every
 * read or write to the KBC, together with the read or writed data is
 * echoed to the screen. In this mode the function name being executed
 * is printed followed by a ':', add=xx means the I/O address written,
 * and data=xx the data read or written.
 *
 *  A 1 is returned if a mouse is found.
 *
 * The function starts to flush any pending data in the KBC, reading
 * the data register until a timeout is received.
 *
 * Then it enables the KBC mouse interface, send a MouseReset to the
 * mouse and checks for the correct answer (0xFA, 0xAA then 0x00).  If
 * the mouse was detected, data streaming is disabled (StreamDisable),
 * SampleRate is set to 100, Resolution is set to 8 counts/mm, Scaling
 * is set to 1:1, the mouse interrupts generation are enabled at the
 * KBC (not at the PIC!), and data streaming enabled
 * (StreamEnable). All this (but StreamEnable) shouldn't be necessary,
 * as MouseReset is supposed to do it properly.
 *
 * The KBDRate is also set to its maximum speed.
 *
 * Uses write_kbc_cmd(), write_kbc_data(), read_kbc() and write_aux()
 * </pre></code>
 */

/** Returns the data read a the data register.
*
*  Waits for OBF on status register up to KBC_TIMEOUT milliseconds,
*  then reads and returns the data read at the data register. Returns
*  -1 on timeout or transmission error.
*/
int read_kbc(void)
{
	int t = time_tick + KBC_TIMEOUT;
	Byte stat, data;
	if(DEBUG) printf("read_kbc: ");
	while( time_tick < t)
	{
		
		stat = inportb(STAT_REG);
		
		if( (stat & OBF) != 0)
		{
			data = inportb(DATA_REG);
		
			if( (stat & (PAR_ERR | TO_ERR)) == 0)
			{
				if(DEBUG) printf("data=%x\n", data);
				return data;
			}
			else
			{
				if(DEBUG) printf("timeout\n");
				return -1;
			}
		}
		
		mili_sleep(10);
	
	}
	
	if(DEBUG) printf("timeout\n");
	return -1;
}


/** Write 'data' at IO address 'adr' , returning -1 on error or timeout.
 *
 * Waits for IBF on status register , than writes data to 'adr',
 * return -1 on timeout.
 */
int write_kbc(unsigned adr, unsigned data)
{
	Byte stat;
	if(DEBUG) printf("write_kbc: ");
	
	int t = time_tick + KBC_TIMEOUT;
	while(time_tick < t)
	{
		stat = inportb(STAT_REG);
		

		if((stat & IBF) == 0)
		{
			if(DEBUG) printf("add=%x data=%x\n", adr, data);
			outportb(adr, data); 
			return 0;
		}
		
		mili_sleep(30);
	}

	if(DEBUG) printf("timeout\n");
	return -1;
}

/** shortky blink all three keyboard LEDs
 *
 */

/** shortky blink left(1), middle(2) or right(3) keyboard LED
 *
 */
 
void blink_led(uchar led)
{
	disable_irq(KBD_IRQ );
	write_kbc(DATA_REG, WriteLEDS);
	write_kbc(DATA_REG, led);

	mili_sleep(100);
		
	write_kbc(DATA_REG, WriteLEDS);
	write_kbc(DATA_REG, 0x00);
	mili_sleep(10);
	enable_irq(KBD_IRQ );
}

void blink_leds()
{
	int i=3;
	
	for(; i >= 0; i-- )
	{
		blink_led(i);
	}
}


