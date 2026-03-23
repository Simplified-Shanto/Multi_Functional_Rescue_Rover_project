#include "Arduino.h"
  
/*The two servo motors used for the first joint 
 * doesn't align for some pair of angles. 
 * So we have modified the angle values to 
 * achieve the goal. 
*/
const byte leftAngles[177] = {2 ,    3 ,   4 ,   5 ,   6 ,   7 ,   8 ,   9 ,   10 , 11 ,   12 ,  13 ,  14 , 15 ,  16 ,  17 ,  18 ,  19 ,  20 ,  21 ,   22 , 23 ,   24 , 25 ,   26 ,  27 , 28 ,   29 ,  30 ,  31 ,  32 ,  33 ,  34 ,  35 ,  36 ,  37 , 38 ,  39 ,  40 ,  41 ,  42 ,  43 ,  44 ,  45 ,  46 ,  47 ,  48 ,   49 ,  50 ,  51 ,  52 ,  53 ,  54 , 55 ,  56 ,  57 ,  58 ,  59 ,  60 ,  61 ,  62 ,  63 ,   64 ,  65 , 66 ,  67 ,  68 ,  69 ,  70 ,  71 ,  72 ,  73 ,  74 ,  75 ,  76 ,  77 ,  78 ,  79 ,  80 ,  81 , 82 , 83 , 84 , 85 , 86 , 87 , 88 , 89 , 90 , 90 , 91 , 92 , 93 , 94 , 95 , 96 , 97 , 98 , 99 , 100 , 101 , 102 , 103 , 104 , 105 ,  106 , 107 ,  107, 108 , 109 , 110 , 111 , 112 , 113 , 114 , 115 , 116 , 117 , 118 , 119 , 120 , 121 , 122 , 123 , 124 , 125 , 125 , 126 , 127 , 128 , 129 , 130 , 131 , 132 , 133 ,133  , 134,  134 , 135 , 136 , 137 , 138 , 139 , 140 , 141 , 142 , 143 , 144 , 145 , 146 , 147 , 148 , 149 , 150 , 151 , 152 , 153 , 154 , 155 , 156 , 157 , 158 , 159 , 160 , 161 , 162 , 163 , 164 , 165 , 166 , 167, 168 , 169  , 170 , 171 , 172 , 173  };
const byte rightAngles[177] ={178 , 177 , 176 , 175 , 174 , 173 , 172 , 171 , 170 , 169 , 168 , 167 , 166 , 165 , 164 , 163 , 162 , 161 , 160 , 159 , 158 , 157 , 156 , 155 , 154 , 153 , 152 , 151 , 150 , 149 , 148 , 147 , 146 , 145 , 144 , 143 , 142 , 141 , 140 , 139 , 138 , 137 , 136 , 135 , 134 , 133 , 132 , 131 , 130 , 129 , 128 , 127 , 126 , 125 , 124 , 123 , 122 , 121 , 120 , 119 , 118 , 117 , 116 , 115 , 114 , 113 , 112 , 111 , 110 , 109 , 108 , 107 , 106 , 105 , 104 , 103 , 102 , 101 , 100 , 99 , 98 , 97 , 96 , 95 , 94 , 93 , 92 , 91 , 90 , 89 , 88 , 87 , 86 , 85 , 84 , 83 , 82 , 81 , 80 ,  79 ,  78 ,   77 , 76 ,  75 ,  74 ,   73 ,  72 ,  71 ,  70 ,  69 ,  68 ,  67 , 66  , 65  , 64  , 63  , 62  , 61  , 60  , 59  , 58  , 57  , 56  , 55  , 54  , 53  , 52  , 51  , 50  , 49  , 48  , 47  , 46  , 45  , 44  , 43  , 42  , 41  , 40  , 39  , 38  , 37  , 36  , 35  , 34  , 33  , 32  , 31  , 30  , 29  , 28  , 27  , 26 ,  25 ,  24  , 23  , 22  , 21  , 20 ,  19 ,  18  , 17 ,  16   , 15 , 14 ,   13 , 12  , 11 ,   10 ,   9 ,  8 ,  7 ,   6  ,   5 ,   4 ,   3 ,   2  };
byte anglePairIndex = 176; //Index of which angle is being written in the motor according 
                         //the above two lists. 

                    


#define pump


Servo elbowServoLeft; 
Servo elbowServoRight; 



//Constraints for angles of different servos. The parallal servo arrangement of the elbow is considered to be one servo, 
//which is in the fifth position of the array. That means the 5 the element of the following array doesn't indicate to 
// a angle in degrees instead it indicates the anglePairIndex

 #define gripperPressButtonLeftPin  36
 #define gripperPressButtonRightPin 37
 #define servoNumber  5
 Servo armServos[servoNumber];          /*elbowRight-9,elbowLeft-10,*/

                               //Servo index   0               1                      2                                  3               4     
 const byte servoPins[servoNumber] =         { 8,              9,                     6,                                 13,             12    }; // elbowright - 9, elbowleft - 10
 byte dropObjectPositions[servoNumber] =     { 82,             152,                    90,                                90,             60    }; //Arm gets to object dropping position for this set of angles. 
 byte restPositions[servoNumber] =           { 169,            175,                   90,                                 90,             60    }; //Initial rest positions of the servo motors used in the arm
 byte servoPositions[servoNumber] =          { 169,           175,                   90,                                  90,             60    }; //Current positions of the servo motors used in the arm
                              //    Custom 100 rpm gear     anglePairIndex of       Custom CSR to 180   ,             MG90 servo      MG90 servo  
                            //      motor for shoulder     the parallel servo elbow. servo for base ,                 for wrist       for gripper 
 byte maxServoPositions[servoNumber] =       {  170,           176,                   178,                                178,           172 /*Close*/     };
 byte minServoPositions[servoNumber] =       {  10,            0,                     2,                                2,             60  /*Open*/   };
 

#define angleChangeDelay  20

void initializeRoboticArm()
    {
        
          // elbowServoRight.attach(9); 
          // elbowServoLeft.attach(10); 
          // elbowServoRight.write(rightAngles[anglePairIndex]); 
          // elbowServoLeft.write(leftAngles[anglePairIndex]); 

          for(int i = 0; i<servoNumber; i++)
          {
            if(i==1)
            {
              elbowServoRight.attach(9); 
              elbowServoLeft.attach(10); 
              elbowServoRight.write(rightAngles[restPositions[i]]); 
              elbowServoLeft.write(leftAngles[restPositions[i]]); 
            }
            else 
            {
            armServos[i].attach(servoPins[i]); 
            armServos[i].write(restPositions[i]); 
            }
          }

          //Setting up gripper press buttons. 
          pinMode(gripperPressButtonLeftPin, INPUT_PULLUP); 
          pinMode(gripperPressButtonRightPin, INPUT_PULLUP); 


    }


/*
The idea is to take the arm to a vertical position, starting from the elbow -> shoulder -> base and then 
The base, shoulder, wrist and gripper servo motors will be in an array, and the elbow parallel servo pairs will have separate declaration.
*/

//New arm resting algorithm which takes resets in the order 1, 0, 2, 3, 4, 5, 6
void takeArmToRestPosition()
{
    for(int i = 0; i<servoNumber-1; i++)
    {
      // byte angleChange = (restPositions[i] - servoPositions[i])/abs(restPositions[i] - servoPositions[i]); 

        if(servoPositions[i] < restPositions[i])
        {
            for(int j = servoPositions[i]+1; j<= restPositions[i]; j++)
            {
                if(i==1)
                {
                  
                elbowServoLeft.write(leftAngles[j]); 
                elbowServoRight.write(rightAngles[j]); 
                }
                else 
                {
                  armServos[i].write(j); 
                }
                delay(angleChangeDelay); 
            }
            servoPositions[i] = restPositions[i]; 
        }
        else
        {
          for(int j = servoPositions[i]-1; j>= restPositions[i]; j--)
          {
                if(i==1)
                {
                  elbowServoLeft.write(leftAngles[j]); 
                elbowServoRight.write(rightAngles[j]); 
                }
                else 
                {
                  armServos[i].write(j); 
                }
                delay(angleChangeDelay); 
          }
          servoPositions[i] = restPositions[i]; 
        }

        
    }
}



void setArmToDropObject()
{
    for(int i = 0; i<servoNumber-1; i++)
    {
        if(servoPositions[i] < dropObjectPositions[i])
        {
            for(int j = servoPositions[i]+1; j<= dropObjectPositions[i]; j++)
            {
                if(i==1)
                {
                    elbowServoLeft.write(leftAngles[j]); 
                    elbowServoRight.write(rightAngles[j]); 
                }
                else 
                {
                    armServos[i].write(j); 
                }
                delay(angleChangeDelay); 
            }
            servoPositions[i] = dropObjectPositions[i]; 
        }
        else
        {
            for(int j = servoPositions[i]-1; j>= dropObjectPositions[i]; j--)
            {
                if(i==1)
                {
                    elbowServoLeft.write(leftAngles[j]); 
                    elbowServoRight.write(rightAngles[j]); 
                }
                else 
                {
                    armServos[i].write(j); 
                }
                delay(angleChangeDelay); 
            }
            servoPositions[i] = dropObjectPositions[i]; 
        }
    }
}


  


