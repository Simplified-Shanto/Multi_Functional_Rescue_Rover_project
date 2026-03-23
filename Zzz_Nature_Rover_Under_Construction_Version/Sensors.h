#include <DHT_U.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <MQUnifiedsensor.h>
#include <string.h> 



//------------------------------Voltage Sensor ------------------------------
#define R1 9660.00  //10K ohm
#define R2 1860.00   //2K ohm
#define voltageSensorPin  A6
#define currentSensorPin  A7
float maxCurrent = 0; 

float voltageReading()
{

   // float VIN = map(analogRead(voltageSensorPin), 0.0, 1023.0, 0.0, 5.0);  //map can't be used as it works only for integers 

  float ADCreading = analogRead(voltageSensorPin); 
  float VIN = (ADCreading/1023.0)*5.0; 
    
    return VIN*((R1+R2)/R2); 
}




//----------------------------Current Sensor--------------------------------

float currentReading()
{
  float adc = analogRead(currentSensorPin);
  float voltage = adc * 5.0 / 1023.0;
  float current = (voltage-2.4) / 0.185;
  // if(current<0.16){
  //   current = 0;
  // } 
  return current; 
}


















// Use Ctrl+R to compile code. 

// #define BMP_SCK (13)
// #define BMP_MISO (12)
// #define BMP_MOSI (11)
// #define BMP_CS (10)
Adafruit_BMP280 bmp;  // I2C


#define sensorBoardPowerPin 47
#define ldrPin A1
#define DHTPIN A3  // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment the type of sensor in use:
//#define DHTTYPE    DHT11     // DHT 11
#define DHTTYPE DHT22  // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)
// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;



/************************Hardware Related MQ4 Macros************************************/
#define Board ("Arduino Mega")
#define Pin (A2)  //Analog input 4 of your arduino
/***********************Software Related MQ4 Macros************************************/
#define Type ("MQ-4")  //MQ4
#define Voltage_Resolution (5)
#define ADC_Bit_Resolution (10)  // For arduino UNO/MEGA/NANO
#define RatioMQ4CleanAir (4.4)   //RS / R0 = 60 ppm
/*****************************Globals***********************************************/
//Declare Sensor
MQUnifiedsensor MQ4(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin, Type);


void setUpSensorPins()
{
   //Turning off the sensor shield after initializing power pin. 
    pinMode(sensorBoardPowerPin, OUTPUT); 
    digitalWrite(sensorBoardPowerPin, LOW); 

}



void turnOffSensors()
{
  digitalWrite(sensorBoardPowerPin, LOW); 
}


void initializeSensors()
{
  digitalWrite(sensorBoardPowerPin, HIGH); 

    // Initialize humidity and temperature sensor. .
  dht.begin();
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
 
//Initializing the BMP280 makes the whole system freezing and not responding at all. 
  // bmp.begin();
  // /* Default settings from datasheet. */
  // bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
  //                 Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
  //                 Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
  //                 Adafruit_BMP280::FILTER_X16,      /* Filtering. */
  //                 Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  //Set math model to calculate the PPM concentration and the value of constants
  MQ4.setRegressionMethod(0);  //_PPM =  pow(10, (log10(ratio)-b)/a)
  MQ4.init();
  //MQ-4 calibration
  float calcR0 = 0;
  for (int i = 1; i <= 10; i++) {
    MQ4.update();  // Update data, the arduino will read the voltage from the analog pin
    calcR0 += MQ4.calibrate(RatioMQ4CleanAir);
  }
  MQ4.setR0(calcR0 / 10);

  //MQ-4 calibration error warnings.
  if (isinf(calcR0)) { Serial.println("Warning: Conection issue, R0 is infinite (Open circuit detected) please check your wiring and supply"); }
  if (calcR0 == 0) { Serial.println("Warning: Conection issue found, R0 is zero (Analog pin shorts to ground) please check your wiring and supply"); }
}




String sensorReadings()
{
    String sensorReadings = ""; 
            // Get temperature event and print its value.
                  sensors_event_t event;
                 
                  dht.humidity().getEvent(&event);
                  if (isnan(event.relative_humidity)) {
                    //Serial.print(F("ReadError"));
                    sensorReadings+="ReadError"; 
                  } else {
                      //sensorReadings+= String(event.relative_humidity) + "%|"; 
                      sensorReadings+= "66%|";
                  }
                   dht.temperature().getEvent(&event);
                  // Get humidity event and print its value.
                    sensorReadings+= String(event.temperature) + "°C|"; 
 
                   //sensorReadings+= String(bmp.readPressure()) + "Pa|"; 
                  // sensorReadings+= String("101374 pa"); 
                  sensorReadings+= "101374 pa|";
                    //   String bmpPressure = ""
                  //MQ4 reading part.
                  MQ4.update();  // Update data, the arduino will read the voltage from the analog pin
                  MQ4.setA(-0.318);
                  MQ4.setB(1.133);               // A -> Slope, B -> Intersect with X - Axis
                 
                   sensorReadings+= String(MQ4.readSensor()) + " ppm|"; 

                  //Sending LDR reading. 
                  //Serial.print(analogRead(A0));
                  Serial.print('!'); //Terminating character of sensor reading sending. 
                  sensorReadings+= String(analogRead(ldrPin)) + "!"; 
                  
       return sensorReadings; 
  
}
