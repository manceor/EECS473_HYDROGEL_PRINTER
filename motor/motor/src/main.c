/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include <avr/io.h>

void setMotorDir(bool);
void moveMotor(int);

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	board_init();
	/* Insert application code here, after the board has been initialized. */
	
	int dir = 1;
	DDRB = (1<<DDB0) | (1<<DDB1); //set GPIO0 and GPIO1 as outputs
	
	while(1){
		for(int i = 0; i < 10000; ++i){
			moveMotor(1);
		}
		dir = !dir;
		setMotorDir(dir);
		delay_ms(50);
	}
}

void setMotorDir(bool dir){
	//using PORTC0 for pulse dir
	if(dir){
		PORTB |= (1<<PORTB0);
	}
	else{
		PORTB &= ~(1<<PORTB0);
	}
}

void moveMotor(int steps){
	PORTB |= (1<<PORTB1);
	delay_ms(1);
	PORTB &= ~(1<<PORTB1);
	delay_ms(1);
}