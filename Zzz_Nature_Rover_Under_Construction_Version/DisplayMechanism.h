#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>




String appMessage = "No Message";  //Message sent from the mobile App.
byte displayContentIndex = 0;
#define displayContentNumber 6
byte appMessagePrinted = 0;  //Whether the title has been printed on the OLED display; if yes then we'll not update the display in this index.

/*
0 -> Project title. 
1 -> LFR data. 
2 -> Sonar Sensor. 
3 -> Voltage-Current + sensor shield reading. 
4 -> Robotic arm Positions. 
5 -> Message from the App. 
*/


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void printTitle() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Multi Functional Rescue Rover");
  display.display();
}

void initializeOLEDDisplay() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    // Serial.println(F("SSD1306 allocation failed"));
    // for(;;);
  }

  printTitle();
}



/////////////Light mechanisms//////////////////////////////////

#define numberOfLED 6
byte ledLightPins[numberOfLED] = { 11, 44, 45, 46, 35, 48 };
//Names                         led1backPin   led2backPin   led3frontPin led4frontPin  onArmLedPin    Tank led



byte patternIndex = 0;

  unsigned long ledTimer = 0;
  byte step = 0;

#define lightsDelay 100
void initializeLights() {
  for (byte i = 0; i < numberOfLED; i++) {
    pinMode(ledLightPins[i], OUTPUT);
  }

  for (byte i = 0; i < numberOfLED; i++) {
    digitalWrite(ledLightPins[i], HIGH);
    delay(lightsDelay);
  }

  for (byte i = 0; i < numberOfLED; i++) {
    digitalWrite(ledLightPins[i], LOW);
    delay(lightsDelay);
  }
}

#define ldrThresholdValue 200
void glowLightsInAutoMode() {
  // byte brightnessValue = map((1023 - analogRead(ldrPin)), 0, 1023, 0, 255);
  // for (byte i = 0; i < 4; i++)  //LED brightness will be based on surrounding light intensities.
  // {
  //   analogWrite(ledLightPins[i], brightnessValue);
  // }
  if (patternIndex == 1 && millis() - ledTimer > 100) {  // Update pattern every 100ms
    ledTimer = millis();
      if (analogRead(ldrPin) < ldrThresholdValue && digitalRead(ledLightPins[0]) == LOW) {
        for (byte i = 0; i < 4; i++)  //LED brightness will be based on surrounding light intensities.
        {
          digitalWrite(ledLightPins[i], HIGH);
        }
      } else if (analogRead(ldrPin) > ldrThresholdValue && digitalRead(ledLightPins[0]) == HIGH) {
        for (byte i = 0; i < 4; i++)  //LED brightness will be based on surrounding light intensities.
        {
          digitalWrite(ledLightPins[i], LOW);
        }
      }
    }
  }


  void glowLightsInPattern1() {

    if (patternIndex == 2 && millis() - ledTimer > 100) {  // Update pattern every 100ms
      ledTimer = millis();

      // Reset all LEDs to LOW (OFF)
      for (int i = 0; i < numberOfLED; i++) {
        digitalWrite(ledLightPins[i], LOW);
      }

      // Define the pattern
      switch (step) {
        case 0:
          for (int i = 0; i < numberOfLED; i++) {
            digitalWrite(ledLightPins[i], HIGH);  // Turn on all LEDs
          }
          break;
        case 1:
          for (int i = 0; i < numberOfLED; i += 2) {
            digitalWrite(ledLightPins[i], HIGH);  // Turn on even-index LEDs
          }
          break;
        case 2:
          for (int i = 1; i < numberOfLED; i += 2) {
            digitalWrite(ledLightPins[i], HIGH);  // Turn on odd-index LEDs
          }
          break;
        case 3:
          digitalWrite(ledLightPins[0], HIGH);
          digitalWrite(ledLightPins[5], HIGH);  // Turn on first and last LEDs
          break;
        case 4:
          for (int i = 0; i < numberOfLED; i++) {
            if (i % 3 == 0) {
              digitalWrite(ledLightPins[i], HIGH);  // Turn on every third LED
            }
          }
          break;
        case 5:
          for (int i = 0; i < numberOfLED; i++) {
            digitalWrite(ledLightPins[i], HIGH);  // Flash all LEDs quickly
            delay(50);
            digitalWrite(ledLightPins[i], LOW);
          }
          delay(50);
          break;
        default:
          step = 0;  // Reset step if it exceeds the number of patterns
          break;
      }

      // Move to the next step in the pattern
      step++;
      if (step > 5) {
        step = 0;  // Reset step to 0 if it exceeds the number of steps
      }
    }
  }


  void glowLightsInPattern2() {
    // Reset all LEDs to off
    if (patternIndex == 3 && millis() - ledTimer > 100) {
      ledTimer = millis();
      step = (++step) % 6;

      for (int i = 0; i < 6; i++) {
        digitalWrite(ledLightPins[i], LOW);
      }

      switch (step) {
        case 0:
          digitalWrite(ledLightPins[0], HIGH);  // Front left LED on
          digitalWrite(ledLightPins[5], HIGH);  // Arm LED on
          break;
        case 1:
          digitalWrite(ledLightPins[1], HIGH);  // Front right LED on
          digitalWrite(ledLightPins[4], HIGH);  // Water tank LED on
          break;
        case 2:
          digitalWrite(ledLightPins[2], HIGH);  // Back left LED on
          break;
        case 3:
          digitalWrite(ledLightPins[3], HIGH);  // Back right LED on
          break;
        case 4:
          digitalWrite(ledLightPins[0], HIGH);  // Front left LED on
          digitalWrite(ledLightPins[3], HIGH);  // Back right LED on
          break;
        case 5:
          digitalWrite(ledLightPins[1], HIGH);  // Front right LED on
          digitalWrite(ledLightPins[2], HIGH);  // Back left LED on
          break;
      }
    }
  }



  // const int PATTERN_LENGTH = 100;
  // //const float PI = 3.14159265;

  // // Function to generate PWM value based on sine wave
  // byte getSineWaveValue(int step, float frequency, float phaseShift) {
  //   return (byte)((sin(2 * PI * frequency * step / PATTERN_LENGTH + phaseShift) + 1) * 127.5);
  // }

  // // Function to generate ON/OFF value for non-PWM LEDs
  // bool getBlinkValue(int step, int onTime, int offTime) {
  //   return (step % (onTime + offTime)) < onTime;
  // }

  // unsigned long ledTimer;

  // void glowLightsInPattern1()
  // {
  //   static int index = 0;
  //   if(millis() - ledTimer > 50)
  //   {
  //     ledTimer = millis();
  //       // Update LED brightness with the pattern values
  //   analogWrite(ledLightPins[0], getSineWaveValue(index, 1, 0));            // Front LED 1
  //   analogWrite(ledLightPins[1], getSineWaveValue(index, 1, 0));            // Front LED 2
  //   analogWrite(ledLightPins[2], getSineWaveValue(index, 1, PI));            // Back LED 1
  //   analogWrite(ledLightPins[3], getSineWaveValue(index, 1, PI));            // Back LED 2
  //   digitalWrite(ledLightPins[4], getBlinkValue(index, 50, 50) ? HIGH : LOW);  // Water Tank LED
  //   digitalWrite(ledLightPins[5], getBlinkValue(index, 25, 75) ? HIGH : LOW); // Robotic Arm LED

  //   // Update index for the next cycle
  //   index = (index + 1) % PATTERN_LENGTH;
  //   }
  // }
