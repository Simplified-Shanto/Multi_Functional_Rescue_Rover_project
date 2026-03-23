#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>





byte displayContentIndex = 0; 
#define displayContentNumber 5
byte titlePrinted = 0; //Whether the title has been printed on the OLED display; if yes then we'll not update the display in this index. 

/*
0 -> Project title. 
1 -> LFR data. 
2 -> Sonar Sensor. 
3 -> Voltage-Current + sensor shield reading. 
4 -> Robotic arm Positions. 
*/

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void printTitle()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Multi Functional Rescue Rover");
  display.display();
}

void initializeOLEDDisplay()
{
   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
   // Serial.println(F("SSD1306 allocation failed"));
   // for(;;);
  }

  printTitle(); 

}



/////////////Light mechanisms//////////////////////////////////

#define numberOfLED   6
byte ledLightPins[numberOfLED] = {  11,           44,             45,       46,               35   ,    48 }; 
//Names               led1backPin   led2backPin   led3frontPin led4frontPin  onArmLedPin    Tank led



#define lightsDelay  150
void initializeLights()
{
  for(byte i = 0; i<numberOfLED; i++)
  {
    pinMode(ledLightPins[i], OUTPUT); 
  }

      for(byte i = 0; i<numberOfLED; i++)
  {
    digitalWrite(ledLightPins[i], HIGH); 
    delay(lightsDelay); 
  }

      for(byte i = 0; i<numberOfLED; i++)
  {
    digitalWrite(ledLightPins[i], LOW); 
    delay(lightsDelay); 
  }


  
  
}



