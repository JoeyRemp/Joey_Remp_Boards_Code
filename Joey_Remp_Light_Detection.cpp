// C++ code
// Joey Remp

// global variable for button
int modeSel = 0;

void setup()
{
  Serial.begin(9600);
  // defining A0 as an input
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  
  // this for loop will define outputs for the LED starting at pin 2 and ending at pin 7
  for(int i =2; i < 8; i++){
    pinMode(i, OUTPUT);
  }
  pinMode(8, INPUT_PULLUP);
}

void loop()
{
  // setting variable for the button using a boolean variable
  bool selRead = digitalRead(8);
  
  // this if statement will change the mode selection telling the button what to do on push
  if(selRead == 0){
    if(modeSel == 0){
      modeSel = 1;
    }
  } else {
    modeSel = 0;
  }
  
  // this if statement will define the functions for the button depending on if it's pushed or not.
  if(modeSel == 0){
    potSensor();
  } else {
    lightSensor();
  }
  
  delay(100);
  
  // this for loop resets the lights.
  for(int i =2; i <8; i++){
    
    digitalWrite(i, LOW);
  }
}

// this defines the pot sensor's function allowing it to be used with the push button for easy programming    
void potSensor(){
  // this line will constantly display the analog read from our potentionmeter.
  Serial.print("Pot Read Value: ");
  Serial.println(analogRead(A0));
  // defining variables
  int potRead = analogRead(A0);
  
  // these if statements are for the potentiometer to determine what LEDs will get turned on
  // for Blue LED 1
  if(potRead > 170) {
    digitalWrite(2, HIGH);
  }
  // for Blue LED 2
  if(potRead > 341) {
    digitalWrite(3, HIGH);
  }
  // for Green LED 1
  if(potRead > 512) {
    digitalWrite(4, HIGH);
  }
  // for Green LED 2
  if(potRead > 682) {
    digitalWrite(5, HIGH);
  }
  // for Red LED 1
  if(potRead > 852) {
    digitalWrite(6, HIGH);
  }
  // 
  if(potRead == 1023) {
    digitalWrite(7, HIGH);
  }
}
  
// this defines the light sensor's function allowing it to be used with the push button for easy programming 
void lightSensor(){
    
  // this line will constantly display the analog read from our photoresistor.
  int photoRead = analogRead(A1);
  
  Serial.print("Photo Read Value: ");
  Serial.println(analogRead(A1));
  
  // variables needed
  float ddR2 = 0.0F;
  float ddR1 = 0.0F;
  float curr = 0.0F;
  float photoR = 0.0F;
  
  // math for values
  // the float cast in the line below changes our int variable to a float variable allowing the mix of data types to function together.
  ddR2 = 5*(float (photoRead)/1023);
  curr = ddR2/10000;
  ddR1 = 5 - ddR2;
  photoR = ddR1/curr;
  
  
  // these if else if else statements will turn on the respective LEDs based on the value of photoR with our math we did above.
  if(photoR > 1204){
    digitalWrite(7, HIGH);
    digitalWrite(6, HIGH);
  } else if(photoR > 750){
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
  } else{
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
  }
    
  }