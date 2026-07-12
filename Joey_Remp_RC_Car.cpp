// Joey Remp

#include "Adafruit_LEDBackpack.h"

#include <IRremote.h>


int button = 0;

int mtrDrv = 0;

// setting global variables
int mtrAfwd = 8; //input 2
int mtrArev = 7; //input 1
int mtrBfwd = 4; //input 3
int mtrBrev = 5; // input 4

int mtrAen = 9;
int mtrBen = 6;

int speedRun = 0;

Adafruit_7segment led_display1 = Adafruit_7segment();

// Map the IR code to the corresponding remote button.
// The buttons are in this order on the remote:
//    0   1   2
//    4   5   6
//    8   9  10
//   12  13  14
//   16  17  18
//   20  21  22
//   24  25  26
//
// Return -1, if supplied code does not map to a key.
int mapCodeToButton(unsigned long code) {
  // For the remote used in the Tinkercad simulator,
  // the buttons are encoded such that the hex code
  // received is of the format: 0xiivvBF00
  // Where the vv is the button value, and ii is
  // the bit-inverse of vv.
  // For example, the power button is 0xFF00BF000

  // Check for codes from this specific remote
  if ((code & 0x0000FFFF) == 0x0000BF00) {
    // No longer need the lower 16 bits. Shift the code by 16
    // to make the rest easier.
    code >>= 16;
    // Check that the value and inverse bytes are complementary.
    if (((code >> 8) ^ (code & 0x00FF)) == 0x00FF) {
      return code & 0xFF;
    }
  }
  return -1;
}

int readInfrared() {
  int result = -1;
  // Check if we've received a new code
  if (IrReceiver.decode()) {
    // Get the infrared code
    unsigned long code = IrReceiver.decodedIRData.decodedRawData;
    Serial.println(code, HEX);
    // Map it to a specific button on the remote
    result = mapCodeToButton(code);
    // Enable receiving of the next value
    IrReceiver.resume();
  }
  return result;
}

void setup()
{
  Serial.begin(9600);
  Serial.println("Let's Go");
  led_display1.begin(112);
  IrReceiver.begin(2);
  pinMode(A0, INPUT);
  
  
  // this for loop will set all of our pins for our motors as outputs.
  for(int i = 4; i < 10; i++){
    
    pinMode(i, OUTPUT);
    
  }

  // this will enable pins 3 and 6 allowing us to start each time.
  digitalWrite(3, HIGH);
  digitalWrite(6, HIGH);

  led_display1.println("----");
  led_display1.writeDisplay();
}

void loop()
{
  button = readInfrared();
  if (button >= 0) {
    led_display1.println(button);
    led_display1.writeDisplay();
    // this sets the mtrDrv value to button in order to retain the information of what button was pushed.
    mtrDrv = button;
  }
  
  speedSet();
  
  makeRun();
}


// setting function to determine speed.
void speedSet(){
  
  // this line will constantly display the analog read from our potentionmeter.
  Serial.print("Pot Read Value: ");
  Serial.println(analogRead(A0));
  // defining variables
  int potRead = analogRead(A0);
  
  // these if statements are for the potentiometer to determine at what speed the motors will run
  
  // for speed 1
  if(potRead > 0) {
    speedRun = 20;
  }
  
  // for speed 2
  if(potRead > 170) {
    speedRun = 43;
  }
  
  // for speed 3
  if(potRead > 341) {
    speedRun = 86;
  }
  
  // for speed 4
  if(potRead > 512) {
    speedRun = 129;
  }
  // for speed 5
  if(potRead > 682) {
    speedRun = 172;
  }
  // for speed 6
  if(potRead > 852) {
    speedRun = 215;
  }
  // for speed 7
  if(potRead == 1023) {
    speedRun = 255;
  }
  
}


void makeRun(){
  
  // this if statement will make the motors go forward.
  // see button mapping at the top for button values
  if(mtrDrv == 17){
    // reminder that LOWs go first inorder to not burn out the motors
  	digitalWrite(mtrArev, LOW);
  	digitalWrite(mtrBrev, LOW);
  	digitalWrite(mtrAfwd, HIGH);
  	digitalWrite(mtrBfwd, HIGH);
    analogWrite(mtrAen, speedRun);
  	analogWrite(mtrBen, speedRun);
    
  }
  
  // this will make the motors reverse
  if(mtrDrv == 25){
    // reminder that LOWs go first inorder to not burn out the motors
  	digitalWrite(mtrAfwd, LOW);
  	digitalWrite(mtrBfwd, LOW);
  	digitalWrite(mtrArev, HIGH);
  	digitalWrite(mtrBrev, HIGH);
    analogWrite(mtrAen, speedRun);
  	analogWrite(mtrBen, speedRun);
    
  }
  
  // this will make the motors go left
  if(mtrDrv == 20){
    // reminder that LOWs go first inorder to not burn out the motors
  	digitalWrite(mtrAfwd, LOW);
  	digitalWrite(mtrBrev, LOW);
  	digitalWrite(mtrArev, HIGH);
  	digitalWrite(mtrBfwd, HIGH);
    analogWrite(mtrAen, speedRun);
  	analogWrite(mtrBen, speedRun);
    
  }
  
  // this will make the motors go right
  if(mtrDrv == 22){
    // reminder that LOWs go first inorder to not burn out the motors
  	digitalWrite(mtrArev, LOW);
  	digitalWrite(mtrBfwd, LOW);
  	digitalWrite(mtrAfwd, HIGH);
  	digitalWrite(mtrBrev, HIGH);
    analogWrite(mtrAen, speedRun);
  	analogWrite(mtrBen, speedRun);
    
  }
  
  // this will stop the motors
  if(mtrDrv == 21){
    // reminder that LOWs go first inorder to not burn out the motors
  	digitalWrite(mtrArev, LOW);
  	digitalWrite(mtrBrev, LOW);
  	digitalWrite(mtrAfwd, LOW);
  	digitalWrite(mtrBfwd, LOW);
    analogWrite(mtrAen, speedRun);
  	analogWrite(mtrBen, speedRun);
    
  }
  delay(10); // Delay a little bit to improve simulation performance
}