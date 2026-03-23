#include<SoftwareSerial.h> 
#include<Servo.h>
#include "WheelMotors.h"
#include "RoboticArm.h"
#include "ObstacleAvoidance.h"
#include "Line_follower.h"
#include "Sensors.h"
#include "DisplayMechanism.h"  
#include "Pump.h"


int lastReading = millis()/1000; //Last reading timestamp in second. 
byte readingDelays = 3; //Delay between successive readings in second. 





void setup() {
   
 initializeRoboticArm(); //Moves different servo motors to their desired
                           //initial angle. 
  
  Serial.begin(9600); 
  setupPumpPins(); 
  setUpLineFollowerPins();
 

  setUpMotorPins(); 
  setUpSensorPins(); 

 
  

 
  delay(100); 

 

  /*Setting up sensors*/




  setUpObstacleAvoidancePins(); 
  //Line follower IR channels


 // setUpLineFollowerPins(); 

 //Serial.println("Setup done!"); 

    initializeOLEDDisplay(); 
 
}


unsigned long preMillis = millis(); 

int actionValue = 150; 
int timeThreshold = 100; //After how much time we will call Stop(); 


String command = "a";   //Command received via Serial
char Action = 'a'; //Which action we will take. Example: Mode setup
String speedString = "x"; 
unsigned short carMode = 1; // 1 - Joystick driving mood
                            // 2- Obstacle avoidance mood


 
void loop()
{
 
           if (Serial.available())
           {
                command = Serial.readStringUntil('.');  
                Action = command[0]; //The type of action the remote wants us to take. 
                speedString = command.substring(2, command.length()); 
                actionValue = speedString.toInt();   
                preMillis = millis(); 
              //  Serial.println("Recieved command!"); 
        
                        switch(Action) //Which action we are going to take. 
                        {
                              case 'p':
                              {
                                if(actionValue==1) { turnOnPump(); }
                                else if(actionValue==0) { turnOffPump();   }
                              }
                              case 'f': 
                              if(carMode==1)
                              { 
                                     goForward(actionValue); 
                                     timeThreshold = 100; 
                              }
                              break; 
                              
                              case 'b': 
                              if(carMode==1){
                              goBackward(actionValue); 
                              timeThreshold = 100; 
                              }
                              break; 
                              case 'l': //Left direction
                              if(carMode==1){
                              goLeft(actionValue);  //Turning half at a speed of going. 
                              timeThreshold = 60; 
                              }
                              break; 
                              
                              case 'r': //Right direction
                              if(carMode==1){
                              goRight(actionValue); 
                              timeThreshold = 60;   //Turning at the half speed of going
                              }
                              break; 
                      
                              case 'm': //Mode setup 
                              {

                                display.clearDisplay(); 
                                if(actionValue==3)  //the controller wants to set carmode to 3
                                {   
                                   initializeSensors(); 
                                }
                                else if(carMode==3) //If the actionValue is not 3 and the car was previously set
                                                    //to sensor reading mode.  
                                {
                                    turnOffSensors(); 
                                }
                                if(carMode==4 && actionValue!=4) //If the rover was in line following mode but mode is changed then deploy the lfr array. 
                                {
                                  lfrServo.write(lfrArrayRestAngle); ;
                                }
                                //Changing the car mode. 
                                carMode = actionValue; 
                              }
                              break; 
                      
                              case 'u': //The base continuous rotation servo of the arm
                              {
                                   if(actionValue==1)
                                    {     
                                    armServo0.write(CRSspeed+90);       
                                    }  //moving in the forward direction. 
                                    else 
                                    { 
                                    armServo0.write(90-CRSspeed); 
                                    }  //moving in the backward direction
                                    delay(CRSruntime);   //for a short time. 
                                    armServo0.write(90); //then stopping the motor from rotating. 
                                      
                                        
                                      

                              }
                              break; 
                      
                              case 'v': //The left and right CSR from the base of the arm. 
                              {
                                  // if(abs(actionValue) ==1 && anglePairIndex+actionValue>=0 && anglePairIndex+actionValue <= 176)
                                  // {
                                  //   anglePairIndex+=actionValue; 
                                  //   armServo2Left.write(leftAngles[anglePairIndex]); 
                                  //   armServo2Right.write(rightAngles[anglePairIndex]); 
                                  //  delay(10);  
                                  // }  

                                  if(servoPositions[1] + actionValue <= maxServoPositions[1] && servoPositions[1] + actionValue >= minServoPositions[1])
                                        {
                                          servoPositions[1]+=actionValue; 
                                          armServo1.write(servoPositions[1]); 
                                          delay(shoulderServoAngleChangeDelay); 
                                        }       
                              }
                              break; 
                      
                              case 'w': //Third CR servo counting from the base of the arm. 
                              {

                               if(abs(actionValue) ==1 && anglePairIndex+actionValue>=0 && anglePairIndex+actionValue <= 176)
                                  {
                                    anglePairIndex+=actionValue; 
                                    armServo2Left.write(leftAngles[anglePairIndex]); 
                                    armServo2Right.write(rightAngles[anglePairIndex]); 
                                   delay(10);  
                                  }     

                              //  if(actionValue==1){     armServo4.write(CRSspeed+90);       }  //moving in the forward direction. 
                              //  else { armServo4.write(90-CRSspeed); }  //moving in the backward direction
                              //  delay(CRSruntime);   //for a short time. 
                              //  armServo4.write(90); //then stopping the motor from rotating.
                                
                              }
                              break; 
      
                              case 'y': //The wrist of the arm. Mini metal gear motor is used.  
                              {
                                // moveWrist(actionValue); 
                                if(servoPositions[3] + actionValue <= maxServoPositions[3] && servoPositions[3] + actionValue >= minServoPositions[3])
                                        {
                                          servoPositions[3]+=actionValue; 
                                          armServo3.write(servoPositions[3]); 
                                          //delay(shoulderServoAngleChangeDelay); 
                                        }   

                              }
                              break;
                      
                               case 'z': //The gripper mechanism is implemented using gear motor. 
                              {
                                    //  moveGripper(actionValue); 
                                    if(servoPositions[4] + actionValue <= maxServoPositions[4] && servoPositions[4] + actionValue >= minServoPositions[4])
                                        {
                                          servoPositions[4]+=actionValue; 
                                          armServo4.write(servoPositions[4]); 
                                         // delay(shoulderServoAngleChangeDelay); 
                                        }   
                              }
                              break;
                              
                               default: //"c:val." here c comes as 1,2,3,.... indicating the index of the changed OA settings. 
                               {
                                   oaSettingsValue[Action - '0'] = actionValue; 
                               }     
                        } 
           }
           else 
           {
                        if(carMode==1 && millis() - preMillis > timeThreshold) //We will stop only when in mode-1 joystick driving mode. 
                        {
                          Stop(); 
                          preMillis = millis(); 
                        }
           }

            if(carMode==2) //Whether car is in collission avoidance mode. 
            {
                         avoidObstacles();
                      //  display.clearDisplay(); 

                      //                       display.setCursor(0, 0);
                      //   display.print("Front: ");
                      //   display.println(frontDistance());
                      //   display.print("Back ");
                      //   display.println(backDistance());
                      //   display.print("Left ");
                      //   display.println(leftDistance());
                      //   display.print("Right ");
                      //   display.println(rightDistance());
                      //   display.display();
                      //   delay(400); 

            }

            if(carMode==3)
            {
                if(millis()/1000 - lastReading > readingDelays)
                 {
                 lastReading = millis()/1000; 
                 Serial.print(sensorReadings()); 
                 Serial.flush(); 
                 }; 
            }
            if(carMode==4)
            {
              display.clearDisplay(); 
              lfrServo.write(lfrArrayDeployAngle); //Takes the Line follower array close to the surface. 
              while(Serial.available()==0) //LFR starts as soon as some new command comes via the serial monitor. 
              {
              followLine(); 

                
            
    //          displayLFRreadings();

            //  display.clearDisplay(); 
            //   display.setCursor(0, 0); 
            //   display.println(rightIRvalue); 
            //   display.println(middleIRvalue); 
            //   display.println(leftIRvalue); 
            //   display.display(); 
            //   delay(500); 
              
              
              }
             
            }

            
   
    
}


