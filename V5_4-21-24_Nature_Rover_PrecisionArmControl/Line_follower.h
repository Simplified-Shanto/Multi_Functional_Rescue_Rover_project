//#include"ObstacleAvoidance.h"
//#include "DisplayMechanism.h"


Servo lfrServo; 

#define lfrArrayRestAngle 75
#define lfrArrayDeployAngle 67
#define lfrServoPin 7
#define leftIRpin    A10
#define middleIRpin A9
#define rightIRpin   A8 
#define leftIRvalue analogRead(leftIRpin)
#define middleIRvalue analogRead(middleIRpin)
#define rightIRvalue analogRead(rightIRpin)

#define leftThreshold    40
#define middleThreshold 30
#define rightThreshold  25

 setUpLineFollowerPins()
  {
    lfrServo.attach(lfrServoPin); 
    lfrServo.write(lfrArrayRestAngle);  //The servo holting servo shaft remains up the ground when set to this angle. 
  }
 


/*
                  Black                     Threshold                          White
Left           70 - 75 -  80                    100                        110 - 125 -  140
Middle         80 - 85 -  90                    103                        110 - 120 -  130
Right          65   70 -  75                    85                         90  - 100 -  105                        


*/


/*
                  Black                     Threshold                          White
Left                                             20
Middle         80 - 85 -  90                    20                       110 - 120 -  130
Right          65   70 -  75                    18                           90  - 100 -  105                        


*/



//Black value range 
//White value range

#define forwardPwm 80
#define leftRightPwm 150


// void displayLFRreadings()
//               {
//                   display.clearDisplay(); 
//               display.setCursor(0, 0); 
//               display.println(rightIRvalue); 
//               display.println(middleIRvalue); 
//               display.println(leftIRvalue); 
//               display.display(); 
//               delay(500); 
//               }


//We'll try while loop instead of if else. 

/*
if all the sensor faces white then the car will not move and 
indicate it with the sensor servo moving a bit. 

*/
void followLine()
{
  
   if(leftIRvalue < leftThreshold)
      {
          while(middleIRvalue > middleThreshold) //Once the left sensor is on the black line, move until the car is aligned perfectly. 
          {
          //  goLeft(leftRightPwm);
          goRight(leftRightPwm); 
          }
      // delay(wait); 
      }
      else if(rightIRvalue < rightThreshold)
      {
          while(middleIRvalue > middleThreshold) //Once the right sensor is on the black line, move until the car is aligned perfectly. 
          {
         // goRight(leftRightPwm);
         goLeft(leftRightPwm);
          }
      // delay(wait); 
      }
      else
      {
          goForward(forwardPwm); 
      }

}
