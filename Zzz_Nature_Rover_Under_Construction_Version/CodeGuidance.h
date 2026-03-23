/* Introduction to the commands. 

1. "f:x." Move forward with pwm x (0<=x<=255)
2. "b:x." Move backward with pwm x (0<=x<=255)
3. "l:x." Move left with pwm x (0<=x<=255)
4. "r:x." Move right with pwm x (0<=x<=255)
5. "u:1." Move the base continuous rotation servo in forward direction
6. "u:-1." Move the base continuous rotation servo in backward direction
7. "v:1." Move the shoulder joint complementary servo pair in forward direction
8. "v:-1." Move the shoulder joint complementary servo pair in backward direction
9. "w:1." Move the elbow joint CRS motor in forward direction
10. "w:-1." Move the elbow joint CRS motor in backward direction
11. "y:1." Rotate the wrist clockwise.
12. "y:-1." Rotate the wrist anticlockwise.
13. "z:1." Open up the gripper.4
14. "z:-1." Close the gripper.

15. "m:1." Set car to Driving mode.
16. "m:2." Set car to Obstacle avoidance mode.
17. "m:3." Set car to Sensor reading mode and keep sending sensor readings to controller app.
18. "m:4." Set the car to Line follower mode.
    "M:string."  Print the message recieved from app to OLED display. 


    "P:2." Turn ON Pump
19. "p:1." Turn ON only laser
20. "p:0." Turn Off both pump and laser. 
21. "a:1." Set robotic arm positions to initial rest values. 
22. "a:2." Turn on hit protection
23. "a:3." Turn off hit protection
24. "a:4." Take arm to to object dropping position. setArmToDropObject(); 
25. "a:5." Change OLED display content. 
26. "L:x---." This command is for controlling the brightness of the lights. This will be at least a 
              a four digit number where the number formed with the first 3 digits indicates the brightness value
              and number/1000= give the index of the light. 
              L:0255 - set led 1 to pwm value 255
              L:1025 - set led 2 to pwm value 25
              L:2100
              L:3200
              L:4200 - set 5th led or the arm led to high
              L:5000 - set 6th led or the tank led to low
              Q:1.  - set LED to autobrightness mode. 
              Q:2.  glow lights in pattern 1. 
              Q:3.  glow lights in pattern 2. 
 
 "index:value." Change the Obstacle avoidance settings value at 
                the mentioned index with the given value. This was
                introduced to calibrate obstacle avoidance performa
                nce realtime by adjusting variables like safe distance, 
                forward velocity, right-left velocity etc. 

 */
 


/*Written by: Nayeem Islam Shanto (islamshafiul283@gmail.com)
 *Intended board: Arduino Mega
 *Controller: MI2 AI2 built custom Mobile App. 
 * 
 *Modification start:  4-21-2024
 *Modification end:  . 
 *
 * What's new in this version? 
 * 1. The CSR base servo motor has been modified to 180 degree rotation servo. 
   2. Servo array has been created instead of declaring each servo individually. 
   3. Unlike before, the gripper will completely open with one tap from the app. 
 


Changes to the mobile app: 
1. Introduction of reverse gear. 
2. Adding arm commands and other commands in the mode selection list picker. 
3. Rearranging the whole setup with diagrams. 
4. Addtion of another speed slider for left right speed controlling. 

*/


 /*
Hardware connections. Board; Arduino Mega. 

D0: TX0

D1: RX0

~D2:          Left wheel forward pwm

~D3:          Left wheel backward pwm

~D4:         Right wheels forward pwm 

~D5:         Right wheel backward pwm

~D6:         Base Servo motor pwm signal

~D7:            IR array servo pwm signal

~D8:         Shoulder Servo motor pwm signal

~D9:         Elbow Joint Right Servo motor. 

~D10:        Elbow Joint Left Servo motor. 

~D11:        LED1 - Back

~D12:        Gripper Servo PWM signal. 

~D13:        Robotic arm wrist servo signal


D14: TX3

D15: RX3

D16: TX2

D17: RX2

D18: TX1

D19: RX1

D20: SDA

D21: SCL

D22:       

D23:      

D24:      

D25:      

D26:       Sensor shield enable pin. 

D27:       OUTPUT - PUMPLASER

D28:       INPUT  - gripSenseButtonLeft

D29:       INPUT  - gripSenseButtonRight

D30:       Pump In1

D31:       Pump In2

D32:       Sensor power pin. 

D33:       

D34:         On arm LED

D35:         Arm Laser

D36:       Gripper press buttons left

D37:       Gripper press buttons right

D38:      

D39:       

D40:       

D41:

D42:

D43:

~D44:  LED2 - Back 

~D45:  LED3  - Front

~D46:  LED4 - Front

D47:    "Combined Sensor board 
         power transistor signal"


D48:   LED6 - Tank led. 

D49:   IR array led ON

D50:
D51:
D52:
D53:




Analog Pins: 
-----------------------------------------------

A0:

A1:

A2:

A3:

A4:

A5:

A6:  Voltage Sensor analog input

A7:  Current Sensor analog input

A8:  IR1

A9:  IR3

A10: IR4

A11: IR5

A12: IR6

A13: IR7

A14: IR8

A15: IR10

RX0:

TX0:

RX1:

TX1:

RX2:

TX2:

RX3:

TX3:

SDA:

SCL:

MOSI:

MISO:

SCK:

SS:

5V:

3.3V:

GND:

RESET:







