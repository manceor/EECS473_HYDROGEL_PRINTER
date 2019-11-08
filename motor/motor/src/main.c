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
void motorSleep(bool);
void motorReset(void);
void setStepDiv(int);
void setEnable(bool);

int pulseDelay = 750;

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
	setStepDiv(1);
	setEnable(true);
	motorSleep(true); //active low, so this keeps it awake
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
	DDRB = (1<<DDB0) | (1<<DDB1) | (1<<DDB2) | (1<<DDB3); //set GPIO0 through GPIO3 as outputs
	DDRD |= (1<<DDD4) | (1<<DDD5); //enable GPIO4 and GPIO5 as outputs
	DDRC |= (1<<DDC4) | (1<<DDC5); //enable GPIO6 and GPIO7 as outputs
	
	PORTB |= (1<<PORTB3); //set reset high since it is active low
}

void setMotorDir(bool dir){
	//using GPIO0 (PORTB0) for pulse dir
	if(dir){
		PORTB |= (1<<PORTB0);
	}
	else{
		PORTB &= ~(1<<PORTB0);
	}
}

void moveMotor(int steps){
	//using GPIO1 (PORTB1) for step
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

void motorSleep(bool set){
	//using GPIO2 (PORTB2) for sleep
	//active low
	if(set){
		PORTB |= (1<<PORTB2);
	}
	else{
		PORTB &= ~(1<<PORTB2);
	}
}

void motorReset(){
	//using GPIO3 (PORTB3) for reset
	//active low
	PORTB &= ~(1<<PORTB3);
	delay_us(50);
	PORTB |= (1<<PORTB3);
	return;
}

//Change the microstepping division. Takes effect on next STEP pulse.
void setStepDiv(int div){
	//using GPIO4 (PORTD4) as MS3
	//using GPIO5 (PORTD5) as MS2
	//using GPIO6 (PORTC4) as MS1
	switch(div){ //consider stopping motor while changing settings
		case 1: //full step
			PORTD &= ~(1<<PORTD4); //0
			PORTD &= ~(1<<PORTD5); //0
			PORTC &= ~(1<<PORTC4); //0
			break;
		case 2: //half step
			PORTD &= ~(1<<PORTD4); //0
			PORTD &= ~(1<<PORTD5); //0
			PORTC |= (1<<PORTC4);  //1
			break;
		case 4:
			PORTD &= ~(1<<PORTD4); //0
			PORTD |= (1<<PORTD5);  //1
			PORTC &= ~(1<<PORTC4); //0
			break;
		case 8:
			PORTD &= ~(1<<PORTD4); //0
			PORTD |= (1<<PORTD5);  //1
			PORTC |= (1<<PORTC4);  //1
			break;
		case 16:
			PORTD |= (1<<PORTD4);  //1
			PORTD |= (1<<PORTD5);  //1
			PORTC |= (1<<PORTC4);  //1
			break;
		default: //not one of the supported options; maybe return an error msg
			break;
	}
	return;
}

void setEnable(bool set){
	if(set){
		PORTC |= (1<<PORTC5);
	}
	else{
		PORTC &= ~(1<<PORTC5);
	}
}