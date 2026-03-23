//Common enable pin for Enable1 and Enable2;
//Speed of 2 right wheels and 2 left wheels is controlled by this common pin. 
#define rightWheelEnable 2
#define leftWheelEnable 3

//Pin declaration for left motor. 
#define in1   22
#define in2  23

//Pin declaration for right motor. 
#define in3  24
#define in4  25





void Stop()
{
  analogWrite(rightWheelEnable, 0); 
  analogWrite(leftWheelEnable, 0); 
}

void rightForward(int actionValue) //Sets the right motor to move forward
{
  analogWrite(leftWheelEnable, actionValue); 
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW); 
}

void rightBackward(int actionValue)
{
   analogWrite(leftWheelEnable, actionValue);  
  digitalWrite(in3, LOW); 
  digitalWrite(in4, HIGH); 
}

void leftForward(int actionValue)
{
 analogWrite(rightWheelEnable, actionValue); 
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW); 
  
}

void leftBackward(int actionValue)
{
   analogWrite(rightWheelEnable, actionValue);  
  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH); 
}


void goForward(int actionValue)
{
 rightForward(actionValue); 
 leftForward(actionValue); 
}

void goBackward(int actionValue)
{
  rightBackward(actionValue); 
  leftBackward(actionValue); 
}

void goLeft(int actionValue)
{
 rightForward(actionValue); 
 leftBackward(actionValue); 
}


void goRight(int actionValue)
{
    left  Forward(actionValue); 
    rightBackward(actionValue); 
}


setUpMotorPins()
{
   //Declaring 4 wheel's motor's common enable pin and setting it to 0 (In range 0 to 255)
  
   pinMode(rightWheelEnable, OUTPUT);
   pinMode(leftWheelEnable, OUTPUT); 
   pinMode(in1, OUTPUT); 
   pinMode(in2, OUTPUT); 
   pinMode(in3, OUTPUT); 
   pinMode(in4, OUTPUT); 

   

  Stop(); //Setting the enable pins to 0 for all the wheels. 
  //setUpSensorPins(); 


}
