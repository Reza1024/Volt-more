// Written by: Mohamed Soliman
// This code is for controlling servo motor with IR remote control
// When clicking at any of two buttons the motor is toggling between the rotation and stop

#include <IRremote.h>      //must copy IRremote library to arduino libraries
#include <Servo.h>
#define bNN 0x20DF02FD
#define bSS 0x20DF827D
#define bNW 0x20DFC23D
#define bNE 0x20DFA25D
#define bWW 0x20DFE01F
#define bEE 0x20DF609F
#define bSE 0x20DFDA25
#define bSW 0x20DF14EB
#define contd 0xFFFFFFFF
#define stopp 0x20DF22DD // ok key

int RECV_PIN = 2;       //IR receiver pin
Servo servoL, servoR;
int val;                //rotation angle
bool cwRotation, ccwRotation;  //the states of rotation

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  //servoL.attach(9);     //servo pin
  //servoR.attach(10);
}

int left = 90, right = 90;

void loop()
{
  //Serial.println("Loop!");
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value

    switch(results.value)
    {
      case bNN: left = right = 180; break;
      case bSS: left = right = 0; break;
      case bEE: left = 0; right = 180; break;
      case bWW: left = 180; right = 0; break;
      case bNE: left = 100; right = 180; break;
      case bNW: left = 180; right = 100; break;
      case bSE: left = 80; right = 0; break;
      case bSW: left = 0; right = 80; break;
      case stopp: left = right = 90;
      default: break; 
    }
    if (left == 90 && right == 90)
    {
      servoL.detach();
      servoR.detach();
    }
    else
    {
      if (!servoL.attached())
        servoL.attach(9);
      if (!servoR.attached())
        servoR.attach(10);
      servoL.write(180 - left);
      servoR.write(right);
    }
  }
  delay(50);          //General speed
}
