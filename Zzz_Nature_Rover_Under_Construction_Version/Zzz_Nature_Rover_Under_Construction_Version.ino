#include <SoftwareSerial.h>
#include <Servo.h>
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

  initializeRoboticArm();  //Moves different servo motors to their desired
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



unsigned long preMillis = millis();  //Timer variable for driving.
unsigned long lastPrint = millis();  //Last printing time of debug info on the display.

int actionValue = 150;
int timeThreshold = 100;  //After how much time we will call Stop();

String command = "a";  //Command received via Serial
char Action = 'a';     //Which action we will take. Example: Mode setup
String valueString = "x";
unsigned short carMode = 1;  // 1 - Joystick driving mood
                             // 2- Obstacle avoidance mood



void loop() {
  // glowLightsInPattern1();

  // for(int i = 0; i<4; i++)
  // {
  //   for(int j = 0; j<255; j++)
  //   {
  //     analogWrite(ledLightPins[i], j);
  //     delay(25);
  //   }
  // }

  if (Serial.available()) {
    preMillis = millis();
    command = Serial.readStringUntil('.');
    Action = command[0];  //The type of action the remote wants us to take.
    valueString = command.substring(2, command.length());
    if (Action == 'M') {
      appMessage = valueString;
      appMessagePrinted = 0;
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(0, 0);
      display.print(valueString);
      display.display();
    } else {

      actionValue = valueString.toInt();
      switch (Action)  //Which action we are going to take.
      {
        case 'p':  //Pump functionality.
          {
            switch (actionValue) {
              case 0:
                {
                  turnOffPump();
                  turnOffPumpLaser();
                }
                break;
              case 1:
                {
                  turnOffPump();
                  //First we'll move the wrist motor to rest position for clearing the path of the light and water.
                  armServos[3].write(restPositions[3]);
                  turnOnPumpLaser();
                }
                break;
              case 2:
                {
                  turnOnPump();
                }
                break;
              default: break;
            }
          }
          break;

        case 'f':  //Forward motion of the rover
          if (carMode == 1) {
            goForward(actionValue);
            timeThreshold = 100;
          }
          break;
        case 'b':  //Backward motion of the rover
          {
            if (carMode == 1) {
              goBackward(actionValue);
              timeThreshold = 100;
            }
          }
          break;
        case 'l':  //Left direction
          {
            if (carMode == 1) {
              goLeft(actionValue);  //Turning half at a speed of going.
              timeThreshold = 60;
            }
          }
          break;

        case 'r':  //Right direction
          if (carMode == 1) {
            goRight(actionValue);
            timeThreshold = 60;  //Turning at the half speed of going
          }
          break;

        case 'm':  //Mode setup
          {

            display.clearDisplay();
            if (actionValue == 3)  //the controller wants to set carmode to 3
            {
              initializeSensors();
            } else if (carMode == 3)  //If the actionValue is not 3 and the car was previously set
                                      //to sensor reading mode.
            {
              turnOffSensors();
            }
            if (carMode == 4 && actionValue != 4)  //If the rover was in line following mode but mode is changed then deploy the lfr array.
            {
              //lfrServo.write(lfrArrayRestAngle); ;
              deactivateLineFollower();
            }

            //Changing the car mode.
            carMode = actionValue;
            //Line follower mode
            if (carMode == 4) { activateLineFollower(); }
          }
          break;

        case 'u':
          {
            byte servoIndex = 2;
            if (servoPositions[servoIndex] + actionValue <= maxServoPositions[servoIndex] && servoPositions[servoIndex] + actionValue >= minServoPositions[servoIndex]) {
              servoPositions[servoIndex] += actionValue;
              armServos[servoIndex].write(servoPositions[servoIndex]);
            }
          }
          break;
        case 'v':
          {
            byte servoIndex = 0;
            if (servoPositions[servoIndex] + actionValue <= maxServoPositions[servoIndex] && servoPositions[servoIndex] + actionValue >= minServoPositions[servoIndex]) {
              servoPositions[servoIndex] += actionValue;
              armServos[servoIndex].write(servoPositions[servoIndex]);
              delay(angleChangeDelay);
            }
          }
          break;
        case 'w':  //Third CR servo counting from the base of the arm.
          {
            byte servoIndex = 1;
            if (servoPositions[servoIndex] + actionValue <= maxServoPositions[servoIndex] && servoPositions[servoIndex] + actionValue >= minServoPositions[servoIndex]) {
              servoPositions[servoIndex] += actionValue;
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
        case 'y':  //The wrist of the arm. MG995 servo motor
          {
            byte servoIndex = 3;
            if (servoPositions[servoIndex] + actionValue <= maxServoPositions[servoIndex] && servoPositions[servoIndex] + actionValue >= minServoPositions[servoIndex]) {
              servoPositions[servoIndex] += actionValue;
              armServos[servoIndex].write(servoPositions[servoIndex]);
              // lfrServo.write(servoPositions[servoIndex]);
            }
          }
          break;
        case 'z':  //3D printed gripper uses MG995 gear motor. Will completely open upon receiveing 1.
          {
            byte servoIndex = 4;
            // if(servoPositions[servoIndex] + actionValue <= maxServoPositions[servoIndex] && servoPositions[servoIndex] + actionValue >= minServoPositions[servoIndex])
            //       {
            //         servoPositions[servoIndex]+=actionValue;
            //         armServos[servoIndex].write(servoPositions[servoIndex]);
            //       }
            switch (actionValue)  //the gripper remains completely open when the angle is 60 degree.
            {
              case 1:  //Close the gripper.
                {
                  if (servoPositions[servoIndex] + actionValue <= maxServoPositions[servoIndex] && servoPositions[servoIndex] + actionValue >= minServoPositions[servoIndex]) {
                    servoPositions[servoIndex] += actionValue;
                    armServos[servoIndex].write(servoPositions[servoIndex]);
                  }
                }
                break;
              case -1:  //Open up the gripper completely
                {


                  for (byte i = servoPositions[servoIndex]; i >= minServoPositions[servoIndex]; i--) {
                    armServos[servoIndex].write(i);
                    delay(angleChangeDelay - 10);
                  }
                  servoPositions[servoIndex] = minServoPositions[servoIndex];
                }
            }
          }
          break;

        case 'a':
          {
            switch (actionValue) {
              case 1:  //takeArmtoRestPosition
                {
                  takeArmToRestPosition();
                }
                break;
              case 4:  //takeArmtoDropObjectPosition
                {
                  setArmToDropObject();
                }
                break;
              case 5:  //Change OLED display content.
                {
                  lastPrint = millis() / 100;
                  displayContentIndex = (++displayContentIndex) % displayContentNumber;
                  switch (displayContentIndex) {
                    case 0:
                      {
                        printTitle();
                      }
                      break;
                    case 1:
                      {
                        activateLineFollower();
                      }
                      break;
                    case 2:
                      {
                        deactivateLineFollower();
                      }
                      break;
                    case 5:
                      {
                        display.clearDisplay();
                        display.setTextSize(1);
                        display.setCursor(0, 0);
                        display.print(appMessage);
                      }
                  }
                  default:
                    break;
                }
            }
          }
          break;   //Switch 1
        case 'L':  //Lights functionality.
          {
            byte ledIndex = actionValue / 1000;
            byte brightnessPwm = actionValue % 1000;
            //  if (ledIndex < numberOfLED)  //ledIndex value = 0, 1, 2......numberOfLED-1 indicates to toggle that LED with PWM value.
            // {
            if (patternIndex != 0)  //If any pattern or mode is currently active.
            {
              digitalWrite(sensorBoardPowerPin, LOW);  //Turn of sensor board once we exit automatic brightness mode.
              patternIndex = 0;                        //Disable patterns and toggle particular LED
              for (byte i = 0; i < numberOfLED; i++)   //Turning Off all lights when individual light command is received.
              {
                digitalWrite(ledLightPins[i], LOW);
              }
            }
            digitalWrite(ledLightPins[ledIndex], brightnessPwm);
          }
          break;
        case 'q':
          {
            step = 0;
            patternIndex = actionValue;
            Serial.println(patternIndex);
            if (patternIndex = 1)  //Automatic brightness mode
            {
              digitalWrite(sensorBoardPowerPin, HIGH);  //Turn on sensor board power to receive ldr Reading.
            } else {
              digitalWrite(sensorBoardPowerPin, LOW);  //Turn of sensor board once we exit automatic brightness mode.
            }
          }
          break;

        default:  //"c:val." here c comes as 1,2,3,.... indicating the index of the changed OA settings.
          {
            oaSettingsValue[Action - '0'] = actionValue;
          }
      }
    }
  } else {                                                     //If serial.available() == 0
    if (carMode == 1 && millis() - preMillis > timeThreshold)  //We will stop only when in mode-1 joystick driving mode.
    {
      Stop();
      preMillis = millis();
    }
  }



  if (carMode == 2)  //Whether car is in collission avoidance mode.
  {
    avoidObstacles();
  }

  if (carMode == 3) {
    if (millis() - lastPrint > 3000)  //Sending sensor readings over bluetooth every 3000 millisecond.
    {
      lastPrint = millis();
      Serial.print(sensorReadings());
      Serial.flush();
    };
  }

  if (carMode == 4) {
    //lfrServo.write(lfrArrayDeployAngle); //Takes the Line follower array close to the surface.
    while (Serial.available() == 0)  //LFR stops as soon as some new command comes via the serial monitor.
    {
      followLine();
    }
  }

  if (displayContentIndex != 0)  //Display Printing Mechanisms.
  {
    switch (displayContentIndex) {
      case 1:
        {
          displayLFRreadings();
        }
        break;
      case 2:
        {
          printOAdebugData();
        }
        break;  //OA = obstacle avoidance.
      case 3:
        {
          displayOtherSensorReadings();
        }
        break;
      case 4:
        {
          printRoboticArmDebugData();
        }
        break;
      case 5:
        {
          if (appMessagePrinted == 0) {
            appMessagePrinted = 1;
            display.clearDisplay();
            display.setTextSize(1);
            display.setCursor(0, 0);
            display.print(valueString);
            display.display();
          }
        }
      default: break;
    }
  }
  glowLightsInAutoMode(); 
  glowLightsInPattern1(); 
  glowLightsInPattern2();

  // if (patternIndex != 0)  //We have some pattern active for lights.
  // {
  //   switch (patternIndex) {
  //     case 1:
  //       {
  //         glowLightsInAutoMode();
  //       }
  //       break;
  //     case 2:
  //       {
  //         glowLightsInPattern1();
  //       }
  //       break;
  //     case 3:
  //       {
  //         glowLightsInPattern2();
  //       }
  //     default: break;
  //   }

  // if (patternIndex == 1) {
  //   //glowLightsInAutoMode();

  //   if (analogRead(ldrPin) < ldrThresholdValue && digitalRead(ledLightPins[0]) == LOW) {
  //     for (byte i = 0; i < 4; i++)  //LED brightness will be based on surrounding light intensities.
  //     {
  //       digitalWrite(ledLightPins[i], HIGH);
  //     }
  //   } else if (analogRead(ldrPin) > ldrThresholdValue && digitalRead(ledLightPins[0]) == HIGH) {
  //     for (byte i = 0; i < 4; i++)  //LED brightness will be based on surrounding light intensities.
  //     {
  //       digitalWrite(ledLightPins[i], LOW);
  //     }
  //   }
  // }  //There are problems inside those functions. The if statement is turning Okay but they are not glowing from inside.
  // if (patternIndex == 2) {
  //    //glowLightsInPattern1(); 
  //     if (millis() - ledTimer > 100) {  // Update pattern every 100ms
  //   ledTimer = millis();

  //   // Reset all LEDs to LOW (OFF)
  //   for (int i = 0; i < numberOfLED; i++) {
  //     digitalWrite(ledLightPins[i], LOW);
  //   }

  //   // Define the pattern
  //   switch (step) {
  //     case 0:
  //       for (int i = 0; i < numberOfLED; i++) {
  //         digitalWrite(ledLightPins[i], HIGH);  // Turn on all LEDs
  //       }
  //       break;
  //     case 1:
  //       for (int i = 0; i < numberOfLED; i += 2) {
  //         digitalWrite(ledLightPins[i], HIGH);  // Turn on even-index LEDs
  //       }
  //       break;
  //     case 2:
  //       for (int i = 1; i < numberOfLED; i += 2) {
  //         digitalWrite(ledLightPins[i], HIGH);  // Turn on odd-index LEDs
  //       }
  //       break;
  //     case 3:
  //       digitalWrite(ledLightPins[0], HIGH);
  //       digitalWrite(ledLightPins[5], HIGH);  // Turn on first and last LEDs
  //       break;
  //     case 4:
  //       for (int i = 0; i < numberOfLED; i++) {
  //         if (i % 3 == 0) {
  //           digitalWrite(ledLightPins[i], HIGH);  // Turn on every third LED
  //         }
  //       }
  //       break;
  //     case 5:
  //       for (int i = 0; i < numberOfLED; i++) {
  //         digitalWrite(ledLightPins[i], HIGH);  // Flash all LEDs quickly
  //         delay(50);
  //         digitalWrite(ledLightPins[i], LOW);
  //       }
  //       delay(50);
  //       break;
  //     default:
  //       step = 0;  // Reset step if it exceeds the number of patterns
  //       break;
  //   }

  //   // Move to the next step in the pattern
  //   step++;
  //   if (step > 5) {
  //     step = 0;  // Reset step to 0 if it exceeds the number of steps
  //   }
  // }
  //    }
  // if (patternIndex == 3) { 
  //  // glowLightsInPattern2(); 
  //   if (millis() - ledTimer > 100) {
  //   ledTimer = millis();
  //   step = (++step) % 6;

  //   for (int i = 0; i < 6; i++) {
  //     digitalWrite(ledLightPins[i], LOW);
  //   }

  //   switch (step) {
  //     case 0:
  //       digitalWrite(ledLightPins[0], HIGH);  // Front left LED on
  //       digitalWrite(ledLightPins[5], HIGH);  // Arm LED on
  //       break;
  //     case 1:
  //       digitalWrite(ledLightPins[1], HIGH);  // Front right LED on
  //       digitalWrite(ledLightPins[4], HIGH);  // Water tank LED on
  //       break;
  //     case 2:
  //       digitalWrite(ledLightPins[2], HIGH);  // Back left LED on
  //       break;
  //     case 3:
  //       digitalWrite(ledLightPins[3], HIGH);  // Back right LED on
  //       break;
  //     case 4:
  //       digitalWrite(ledLightPins[0], HIGH);  // Front left LED on
  //       digitalWrite(ledLightPins[3], HIGH);  // Back right LED on
  //       break;
  //     case 5:
  //       digitalWrite(ledLightPins[1], HIGH);  // Front right LED on
  //       digitalWrite(ledLightPins[2], HIGH);  // Back left LED on
  //       break;
  //   }
  // }
  //   }


}  //Void loop


//Following Functions are used to debugprint Different datas on the OLED display.

void displayOtherSensorReadings() {
  if (millis() - lastPrint > 300)  //Print every 300 millisecond.
  {
    lastPrint = millis();
    display.clearDisplay();
    display.setTextSize(1);
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

void printOAdebugData() {

  if (millis() - lastPrint > 200)  //Print every 200 millisecond.
  {
    lastPrint = millis();

    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
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

void displayLFRreadings() {
  if (millis() - lastPrint > 500) {
    lastPrint = millis();

    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
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

void printRoboticArmDebugData() {
  if (millis() - lastPrint > 500) {
    lastPrint = millis();
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);

    for (int i = 0; i < servoNumber; i++) {

      display.print("Servo");
      display.print(i);
      display.print(": ");
      display.println(servoPositions[i]);
    }
    display.display();
  }
}
