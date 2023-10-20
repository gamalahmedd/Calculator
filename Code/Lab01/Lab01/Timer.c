#include <avr/io.h>
#include "MACROS.h"

void Timer_vInitPhaseCorrectMode(unsigned char duty_cycle)
{
	SET_BIT(DDRB, PIN3);
	SET_BIT(TCCR0, CS00);
	SET_BIT(TCCR0, CS02); //Prescaler 1024
	SET_BIT(TCCR0, WGM00); //Phase Correct PWM
	SET_BIT(TCCR0, COM00); //Inverting Mode
	SET_BIT(TCCR0, COM01);
	OCR0 = 255 * ((100 - duty_cycle) * 0.01);
}
