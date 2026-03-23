#define pumpIn1   30
#define pumpIn2   31



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




void setupPumpPins()
{
  pinMode(pumpIn1, OUTPUT); 
  pinMode(pumpIn2, OUTPUT); 

  turnOffPump(); 

}