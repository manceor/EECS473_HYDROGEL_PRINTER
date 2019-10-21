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

void initGPIO(void);
void setMotorDir(bool);
void moveMotor(int);
void setSpeed(int);

int pulseDelay = 250;

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	board_init();
	/* Insert application code here, after the board has been initialized. */
	initGPIO();
	
	//change stuff below; SW0 = PB0 = PCINT8
	//PCMSK0 |= (1<<PCINT0); //enable PCINT0
	//PCIFR |= (1<<PCIF0); //clear PCINT0
	//PCICR |= (1<<PCIE0); //enable PCINT0
	
	sei(); //enable interrupts
	int dir = 0;
	
	while(1){
		for(int i = 0; i < 20000; ++i){
			moveMotor(1);
		}
		dir = !dir;
		setMotorDir(dir);
		delay_ms(50);
	}
}

void initGPIO(){
	DDRB = (1<<DDB0) | (1<<DDB1); //set GPIO0 and GPIO1 as outputs
	//DDRD |= (1<<DDD4); //enable GPIO4
	//DDRC |= (1<<DDC4); //enable GPIO6
}

void setMotorDir(bool dir){
	//using PORTD4 for pulse dir
	if(dir){
		PORTB |= (1<<PORTB0);
	}
	else{
		PORTB &= ~(1<<PORTB0);
	}
}

void moveMotor(int steps){
	PORTB |= (1<<PORTB1);
	delay_us(pulseDelay);
	PORTB &= ~(1<<PORTB1);
	delay_us(pulseDelay);
}

void setSpeed(int speed){
	if(speed < 50){
		pulseDelay = 250;
	}
	else{
		pulseDelay = 750;
	}
}