#define pumpIn1        30
#define pumpIn2        31
#define laserSignalPin 34




void turnOffPump()
{
    digitalWrite(pumpIn1, LOW); 
    digitalWrite(pumpIn2, LOW); 
}

void turnOnPump()
{
    digitalWrite(pumpIn1, HIGH); 
    digitalWrite(pumpIn2, LOW); 
}

void turnOnPumpLaser()
{
    

    digitalWrite(laserSignalPin, HIGH); 
}

void turnOffPumpLaser()
{
    digitalWrite(laserSignalPin,  LOW); 
}



void setupPumpPins()
{
  pinMode(pumpIn1, OUTPUT); 
  pinMode(pumpIn2, OUTPUT); 
  pinMode(laserSignalPin, OUTPUT); 

  turnOffPump(); 
  turnOffPumpLaser(); 

}