#define ESPIO0     33
#define ESPIO2     34
#define ESPIO4     35
#define ESPIO17    36
#define ESPIO16    37
#define ESPIO15    38
#define ESPIO14    39
#define ESPIO13    40


initializePictobloxControlPins()
{
pinMode(ESPIO0, INPUT_PULLUP);
pinMode(ESPIO2, INPUT_PULLUP);
pinMode(ESPIO4, INPUT_PULLUP);
pinMode(ESPIO17, INPUT_PULLUP);
pinMode(ESPIO16, INPUT_PULLUP);
pinMode(ESPIO15, INPUT_PULLUP);
pinMode(ESPIO14, INPUT_PULLUP);
pinMode(ESPIO13, INPUT_PULLUP);

}

#define forwardCombination  (digitalRead(ESPIO0)==0 && digitalRead(ESPIO2) ==0)
#define backwardCombination  (digitalRead(ESPIO0)==0 && digitalRead(ESPIO4) ==0)
#define leftCombination  (digitalRead(ESPIO0)==0 && digitalRead(ESPIO17) ==0) 
#define rightCombination  (digitalRead(ESPIO0)==0 && digitalRead(ESPIO16) ==0) 


void obeyPictoblox()
{
  if(forwardCombination==1)
  {
    goForward(100); 
  }
  if(backwardCombination==1)
  {
    goBackward(100);
  }
  if(rightCombination==1)
  {
    goRight(220); 
  }
  if(leftCombination==1)
  {
    goLeft(220); 
  }
}
