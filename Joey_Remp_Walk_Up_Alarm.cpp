// Joey Remp SIP Digital Prototype
// https://joeyremp.wixsite.com/joeyrempuatsip
// May 20, 2026

/*

The goal for this project is to have the two sensors constantly
read the distance of any object in its view. Once anything gets
within 46 centimeters or 1.5 feet the motor will spin and the 
speakers will sounds. In real life the motors will be virbation
motors on the legs of a walker to alert the user that an obstacle
is coming up.
*/


/*
  Keyboard

  Plays a pitch that changes based on a changing
  input circuit:
  * 3 pushbuttons from +5V to analog in 0 through
  3
  * 3 10K resistors from analog in 0 through 3 to
  ground
  * 8-ohm speaker on digital pin 8
*/


// setting global variables for the distance on the sensors.
int Lcm = 0;
int Rcm = 0;

// setting global variables for the speed of the motors
int LpwmLevel = 0;
int RpwmLevel = 0;

// Read Time Function for the left sensor
long LreadUltrasonicDistance(int LtriggerPin, int LechoPin)
{
  pinMode(LtriggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(LtriggerPin, LOW);
 
  // delays 2 microseconds
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(LtriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(LtriggerPin, LOW);
  pinMode(LechoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(LechoPin, HIGH);
}

// Read Time Function for the right sensor
long RreadUltrasonicDistance(int RtriggerPin, int RechoPin)
{
 
  pinMode(RtriggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(RtriggerPin, LOW);
 
  // delays 2 mircoseconds
  delayMicroseconds(2);
 
  digitalWrite(RtriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(RtriggerPin, LOW);
  pinMode(RechoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(RechoPin, HIGH);
}

void setup()
{
  // serial start
  Serial.begin(9600);
 
  //define output pins
  for (int i = 2; i < 14; i++) {
    pinMode(i, OUTPUT); }
}

void loop()
{
  //read distance for left sensor
  Lcm = 0.01723 * LreadUltrasonicDistance(7, 6);
  // the arduino will constantly print the distance to show that it is working.
  Serial.print("Lcm: ");
  Serial.println(Lcm);
  
  //read distance for the right sensor
  Rcm = 0.01723 * RreadUltrasonicDistance(13, 12);
  // the arduino will constantly print the distance to show that it is working.
  Serial.print("Rcm: ");
  Serial.println(Rcm);
  
  
  // this if statement will check to see if the sensors detect an object within 46 centimeters or 1.5 feet and will start the function of the circuit if it is.
  if (Lcm <= 46 || Rcm <= 46) {
    // setting motor speeds to high
    LpwmLevel = 255;
    RpwmLevel = 255; 
    
      // the nested if is so that once the motors speeds are set the speakers will then sound.
      if (LpwmLevel == 255 || RpwmLevel == 255){
        
        // plays the right speaker at a low tone for a second
        tone(2, 415, 3500);
        delay(1000);
        //turns off the right speaker
        noTone(2);
        
        // plays the left speaker at a high tone for a second
        tone(4, 1000, 3500);
        delay(1000);
        // stops the high tone for the right speaker
        noTone(4);

		// plays the right speaker on a low tone for a second
        tone(4, 400, 3500);
        delay(1000);
        // stops the right speaker
        noTone(4);
        
        // plays the left speaker at a low tone for a seconds and then delays for a second before starting the loop again
        tone(2, 1000, 3500);
        delay(1000);
        noTone(2);
      }
  } else { // if the distance on the sensors is not less than or equal to 46 centimeters the motor speed will be set to 0 so nothing will happen with the motors or speakers.
    
    // setting motor speeds to 0
    LpwmLevel = 0;
    RpwmLevel = 0; 
    
    
  } 
  
  // constantly printing the motor speed in order to see if something stops working.
  Serial.print("LpwmLevel: ");
  Serial.println(LpwmLevel);
  // setting left motor
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  analogWrite(3, LpwmLevel);
  
  // constantly printing the motor speed in order to see if something stops working.
  Serial.print("RpwmLevel: ");
  Serial.println(RpwmLevel);
  // set motor
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  analogWrite(5, RpwmLevel);
  
  // delay then repeat
  delay(1000); // Wait for 1000 millisecond(s)
    
}