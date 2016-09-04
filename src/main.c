#include	<avr/io.h>
#include	<util/delay.h>
#define	BLINK_DELAY_MS	1000
int	main	(void)
{
				/*	set	pin	25	of	PORTA	for	output*/
				DDRA	|=	_BV(DDA3);
				while(1)	{
								/*	set	pin	25	high	to	turn	led	on	*/
								PORTB	|=	_BV(PORTA3);
								_delay_ms(BLINK_DELAY_MS);
								/*	set	pin	25	low	to	turn	led	off	*/
								PORTB	&=	~_BV(PORTA3);
								_delay_ms(BLINK_DELAY_MS);
				}
}
