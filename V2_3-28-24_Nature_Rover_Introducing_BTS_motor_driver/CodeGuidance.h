/*Written by: Nayeem Islam Shanto (islamshafiul283@gmail.com)
 *Intended board: Arduino Mega
 *Controller: MI2 AI2 built custom Mobile App. 
 * 
 *Modification start:  3-21-2024
 *Modification end:  . 
 *
 * What's new in this version? 
 * 1.Arduino Uno is replaced with arduino Mega. 
    and the structure of the vehicle is radically changed. 
 */



 /*
Hardware connections. Board; Arduino Mega. 

D0: TX0

D1: RX0

~D2:         Right wheels enable pin

~D3:         Left wheels enable pin

~D4:

~D5:

~D6:

~D7:

~D8:

~D9:

~D10:

~D11:

~D12:

~D13:


D14: TX3

D15: RX3

D16: TX2

D17: RX2

D18: TX1

D19: RX1

D20: SDA

D21: SCL

D22:       Right Wheel signal 1. (in1)

D23:       Right Wheel signal 2. (in2)

D24:       Left Wheel signal 1.  (in3)

D25:       Left Wheel signal 2.  (in4)

D26:       Sensor shield enable pin. 

D27:

D28:

D29:

D30:

D31:

D32:

D33:

D34:

D35:

D36:

D37:

D38:

D39:

D40:

D41:

D42:

D43:

~D44:

~D45:

~D46:

D47:
D48:
D49:
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

A6:

A7:

A8:

A9:

A10:

A11:

A12:

A13:

A14:

A15:

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



////////////////////////////////////////////////////Deprecated region starts-kept for copy pasting./////////////////////

Analog Pins. 
-------------------------------------
A0   echoPin of sonar sensor. 
A1   
A2   txPin of softwareSerial.
A3   rxPin of softwareSerial.  
A4   
A5   
A6
A7
A8
A9
A10
A11
A12
A13
A14
A15




Digital Pins (PWM 3, 5, 6, 9, 10, 11)
-------------------------------------
D0        TX of the Bluetooth module. 
D1        RX of the Bluetooth module. 
D2        dataPin of shift register. 
~D3       common enable pins of the wheel motors. 
D4        clockPin of shift register. 
~D5        Sensor shield power Transistor switching pin.
~D6       armServo4
D7        
D8        latchPin of shift register. 
~D9       armServo1. 
~D10      armServo2Left. 
~D11      armServo2Right. 
D12       Sonar sensor carrying servo. 
D13       trigPin of sonar sensor. 


New Digital Pins from shift register. 
14        GripperIN1
15        WristMotor(in3)
16        in1 of wheel motor. 
17        in3 of wheel motor. 
18        GripperIN2
19        in2 of wheel motor. 
20        in4 of wheel motor. 
21        WristMotor(in4)


*//////////////////////////////////////////////////////////Deprecated region ends. //////////////////////////////////////////




/*
 * Control Characters
 "f:x." Move forward with pwm x (0<=x<=255)
 "b:x." Move backward with pwm x (0<=x<=255)
 "l:x." Move left with pwm x (0<=x<=255)
 "r:x." Move right with pwm x (0<=x<=255)
 "u:1." Move the base continuous rotation servo in forward direction
 "u:-1." Move the base continous rotation servo in backward direction
 "v:1."  Move the shoulder joint complementary servo pair in forward direction 
 "v:-1." Move the shoulder joint complementary servo pair in backward direction 
 "w:1."  Move the elbow joint CRS motor in forward direction 
 "w:-1." Move the elbow joint CRS motor in backward direction 
 "y:1." Rotate the wrist clockwise. 
 "y:-1." Rotate the wrist anticlockwise. 
 "z:1." Open up the gripper. 
 "z:-1." Close the gripper. 
 "m:1." Set car to Driving mode. 
 "m:2." Set car to Obstacle avoidance mode. 
 "m:3." Set car to Sensor reading mode and keep sending 
        sensor readings to controller app. 
 "m:4." Set the car to Line follower mode. 
 
 "index:value." Change the Obstacle avoidance settings value at 
                the mentioned index with the given value. This was
                introduced to calibrate obstacle avoidance performa
                nce realtime by adjusting variables like safe distance, 
                forward velocity, right-left velocity etc. 

 */
 