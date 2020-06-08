/*
RC Arduino Robot FR Sky interface

--------------
|Description:|
--------------
This code connects an FRSKY Reciever to 2 DC Motors for controlling a robot.


--------------
|CONNECTIONS:|
--------------

Motor Shield: Cytron SHIELD-MDD10
---------------------------------------
Arduino D3  - Motor Driver PWM 1 Input
Arduino D4  - Motor Driver DIR 1 Input
Arduino D9 - Motor Driver PWM 2 Input
Arduino D10 - Motor Driver DIR 2 Input

RC Interface: FR Sky FS-iA6B
---------------------------------------
Arduino D5  - Steering
Arduino D6  - Throttle
Arduino D7  - Elevator (Unused)


AUTHOR: Ryan McGuire
DATE: 6/4/2020

 */

 #include <Servo.h>     //Servo library
 #include "CytronMotorDriver.h" //Motor Shield Library


//Input Variables
//---------------
int ch1; // Steering
int steer;

int ch2; // Throttle
int throt;

int ch3; // Throttle
int elev;

//Output Variables
//----------------
CytronMD motor1(PWM_DIR, 3, 4);   // PWM 1A = Pin 3, PWM 1B = Pin 9.
CytronMD motor2(PWM_DIR, 9, 10); // PWM 2A = Pin 10, PWM 2B = Pin 11.






//Servp Variables TEMPORARY
Servo servo_test;      //initialize a servo object for the connected servo            
int angle = 0;    

void setup() {

  
  pinMode(5, INPUT); // Set our input pins as such
  pinMode(6, INPUT);
  pinMode(7, INPUT);

  servo_test.attach(9); 
  
  Serial.begin(9600); // Pour a bowl of Serial

}

void loop() {

  ch1 = pulseIn(5, HIGH, 25000); // Read the pulse width of 
  Serial.print("Channel 1: ");
  Serial.println(ch1);
  if (ch1<100 || ch1>5000) // no signal or weird signal!
    { failsafe();}
  ch2 = pulseIn(6, HIGH, 25000); // each channel
  Serial.print("Channel 2: ");
  Serial.println(ch2);
  if (ch2<100 || ch1>5000) // no signal or weird signal!
    { failsafe();}
  ch3 = pulseIn(7, HIGH, 25000);
  Serial.print("Channel 3: ");
  Serial.println(ch3);
  if (ch3<100 || ch1>5000) // no signal or weird signal!
    { failsafe();}

  //Throttle
  Serial.print("Throttle:"); // Ch2 is Throttle
  throt=map(ch2, 1000,2000,0,100);
  Serial.println(throt); // 0 to 100

  Serial.print("Steering:"); // Ch1 is Steering
  steer=map(ch1, 1000,2000,-500,500);
  
  Serial.println(steer); // 0 to 100

  //Throttle Control
  motor1.setSpeed(map(throt,0,100,0,128));
  motor2.setSpeed(map(throt,0,100,0,128));

  angle = map(steer, -500, 500, 0, 179);     // scaling the potentiometer value to angle value for servo between 0 and 180) 
  servo_test.write(angle);                   //command to rotate the servo to the specified angle 
 

  delay(5); // I put this here just to make the terminal 
              // window happier
}

void mixing() {
  
}
void failsafe(){
  Serial.println("Failsafe");
}
