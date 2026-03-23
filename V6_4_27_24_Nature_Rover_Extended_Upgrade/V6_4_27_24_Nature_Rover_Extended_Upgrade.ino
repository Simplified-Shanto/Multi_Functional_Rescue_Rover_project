#include<SoftwareSerial.h> 
#include<Servo.h>
#include "WheelMotors.h"
#include "RoboticArm.h"
#include "ObstacleAvoidance.h"
#include "Line_follower.h"
#include "Sensors.h"
#include "DisplayMechanism.h"  
#include "Pump.h"

void printOAdebugData(); 
void printRoboticArmDebugData(); 



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
  initializeOLEDDisplay(); 
  initializeLights(); 
}


unsigned long preMillis = millis(); //Timer variable for driving. 
unsigned long lastPrint = millis(); //Last printing time of debug info on the display. 
//int lastReading = millis()/100; //Common timer variable.  


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
                              case 'p': //Pump functionality. 
                              { 
                                switch(actionValue)
                                {
                                    case 0: { turnOffPump(); turnOffPumpLaser(); } break; 
                                    case 1: 
                                    { 
                                      turnOffPump();
                                      //First we'll move the wrist motor to rest position for clearing the path of the light and water. 
                                      armServos[3].write(restPositions[3]); 
                                      turnOnPumpLaser(); 

                                    } 
                                    break; 
                                    case 2: { turnOnPump();      } break; 
                                    default: break; 
                                }
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
                                  //lfrServo.write(lfrArrayRestAngle); ;
                                  deactivateLineFollower(); 
                                }
            
                                //Changing the car mode. 
                                carMode = actionValue; 
                                 //Line follower mode
                                if(carMode==4) { activateLineFollower();  }
                               
                                
                              }
                              break; 
                      
                              case 'u': 
                              {  
                                byte servoIndex = 2; 
                                  if(servoPositions[servoIndex] + actionValue <= maxServoPositions[servoIndex] && servoPositions[servoIndex] + actionValue >= minServoPositions[servoIndex])
                                        {
                                          servoPositions[servoIndex]+=actionValue; 
                                          armServos[servoIndex].write(servoPositions[servoIndex]); 
                                        }        
                              }
                              break; 
                              case 'v': 
                              {
                                  byte servoIndex = 0; 
                                  if(servoPositions[servoIndex] + actionValue <= maxServoPositions[servoIndex] && servoPositions[servoIndex] + actionValue >= minServoPositions[servoIndex])
                                        {
                                          servoPositions[servoIndex]+=actionValue; 
                                          armServos[servoIndex].write(servoPositions[servoIndex]); 
                                          delay(angleChangeDelay); 
                                        }      
                              }
                              break; 
                              case 'w': //Third CR servo counting from the base of the arm. 
                              {
                                  byte servoIndex = 1; 
                                  if(servoPositions[servoIndex] + actionValue <= maxServoPositions[servoIndex] && servoPositions[servoIndex] + actionValue >= minServoPositions[servoIndex])
                                        {
                                          servoPositions[servoIndex]+=actionValue; 
                                          armServos[servoIndex].write(servoPositions[servoIndex]); 
                                          elbowServoLeft.write(leftAngles[servoPositions[servoIndex]]); 
                                          elbowServoRight.write(rightAngles[servoPositions[servoIndex]]); 
                                          delay(10); 
                                        }   

                              //  if(abs(actionValue) ==1 && anglePairIndex+actionValue>=0 && anglePairIndex+actionValue <= 176)
                              //     {
                              //       anglePairIndex+=actionValue; 
                              //       elbowServoLeft.write(leftAngles[anglePairIndex]); 
                              //       elbowServoRight.write(rightAngles[anglePairIndex]); 
                              //      delay(10);  
                              //     }         
                              }
                              break; 
                              case 'y': //The wrist of the arm. MG995 servo motor 
                              {
                                byte servoIndex = 3; 
                                  if(servoPositions[servoIndex] + actionValue <= maxServoPositions[servoIndex] && servoPositions[servoIndex] + actionValue >= minServoPositions[servoIndex])
                                        {
                                          servoPositions[servoIndex]+=actionValue; 
                                          armServos[servoIndex].write(servoPositions[servoIndex]); 
                                         // lfrServo.write(servoPositions[servoIndex]);  
                                        }   
                              }
                              break;
                               case 'z': //3D printed gripper uses MG995 gear motor. Will completely open upon receiveing 1. 
                              {
                                     byte servoIndex = 4; 
                                  // if(servoPositions[servoIndex] + actionValue <= maxServoPositions[servoIndex] && servoPositions[servoIndex] + actionValue >= minServoPositions[servoIndex])
                                  //       {
                                  //         servoPositions[servoIndex]+=actionValue; 
                                  //         armServos[servoIndex].write(servoPositions[servoIndex]);  
                                  //       }  
                                  switch(actionValue)  //the gripper remains completely open when the angle is 60 degree. 
                                  {
                                    case 1:  //Close the gripper. 
                                    {
                                        if(servoPositions[servoIndex] + actionValue <= maxServoPositions[servoIndex] && servoPositions[servoIndex] + actionValue >= minServoPositions[servoIndex])
                                        {
                                          servoPositions[servoIndex]+=actionValue; 
                                          armServos[servoIndex].write(servoPositions[servoIndex]); 

                                        } 
                                    }
                                    break; 
                                    case -1: //Open up the gripper completely
                                    {
                                       

                                         for(byte i = servoPositions[servoIndex]; i >= minServoPositions[servoIndex]; i--)
                                        {
                                          armServos[servoIndex].write(i); 
                                          delay(angleChangeDelay-10); 
                                        }
                                        servoPositions[servoIndex] = minServoPositions[servoIndex];
 
                                    }
                                  } 
                              }
                              break;

                              case 'a':
                              {
                                switch(actionValue)
                                {
                                  case 1:  {      takeArmToRestPosition();     }   break;
                                  case 4:  {       setArmToDropObject();       }   break; 
                                  case 5:  //Change OLED display content. 
                                  {
                                    lastPrint = millis()/100; 
                                    displayContentIndex = (++displayContentIndex)%displayContentNumber; 
                                    if(displayContentIndex==0)
                                    { printTitle(); }
                                    if(displayContentIndex==1)
                                    {
                                      activateLineFollower();  //Sensor power is turned on and the servo takes it closer to the mat. 
                                    } 
                                    else { deactivateLineFollower(); }
                                  }
                                  default: 
                                  break; 
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
            }

            if(carMode==3)
            {
                if(millis() - lastPrint > 3000)  //Sending sensor readings over bluetooth every 3000 millisecond. 
                 {
                 lastPrint = millis(); 
                 Serial.print(sensorReadings()); 
                 Serial.flush(); 
                 }; 
            }

            if(carMode==4)
            {
                //lfrServo.write(lfrArrayDeployAngle); //Takes the Line follower array close to the surface. 
                while(Serial.available()==0) //LFR stops as soon as some new command comes via the serial monitor. 
                {
                followLine();          
                }
            }

            if(displayContentIndex!=0)
            {
                switch(displayContentIndex)
                {
                  case 1: { displayLFRreadings();     } break; 
                  case 2: { printOAdebugData();   } break;   //OA = obstacle avoidance. 
                  case 3: { displayOtherSensorReadings(); } break; 
                  case 4: { printRoboticArmDebugData();  } break; 
                  default: break; 
                }
            }
            
           
   
}


//Following Functions are used to debugprint Different datas on the OLED display. 

void displayOtherSensorReadings()
{
  if(millis() - lastPrint > 300) //Print every 300 millisecond. 
  {
    lastPrint = millis(); 
    display.clearDisplay(); 
    display.setCursor(0, 0);

    display.print("VS analogRead: "); 
    display.println(analogRead(voltageSensorPin)); 
    display.print("Voltage: "); 
    display.println(voltageReading()); 
    display.print("V"); 

    display.print("CS analogRead: "); 
    display.println(analogRead(voltageSensorPin)); 
    display.print("Current: ");
    display.println(currentReading());
    maxCurrent = max(maxCurrent, currentReading()); 
    display.print("Max Current: ");
    display.println(maxCurrent);
    display.display();  
  }
}

void printOAdebugData()
{

   if(millis() - lastPrint > 200) //Print every 200 millisecond. 
  {
    lastPrint = millis(); 

    display.clearDisplay(); 
    display.setCursor(0, 0);
    display.print("Front: ");
    display.println(frontDistance());
    display.print("Back:        ");
    display.println(backDistance());
    display.print("Left: ");
    display.println(leftDistance());
    display.print("Right:        ");
    display.println(rightDistance());
    display.display();
  }
    
}



void displayLFRreadings()
{
  if(millis() - lastPrint > 500)
  {    
      lastPrint = millis(); 

      display.clearDisplay(); 
      display.setCursor(0, 0); 
      display.print("IR1= "); 
      display.println(IR1reading);
      display.print("IR3=       "); 
      display.println(IR3reading); 
      display.print("IR4= ");
      display.println(IR4reading);
      display.print("IR5=       ");
      display.println(IR5reading);
      display.print("IR6= ");
      display.println(IR6reading);
      display.print("IR7=       ");
      display.println(IR7reading);
      display.print("IR8= ");
      display.println(IR8reading);
      display.print("IR10=      ");
      display.println(IR10reading);

      display.display(); 
  }
}



void printRoboticArmDebugData()
{
    if(millis() - lastPrint > 500)
    {    
        lastPrint = millis(); 
        display.clearDisplay();   
        display.setCursor(0, 0);

        for(int i = 0; i<servoNumber; i++)
        {
        
          display.print("Servo"); 
          display.print(i); 
          display.print(": "); 
          display.println(servoPositions[i]); 
        }
         display.display(); 
    }
}


