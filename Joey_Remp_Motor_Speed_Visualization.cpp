
#include <avr/io.h>
#include <avr/interrupt.h>

// define global variables
// NOTE: global variables must be defined as volatile in order for the interrupts to call them.
volatile uint8_t phase = 0;
volatile int ovrFloCt = 0;

//setup for timer
static inline void initTimer0(void){
	// the prescaler set up here is the 64 prescaler in Timer0
	TCCR0B |= (1 << CS01 | 1 << CS00);
	TIMSK0 |= (1 << OCIE1B);
	TIMSK0 |= (1 << TOIE0);
	sei(); // sei is to enable the interrupt
}

// setting interrupt for overflow
ISR(TIMER0_OVF_vect){
	
	PORTB |= 14; // both PORT B5 and B6 need to be enabled in order to move the motor which in binary would be 0b01100000 or equal to 14.
	
	ovrFloCt++; // this will add to the overflow count causing the if statement below to trigger at a specific point.
	
	if(ovrFloCt == 4883){ // the 4883 is calculated in order to set the time for 5 seconds to meet my aimed goal.
		// general not for the PORTD commands, there is not an |= here because we want to turn off the prior LED in each phase so that the lights can be visualizations of the speed
		if (phase == 0){
			OCR0B = 255; // sets the motor to 100% speed
			PORTD = 1; // this sets the green LED on to show the motor is in full speed
			phase = 1;
			} else if (phase == 1){
			OCR0B = 128; // sets the motor to 50% speed
			PORTD = 4; // this sets the yellow LED on to show that the speed was cut in half
			phase = 2;
			} else if (phase == 2){
			OCR0B = 191; // sets the motor to 75% speed
			PORTD = 2; //this sets on the blue LED to show the speed is ramping back up
			phase = 3;
			} else if (phase == 3){
			PORTB = 0; // sets the motor to 0% speed
			PORTD = 8; // this sets the red LED to show that the motor has stopped
			phase = 0; // phase gets set to 0 to reset the if statement loop.
		}
		
		ovrFloCt = 0;
	}
}

ISR(TIMER0_COMPB_vect){
	PORTB &= ~(14); //  if it hits the comparator for B it will turn the motor off.
}


int main(void)
{
	DDRB |= 14;
	DDRD |= 15;
	initTimer0();
	OCR0B = 255;
	while (1)
	{
	}
}
