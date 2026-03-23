#include<SoftwareSerial.h> 
#include<Servo.h>
#include "WheelMotors.h"
#include "RoboticArm.h"
#include "ObstacleAvoidance.h"
#include "Line_follower.h"
//#include "Sensors.h"


int lastReading = millis()/1000; //Last reading timestamp in second. 
byte readingDelays = 3; //Delay between successive readings in second. 


void setup() {
  Serial.begin(9600); 

 // setUpMotorPins(); 
  //Declaring 4 wheel's motor's common enable pin and setting it to 0 (In range 0 to 255)
   pinMode(rightWheelEnable, OUTPUT);
   pinMode(leftWheelEnable, OUTPUT); 
   pinMode(in1, OUTPUT); 
   pinMode(in2, OUTPUT); 
   pinMode(in3, OUTPUT); 
   pinMode(in4, OUTPUT); 

  Stop(); //Setting the enable pins to 0 for all the wheels. 
  //setUpSensorPins(); 

 //PWM pins in arduino Uno:  3, 5, 6, 9, 10, 11
  //Handling the servo motors
  sensorServo.attach(SensorServoPin); 
  sensorServo.write(90); 
  armServo1.attach(9); 
  armServo2Left.attach(10); 
  armServo2Right.attach(11); 
 // armServo3.attach(5); 
  armServo4.attach(6); //6th port of the servo power module. 
 // armServo5.attach(7); 
  

 // initializeRoboticArm(); //Moves different servo motors to their desired
                           //initial angle. 
  delay(100); 

 

  /*Setting up sensors*/




  //  setUpObstacleAvoidancePins(); 
  //Line follower IR channels


 // setUpLineFollowerPins(); 

 //Serial.println("Setup done!"); 
 
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
                                if(actionValue==3)  //the controller wants to set carmode to 3
                                {   
                                  // initializeSensors(); 
                                }
                                else if(carMode==3) //If the actionValue is not 3 and the car was previously set
                                                    //to sensor reading mode.  
                                {
                                    //turnOffSensors(); 
                                }
                                //Changing the car mode. 
                                carMode = actionValue; 
                              }
                              break; 
                      
                              case 'u': //The base continuous rotation servo of the arm
                              {
                               if(actionValue==1){     armServo1.write(CRSspeed+90);       }  //moving in the forward direction. 
                               else { armServo1.write(90-CRSspeed); }  //moving in the backward direction
                               delay(CRSruntime);   //for a short time. 
                               armServo1.write(90); //then stopping the motor from rotating. 
                              }
                              break; 
                      
                              case 'v': //The left and right CSR from the base of the arm. 
                              {
                                  if(abs(actionValue) ==1 && anglePairIndex+actionValue>=0 && anglePairIndex+actionValue <= 176)
                                  {
                                    anglePairIndex+=actionValue; 
                                    armServo2Left.write(leftAngles[anglePairIndex]); 
                                    armServo2Right.write(rightAngles[anglePairIndex]); 
                                   delay(10);  
                                  }         
                              }
                              break; 
                      
                              case 'w': //Third CR servo counting from the base of the arm. 
                              {
                               if(actionValue==1){     armServo4.write(CRSspeed+90);       }  //moving in the forward direction. 
                               else { armServo4.write(90-CRSspeed); }  //moving in the backward direction
                               delay(CRSruntime);   //for a short time. 
                               armServo4.write(90); //then stopping the motor from rotating.
                                
                              }
                              break; 
      
                              case 'y': //The wrist of the arm. Mini metal gear motor is used.  
                              {
                                 moveWrist(actionValue); 
                              }
                              break;
                      
                               case 'z': //The gripper mechanism is implemented using gear motor. 
                              {
                                 moveGripper(actionValue); 
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
            }

            if(carMode==3)
            {
                if(millis()/1000 - lastReading > readingDelays)
                 {
                //  lastReading = millis()/1000; 
                //  Serial.print(sensorReadings()); 
                //  Serial.flush(); 
                 }; 
            }
            if(carMode==4)
            {
              while(Serial.available()==0) //LFR starts as soon as some new command comes via the serial monitor. 
              {
                followLine(); 
              }
              /*
              Serial.print(analogRead(A5)); 
              Serial.print("   "); 
              Serial.print(analogRead(A4)); 
              Serial.print("   "); 
              Serial.println(analogRead(A3)); 
              delay(500); 
              */
            }

            
   
    
}


