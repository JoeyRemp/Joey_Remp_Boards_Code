/*
Joey Remp
Assignment 5.2 Inverse Kinematics with a Two Link Robot
*/

// create needed variables
int l1 = 0;
int l2 = 0;
int x = 0;
int y = 0;
float theta1 = 0.0f;
float theta2 = 0.0f;
float theta1Rad = 0.0f;
float theta2Rad = 0.0f;
bool valid = 0;
float hyp = 0;

void setup()
{
  //begin serial port
  Serial.begin(9600);
}

void loop()
{
  while(valid == 0){
    //input l1
    Serial.println("Input arm length 1 (whole number)");
    while(l1 == 0){
      if(Serial.available() >0){
        l1= Serial.parseInt();
      }
    }
    Serial.print("l1: ");
    Serial.println(l1);

    //input l2
    Serial.println("Input arm length 2 (whole number)");
    while(l2 == 0){
      if(Serial.available() >0){
        l2= Serial.parseInt();
      }
    }
    Serial.print("l2: ");
    Serial.println(l2);

    // input x
     Serial.println("Input x coordinate (whole number)");
    while(x == 0){
      if(Serial.available() >0){
        x = Serial.parseInt();
      }
    }
    Serial.print("x: ");
    Serial.println(x);

    // input y
     Serial.println("Input y coordinate (whole number)");
    while(y == 0){
      if(Serial.available() >0){
        y= Serial.parseInt();
      }
    }
    Serial.print("y: ");
    Serial.println(y);
    // test to see if it is viable
    int reach = l1 + l2; 
    hyp = sqrt(sq(x) + sq(y));
    Serial.print("reach: ");
    Serial.println(reach);

    Serial.print("hyp: ");
    Serial.println(hyp);

    if (hyp > reach){
     Serial.println("Does Not Work.");
      valid = 0;
      l1 = 0;
  	  l2 = 0;
  	  x = 0;
  	  y = 0;
    } else {
     Serial.println("Coordinates are accepted.");
      valid = 1;
    }
    
  }
  Serial.println("Proceeding with calculations...");
  
  // determine theta2
  float gamma = acos((sq(l1) + sq(l2) - sq(hyp)) / (2*l1*l2));
  theta2Rad = PI - gamma;
  theta2 = (theta2Rad/PI) * 180;
  // determine theta1
  float beta = atan(y/x);
  float alpha = acos((sq(l1) + sq(hyp) - sq(l2)) / (2*l1*hyp));
  theta1Rad = beta - alpha;
  theta1 = (theta1Rad/PI) * 180;
  
  // print theta1 and theta2
  Serial.println("Elbow Down");
  Serial.print("theta1 = ");
  Serial.println(theta1);
  Serial.print("theta2 = ");
  Serial.println(theta2);
  
  Serial.println("Elbow Up");
  theta1Rad = beta + alpha;
  theta1 = (theta1Rad/PI) * 180;
  Serial.print("theta1 = ");
  Serial.println(theta1);
  theta2 = -theta2;
  Serial.print("theta2 = ");
  Serial.println(theta2);
  //finished (setting everything back to 0 resets the cycle.
  l1 = 0;
  l2 = 0;
  x = 0;
  y = 0;
  valid = 0;
}