//Servo sensorServo;  //Servomotor carrying the sonar sensor.
//#define SensorServoPin 12 //Pin for sensorServo

#define frontSonarTrig  22
#define frontSonarEcho  23
#define backSonarTrig   24
#define backSonarEcho   25
#define leftSonarTrig   26
#define leftSonarEcho   27
#define rightSonarTrig  28
#define rightSonarEcho  29


int frontDistance(); 
int backDistance(); 
int leftDistance(); 
int rightDistance(); 

// //unsigned short middleDistance = 0; 
// unsigned short rightDistance = 0; 
// unsigned short leftDistance = 0; 
unsigned short oaSpeed = 90; //PWM value while driving in obstacle avoidance (OA) mode.
  
void setUpObstacleAvoidancePins()
{
 pinMode(frontSonarTrig, OUTPUT); 
 pinMode(backSonarTrig,  OUTPUT); 
 pinMode(leftSonarTrig, OUTPUT); 
 pinMode(rightSonarTrig, OUTPUT); 

 pinMode(frontSonarEcho, INPUT); 
 pinMode(backSonarEcho, INPUT); 
 pinMode(leftSonarEcho, INPUT); 
 pinMode(rightSonarEcho, INPUT); 
}

//#define successiveAngleWriteDelay 5 //The delay between changing each degree angle of the ultrasonic sensor. 

//When the car was initially built it was being controlled by 
//another arduino (Nano) via a joystick over bluetooth. 
//These settings helped to finetune different parameters realtime without uploading the code. 
//Though the current version expects a mobile app to send commands; 
//but this setting was pretty meaningful for the Arduino Nano controller. 

#define noSettings 5               //Number of Settings

        //   String oaSettings[noSettings] =  {"OA BF PWM", "OA Backward time", "OA LR PWM" , "OA LR time", "Safe Distance"};   //The obstacle avoidance mode settings and values. 
 unsigned short  oaSettingsValue[noSettings] = {90 ,         150,                    230,           150,             15 };     //Time in millisecond, Safe distance is in inch. 
                                      /*Index:  0             1             2             3             4*/
                  
 #define backwardTravelOffset 10  // in inch. 



void avoidObstacles()
{
   //middleDistance = calculateDistance(); 
// serialPrint('M', middleDistance); 

      if(frontDistance() < oaSettingsValue[4]) //oaSettingsValue[4] = safeDistance
      {
                Stop(); 
              
                  if(rightDistance() >= oaSettingsValue[4] && rightDistance >= leftDistance)  //Whether right side has enough safe
                {
                  goRight(oaSettingsValue[2]);  
                  delay(oaSettingsValue[3]); 
                }
                else if(leftDistance() >= oaSettingsValue[4])   //oaSettingsValue[4]  = safe distance. 
                {
                    goLeft(oaSettingsValue[2]); 
                    delay(oaSettingsValue[3]);
                }
                else if(backDistance() >= oaSettingsValue[4] + backwardTravelOffset)
                {
                  goBackward(oaSettingsValue[0]); 
                  delay(oaSettingsValue[1]); 
                }
                else
                {
                  Stop(); 
                }
       } 

        else 
      {
        goForward(oaSettingsValue[0]); 
      }
       
      } 
     



int frontDistance()
{
  digitalWrite(frontSonarTrig, LOW); //Extra pin number 14
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(frontSonarTrig, HIGH); 
  delayMicroseconds(10);
  digitalWrite(frontSonarTrig, LOW);
 long duration = pulseIn(frontSonarEcho, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  
  return duration*0.0068; //returns distance in inch. 
}



int backDistance()
{
  digitalWrite(backSonarTrig, LOW); //Extra pin number 14
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(backSonarTrig, HIGH); 
  delayMicroseconds(10);
  digitalWrite(backSonarTrig, LOW);
 long duration = pulseIn(backSonarEcho, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  
  return duration*0.0068; //returns distance in inch. 
}

int leftDistance()
{
  digitalWrite(leftSonarTrig, LOW); //Extra pin number 14
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(leftSonarTrig, HIGH); 
  delayMicroseconds(10);
  digitalWrite(leftSonarTrig, LOW);
 long duration = pulseIn(leftSonarEcho, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  
  return duration*0.0068; //returns distance in inch. 
}


int rightDistance()
{
  digitalWrite(rightSonarTrig, LOW); //Extra pin number 14
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(rightSonarTrig, HIGH); 
  delayMicroseconds(10);
  digitalWrite(rightSonarTrig, LOW);
 long duration = pulseIn(rightSonarEcho, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  
  return duration*0.0068; //returns distance in inch. 
}




