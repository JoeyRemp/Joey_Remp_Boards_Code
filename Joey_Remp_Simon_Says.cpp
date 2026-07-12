// C++ code
//Joey Remp

// setting global variables
// setting array variables
int solSet[10];
int LEDpins[4] = {8, 9, 10, 11};
int buttonPins[4] = {2, 3, 4, 5};

void setup()
{
  Serial.begin(9600);
  // this for loop will define pins 2-5 as input pullups for the LEDs and the buttons as outputs using the array variables
  for(int i = 0; i < 4; i++){
    pinMode(buttonPins[i], INPUT_PULLUP);
    pinMode(LEDpins[i], OUTPUT);
    
  }
  
  // this sets a randomized seed allowing for our random command to actually be random.
  randomSeed(analogRead(A1));
}

void loop()
{
  
  // setting local variables
  bool lose = 0;
  
  // generate winning sequence
  generSeq();
  
  //start play
  // level loop
  for(int level = 0; level < 10; level++){
  	//show current sequence
    // this for loop is what will run show the player the level they are on
    for(int i = 0; i <= level; i++){
      
      digitalWrite(LEDpins[solSet[i]], HIGH);
      delay(750);
      digitalWrite(LEDpins[solSet[i]], LOW);
      delay(750);
      
    }
  
  	// response current sequence
    for(int i = 0; i <= level; i++){
      
      // this will constantly check to see if and when the player presses a button
      int buttonRes = -1;
      while(buttonRes < 0){
       	buttonRes = buttonPressed();
      }
      // this will briefly turn on the LED associated to the button that the player presses
      digitalWrite(LEDpins[buttonRes], HIGH);
      delay(250);
      digitalWrite(LEDpins[buttonRes], LOW);
      delay(250);
      // this checks to see if the button is correct.
      // this if statement will determine what happens when the player loses.
      if(solSet[i] != buttonRes){
        lose = 1;
        break;
      }
    }
  
  	// win continuation or lose breakout
    // this will run the lose sequence once a player loses
    if(lose == 1){
      loseSeq();
      break;
      // this else if will trigger the win sequence when the player wins.
    } else if(lose == 0 && level == 9){
      winSeq();
    }
  
  
  	// end of loop
  }
  
}
 



// this squence is for if we lose what will happen
void loseSeq(){
  
  Serial.println("Lose Running");
  // this will turn all the LEDs on and then slowly fade them to off
  // turning all the LEDs on
  for(int i = 0; i < 4; i++){
    digitalWrite(LEDpins[i], HIGH);  
  }
  delay(1000);
  // fading them out
  for(int i = 0; i < 4; i++){
    digitalWrite(LEDpins[i], LOW);  
    delay(750);
  }
}

// this sequence is for if we win what will happen
void winSeq(){
  
  Serial.println("Win Running");
  // this will flash the LEDs when the player wins
  // turning on the LEDs
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 4; j++){
      digitalWrite(LEDpins[j], HIGH);
    }
    delay(500);
    // turning off the LEDs
    for(int j = 0; j < 4; j++){
      digitalWrite(LEDpins[j], LOW);
    }
    delay(500);
    
  }
}

// this will generate the sequence
void generSeq(){
  
  // Generating solution set 
  // this for loop will have the solSet variable climb from 1 to 10  
  for(int i = 0; i < 10; i++){
    solSet[i] = random(4);
  }
  
  Serial.print("solSet = ");
  
  for(int i = 0; i < 10; i++){
    Serial.print(solSet[i]);
    Serial.print(", ");
  }
  Serial.println(" ");
}

// this sequence will check for debouncing
bool isPressed(int buttonNum){
  
  // setting boolean local variable
  bool pressed = false;
  
  // this will check to see if the button is pressed then to see if it is still pressed after 10 miliseconds if both are pressed it will return as false otherwise it will return as true
  if(digitalRead(buttonPins[buttonNum])== LOW){
   delay(10);
    if(digitalRead(buttonPins[buttonNum])== LOW){
      pressed = true;
    }
  }
  
  return pressed;
}

// this sets the sequence on determining what button is pressed, using int instead of void allows for an integer to be passed out of it.
int buttonPressed(){
  // setting local variables
  int buttonNumb = -1; 
  
  // this for loop will look to see if any buttons are pressed.
  for(int i = 0; i < 4; i++){
    if(isPressed(i) == true){
      buttonNumb = i;
    }
  }
  
  //this will return the buttonNum variable to  
  return buttonNumb;
}