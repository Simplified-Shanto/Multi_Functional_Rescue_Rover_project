//#include"ObstacleAvoidance.h"
//#include "DisplayMechanism.h"


Servo lfrServo; 

#define lfrArrayRestAngle   98   //Initially 75
#define lfrArrayDeployAngle  52         //67
#define lfrServoAngleChangeDelay 45
//byte currentAngle = lfrArrayRestAngle; 
#define lfrServoPin 7




#define IRarrayPowerPin     35
                                       //Position     // White  value   Threshold value               Black value. 
#define IR1reading  analogRead(A8)   //Left most            900 - 920                                       920 - 930
          #define IR3reading  analogRead(A9)    //                 910 - 920                   817                 700 - 730
#define IR4reading  analogRead(A10)    //                915-920                                         910 - 925 
#define IR5reading  analogRead(A11)   //                 905-915                                         870 - 890
          #define IR6reading  analogRead(A12)   //                 900-910                     857                 800 - 820
#define IR7reading  analogRead(A13)   //                 900-905                                         880- 895
#define IR8reading  analogRead(A14)   //                 Above 900                                       Below 750
          #define IR10reading analogRead(A15)    //Right most     Above 900                    775                   Below 650  



#define leftIRvalue analogRead(A9)
#define middleIRvalue analogRead(A12)
#define rightIRvalue analogRead(A15)

#define leftThreshold     850     //817
#define middleThreshold  750
#define rightThreshold    720   //775

void setUpLineFollowerPins()
  {
     pinMode(IRarrayPowerPin, OUTPUT); 
    digitalWrite(IRarrayPowerPin, LOW); 
    lfrServo.attach(lfrServoPin); 
     for(byte i = (lfrArrayDeployAngle + lfrArrayRestAngle)/2; i <= lfrArrayRestAngle; i++ )
  {
     lfrServo.write(i);  //The servo holting servo shaft remains up the ground when set to this angle.
     delay(lfrServoAngleChangeDelay);  
  }
    //lfrServo.write(lfrArrayRestAngle);  //The servo holting servo shaft remains up the ground when set to this angle. 
   
  }


void activateLineFollower()
{
  digitalWrite(IRarrayPowerPin, HIGH); 
  for(byte i = lfrArrayRestAngle; i>= lfrArrayDeployAngle; i-- )
  {
     lfrServo.write(i);  //The servo holting servo shaft remains up the ground when set to this angle.
     delay(lfrServoAngleChangeDelay);  
  }
   
    
}

void deactivateLineFollower()
{
    digitalWrite(IRarrayPowerPin, LOW); 
     for(byte i = lfrArrayDeployAngle; i<= lfrArrayRestAngle; i++ )
  {
     lfrServo.write(i);  //The servo holting servo shaft remains up the ground when set to this angle.
     delay(lfrServoAngleChangeDelay);  
  }
}
 





//Black value range 
//White value range

#define forwardPwm 60
#define leftRightPwm 140 //150



void followLine()
{
   
   if(leftIRvalue < leftThreshold)
      {
          while( middleIRvalue > middleThreshold) //Once the left sensor is on the black line, move until the car is aligned perfectly. 
          {
          goRight(leftRightPwm); 
          }
      }
      else if(rightIRvalue < rightThreshold)
      {
          while(middleIRvalue > middleThreshold) //Once the right sensor is on the black line, move until the car is aligned perfectly. 
          {
         goLeft(leftRightPwm); 
          }
      }
      else
      {
          goForward(forwardPwm); 
      }
}




//We'll try while loop instead of if else. 

/*
if all the sensor faces white then the car will not move and 
indicate it with the sensor servo moving a bit. 

*/