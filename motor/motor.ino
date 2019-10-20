// G28 Z90.6 with 1/2" nozzle

// Direction
// From A to B Red, RWhite, Green, GWhite
// digitalWrite(dir, HIGH) = INWARDS

// ALWAYS RETURN TO 0 POS OR RESET POS TO CURRENT VALUE
// TYPE zero IN SERIAL PORT AND HIT ENTER


// default settings
int delaytime = 1; 
int steps = 1500;
int pos = 0; 
int stroke = 2;
float strain = 6.5; // percentage
int delay1 = 3035; // time from hitting limit switch to print begin
int print_array[2] = { 573, 10  }; // steps , delaytime

const byte numChars = 32;
char receivedChars[numChars];
boolean newData = false;

#include <SPI.h>

#define stp 2
#define dir 3
#define EN 4
#define lim 7

void setup() {
  // put your setup code here, to run once:
  pinMode(stp, OUTPUT);
  digitalWrite(stp, LOW);
  pinMode(dir, OUTPUT);
  digitalWrite(dir, LOW);
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);
  pinMode(lim, INPUT_PULLUP);

}

void loop() {
  moveMotor(0, LOW);
}

void moveMotor(int x, uint8_t d)
{
  if (delaytime < 1)
    return;

  digitalWrite(dir,d);
  //digitalWrite(EN, HIGH);
  if ((steps > pos && d == LOW) || x == 3)
    steps = pos;
  for (unsigned int i = 0; i < steps; i++)
  {
    digitalWrite(stp,HIGH); 
    delay(delaytime);
    digitalWrite(stp,LOW); 
    delay(delaytime);
  }
  //digitalWrite(EN, LOW);
  
  if (x == 1)
    pos = pos + steps;
  else if (x == 0 || x == 3)
    pos = pos - steps;
}
