/*
Joey Remp

Part B of Assignment 5.3 DC Motor Movement

motor needs to start breaking at 336cm to fullfil assignment requirements
so at 336 cm motor will be at 100% 
at 2 cm motor will be 0% 
stay linear from 336 cm to 2 cm
*/


// making global variables
int cm = 0;
int pwmLevel1 = 0;
int pwmLevel2 = 0;


// Read Time Function
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}


void setup()
{
  // start serial 
  Serial.begin(9600);
  
  //define outputs 
  for (int i = 3; i < 11; i++) {
    pinMode(i, OUTPUT);
  }
 
}

void loop()
{
  //read distance 
  cm = 0.01723 * readUltrasonicDistance(7, 7);
  Serial.print("cm: ");
  Serial.println(cm);
  // set motor speed (PWM on Enable)
  // create range for pwm 
  if (cm > 200) {
    pwmLevel1 = 255;
    pwmLevel2 = 255;
  } else if ( cm < 45){
    pwmLevel1 = 0;
    pwmLevel2 = 0;
  } else {
  	pwmLevel1 = 75;
    pwmLevel2 = 75;
  }
  
  // moving and recording left motor
  Serial.print("pwmLevel1: ");
  Serial.println(pwmLevel1);
  // set motor
  digitalWrite(4, LOW);
  digitalWrite(3, HIGH);
  analogWrite(5, pwmLevel1);

  // moving and recording right motor
  Serial.print("pwmLevel2: ");
  Serial.println(pwmLevel2);
  // set motor
  digitalWrite(9, HIGH);
  digitalWrite(8, LOW);
  analogWrite(10, pwmLevel2);
  // delay then repeat
  delay(1000); // Wait for 1000 millisecond(s)
  
  
  
}