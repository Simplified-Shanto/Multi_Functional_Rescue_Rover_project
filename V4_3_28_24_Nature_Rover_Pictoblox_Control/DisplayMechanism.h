#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void initializeOLEDDisplay()
{
   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
   // Serial.println(F("SSD1306 allocation failed"));
   // for(;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Multi Functional Rescue Rover");
  display.display();

}



// void setup() {
//   // Initialize serial communication
//   Serial.begin(9600);

//   // Initialize OLED display
//   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
//    // Serial.println(F("SSD1306 allocation failed"));
//    // for(;;);
//   }
  
//   // // Initialize servos
//   // servo1.attach(pwmPins[0]);
//   // servo2.attach(pwmPins[1]);
//   // servo3.attach(pwmPins[2]);
//   // servo4.attach(pwmPins[3]);
// }

// void loop() {
//   // Read analog inputs and map to servo angles
//   int angles[4];
//   for (int i = 0; i < 4; i++) {
//     int analogValue = analogRead(analogPins[i]);
//     angles[i] = map(analogValue, 0, 1023, 0, 180);
//   }

//   // Set servo positions
//   servo1.write(angles[0]);
//   servo2.write(angles[1]);
//   servo3.write(angles[2]);
//   servo4.write(angles[3]);

//   // Update OLED display with servo angles
//   display.clearDisplay();
//   display.setTextSize(1);
//  // display.setTextColor(SSD1306_WHITE);
//   display.setCursor(0, 0);
//   display.print("Servo 1: ");
//   display.println(angles[0]);
//   display.print("Servo 2: ");
//   display.println(angles[1]);
//   display.print("Servo 3: ");
//   display.println(angles[2]);
//   display.print("Servo 4: ");
//   display.println(angles[3]);
//   display.display();

//   delay(0); // Adjust delay as needed for smoother display updating
// }
